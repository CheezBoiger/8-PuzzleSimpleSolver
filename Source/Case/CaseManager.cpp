// 8 Puzzle Solver Algorithm Assignment
// Assignment #1
// Author : Mario Garcia
// Class : CS 420
// Instructor : Dr. Daisy Tang
//
// Copyright (c) 2017 Mario Garcia, MIT License.
// Built with <3 
#include "CaseManager.hpp"

namespace cs420 {


CaseManager::CaseManager()
{  
}

void CaseManager::Store(depth_t depth, uint32_t generated, 
  float tts)
{
  Case obj = { };
  obj.depth = depth;
  obj.generated = generated;
  obj.tts = tts;
  
  auto it = m_timed_cases.find(depth);
  if (it == m_timed_cases.end()) {
    m_timed_cases[depth] = std::vector<Case>();
  }
  m_timed_cases[depth].push_back(std::move(obj));
}


std::vector<Case> *CaseManager::get_cases(depth_t depth)
{
  std::vector<Case> *cases = nullptr;
  auto iter = m_timed_cases.find(depth);
  if (iter != m_timed_cases.end()) {  
    cases = &m_timed_cases[depth];
  }
  return cases;
}


void CaseManager::ClearAll()
{
  m_timed_cases.clear();
}
} // cs420