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
#include <string>

#if defined(_DEBUG)
 #define PAI_PRINT(str) std::cout << str << "\n"; 
 #define PAI_PRINTF(str, ...) std::printf(str, ## __VA_ARGS__);
#else
 #define PAI_PRINT(str)
 #define PAI_PRINTF(str, ...)
#endif // _DEBUG

namespace pai {


// Get the last error that was logged by this engine module.
// This helps in determining what went wrong with the method
// that the use may have done, or the program has done. Be sure
// to note what the error states is the issue, as it will clear 
// when this function is called.
std::string LastError();
} // pai