cmake_minimum_required(VERSION 2.8.11)
project("CS420Project1-Log")


include_directories(
  ../../Engine/Include
)


add_executable(LogTest
  Main.cpp
)


target_link_libraries(LogTest PuzzleEngine)

install(TARGETS LogTest
  RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/Bin
)