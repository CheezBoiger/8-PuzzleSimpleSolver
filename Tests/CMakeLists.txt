cmake_minimum_required(VERSION 2.8.11)
project("CS420Project1-Tests")


set(EXACT_FOLDER_TEST Exact)
set(STRESS_FOLDER_TEST Stress)
set(LOGGING_FOLDER_TEST Logging)

add_subdirectory(Exact)
add_subdirectory(Logging)