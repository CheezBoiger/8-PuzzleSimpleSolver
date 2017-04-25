// 8 Puzzle Solver Algorithm Assignment
// Assignment #1
// Author : Mario Garcia
// Class : CS 420
// Instructor : Dr. Daisy Tang
//
// Copyright (c) 2017 Mario Garcia, MIT License.
// Built with my cat Tom. mew...
#pragma once

#include "StateNode.hpp"

#include <unordered_map>


namespace pai {


class Puzzle;

// StateTree, which is used to keep the state of each puzzle
// with different movements. We keep track of the number of 
// nodes in this tree with their unique ids.
class StateTree {
public:
  // Constructor with the initial puzzle. This tree will initialize
  // a root node.
  StateTree(const Puzzle &initial)
    : root(nullptr)
  {
    Puzzle puzzle = initial;
    StateNode node;
    node.set_puzzle_state(puzzle);
    node_uid_t uid = node.get_id();
    m_nodes[uid] = std::move(node);
    root = &m_nodes[uid];
  }

  StateTree()
    : root(nullptr)
  { 
  }

  // Get the root node of this tree.
  StateNode *get_root() const { 
    return root; 
  }

  // Insert a puzzle into this tree. Returns the node id
  // that was stored. If node can not be stored, Nan is returned.
  // If parent_id is specified, function will search for the state
  // node parent within this tree. If none, parent is set to nan.
  // Also note that the puzzle WILL MOVE over to a created node inside
  // this tree, causing the puzzle parameter to become unusable after.
  node_uid_t Insert(Puzzle &puzzle, 
    node_uid_t parent_id = StateNode::nan);

  // Clear the tree of any nodes. This will clear out the entire
  // node container, resetting even the root back to nullptr.
  void Clear() {
    m_nodes.clear();
    root = nullptr;
  }

  // Get the node from this tree, with the given unique identification
  // number. If found, the state node ptr is returned, other wise a
  // nullptr is returned.
  StateNode *get_node(node_uid_t id) {
    auto it = m_nodes.find(id);
    if (it != m_nodes.end()) {
      return &m_nodes[id];
    }
    return nullptr;
  }

  // Get the total number of nodes in the state tree.
  uint32 get_total_nodes() const {
    return static_cast<uint32>(m_nodes.size());
  }

private:
  // The starting root of the node.
  StateNode *root;

  // The nodes in the StateTree. All nodes are stored inside a 
  // map container. They provide quick performance, along with 
  // convenient cleanup.
  std::unordered_map<node_uid_t, StateNode> m_nodes;
};
} // pai