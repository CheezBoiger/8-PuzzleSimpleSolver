# Implementation of the A* algorithm on the 8-Puzzle solver.
CS 420 - Project 1
Author: Mario Garcia
Class: CS420-01
Date Due: 4-30-2017
Language: C++ with C++11 standard
Professor: Dr. Fang "Daisy" Tang


# Note
Too much time was spend on designing this project program... grade suffered, but it was totally worth it... I think...sigh.

# Architecture
A small engine was created for the puzzle solving, while file parsing, as 
well as case testing are implemented in source. Much consideration was taken to write the solver with as much optimization as possible, or at least what I could do to make it optimal and fast.

# How to build
Of course, if you do not wish to build from scratch, this project folder already comes with a prebuilt version of the program, all you need to do is simply open the project up, depending on which OS and cpu architecture you are on, and double click the application:
  - If using Windows, the folder Prebuilt comes with already compiled executables (both for win32 and win64) Go to Prebuilt and find your folder of choice, then double click the exe.
  - If using Linux, a makefile is provided for you, along with the executable, traverse to the Folder Prebuilt and enter Linux-amd64, then type command "./PuzzleApp".

# Building from Scratch

The following software is optional, if you plan to build the project starting from the build scripts:
  
  - CMake (the latest version)

The following compilers are required in order to properly build this project.
  
  - Visual Studio 2013 and up (If using Windows I recommend 2015 and up)
  - GCC 4.8 and up (If using Linux)
  - LLVM is untested.

If on Windows, ensure you set your visual studio project to release mode, otherwise you will build the slower version of the project, with
all the windows debugging calls! It's really slow!

# Using the Program

To use the program, you have multiple choices:

  1. Input a puzzle yourself.
  2. Input a randomly generated puzzle to solve.
  3. Input a file name, which will run the puzzle solver for all cases inside.
  4. See the steps taken to solve the last puzzle you entered.
  5. See a table of the average search cost, and time taken to solve, for each depth you inputted.  

We understand having to know commands is perhaps a difficult journey to partake, lets break things down quick though:

  1. the command "solve file" will allow you to solve multiple puzzles that are stored inside a file (provided they are separated on new lines).
  2. the command "solve" will allow you to input a puzzle in the format x x x x x x x x x (spaces are not needed).
  3. the command "show" will let you see how the last puzzle was solved (this will let you see the steps taken).
  4. the command "dump" will let you see the number of cases you have tried to have this program solve. All puzzles solved will be recorded in a 
     database. "dump" will let you see the average cost (with the total test cases in parantheses) and time it took to solve these puzzles by depth.


Example commands to type:

  input> solve
  enter> 580362147
  
  ... Puzzle is solved ...

  input> show both
  ... shows the steps it took to solve the last puzzle ...

  input> dump
  ... look at the average cost and time it took to solve puzzles of certain depth ...

  input> solve file
  enter> 100cases.txt
  ... find the file, parse it, and solve all puzzles inside it ...
  input> dump
  ... show average solve case for that file and its data ...

  input> solve random
  ...   solves a randomly generated puzzle ...

  input> exit 
  ... exit the program ...


That's all there is to it!