// 8 Puzzle Solver Algorithm Assignment
// Assignment #1
// Author : Mario Garcia
// Class : CS 420
// Instructor : Dr. Fang "Daisy" Tang
//
// Copyright (c) 2017 Mario Garcia, MIT License.
// Built with my cat Tom. mew...
#include "Console.hpp"

// 8 puzzle solver Engine Defines.
#include "Engine/PuzzleSolver.hpp"
#include "Engine/Heuristic.hpp"
#include "Engine/Puzzle.hpp"
#include "Engine/Utils/Log.hpp"
#include "Case/CaseManager.hpp"
#include "Input/FileParser.hpp"

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
#include <unordered_map>
#include <random>

// VT100 aware terminals would get this...
// It's a joke, get it? sigh...
#if !defined(_WIN32)
#define CMD_VT100_CLR "\33[2K\r" 
#else
#define CMD_VT100_CLR "\r"
#endif 

namespace cs420 {


// Puzzle solving. Heuristics are defined in global scope.
// This allows for some speed.
pai::ManhattanDistanceHeuristic mdh;
pai::MisplacedTilesHeuristic mth;
pai::PuzzleSolver solver;

enum HeuristicUse {
  MANHATTAN,
  MISPLACED,
  BOTH,
};

HeuristicUse user_use = BOTH;

// Tracks the last branch.
std::vector<pai::Puzzle> last_path;

std::vector<pai::Puzzle> mth_last_path;
// Manhattan Distance Case Manager.
CaseManager mdh_manager;
// Misplaced Tiles Case Manager.
CaseManager mth_manager;


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


void SwitchHeuristic(HeuristicUse use)
{
  switch (use) {
    case MANHATTAN: solver.set_heuristic(mdh); break;
    case MISPLACED: solver.set_heuristic(mth); break;
    default:        solver.set_heuristic(mdh); break;
  };
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


// Dump cases depending on what the user specified.
void DumpCases(std::vector<std::string> &tokens)
{
  std::cout << "+";
  for (pai::uint32 i = 1; i < 90; ++i) {
    std::cout << "-";
  }
  std::cout << "+\n";
  std::cout << "|" << std::setw(8) << "Depth |";
  std::cout << std::setw(22) << "AVG Search Cost MDH |";
  std::cout << std::setw(22) << "AVG Search Cost MTH |";
  std::cout << std::setw(19) << "AVG tts MDH (ms) |";
  std::cout << std::setw(20) << "AVG tts MTH (ms) |\n";
  std::cout << "+";
  for (pai::uint32 i = 1; i < 90; ++i) {
    std::cout << "-";
  }
  std::cout << "+\n";

  for (depth_t depth = 0; depth <= 31; ++depth) {
    auto casesMDH = mdh_manager.get_cases(depth);
    auto casesMTH = mth_manager.get_cases(depth);
    if (casesMDH || casesMTH) {
      pai::real32 avgTimeMDH = 0.0f;
      pai::real32 avgTimeMTH = 0.0f;
      std::cout << "|";
      std::cout << std::setw(7) << depth << "|";
      if (casesMDH) {
        pai::uint32 avg = 0;
        for (pai::uint32 i = 0; i < casesMDH->size(); ++i) {
          avg += casesMDH->at(i).generated;
          avgTimeMDH += casesMDH->at(i).tts;
        }
        avgTimeMDH /= casesMDH->size();
        std::cout << std::setw(21) << 
          std::to_string(avg / casesMDH->size()) + "(" + std::to_string(casesMDH->size()) + ")" << "|";
      } else {
        std::cout << std::setw(22) << "|";
      }
      
      if (casesMTH) {
        pai::uint32 avg = 0;
        for (pai::uint32 i = 0; i < casesMTH->size(); ++i) {
          avg += casesMTH->at(i).generated;
          avgTimeMTH += casesMTH->at(i).tts;
        }
        avgTimeMTH /= casesMTH->size();
        std::cout << std::setw(21) << 
          std::to_string(avg / casesMTH->size()) + "(" + std::to_string(casesMTH->size()) + ")" << "|";
      } else {
        std::cout << std::setw(22) << "|";
      }
      
      std::cout << std::setw(18) << avgTimeMDH << "|";
      std::cout << std::setw(18) << avgTimeMTH << "|";
      std::cout << "\n+";
      for (pai::uint32 i = 1; i < 90; ++i) {
        std::cout << "-";
      }
      std::cout << "+\n";
    }
  }
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

  // If statement hell...
  if (!tokens.empty()) {
    if (tokens[0].compare("exit") == 0) {
      SubmitToOutput("Exiting...\n");
      RequestShutDown();
    } else if (tokens[0].compare("heuristic") == 0) {
      if (tokens.size() <= 1) {
        SubmitToOutput("Nothing to set...\n");
        return;
      }
      if (tokens[1].compare("1") == 0) {
        user_use = MANHATTAN;
        SubmitToOutput("Setting heuristic to use Manhattan Distance.\n");
      } else if (tokens[1].compare("2") == 0) {
        user_use = MISPLACED;
        SubmitToOutput("Setting heuristic to use Misplaced Tiles\n");
      } else if (tokens[1].compare("both") == 0) {
        user_use = BOTH;
        SubmitToOutput("Setting heuristic to use both.\n");
      } else if (tokens[1].compare("what") == 0) {
        std::string heuristic = "";
        switch (user_use) {
          case MANHATTAN: heuristic = "Manhattan Distance"; break;
          case MISPLACED: heuristic = "Number of Misplaced Tiles"; break;
          case BOTH:  heuristic = "Both Manhattan and Misplaced"; break;
        }
        SubmitToOutput("Current heuristic: " + heuristic + "\n");
      } else {
        SubmitToOutput("Nothing to set...\n");
      }
    } else if (tokens[0].compare("clear") == 0) {
      mdh_manager.ClearAll();
      mth_manager.ClearAll();
      SubmitToOutput("Cleared all cases...\n");
    } else if (tokens[0].compare("help") == 0) {
      SubmitToOutput(R"(
  Commands:
    solve [file] or [custom] or [random] := Solves an 8 puzzle, provided with furthur instructions. 
    heuristic [i]  := Allows you to change the heuristic of this puzzle with integer i.
                        By default, set to solve with both heuristics. 
                        ex.   heuristic 1 (use Manhattan Distance Heuristic).
                          heuristic 2 (use Misplaced Tiles Heuristic).
                          heuristic both (display both heuristics when solving).
                          heuristic what (display what heuristic currently using).

    show [i]  := Shows how the last puzzle was solved:
                   i = 1 (show last path of Manhattan Distance solved puzzle)
                   i = 2 (show last path of Misplaced Tiles solved puzzle)
                   i = both (show both last paths)

    dump    := Dump all solved puzzle cases held by this program. Program will display
                 depth, average search cost of Manhattan Distance (MDH) and Misplaced Tiles (MTH),
                 along with their respective times in milliseconds.

    clear   := Clear puzzle cases from this program. This is done autonomously.
    help    := Shows commands or (optional) a command in more detail.
    exit    := exit this program. This can be entered at any point in the program.
)");
    } else if(tokens[0].compare("show") == 0) {
      auto &path = last_path;
      if (tokens.size() > 1 && tokens[1].compare("2") == 0) {
        std::cout << "+-------------------------------------------+\n";
        std::cout << "|             MISPLACED TILES PATH          |\n";
        std::cout << "+-------------------------------------------+\n";
        path = mth_last_path;
      } else {
        std::cout << "+-------------------------------------------+\n";
        std::cout << "|               MANHATTAN PATH              |\n";
        std::cout << "+-------------------------------------------+\n";
      }
      uint32_t i = 0;
      for (pai::int32 j = static_cast<pai::int32>(path.size() - 1); j >= 0; --j) {
        pai::Puzzle &p = path[j];
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

      if (tokens.size() > 1 && tokens[1].compare("both") == 0) {  
        std::cout << "+-------------------------------------------+\n";
        std::cout << "|             MISPLACED TILES PATH          |\n";
        std::cout << "+-------------------------------------------+\n";
        path = mth_last_path;
        uint32_t i = 0;
        for (pai::int32 j = static_cast<pai::int32>(path.size() - 1); j >= 0; --j) {
          pai::Puzzle &p = path[j];
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
      }
    } else if (tokens[0].compare("dump") == 0) {
      DumpCases(tokens);
    } else if (tokens[0].compare("solve") ==  0) {
      if (tokens.size() > 1 && (tokens[1].compare("file") == 0)) {
        SolveFileCases();
      } else if (tokens.size() > 1 && tokens[1].compare("random") == 0) {
        SolveRandomCase();
      } else { 
        SolveCustomCase();
      }
    // don't type it please... ;=;
    } else if (tokens[0].compare("\154\157\166\145") == 0) {
      SubmitToOutput("\102\145\40\115\151\156\145\40\74\63\40");
      SubmitToOutput("\163\151\147\150\56\56\56\40\111\40\114\157\166\145\40\171\157\165");
    }
  }
}


void Console::SolveRandomCase()
{
  std::cout << "Generating random case...\n";
  pai::Puzzle puzzle;
  std::array<pai::puzzle_t, 9> rand_puzzle;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<pai::puzzle_t> uniform_dist(0, 8);
  std::unordered_map<pai::puzzle_t, bool> stored;

  std::cout << "Puzzle to solve: \n";
  for (pai::int32 i = 0; i < rand_puzzle.size(); ++i) {
    pai::puzzle_t p = uniform_dist(gen);
    while (stored[p]) {
      p = uniform_dist(gen);
    }
    rand_puzzle[i] = p;
    stored[p] = true;

    if (i % 3 == 0) {
      std::cout << "\n";
    }
    std::cout << rand_puzzle[i] << " ";
  }
  std::cout << "\n";

  if (!puzzle.Digest(rand_puzzle)) {
    std::cout << "Failed to input puzzle\n";
  }
  if (user_use == BOTH) {
    SwitchHeuristic(MANHATTAN);
  }
 
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
    if (user_use == BOTH) {
      mdh_manager.Store(static_cast<depth_t>(path.size() - 1), 
        solver.get_search_cost(), solver.get_time_solved());
      last_path = path;
      std::cout << R"(
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
          MANHATTAN DISTANCE 
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-)";
      std::cout << "\n\n";
      std::cout << "Time took to solve: " << solver.get_time_solved() << " ms\n";
      std::cout << "Total Solved Depth: " << path.size() - 1 << " nodes\n";
      std::cout << "Search Cost: " << solver.get_search_cost() << "\n\n";
      SwitchHeuristic(MISPLACED);
      std::cout << "Switching to misplaced and solving...\n";
      std::cout << R"(
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
            MISPLACED TILES 
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-)";
      solver.Solve(puzzle);
      path = solver.GetSolvedPath();
      mth_manager.Store(static_cast<depth_t>(path.size() - 1), 
        solver.get_search_cost(), solver.get_time_solved());
      std::cout << "\n\n";
      std::cout << "Time took to solve: " << solver.get_time_solved() << " ms\n";
      std::cout << "Total Solved Depth: " << path.size() - 1 << " nodes\n";
      std::cout << "Search Cost: " << solver.get_search_cost() << "\n\n";
      mth_last_path = path;
    } else {
      switch (user_use) {
        case MANHATTAN:
        { 
          mdh_manager.Store(static_cast<depth_t>(path.size() - 1),
            solver.get_search_cost(), solver.get_time_solved()); 
          last_path = path;
        } break;
        case MISPLACED: 
        {   
          mth_manager.Store(static_cast<depth_t>(path.size() - 1),
            solver.get_search_cost(), solver.get_time_solved()); 
          mth_last_path = path;
        } break;
        default: break;
      }
      std::cout << "\n\n";
      std::cout << "Time took to solve: " << solver.get_time_solved() << " ms\n";
      std::cout << "Total Solved Depth: " << path.size() - 1 << " nodes\n";
      std::cout << "Search Cost: " << solver.get_search_cost() << "\n\n";
    }
  } else {
    std::cout << "Unable to solve puzzle. Unsolvable...\n";
  }
}


void Console::SolveFileCases()
{
  std::string cmd;
  SubmitToOutput("Enter filepath:\n");
  SubmitToOutput("enter> ");
  cmd = GetInput();
  if (cmd.compare("exit") == 0) {
    SubmitToOutput("Exiting...\n");
    RequestShutDown();
    return;
  }
  FileParser parser;
  if (!parser.Parse(cmd)) {
    SubmitToOutput("Unable to find and parse file.\n");
    return;
  }
  std::cout << "Solving file...\n";
  std::cout << "Time to completion:\n";
  int32_t total = parser.get_curr_size();
  int32_t completed = 0;
  while (!parser.is_empty()) {
    std::cout << 
      static_cast<int32_t>(
      (static_cast<float>(completed) / static_cast<float>(total)) * 100) << "%";
    std::string line = parser.Next();
    pai::Puzzle puzzle;
    // Ignore if puzzle is invalid.
    if (!puzzle.Digest(line)) {
      ++completed;
      std::cout << CMD_VT100_CLR;
      continue;
    }
  
    if (user_use == BOTH) SwitchHeuristic(MANHATTAN);
    // Ignore if puzzle is not solved. Go to next case.
    if (!solver.Solve(puzzle)) {
      ++completed;
      std::cout << CMD_VT100_CLR;
      continue;
    }
    
    auto path = solver.GetSolvedPath();
    if (user_use == BOTH) {
      last_path = path;
      mdh_manager.Store(static_cast<depth_t>(path.size() - 1), 
        solver.get_search_cost(), solver.get_time_solved());
      SwitchHeuristic(MISPLACED);
      solver.Solve(puzzle);
      path = solver.GetSolvedPath();
      mth_last_path = path;
      mth_manager.Store(static_cast<depth_t>(path.size() - 1),
        solver.get_search_cost(), solver.get_time_solved());
    } else {
      switch (user_use) {
        case MANHATTAN:
        {
          mdh_manager.Store(static_cast<depth_t>(path.size() - 1),
            solver.get_search_cost(), solver.get_time_solved()); 
          last_path = path;
        } break;
        case MISPLACED:
        {
          mth_manager.Store(static_cast<depth_t>(path.size() - 1),
            solver.get_search_cost(), solver.get_time_solved()); 
          mth_last_path = path;
        } break;
      }
    }
    ++completed;
    std::cout << CMD_VT100_CLR;
  }
  std::cout << "\n";
  std::cout << "Finished\n";
}


void Console::SolveCustomCase()
{
  if (user_use == BOTH) {
    SwitchHeuristic(MANHATTAN);
  } else { 
    SwitchHeuristic(user_use); 
  }

  std::string cmd;
  SubmitToOutput("Enter puzzle of format x x x x x x x x\n");
  SubmitToOutput("(you don't need to have spaces between)\n");
  SubmitToOutput("enter> ");
  cmd = GetInput();
  if (cmd.compare("exit") == 0) {
    SubmitToOutput("Exiting...\n");
    RequestShutDown();
    return;
  }
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
      if (user_use == BOTH) {
        // last path to be used when solving.
        last_path = path;
        mdh_manager.Store(static_cast<depth_t>(path.size() - 1), 
          solver.get_search_cost(), solver.get_time_solved());
        std::cout << R"(
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
          MANHATTAN DISTANCE 
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-)";
        std::cout << "\n\n";
        std::cout << "Time took to solve: " << solver.get_time_solved() << " ms\n";
        std::cout << "Total Solved Depth: " << path.size() - 1 << " nodes\n";
        std::cout << "Search Cost: " << solver.get_search_cost() << "\n\n";
        SwitchHeuristic(MISPLACED);
        std::cout << "Switching to misplaced and solving...\n";
        std::cout << R"(
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
            MISPLACED TILES 
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-)";
        solver.Solve(puzzle);
        path = solver.GetSolvedPath();
        mth_last_path = path;
        mth_manager.Store(static_cast<depth_t>(path.size() - 1), 
          solver.get_search_cost(), solver.get_time_solved());
        std::cout << "\n\n";
        std::cout << "Time took to solve: " << solver.get_time_solved() << " ms\n";
        std::cout << "Total Solved Depth: " << path.size() - 1 << " nodes\n";
        std::cout << "Search Cost: " << solver.get_search_cost() << "\n\n";
      } else {
        switch (user_use) {
          case MANHATTAN: 
          {
            mdh_manager.Store(static_cast<depth_t>(path.size() - 1),
              solver.get_search_cost(), solver.get_time_solved());
            // last path to be used when solving.
            last_path = path;
          } break;
          case MISPLACED:
          {
            mth_manager.Store(static_cast<depth_t>(path.size() - 1),
              solver.get_search_cost(), solver.get_time_solved());
            mth_last_path = path;
          } break;
          default: break;
        }
        std::cout << "\n\n";
        std::cout << "Time took to solve: " << solver.get_time_solved() << " ms\n";
        std::cout << "Total Solved Depth: " << path.size() - 1 << " nodes\n";
        std::cout << "Search Cost: " << solver.get_search_cost() << "\n\n";
      }
    }
    
    else {
      std::cout << "Puzzle could not be solved.!\n";
    }
  }
  else {
    SubmitToOutput(pai::LastError() + "\n");
    SubmitToOutput("Aborting solve...\n");
  }
}


std::string GetInput()
{
  std::string input;
  std::getline(std::cin, input);
  return input;
}
} // cs420