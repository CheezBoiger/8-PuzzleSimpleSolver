# Copyright (c) Mario Garcia. MIT License.
cmake_minimum_required(VERSION 2.8.11)
project("CS420-PuzzleEngine")

if (CMAKE_VERSION VERSION_GREATER 3.0)
  cmake_policy(SET CMP0064 NEW)
endif()

set(ENGINE_NAME                   "PuzzleEngine")
set(ENGINE_VERSION                0x001)
set(ENGINE_DIR                    ${CMAKE_CURRENT_SOURCE_DIR})
set(ENGINE_PUBLIC_DIR             Include/Engine)
set(ENGINE_PRIVATE_DIR            Source)
set(ENGINE_PRIVATE_FRONTIER_DIR   ${ENGINE_PRIVATE_DIR}/Frontier)
set(ENGINE_PUBLIC_ALGORITHMS_DIR  ${ENGINE_PUBLIC_DIR}/Algorithms)
set(ENGINE_PRIVATE_ALGORITHMS_DIR ${ENGINE_PRIVATE_DIR}/Algorithms)
set(ENGINE_PUBLIC_TOOLS_DIR       ${ENGINE_PUBLIC_DIR}/Tools)
set(ENGINE_PRIVATE_TOOLS_DIR      ${ENGINE_PRIVATE_DIR}/Tools)
set(ENGINE_PUBLIC_UTILS_DIR       ${ENGINE_PUBLIC_DIR}/Utils)
set(ENGINE_PRIVATE_UTILS_DIR      ${ENGINE_PRIVATE_DIR}/Utils)
set(ENGINE_PUBLIC_PLATFORM_DIR    ${ENGINE_PUBLIC_DIR}/Platform)

include_directories(SYSTEM
  ${ENGINE_PUBLIC_DIR}
)

set(ENGINE_MAIN
  ${ENGINE_PUBLIC_DIR}/PuzzleSolver.hpp
  ${ENGINE_PRIVATE_DIR}/PuzzleSolver.cpp
  ${ENGINE_PUBLIC_DIR}/Heuristic.hpp
  ${ENGINE_PRIVATE_DIR}/Heuristic.cpp
  ${ENGINE_PRIVATE_DIR}/StateTree.hpp
  ${ENGINE_PRIVATE_DIR}/StateNode.hpp
  ${ENGINE_PRIVATE_DIR}/StateTree.cpp
  ${ENGINE_PRIVATE_DIR}/StateNode.cpp
  ${ENGINE_PUBLIC_DIR}/Puzzle.hpp
  ${ENGINE_PRIVATE_DIR}/Puzzle.cpp
)


set(ENGINE_PLATFORM
  ${ENGINE_PUBLIC_PLATFORM_DIR}/Platform.hpp
  ${ENGINE_PUBLIC_PLATFORM_DIR}/Types.hpp
)

set(ENGINE_UTILS
  ${ENGINE_PUBLIC_UTILS_DIR}/Assertion.hpp
  ${ENGINE_PUBLIC_UTILS_DIR}/Log.hpp
  ${ENGINE_PRIVATE_UTILS_DIR}/Log.cpp
  ${ENGINE_PRIVATE_UTILS_DIR}/Error.cpp
  ${ENGINE_PRIVATE_UTILS_DIR}/Error.hpp
)

set(ENGINE_FRONTIER
  ${ENGINE_PRIVATE_FRONTIER_DIR}/Frontier.hpp
  ${ENGINE_PRIVATE_FRONTIER_DIR}/Frontier.cpp
)

set(ENGINE_ALGORITHMS
)

# Store all files into one glob.
set(ENGINE_FILES
  ${ENGINE_MAIN}
  ${ENGINE_PLATFORM}
  ${ENGINE_UTILS}
  ${ENGINE_FRONTIER}
  ${ENGINE_ALGORITHMS}
)

if (${CMAKE_CXX_COMPILER_ID})
  # Doing some stuff for organization.
  if (MSVC)
    foreach(source IN LISTS ENGINE_FILES)
      get_filename_component(source_path "${source}" PATH)
      string(REPLACE "/" "\\" source_path_msvc "${source_path}")
      source_group("${source_path_msvc}" FILES "${source}")
    endforeach()
  endif()
endif()


add_library(${ENGINE_NAME} STATIC
  ${ENGINE_FILES}
)

install(TARGETS ${ENGINE_NAME}
  LIBRARY DESTINATION ${CMAKE_BINARY_DIR}/Lib
  ARCHIVE DESTINATION ${CMAKE_BINARY_DIR}/Lib/Archives
)