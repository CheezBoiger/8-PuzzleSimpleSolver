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
#include <list>


namespace cs420 {


// Parses the given file to this object. The 
// file parser will then parse the contents and 
// produce sample cases for each.
class FileParser {
public:
  FileParser();

  bool Parse(std::string &filepath);
  std::string Next();

  bool is_empty() const {
    return text.empty();
  }

  int get_curr_percentage_done() const {
    return percentage_done;
  }

  int get_curr_size() const {
    return static_cast<int>(text.size());
  }

private:
  int percentage_done;
  std::list<std::string> text;
};
} // cs420