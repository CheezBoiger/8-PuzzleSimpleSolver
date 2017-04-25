// 8 Puzzle Solver Algorithm Assignment
// Assignment #1
// Author : Mario Garcia
// Class : CS 420
// Instructor : Dr. Daisy Tang
//
// Copyright (c) 2017 Mario Garcia, MIT License.
// Built with my cat Tom. mew...
#include "Heuristic.hpp"
#include "Utils/Assertion.hpp"
#include "Puzzle.hpp"

#include <cmath>

namespace pai {


uint32 ManhattanDistanceHeuristic::Calculate(const Puzzle &p)
{
  uint32 man_dist = 0;
  for (uint32 i = 0; i < 9; ++i) {
    puzzle_t piece = p[i];
    uint32 hori = piece % 3;
    uint32 vert = piece / 3;
    // Horizontal distance.
    uint32 x = i % 3;
    // Vertical Distance.
    uint32 y = i / 3;
    man_dist += std::abs(static_cast<int32>(x - hori)) + 
      std::abs(static_cast<int32>(y - vert));
  }
  return man_dist;
}


uint32 MisplacedTilesHeuristic::Calculate(const Puzzle &p)
{
  uint32 misplaced = 0;
  uint32 tile = 0;
  for (uint32 i = 0; i < 9; ++i) {
    if (tile != p[i]) {
      ++misplaced;
    }
    ++tile;
  }
  return misplaced;
}
} // pai