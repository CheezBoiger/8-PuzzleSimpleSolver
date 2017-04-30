// 8 Puzzle Solver Algorithm Assignment
// Assignment #1
// Author : Mario Garcia
// Class : CS 420
// Instructor : Dr. Daisy Tang
//
// Copyright (c) 2017 Mario Garcia, MIT License.
// Built with <3 
#pragma once

#include <cstdint>
#include <vector>
#include <map>
#include <string>
#include "Engine/Puzzle.hpp"

namespace cs420 {

typedef uint32_t depth_t;

// Case study to store.
struct Case {
  // Time-to-solve in milliseconds.
  float     tts;
  // Number of generated nodes taken to get the 
  // solved puzzle.
  uint32_t  generated;
  // The depth of the solve branch.
  depth_t   depth;
};


class CaseManager {
public:
  CaseManager();
  
  void Store(depth_t depth, uint32_t generated, float tts);

  std::vector<Case> *get_cases(depth_t depth);

  void ClearAll();

private: 
  std::vector<std::string> m_case_samples;
  std::map<depth_t, std::vector<Case> > m_timed_cases;
};
} // cs420