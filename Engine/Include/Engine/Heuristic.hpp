// 8 Puzzle Solver Algorithm Assignment
// Assignment #1
// Author : Mario Garcia
// Class : CS 420
// Instructor : Dr. Daisy Tang
//
// Copyright (c) 2017 Mario Garcia, MIT License.
// Built with my cat Tom. mew...
#pragma once

#include "Platform/Types.hpp"
#include "Platform/Platform.hpp"


namespace pai {


class Puzzle;


// Heuristic definition for the AI 8 puzzle solver.
// A Heuristic is a function state that attempts to
// solve a problem more efficiently when classical 
// methods are too slow. 
// We define our Heuristic as h(n) which represents
// the estimated cost of the cheapest path from our node
// n to a goal node.
// We also define a few other rules:
//
//  h(n) = 0 if n is the goal
//  h(n) could be general or problem specific.
//
// 
class Heuristic {
public:
  virtual ~Heuristic() { }
  virtual uint32 Calculate(const Puzzle &p) = 0;
};


// The manhattan distance heuristic. We calculate the manhattan
// distance for every piece in the puzzle, then combine them to 
// get the total sum.
class ManhattanDistanceHeuristic : public Heuristic {
public:
  // Calculate the Manhattan distance.
  uint32 Calculate(const Puzzle &p) override;
};


// Calculate the number of misplaced tiles in the current state
// of our puzzle.
class MisplacedTilesHeuristic : public Heuristic {
public:
  uint32 Calculate(const Puzzle &p) override;
};
} // pai