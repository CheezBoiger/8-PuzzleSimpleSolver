// 8 Puzzle Solver Algorithm Assignment
// Assignment #1
// Author : Mario Garcia
// Class : CS 420
// Instructor : Dr. Daisy Tang
//
// Copyright (c) 2017 Mario Garcia, MIT License.
// Built with my cat Tom. mew...
#pragma once

#include <iostream>


#if defined(_DEBUG)
 #define PAI_PRINT(str) std::cout << str << "\n"; 
 #define PAI_PRINTF(str, ...) std::printf(str, ## __VA_ARGS__);
#else
 #define PAI_PRINT(str)
 #define PAI_PRINTF(str, ...)
#endif // _DEBUG