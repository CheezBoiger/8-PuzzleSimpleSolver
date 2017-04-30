cmake_minimum_required(VERSION 2.8.11)
project("CS420-P1")

if (CMAKE_VERSION VERSION_GREATER 3.0.2)
  cmake_policy(SET CMP0064 NEW)
endif()

set(AUTHOR        "Mario Garcia")
set(DUE_DATE      "4-30-2017")
set(PROJECT_NUM   1)
set(INSTRUCTOR    "Dr. Daisy Tang")
set(CASE_FILES   100cases.txt 200cases.txt)

option(TEST "" OFF)


if (WIN32)
 # dunno
elseif(UNIX)
 #dunno
else()
 message(WARNING "build not garanteed to work on this system.")
endif()


add_subdirectory(Engine)
add_subdirectory(Source)

file(COPY ${CASE_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Bin)
# Copy also into Source as well... If the user plans on testing from ide. UNIX is the same thing.
file(COPY ${CASE_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Source)

if (TEST)
  add_subdirectory(Tests)
endif()