// 8 Puzzle Solver Algorithm Assignment
// Assignment #1
// Author : Mario Garcia
// Class : CS 420
// Instructor : Dr. Daisy Tang
//
// Copyright (c) 2017 Mario Garcia, MIT License.
// Built with my cat Tom. mew...
#include "PuzzleSolver.hpp"
#include "Heuristic.hpp"
#include "Puzzle.hpp"
#include "Utils/Log.hpp"
#include "Utils/Assertion.hpp"
#include "Frontier/Frontier.hpp"
#include "StateTree.hpp"

#include <chrono>

namespace pai {


// State Search Tree, only one implemented to keep private 
// tree hidden. There is no need to make this public unless
// use decides it's a fun idea to run multiple Solver objects
// at once or something...
StateTree tree;

// Child reference that describes the path of the solved puzzle
// steps.
StateNode *path_child = nullptr;


// A* Algorithm. As optimal as possible.
bool PuzzleSolver::Solve(const Puzzle &puzzle)
{
  if (unlikely(is_solvable(puzzle))) {
    PAI_PRINT("Puzzle is not solvable! Aborting...");
    return false;
  }
  // Clear the tree first before solving.
  tree.Clear();
  path_child = nullptr;
  Frontier frontier;
  Puzzle p = puzzle;
  tree.Insert(p);
  frontier.Push(tree.get_root());
  auto start = std::chrono::high_resolution_clock::now();
  while (!frontier.is_empty()) {
    StateNode *node = frontier.Pop();
    if (!node->get_puzzle_state().is_solved()) {
      if (!frontier.HasVisited(node)) {
        std::vector<Puzzle> puzzle_states = 
          GenerateStates(node->get_puzzle_state());
        for (Puzzle &puzzle_state : puzzle_states) {
          if (!frontier.HasKey(puzzle_state)) {
            node_uid_t node_id = 
            tree.Insert(puzzle_state, node->get_id());
            StateNode *n = tree.get_node(node_id);
            n->set_depth(node->get_depth() + 1);
            if (n) {
              // Need to calculate f(n) = g(n) + h(n) 
              cost_t total_cost = n->get_depth();
              // Don't necessarily need a heuristic, but best to have one.
              if (curr_heuristic) {
                total_cost += 
                  curr_heuristic->Calculate(n->get_puzzle_state());
              }
              n->evaluate_cost(total_cost);
              frontier.Push(n);
            }
          }
        }
        frontier.PushVisited(node);
      }
    } else {
      auto end = std::chrono::high_resolution_clock::now();
      auto time = 
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
      tts = static_cast<real32>(time.count()) / 1000000.0f;
      path_child = node;
      return true;
    }
  }
  tts = 0.0f; 
  path_child = nullptr;
  return false;
}


std::vector<Puzzle> PuzzleSolver::GenerateStates(Puzzle &puzzle)
{
  std::vector<Puzzle> states;
  if (puzzle.is_moveable(ACTION_UP)) {
    Puzzle p = puzzle;
    p.Shift(ACTION_UP);
    states.push_back(std::move(p));
  }

  if (puzzle.is_moveable(ACTION_DOWN)) {
    Puzzle p = puzzle;
    p.Shift(ACTION_DOWN);
    states.push_back(std::move(p));
  }

  if (puzzle.is_moveable(ACTION_LEFT)) {
    Puzzle p = puzzle;
    p.Shift(ACTION_LEFT);
    states.push_back(std::move(p));
  }

  if (puzzle.is_moveable(ACTION_RIGHT)) {
    Puzzle p = puzzle;
    p.Shift(ACTION_RIGHT);
    states.push_back(std::move(p));
  }
  
  return states;
}


std::vector<Puzzle *> PuzzleSolver::GetSolvedPath() const
{
  std::vector<Puzzle *> puzzles;
  if (path_child) {
    StateNode *trav = path_child;
    while (trav) {
      puzzles.push_back(&trav->get_puzzle_state());
      trav = trav->get_parent();
    }
  }
  return puzzles;
}


bool PuzzleSolver::is_solvable(const Puzzle &puzzle) const
{
  uint32 nInversions = 0;
  auto &p = puzzle.get_puzzle();
  for (uint32 i = 0; i < p.size(); ++i) {
    for (uint32 j = i + 1; j < p.size(); ++j) {
      if (p[i] != 0 && p[i] < p[j]) {
        ++nInversions;
      }
    }
  }
  // Not solvable.
  if ((nInversions % 2) != 0) {
    return false;
  }
  return true;
}


uint32 PuzzleSolver::get_search_cost() const
{
  return tree.get_total_nodes();
}
} // pai