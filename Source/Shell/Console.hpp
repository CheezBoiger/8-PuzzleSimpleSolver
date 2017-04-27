// 8 Puzzle Solver Algorithm Assignment
// Assignment #1
// Author : Mario Garcia
// Class : CS 420
// Instructor : Dr. Daisy Tang
//
// Copyright (c) 2017 Mario Garcia, MIT License.
// Built with <3 
#pragma once

#include "Interface.hpp"

namespace cs420 {

bool InitOutput();
bool CleanupOutput();


// The Console display.
class Console : public Interface {
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

  void PerformSolving();

private:
  bool running;
};


std::string GetInput();
} // cs420