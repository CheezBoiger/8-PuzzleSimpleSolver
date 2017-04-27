// 8 Puzzle Solver Algorithm Assignment
// Assignment #1
// Author : Mario Garcia
// Class : CS 420
// Instructor : Dr. Daisy Tang
//
// Copyright (c) 2017 Mario Garcia, MIT License.
// Built with my cat Tom. mew...
#include "Engine/Puzzle.hpp"
#include "Engine/PuzzleSolver.hpp"
#include "Engine/Utils/Log.hpp"
#include <iostream>

int main(int c, char *argv[])
{
  pai::Puzzle puzzle;
  puzzle.Digest("012345678");
  
  pai::PuzzleSolver solver;
  std::cout << pai::LastError() << "\n";
  puzzle.Digest("012345679");
  std::cout << pai::LastError() << "\n";
  std::cin.ignore();
  return 0;
}