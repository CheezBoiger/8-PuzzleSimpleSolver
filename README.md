# Implementation of the A* algorithm on the 8-Puzzle solver.
CS 420 - Project 1
Author: Mario Garcia
Class: CS420-01
Date Due: 4-30-2017
Language: C++ with C++11 standard
Professor: Dr. Daisy Tang

# Architecture
A small engine was created for the puzzle solving, while file parsing, as 
well as case testing are implemented in source. Much consideration was taken to write the solver with as much optimization as possible, or at least what I could do to make it optimal and fast.

# How to build
The following software is optional, if you plan to build the project starting from the build scripts:
  
  - CMake (the latest version)

The following compilers are required in order to properly build this project.
  
  - Visual Studio 2013 and up (If using Windows)
  - GCC 4.8 and up (If using Linux)

Of course, if you do not wish to build from scratch, this project folder already comes with a prebuilt version of the program, all you need to do is simply open the project up, depending on which OS you are on, and compile the project:
  - If using Windows, there is a .sln file in your bit version of choice. Double click and press Build Project once inside. Highly recommended you switch the build mode from "Debug" to "Release", as compiling in Debug mode will also keep in debug API calls from Windows SDK, causing slow performance (and I mean really slow if you plan on using puzzles with length 20) when running.
  - If using Linux, a makefile is provided for you, simply navigate to the folder "Linux" inside the Prebuilt folder and type the command "make" inside. This will build the project with the GCC compiler.


# Using the Program

To use the program, you have two choices:

  1. Input a puzzle yourself.
  2. Input a file name, which will run the puzzle solver for all cases inside.