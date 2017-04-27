// 8 Puzzle Solver Algorithm Assignment
// Assignment #1
// Author : Mario Garcia
// Class : CS 420
// Instructor : Dr. Daisy Tang
//
// Copyright (c) 2017 Mario Garcia, MIT License.
// Built with my cat Tom. mew...
#pragma once

#include <cstdint>

namespace pai {
// Simple Type defines for our library. We use these throughout the 
// Engine public and private source code. Readability is key when figuring
// out how optimal, and proficient, our library is going to be. This also 
// reduces the headaches of unknown precision when it comes to cross
// compatibility of data types that are specified differently on other
// compilers. 


typedef float         real32;
typedef double        real64;
typedef uint16_t      uint16;
typedef int16_t       int16;
typedef uint32_t      uint32;
typedef int32_t       int32;
typedef uint64_t      uint64;
typedef int64_t       int64;
typedef unsigned char byte;

typedef real32        single_precise_t;
typedef real64        double_precise_t;

typedef uint32        fast_uint32;
typedef int32         fast_int32;
typedef byte          uchar;
} // pai