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

    }
    else if (tokens[0].compare("solve") == 0) {
      SubmitToOutput("Enter ");
      cmd = GetInput();
      pai::Puzzle puzzle;
      puzzle.Digest(cmd);
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