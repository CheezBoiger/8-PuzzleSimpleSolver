// 8 Puzzle Solver Algorithm Assignment
// Assignment #1
// Author : Mario Garcia
// Class : CS 420
// Instructor : Dr. Daisy Tang
//
// Copyright (c) 2017 Mario Garcia, MIT License.
// Built with my cat Tom. mew...
#include "Puzzle.hpp"
#include "Utils/Log.hpp"

#include <cctype>
#include <algorithm>
#include <utility>


namespace pai {


bool Puzzle::Digest(std::string str)
{
  str.erase(std::remove_if(str.begin(), str.end(), std::isspace), 
    str.end());
  if (str.size() != 9) {
    PAI_PRINT("Size does not equal 9! => " << str.size() <<
      ".\nCan not print");
    return false;
  }
  puzzle_t p[10] = { 
    (std::numeric_limits<uint32>::max)(),
    (std::numeric_limits<uint32>::max)(),
    (std::numeric_limits<uint32>::max)(),
    (std::numeric_limits<uint32>::max)(),
    (std::numeric_limits<uint32>::max)(),
    (std::numeric_limits<uint32>::max)(),
    (std::numeric_limits<uint32>::max)(),
    (std::numeric_limits<uint32>::max)(),
    (std::numeric_limits<uint32>::max)(),
    (std::numeric_limits<uint32>::max)() 
  };

  for (uint32 i = 0; i < str.size(); ++i) {
    char c = str[i];
    if (!std::isdigit((int)c)) {
      PAI_PRINT("Not a qualified digit!");
      return false;
    }
    puzzle_t n = static_cast<puzzle_t>(c - '0');
    if (n == 0 && p[n] != n && cursor == (std::numeric_limits<uint32>::max)()) {
      cursor = i;
      p[n] = n;
    } else if (n != p[i]) {
      p[n] = n;
    } else {
      PAI_PRINT("Redefinition of two puzzle pieces! Aborting...");
      return false;
    }
    m_puzzle[i] = n;
  }
  if (cursor == (std::numeric_limits<uint32>::max)()) {
    PAI_PRINT("Cursor 0 is missing from puzzle! Aborting...");
    return false;
  }
  if (p[9] != (std::numeric_limits<uint32>::max)()) {
    PAI_PRINT("the number 9 should not be in this puzzle! Aborting...");
    return false;
  }
  CheckIfPuzzleSolved();
  return true;
}


bool Puzzle::Digest(uint32 size, puzzle_t *puzzle)
{
  if (size != 9) {
    PAI_PRINT("Size does not equal 9! => " << size <<
    ".\nCan not print");
    return false;
  }
  puzzle_t p[10] = {
    (std::numeric_limits<uint32>::max)(),
    (std::numeric_limits<uint32>::max)(),
    (std::numeric_limits<uint32>::max)(),
    (std::numeric_limits<uint32>::max)(),
    (std::numeric_limits<uint32>::max)(),
    (std::numeric_limits<uint32>::max)(),
    (std::numeric_limits<uint32>::max)(),
    (std::numeric_limits<uint32>::max)(),
    (std::numeric_limits<uint32>::max)(),
    (std::numeric_limits<uint32>::max)()
  };
  for (uint32 i = 0; i < size; ++i) {
    if (puzzle[i] == 0 && p[i] == (std::numeric_limits<uint32>::max)()) {
      cursor = i;
    } else if (puzzle[i] != p[puzzle[i]]) {
      p[puzzle[i]] = puzzle[i];
    } else {
      PAI_PRINT("Redefinition of two puzzle pieces! Aborting...");
      return false;
    }
    m_puzzle[i] = puzzle[i];
  }
  if (cursor == (std::numeric_limits<uint32>::max)()) {
    PAI_PRINT("Cursor 0 is missing from puzzle! Aborting...");
    return false;
  }
  if (p[9] != (std::numeric_limits<uint32>::max)()) {
    PAI_PRINT("the number 9 should not be in this puzzle! Aborting...");
    return false;
  }
  CheckIfPuzzleSolved();
  return true;
}


bool Puzzle::Digest(std::array<puzzle_t, 9> &puzzle)
{
  m_puzzle = std::move(puzzle);
  CheckIfPuzzleSolved();
  return true;
}


void Puzzle::CheckIfPuzzleSolved()
{
  uint32 count = 0;
  for (puzzle_t piece : m_puzzle) {
    if (piece != count) {
      // Breaks off the loop quick before causing O(n^2) 
      // runtime.
      return;
    }
    count++;
  }
  solved = true;
}


bool Puzzle::Shift(Action action)
{
  switch (action) {
    case ACTION_UP: return ShiftCursorUp();
    case ACTION_DOWN: return ShiftCursorDown();
    case ACTION_LEFT: return ShiftCursorLeft();
    case ACTION_RIGHT: return ShiftCursorRight();
    default: return false;
  };
}


bool Puzzle::ShiftCursorUp()
{
  if (!is_moveable(ACTION_UP)) {
    return false;
  }
  std::swap(m_puzzle[cursor], m_puzzle[cursor - 3]);
  cursor -= 3;
  last_action = ACTION_UP;
  CheckIfPuzzleSolved();
  return true;
}


bool Puzzle::ShiftCursorDown()
{
  if (!is_moveable(ACTION_DOWN)) {
    return false;
  }
  std::swap(m_puzzle[cursor], m_puzzle[cursor + 3]);
  cursor += 3;
  last_action = ACTION_DOWN;
  CheckIfPuzzleSolved();
  return true;
}


bool Puzzle::ShiftCursorLeft()
{
  if (!is_moveable(ACTION_LEFT)) {
    return false;
  }
  std::swap(m_puzzle[cursor], m_puzzle[cursor - 1]);
  cursor -= 1;
  last_action = ACTION_LEFT;
  CheckIfPuzzleSolved();
  return true;
}


bool Puzzle::ShiftCursorRight()
{
  if (!is_moveable(ACTION_RIGHT)) {
    return false;
  }
  std::swap(m_puzzle[cursor], m_puzzle[cursor + 1]);
  cursor += 1;
  last_action = ACTION_RIGHT;
  CheckIfPuzzleSolved();
  return true;
}


bool Puzzle::is_moveable(Action action)
{
  switch (action) {
    case ACTION_DOWN:
    {
      for (uint32 i = 6; i < 9; ++i) {
        if (m_puzzle[i] == 0) {
          return false;
        }
      }
    }
    break;
    case ACTION_UP:
    {
      for (uint32 i = 0; i < 3; ++i) {
        if (m_puzzle[i] == 0) {
          return false;
        }
      }
    }
    break;
    case ACTION_LEFT:
    {
      for (uint32 i = 0; i < 9; i += 3) {
        if (m_puzzle[i] == 0) {
          return false;
        }
      }
    }
    break;
    case ACTION_RIGHT:
    {
      for (uint32 i = 2; i < 9; i += 3) {
        if (m_puzzle[i] == 0) {
          return false;
        }
      }
    }
    break;
    default: 
      return false;
  };
  return true;
}


bool Puzzle::equal(const Puzzle &other) const
{
  for (uint32 i = 0; i < 9; ++i) {
    if (m_puzzle[i] != other[i]) {
      return false;
    }
  }
  return true;
}


bool Puzzle::operator==(const Puzzle &other) const
{
  return equal(other);
}


bool Puzzle::operator!=(const Puzzle &other) const
{
  return equal(other) == false;
}


std::string Puzzle::Interpret(Action action)
{
  switch (action) {
    case ACTION_DOWN:   return "Down";
    case ACTION_LEFT:   return "Left";
    case ACTION_RIGHT:  return "Right";
    case ACTION_UP:     return "Up";
    case ACTION_NONE:
    default:            return "None";
  };
}
} // pai