cmake_minimum_required(VERSION 2.8.11)
project("CS420Project1-Log")


include_directories(
  ../../Engine/Include
)


add_executable(LogTest
  Main.cpp
)

set_property(TARGET LogTest PROPERTY CXX_STANDARD 11)
set_property(TARGET LogTest PROPERTY CXX_STANDARD_REQUIRED 11)


target_link_libraries(LogTest PuzzleEngine)

install(TARGETS LogTest
  RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/Bin
)