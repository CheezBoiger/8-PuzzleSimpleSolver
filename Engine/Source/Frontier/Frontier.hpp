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
#include "../StateNode.hpp"

#include <vector>
#include <unordered_map>
#include <queue>
#include <set>

namespace pai {


class StateNode;

// Frontier handler that deals with using the frontier data structure.
class Frontier {
public:

  // Pop a StateNode out of the Frontier. Node is still kept 
  // track inside the explored set of this object though.
  inline StateNode *Pop() {
    StateNode *state = m_queue.top();
    m_queue.pop(); 
    return state;  
  }

  // Push a StateNode into this Frontier object.
  inline void Push(StateNode *state) {
    m_queue.push(state);
  }

  // Push a state node into the visited set. We use this to check
  // if we have already generated a node with a similar puzzle.
  inline void PushVisited(StateNode *state) {
    m_explored[state->get_puzzle_state()] = state;
  }

  // Check if this set has already visited the state node.
  inline bool HasVisited(StateNode *state) {
    auto iter = m_explored.find(state->get_puzzle_state());
    if (iter  != m_explored.end()) {
      return true;
    }
    return false;
  }

  // Check if this Frontier already has a Puzzle key in its explored set.
  inline bool HasKey(Puzzle &puzzle) {
    auto iter = m_explored.find(puzzle);
    if (iter != m_explored.end()) {
      return true;
    }
    return false;
  }

  // Check if this frontier queue is empty.
  inline bool is_empty() const { 
    return m_queue.empty();
  }

  // Get the number of explored nodes.
  inline uint32 get_num_explored_nodes() const {
    return static_cast<uint32>(m_explored.size());  
  }

private: 
  // Priority queue for the Frontier.
  std::priority_queue<StateNode *, 
    std::vector<StateNode *>, StateNodePtrComparator> m_queue;

  // Visited states that are handled in the frontier.
  std::unordered_map<Puzzle, StateNode *, PuzzleHash> m_explored;
};
} // pai