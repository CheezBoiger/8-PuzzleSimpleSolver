// 8 Puzzle Solver Algorithm Assignment
// Assignment #1
// Author : Mario Garcia
// Class : CS 420
// Instructor : Dr. Daisy Tang
//
// Copyright (c) 2017 Mario Garcia, MIT License.
// Built with my cat Tom. mew...
#pragma once

#include "Platform/Platform.hpp"
#include "Platform/Types.hpp"
#include "Puzzle.hpp"

#include <string>
#include <array>
#include <vector>


namespace pai {


class Heuristic;
class Puzzle;

// Solver Object, which utilizies the State Machine of this
// Library. Solver is intended to solve an 8-puzzle problem,
// while also providing speed and efficiency in doing so.
// To start up this Solver, the programmer needs to initialize
// the g(n) and (optional) h(n) functions in order to get this working. A 
// Default algorithm is already set up for this Solver, so there is no need
// to initialize manually, unless you require using another algorithm.
// The function of this solver is as follows:
//
//      f(n) = g(n) + h(n)
//
// Used to solve the puzzle: 
//
//        | 0 1 2 |
//        | 3 4 5 |
//        | 6 7 8 |
// 
// We use A* as our search algorithm, along with the optional Heuristic of
// your choice. 
class PuzzleSolver {
public:
  // Default constructor.
  PuzzleSolver()
    : curr_heuristic(nullptr)
    , tts(0)
  { }

  // Solve the puzzle. this function takes in a puzzle that needs 
  // to be solved. This is performed using A* Search.
  bool Solve(const Puzzle &puzzle);

  // Get the current heuristic that is registered to this 
  // solver.
  Heuristic *get_current_heuristic() { 
    return curr_heuristic; 
  }

  // Set the heuristic for this Solver object.
  void set_heuristic(Heuristic &heuristic) { 
    curr_heuristic = &heuristic;
  }

  // Get the Solved path of this solver, which was generated after
  // the solving of the input puzzle. The path returned is in the 
  // reversed order, so be sure to read from back to front to get 
  // the steps from beginning to end.
  std::vector<Puzzle> GetSolvedPath() const;

  // Get the time it took to solve the puzzle, in milliseconds.
  // This time will be modified once the puzzle given to this
  // solver, is solved.
  real32 get_time_solved() const {
    return tts;
  }

  // The the cost taken to search for the optimal solution.
  // This cost should average about the same as the table given
  // by our book reference table.
  uint32 get_search_cost() const;

private:
  // Generates our states for our solver. We do not have the puzzle 
  // do this for us, as it would be rather strange to see a list of
  // puzzle states created by the original puzzle, instead we will 
  // explicitly do this for ourselves.
  std::vector<Puzzle> GenerateStates(Puzzle &puzzle);

  // Check if this puzzle is solvable in the first place. This will likely
  // reduce the amount of time to determine if a puzzle is even solvable or
  // not. Returns true if the puzzle is solvable, false otherwise.
  bool is_solvable(const Puzzle &puzzle) const;

  // The time it took to solve the puzzle. Time-To-Solve. this is measured
  // in milliseconds (ms).
  real32 tts;

  // The current heuristic used to solve the puzzle. Set as nullptr
  // if no heuristic is going to be used. This is optional, so as 
  // to increase performance of the A* algorithm.
  Heuristic *curr_heuristic;
};
} // pai