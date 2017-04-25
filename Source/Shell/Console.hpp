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


class Console : public Interface {
public:
  void Display() override;

  void DigestInput() override;
  
  bool is_running() override {
    return running;
  }

  void RequestShutDown() override;

private:
  bool running;
};
} // cs420