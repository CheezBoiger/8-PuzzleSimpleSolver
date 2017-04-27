// 8 Puzzle Solver Algorithm Assignment
// Assignment #1
// Author : Mario Garcia
// Class : CS 420
// Instructor : Dr. Daisy Tang
//
// Copyright (c) 2017 Mario Garcia, MIT License.
// Built with my cat Tom. mew...
#include "Error.hpp"

namespace pai {


static Error last_error;


const Error &GetLastError()
{
  return last_error;
}


void StateError(ErrorType type, std::string str, std::string verbose)
{
  last_error = Error(str, verbose, type);
}
} // pai