// 8 Puzzle Solver Algorithm Assignment
// Assignment #1
// Author : Mario Garcia
// Class : CS 420
// Instructor : Dr. Daisy Tang
//
// Copyright (c) 2017 Mario Garcia, MIT License.
// Built with <3 
#pragma once

#include <string>
#include <cstdint>

namespace cs420 {


class Interface {
public:
 virtual ~Interface() { }
  virtual void Input(std::string cmd) = 0;
  virtual void SubmitToOutput(std::string str, uint32_t width = 0) = 0;

  virtual bool is_running() = 0;
  virtual void RequestShutDown() = 0;
};
} // cs420