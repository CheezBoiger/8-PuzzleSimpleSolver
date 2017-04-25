// 8 Puzzle Solver Algorithm Assignment
// Assignment #1
// Author : Mario Garcia
// Class : CS 420
// Instructor : Dr. Daisy Tang
//
// Copyright (c) 2017 Mario Garcia, MIT License.
// Built with my cat Tom. mew...
#include "StateTree.hpp"

namespace pai {


node_uid_t StateTree::Insert(Puzzle &puzzle, node_uid_t parent_id)
{
  StateNode node;
  node.set_puzzle_state(puzzle);
  if (parent_id != StateNode::nan) {
    auto it = m_nodes.find(parent_id);
    if (it != m_nodes.end()) {  
      node.set_parent(&it->second);
    }
  }
  node.set_action(puzzle.get_last_action());
  node_uid_t id = node.get_id();
  m_nodes[id] = std::move(node);
  if (!root) {
    root = &m_nodes[id];
  }
  return id;
}
} // pai