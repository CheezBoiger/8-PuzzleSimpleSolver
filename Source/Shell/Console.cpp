// 8 Puzzle Solver Algorithm Assignment
// Assignment #1
// Author : Mario Garcia
// Class : CS 420
// Instructor : Dr. Daisy Tang
//
// Copyright (c) 2017 Mario Garcia, MIT License.
// Built with my cat Tom. mew...
#include "Console.hpp"

// 8 puzzle solver Engine Defines.
#include "Engine/PuzzleSolver.hpp"
#include "Engine/Heuristic.hpp"
#include "Engine/Puzzle.hpp"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <queue>


namespace cs420 {


// Puzzle solving. Heuristics are defined in global scope.
// This allows for some speed.
pai::ManhattanDistanceHeuristic mdh;
pai::MisplacedTilesHeuristic mth;
pai::PuzzleSolver solver;
bool both_heuristics = true;


std::vector<pai::Puzzle> last_path;


// String display handler. This is a struct that is sent into the 
// standard output.
struct StringDisplay {
  std::string str;
  uint32_t    width;
};


// The standard output handler for dealing with strings to be 
// sent out into the console.
struct {
  std::thread               handle;
  std::mutex                m;
  std::queue<StringDisplay> buffer;
  bool                      running;

  // Submit to the buffer.
  void Submit(StringDisplay &str) {
    std::unique_lock<std::mutex> lock(m, std::defer_lock);
    buffer.push(std::move(str));
  }
} standard_output;


void StandardHandleOutput() 
{
  StringDisplay *str = nullptr;
  while (standard_output.running) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    {
      std::unique_lock<std::mutex> lock(standard_output.m, std::defer_lock);
      if (!standard_output.buffer.empty()) {
        str = &standard_output.buffer.front();
        if (str->width > 0) {
          std::cout << std::setw(str->width) << str->str;
        } else {
          std::cout << str->str;
        }
        standard_output.buffer.pop();
        str = nullptr;
      }
    }
  }
}


// Trim the string.
std::string Trim(std::string &str)
{
  const auto str_begin = str.find_first_not_of(" \t");
  if (str_begin == std::string::npos) {
    return "";
  }
  const auto end = str.find_last_not_of(" \t");
  const auto range = end - str_begin + 1;
  return str.substr(str_begin, range);
}


bool InitOutput()
{
  solver.set_heuristic(mdh);
  standard_output.running = true;
  standard_output.handle = std::thread(StandardHandleOutput);
  return true;
}


bool CleanupOutput()
{
  standard_output.running = false;
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  if (standard_output.handle.joinable()) {
    standard_output.handle.join();
  } else {
    return false;
  }
  return true;
}


void Console::SubmitToOutput(std::string str, uint32_t width)
{
  if (standard_output.running) {
    StringDisplay display;
    if (width > 0) {
      display.width = width;  
    } else {
      display.width = 0;
    }
    display.str = std::move(str);
    standard_output.Submit(display);
  }
}


void Console::Input(std::string cmd)
{
  cmd = Trim(cmd);
  std::vector<std::string> tokens;
  std::istringstream iss(cmd);
  std::copy(std::istream_iterator<std::string>(iss),
    std::istream_iterator<std::string>(),
    std::back_inserter(tokens));

  if (!tokens.empty()) {
    if (tokens[0].compare("exit") == 0) {
      SubmitToOutput("Exiting...\n");
      RequestShutDown();
    }
    else if (tokens[0].compare("help") == 0) {
      SubmitToOutput(R"(
  Commands:
    solve [file] or [custom] := Solves an 8 puzzle, provided with furthur instructions. 

    heuristic [i]            := Allows you to change the heuristic of this puzzle with integer i.
                                By default, set to solve with both heuristics. 
                              ex.   heuristic 1 (use Manhattan Distance Heuristic).
                                    heuristic 2 (use Misplaced Tiles Heuristic).
                                    heuristic both (display both heuristics when solving).

    show              := Shows how the last puzzle was solved.

    dump              := Dump all solved puzzle cases held by this program.

    clear             := Clear puzzle cases from this program. This is done autonomously.

    help *[command]   := Shows commands or (optional) a command in more detail.

    exit              := exit this program. This can be entered at any point in the program.
)");
    } else if(tokens[0].compare("show") == 0) {
      uint32_t i = 0;
      for (pai::int32 j = static_cast<pai::int32>(last_path.size() - 1); j >= 0; --j) {
        pai::Puzzle &p = last_path[j];
        auto &puzzle_board = p.get_puzzle();
        std::cout << "step: " << i << "\n";
        std::cout << "action taken: " << pai::Puzzle::Interpret(p.get_last_action()) << "\n";
        for (pai::uint32 i = 0; i < puzzle_board.size(); ++i) {
          if (i % 3 == 0) {
            std::cout << "\n";
          }
          std::cout << puzzle_board[i] << " ";
        }
        ++i;
        std::cout << "\n\n";
      }
    } else if (tokens[0].compare("solve") == 0) {
      SubmitToOutput("Enter puzzle of format x x x x x x x x\n");
      SubmitToOutput("(you don't need to have spaces between)\n");
      SubmitToOutput("enter> ");
      cmd = GetInput();
      pai::Puzzle puzzle;
      auto &p = puzzle.get_puzzle();
      if (puzzle.Digest(cmd)) {
        std::cout << "Puzzle To Solve: \n";
        for (uint32_t i = 0; i < p.size(); ++i) {
          if (i % 3 == 0) {
            std::cout << "\n";
          }
          std::cout << p[i] << " ";
        }
        std::cout << "\n\n";
        std::cout << "Solving...\n";
        bool success = solver.Solve(puzzle);
        if (success) {
          auto path = solver.GetSolvedPath();
          std::cout << "Solved puzzle: \n\n";
          auto solved = path[0].get_puzzle();
          for (uint32_t i = 0; i < solved.size(); ++i) {
            if (i % 3 == 0) {
              std::cout << "\n";
            }
            std::cout << solved[i] << " ";
          }
          std::cout << "\n\n";
          std::cout << "Time took to solve: " << solver.get_time_solved() << " ms\n";
          std::cout << "Total Solved Depth: " << path.size() - 1 << " nodes\n";
          std::cout << "Search Cost: " << solver.get_search_cost() << "\n\n";
          last_path = path;
        } else {
          std::cout << "Puzzle could not be solved.!\n";
        }
      } else {
        SubmitToOutput("Incorrect Format or size. type in 8 valid numbers.\n");
      }
    }
  }
  SubmitToOutput(cmd);
}


std::string GetInput()
{
  std::string input;
  std::getline(std::cin, input);
  return input;
}
} // cs420