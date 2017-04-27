# Copyright (c) Mario Garcia. MIT License.
cmake_minimum_required(VERSION 2.8.11)
project("CS420-PuzzleApplication")


set(PUZZLE_APPLICATION "PuzzleApp")
set(PUZZLE_CASE_DIR    Case)
set(PUZZLE_INPUT_DIR   Input)
set(PUZZLE_UTILITY_DIR Utility)
set(PUZZLE_SHELL_DIR   Shell)

include_directories(SYSTEM
  ../Engine/Include
)


set(INPUT_FILES
  ${PUZZLE_INPUT_DIR}/FileParser.cpp
  ${PUZZLE_INPUT_DIR}/FileParser.hpp
)

set(CASE_FILES
  ${PUZZLE_CASE_DIR}/CaseManager.hpp
  ${PUZZLE_CASE_DIR}/CaseManager.cpp
)

set(UTILITY_FILES
  ${PUZZLE_UTILITY_DIR}/Assert.hpp
  ${PUZZLE_UTILITY_DIR}/Logging.hpp
  ${PUZZLE_UTILITY_DIR}/Logging.cpp
)

set(SHELL_FILES
  ${PUZZLE_SHELL_DIR}/Console.hpp
  ${PUZZLE_SHELL_DIR}/Console.cpp
  ${PUZZLE_SHELL_DIR}/Interface.hpp 
)

set(APP_FILES
  ${CASE_FILES}
  ${INPUT_FILES}
  ${UTILITY_FILES}
  ${SHELL_FILES}
  Main.cpp
)

if (${CMAKE_CXX_COMPILER_ID})
  # Doing some stuff for organization.
  if (MSVC)
    foreach(source IN LISTS APP_FILES)
      get_filename_component(source_path "${source}" PATH)
      string(REPLACE "/" "\\" source_path_msvc "${source_path}")
      source_group("${source_path_msvc}" FILES "${source}")
    endforeach()
  endif()
endif()

add_executable(${PUZZLE_APPLICATION}
  ${APP_FILES}
)

set_property(TARGET ${PUZZLE_APPLICATION} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${PUZZLE_APPLICATION} PROPERTY CXX_STANDARD_REQUIRED ON)

install(TARGETS ${PUZZLE_APPLICATION}
  RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/Bin
  LIBRARY DESTINATION ${CMAKE_BINARY_DIR}/Lib
)

target_link_libraries(${PUZZLE_APPLICATION} PuzzleEngine)