cmake_minimum_required(VERSION 2.8.11)
project("CS420Project1-Exact")


include_directories(
  ../../Engine/Include
)


add_executable(ExactTest
  Main.cpp
)


target_link_libraries(ExactTest PuzzleEngine)

install(TARGETS ExactTest
  RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/Bin
)