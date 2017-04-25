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
#include "Utils/Assertion.hpp"
#include "Platform/Types.hpp"

#include <string>
#include <array>
#include <limits>


namespace pai {


// Puzzle data type. Uses an unsigned 32 byte to represent
// the pieces in the puzzle.
typedef uint32 puzzle_t;

// Action describes the event in which to invoke on the puzzle,
// thereby allowing modification to the object.
enum Action {
  ACTION_NONE,
  ACTION_LEFT,
  ACTION_RIGHT,
  ACTION_UP,
  ACTION_DOWN
};

// Puzzle Object, used by the solver engine to calculate 
// the solving of the 8 puzzle piece. This simply serves 
// as a container object to use for our solver. In order to
// solve the 8-puzzle, we need to convert our string, or 
// buffer to this puzzle object to use.
// We go about representing the board as so:
//
//        | 0 1 2 |
//        | 3 4 5 |
//        | 6 7 8 |
// 
// However, we implement the buffer as a one dimensional array,
// for performance.
class Puzzle {
public:
  // Interpret our action as a verbal string.
  static std::string Interpret(Action action);

  // Standard puzzle solving.
  explicit Puzzle()
    : solved(false)
    , cursor((std::numeric_limits<uint32>::max)())
    , last_action(ACTION_NONE)
  { }

  // will require both copy and move constructors.

  Puzzle(const Puzzle &puzzle)
    : solved(puzzle.solved) 
    , cursor(puzzle.cursor) 
    , last_action(puzzle.last_action)
  {
    m_puzzle = puzzle.m_puzzle;
  }

  Puzzle(Puzzle &&puzzle) 
    : solved(puzzle.solved) 
    , cursor(puzzle.cursor) 
    , last_action(puzzle.last_action)
  {
    std::swap(m_puzzle, puzzle.m_puzzle);
  }

  Puzzle &operator=(const Puzzle &puzzle) {
    m_puzzle = puzzle.m_puzzle;
    solved = puzzle.solved;
    cursor = puzzle.cursor;
    last_action = puzzle.last_action;
    return (*this);
  }

  Puzzle &operator=(Puzzle &&puzzle) {
    std::swap(m_puzzle, puzzle.m_puzzle);
    solved = puzzle.solved;
    cursor = puzzle.cursor;
    last_action = puzzle.last_action;
    return (*this);
  }

  // Digest a string that contains the data of 
  // the 8-puzzle. 
  void Digest(std::string str);

  // Digest a puzzle buffer that contains the values of 
  // the 8-puzzle.
  void Digest(uint32 size, puzzle_t *puzzle);

  // Moves specified puzzle array to this puzzle.
  void Digest(std::array<puzzle_t, 9> &puzzle);

  // Shifts our cursor piece '0' depending on the specified action, 
  // swapping pieces with the node in the direction. Returns true if the cursor
  // successfully moved, false if movement is not possible.
  bool Shift(Action action);

  // Returns the value true (1) if the puzzle is solved, otherwise
  // false (0) is returned if not yet solved.
  bool is_solved() const { return solved; }

  // Returns the value in the specified index of this puzzle
  // object.
  puzzle_t operator[](uint32 i) const {
    return at(i);
  };

  // Returns the value in the specified index of this puzzle 
  // object.
  puzzle_t at(uint32 i) const {
    PASSERT(i >= 0 && i < 9);
    return m_puzzle[i];
  }

  // Determine if this puzzle is equal to the other. Returns
  // true if equal, false otherwise.
  bool equal(const Puzzle &other) const;

  // Determine if this puzzle is equal to the other. Returns
  // true if equal, false otherwise.
  bool operator==(const Puzzle &other) const;

  // Determine if this puzzle is NOT equal to the other. Returns
  // true if not equal, false otherwise.
  bool operator!=(const Puzzle &other) const;

  // Get the entirety of the puzzle structure, since we are doing c++.
  const std::array<puzzle_t, 9> &get_puzzle() const { return m_puzzle; }

  // Check if performing an action will allow us to move the cursor.
  // We basically check if we can move to a given spot in the puzzle 
  // without going out of bounds.
  bool is_moveable(Action action);

  // Get the last action to be done onto this puzzle state.
  Action get_last_action() const {
    return last_action;
  }

private:
  // Check if the puzzle is solved. Returns true if the cursor
  // successfully moved, false if movement is not possible.
  void CheckIfPuzzleSolved();

  // Move the cursor left in the puzzle board. Returns true if the cursor
  // successfully moved, false if movement is not possible.
  bool ShiftCursorLeft();

  // Move the cursor right in the puzzle board. Returns true if the cursor
  // successfully moved, false if movement is not possible.
  bool ShiftCursorRight();

  // Move the cursor up in the puzzle board. Returns true if the cursor
  // successfully moved, false if movement is not possible.
  bool ShiftCursorUp();
  
  // Move the cursor down in the puzzle board. Returns true if the cursor
  // successfully moved, false if movement is not possible.
  bool ShiftCursorDown();

  // The 8-puzzle buffer, which holds the values of the puzzle.
  std::array<puzzle_t, 9> m_puzzle;

  // Determines if this puzzle has already been solved.
  bool solved;

  // The cursor index within the puzzle board. This defines where 
  // the cursor '0' is to save performance.
  uint32 cursor;

  // The last action done on this puzzle.
  Action last_action;

  friend class PuzzleSolver;
};


// Simple Puzzle Hash function, used by the Frontier to check if 
// a given puzzle state has already been explored. Hash is implemented
// using Jenkin's avalanche one at a time hash.
class PuzzleHash {
public:
  // Simple Jenkin's One-At-A-Time hash function.
  std::size_t operator()(const Puzzle &p) const {
    std::size_t hash = 0;
    auto &puzzle = p.get_puzzle();
    for (uint32 i = 0; i < puzzle.size(); ++i) {
      hash += puzzle[i];
      hash += (hash << 10);
      hash ^= (hash >> 6);
    }
    hash += (hash >> 3);
    hash ^= (hash << 11);
    hash += (hash >> 15);
    return hash;
  }
};
} // pai