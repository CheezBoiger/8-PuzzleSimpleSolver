// 8 Puzzle Solver Algorithm Assignment
// Assignment #1
// Author : Mario Garcia
// Class : CS 420
// Instructor : Dr. Daisy Tang
//
// Copyright (c) 2017 Mario Garcia, MIT License.
// Built with <3 
#include "FileParser.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

namespace cs420 {


FileParser::FileParser()
  : percentage_done(0)
{
}


bool FileParser::Parse(std::string &filepath)
{
  std::fstream file;
  file.open(filepath.c_str());
  if (!file.is_open()) {
    file.close();
   return false;
  }

  std::string line = "";
  while (std::getline(file, line)) {
    text.push_back(line);
  }
  file.close();
  return true;
}

std::string FileParser::Next()
{
  std::string line = text.front();
  text.pop_front();
  return line;
}
} // cs420