// 8 Puzzle Solver Algorithm Assignment
// Assignment #1
// Author : Mario Garcia
// Class : CS 420
// Instructor : Dr. Daisy Tang
//
// Copyright (c) 2017 Mario Garcia, MIT License.
// Built with my cat Tom. mew...
#include <iostream>
#include <iomanip>
#include "Engine/PuzzleSolver.hpp"
#include "Engine/Puzzle.hpp"
#include "Engine/Heuristic.hpp"
#include "Case/CaseManager.hpp"
#include "Input/FileParser.hpp"


int main(int c, char *argv[])
{
  pai::Puzzle puzzle;
  pai::PuzzleSolver solver;
  pai::ManhattanDistanceHeuristic mdh;
  pai::MisplacedTilesHeuristic mth;
  solver.set_heuristic(mdh);
#if 0
  // Puzzle of 31 length.
  puzzle.Digest(R"(
    8 6 7
    2 5 4
    3 0 1
  )");
#else
 puzzle.Digest(R"(
5 8 0
3 6 2
1 4 7)");
#endif 

  std::cout << "Puzzle is solved: "
    << std::boolalpha << solver.Solve(puzzle)
    << "\n";
  std::cout << "puzzle is as follows: \n\n";
  auto puzzle_board = puzzle.get_puzzle();
  for (pai::uint32 i = 0; i < puzzle_board.size(); ++i) {
    if (i % 3 == 0) {
      std::cout << "\n";
    }
    std::cout << puzzle_board[i] << " ";
  }
  std::cout << "\n\n\n";
  std::cout << "Solved puzzle \n\n";
  std::vector<pai::Puzzle *> solved_path = solver.GetSolvedPath();
  puzzle_board = solved_path[0]->get_puzzle();
  for (pai::uint32 i = 0; i < puzzle_board.size(); ++i) {
    if (i % 3 == 0) {
      std::cout << "\n";
    }
    std::cout << puzzle_board[i] << " ";
  }
  std::cout << "\n";
  std::cout << "Time took to solve: " << solver.get_time_solved() << " ms\n";
  std::cout << "Total Solved Depth: " << solved_path.size() - 1 << " nodes\n";
  std::cout << "Search Cost: " << solver.get_search_cost() << "\n\n";
  std::cout << "Press Enter to continue...\n";
  std::cin.ignore();
  pai::uint32 i = 0;
  for (pai::int32 j = static_cast<pai::int32>(solved_path.size() - 1); j >= 0; --j) {
    pai::Puzzle *p = solved_path[j];
    puzzle_board = p->get_puzzle();
    std::cout << "step: " << i << "\n";
    std::cout << "action taken: " << p->get_last_action() << "\n";
    for (pai::uint32 i = 0; i < puzzle_board.size(); ++i) {
      if (i % 3 == 0) {
        std::cout << "\n";
      }
      std::cout << puzzle_board[i] << " ";
    }
    ++i;
    std::cout << "\n\n";
  }
  std::cin.ignore();
  return 0;
}