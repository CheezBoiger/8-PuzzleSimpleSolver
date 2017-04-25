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
#include <string>

namespace cs420 {

typedef uint32_t depth_t;

class CaseManager {
public:
  CaseManager();

  

  
private: 
  std::vector<std::string> m_case_samples;
  std::vector<depth_t, std::vector<float> > m_timed_cases;
};
} // cs420