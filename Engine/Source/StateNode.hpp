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
#include "Platform/Types.hpp"
#include "Puzzle.hpp"

#include <memory>


namespace pai {

// definitions to define our types in the state node.
// This particular data type describes our cost of travering
// a state node.
typedef uint32 cost_t;

// definition of the node id data type. This is used to reference 
// allocated state nodes by id, rather than simply address, which can prove
// fatal.
typedef uint64 node_uid_t;

// State node that defines the current state of the puzzle that
// is given for this node. Puzzles are solved and their states
// are stored into state nodes to determine the best solution
// for the initial puzzle situation.
class StateNode {
  // the unique id of the state node.
  static node_uid_t id_count;
  PAI_DISALLOW_COPY_AND_ASSIGN(StateNode);
public:
  // Not a number for the state node id type.
  static const node_uid_t nan;

  // Constructor that increments the node unique id.
  StateNode(StateNode *parent = nullptr)
    : parent(parent)
    , cost(0)
    , depth(0)
    , id(id_count++)
  { }

  StateNode(StateNode &&node) 
    : depth(node.depth)
    , cost(node.cost)
    , id(node.id) 
    , parent(node.parent)
  {
    std::swap(state, node.state);
    action = state.get_last_action();
  }

  StateNode &operator=(StateNode &&node) {
    std::swap(state, node.state);
    depth = node.depth;
    cost = node.cost;
    id = node.id;
    parent = node.parent;
    action = state.get_last_action();
    return (*this);
  }

  // Get the parent node of this state node.
  StateNode *get_parent() const { 
    return parent; 
  }

  // Set the parent of this state node.
  void set_parent(StateNode *node) { 
    parent = node; 
  }
 
  // Get the current puzzle state from this state node.
  Puzzle &get_puzzle_state() { 
    return state; 
  }

  // Moves the puzzle into this state node. Any state
  // that was previously, or already, contained in this
  // state node will be replaced.
  void set_puzzle_state(Puzzle &puzzle) {
    state = std::move(puzzle);
  }

  // Evaluate the cost of reaching this StateNode object from
  // which the graph.
  void evaluate_cost(cost_t new_cost) { 
    cost = new_cost; 
  }

  // Set the depth of this state node, that is within the graph.
  void set_depth(uint32 new_depth) {
    depth = new_depth;
  }

  // Get the depth of this state node.
  uint32 get_depth() const { 
    return depth; 
  }

  // Get the cost of this state node.
  cost_t get_cost() const { 
    return cost; 
  }

  // Get the action conducted to reach this state node.
  Action get_action() const { 
    return action;
  }

  // Set the action for this state node.
  void set_action(Action a) {
    action = a;
  }

  // Get the unique identification number of this state node.
  // This number is unique to all nodes, so it should not conflict
  // with other nodes in a tree.
  node_uid_t get_id() const {
    return id;
  }

private:
  // The current state of the puzzle.
  Puzzle state;

  // The Parent node of this child node.
  StateNode *parent;

  // Action taken to get to this state.
  Action action;

  // the current depth within the State graph.
  uint32 depth;

  // The node id.
  node_uid_t id;

  // The overall cost to reach this state node.
  cost_t cost;
};

// State Node Comparator for each state node in the frontier.
// Defines the StateNode comparison object in the form 
// of StateNode ptrs.
class StateNodePtrComparator {
public:
  bool operator()(const StateNode *lhs, const StateNode *rhs) const {
    return lhs->get_cost() > rhs->get_cost();
  }
};


// Default StateNode Comparator object, used to compare two 
// StateNodes
class StateNodeComparator {
public:
  bool operator()(const StateNode &lhs, const StateNode &rhs) const {
    return lhs.get_cost() > rhs.get_cost();
  }
};
} // pai