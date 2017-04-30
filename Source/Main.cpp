// 8 Puzzle Solver Algorithm Assignment
// Assignment #1
// Author : Mario Garcia
// Class : CS 420
// Instructor : Dr. Fang "Daisy" Tang
//
// Copyright (c) 2017 Mario Garcia, MIT License.
// Built with my cat Tom. mew...
#include "Shell/Console.hpp"


int main(int c, char *arv[])
{
  // NOTE(Garcia): This is running a thread! Destroy when done!
  cs420::InitOutput();
  cs420::Console console;
  console.SubmitToOutput("Copyright (c) 2017 Kitten Solvers.\n\n");
  console.SubmitToOutput("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
  console.SubmitToOutput("Enter command \"help\" for how to use this program...\n");

  while (console.is_running()) {
    console.SubmitToOutput("input> ");
    std::string cmd = cs420::GetInput();
    console.Input(cmd);
    console.SubmitToOutput("\n\n");
  }
  cs420::CleanupOutput();
  return 0;
}