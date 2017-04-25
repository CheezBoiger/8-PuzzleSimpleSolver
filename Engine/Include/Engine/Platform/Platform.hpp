// 8 Puzzle Solver Algorithm Assignment
// Assignment #1
// Author : Mario Garcia
// Class : CS 420
// Instructor : Dr. Daisy Tang
//
// Copyright (c) 2017 Mario Garcia, MIT License.
// Built with my cat Tom. mew...
#pragma once

#define PAI_DISALLOW_COPY_AND_ASSIGN(obj) \
  obj(const obj &a) = delete; \
  obj &operator=(const obj &a) = delete;


#define PAI_UNKNOWN  -1
#define PAI_WINDOWS   0
#define PAI_LINUX     1
#define PAI_APPLE     2

#define unlikely(expr) !expr

#if defined(_WIN32)
 #define PAI_TARGET_OS PAI_WINDOWS
 #define PAI_FORCEINLINE __forceinline
#elif defined(__linux__) || defined(__UNIX__)
 #define PAI_TARGET_OS PAI_LINUX
 // Chances of using GNU GCC?
 #define PAI_FORCEINLINE __attribute__(always_inline)
#elif defined(__APPLE__) && defined(__MACH__)
 #define PAI_TARGET_OS PAI_APPLE
 #define PAI_FORCEINLINE
#else
 #error "This operating system is unsupported for this engine."
#endif // win32