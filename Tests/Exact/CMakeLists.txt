cmake_minimum_required(VERSION 2.8.11)
project("CS420Project1-Exact")


include_directories(
  ../../Engine/Include
)


add_executable(ExactTest
  Main.cpp
)

set_property(TARGET ExactTest PROPERTY CXX_STANDARD 11)
set_property(TARGET ExactTest PROPERTY CXX_STANDARD_REQUIRED 11)


target_link_libraries(ExactTest PuzzleEngine)

install(TARGETS ExactTest
  RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/Bin
)