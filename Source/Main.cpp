// 8 Puzzle Solver Algorithm Assignment
// Assignment #1
// Author : Mario Garcia
// Class : CS 420
// Instructor : Dr. Daisy Tang
//
// Copyright (c) 2017 Mario Garcia, MIT License.
// Built with my cat Tom. mew...
#include "Shell/Console.hpp"


int main(int c, char *arv[])
{
  cs420::InitOutput();
  cs420::Console console;
  console.SubmitToOutput("Copyright (c) 2017 Kitten Solvers.");
  console.SubmitToOutput(R"(
  Commands:
    solve [file] or [custom] := Solves an 8 puzzle, provided with furthur instructions. 

    heuristic [i]            := Allows you to change the heuristic of this puzzle with integer i.
                                By default, set to solve with both heuristics. 
                              ex.   heuristic 1 (use Manhattan Distance Heuristic).
                                    heuristic 2 (use Misplaced Tiles Heuristic).
                                    heuristic both (display both heuristics when solving).

    show              := Shows how the last puzzle was solved.

    dump              := Dump all solved puzzle cases held by this program.

    clear             := Clear puzzle cases from this program. This is done autonomously.

    help *[command]   := Shows commands or (optional) a command in more detail.

    exit              := exit this program. This can be entered at any point in the program.
)");

  while (console.is_running()) {
    console.SubmitToOutput("input> ");
    std::string cmd = cs420::GetInput();
    console.Input(cmd);
    console.SubmitToOutput("\n");
  }
  cs420::CleanupOutput();
  return 0;
}