// 8 Puzzle Solver Algorithm Assignment
// Assignment #1
// Author : Mario Garcia
// Class : CS 420
// Instructor : Dr. Daisy Tang
//
// Copyright (c) 2017 Mario Garcia, MIT License.
// Built with my cat Tom. mew...

#include "Utils/Log.hpp"
#include "Error.hpp"


namespace pai {


std::string LastError()
{
  std::string err = last_error.error;
  last_error = Error();
  return err;
}
} // pai