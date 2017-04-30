// 8 Puzzle Solver Algorithm Assignment
// Assignment #1
// Author : Mario Garcia
// Class : CS 420
// Instructor : Dr. Fang "Daisy" Tang
//
// Copyright (c) 2017 Mario Garcia, MIT License.
// Built with <3 
#pragma once

#include "Interface.hpp"

namespace cs420 {

// Initialize the output. This runs an internal thread, used
// with handling the standard output, without creating trouble
// with slowdowns.
//
// Returns True if sucessful with initialization.
bool InitOutput();

// Cleans up the standard output, along with terminating the thread.  Since the 
// thread is dealing with it's own sh*t right now, it's best to step in at times 
// to check up on it, eventually though, you just gotta put it out of its misery... 
// 
// If the standard output thread was not terminated sucessfully, all hell will break 
// loose. Meteors will start falling out of the sky, Elon Musk will be locked away
// in an underground federal gov't dungeon, and sweet muffins will no longer be sweet...
// Returns True when successful, False otherwise.
bool CleanupOutput();


// The Console display.
class Console : public Terminal {
public:
  Console()
    : running(true)
  { }
 
  void Input(std::string cmd) override;
  void SubmitToOutput(std::string str, uint32_t width = 0) override;
  
  bool is_running() override {
    return running;
  }

  void RequestShutDown() override {
    running = false;
  }

private:
  void SolveCustomCase();
  void SolveFileCases();
  void SolveRandomCase();

  bool running;
};


std::string GetInput();
} // cs420