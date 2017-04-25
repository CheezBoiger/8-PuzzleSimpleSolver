// 8 Puzzle Solver Algorithm Assignment
// Assignment #1
// Author : Mario Garcia
// Class : CS 420
// Instructor : Dr. Daisy Tang
//
// Copyright (c) 2017 Mario Garcia, MIT License.
// Built with <3 
#pragma once

namespace cs420 {


class Interface {
 virtual ~Interface() { }

  virtual void Display() = 0;
  virtual void Input() = 0;

  virtual bool is_running() = 0;
  virtual void RequestShutDown() = 0;
};
} // cs420