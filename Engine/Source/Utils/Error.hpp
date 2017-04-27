// 8 Puzzle Solver Algorithm Assignment
// Assignment #1
// Author : Mario Garcia
// Class : CS 420
// Instructor : Dr. Daisy Tang
//
// Copyright (c) 2017 Mario Garcia, MIT License.
// Built with my cat Tom. mew...
#pragma once


#include <string>


namespace pai {


// Error types.
enum ErrorType {
  ERROR_NONE,
  ERROR_DIGESTION,
  ERROR_CALIBRATION,
  ERROR_MALFUNCTION,
  ERROR_SIMPLE,
};


// Error struct, used for message logging of errors and what not.
// This is mainly used for debugging release versions, or for programmers
// to figure out what went wrong with their input into this engine.
struct Error {
  std::string error;
  std::string verbose;
  ErrorType type;

  Error(std::string str = "", std::string verbose = "", ErrorType type = ERROR_NONE)
    : error(str)
    , verbose(verbose)
    , type(type)
  { }
};

const Error &GetLastError();
void StateError(ErrorType type, std::string str, std::string verbose = "");
} // pai