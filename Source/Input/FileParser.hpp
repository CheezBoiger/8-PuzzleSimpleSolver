// 8 Puzzle Solver Algorithm Assignment
// Assignment #1
// Author : Mario Garcia
// Class : CS 420
// Instructor : Dr. Daisy Tang
//
// Copyright (c) 2017 Mario Garcia, MIT License.
// Built with <3 
#pragma once

#include <fstream>
#include <string>
#include <forward_list>


namespace cs420 {


// Parses the given file to this object. The 
// file parser will then parse the contents and 
// produce sample cases for each.
class FileParser {
public:
  FileParser();

  bool Open(std::string filepath);
  bool Parse();
  std::string Next();

  bool Close();

private:
  std::fstream file;
};
} // cs420