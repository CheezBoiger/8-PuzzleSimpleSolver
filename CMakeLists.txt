cmake_minimum_required(VERSION 2.8.11)
project("CS420-P1")

if (CMAKE_VERSION VERSION_GREATER 3.0.2)
  cmake_policy(SET CMP0064 NEW)
endif()

set(AUTHOR        "Mario Garcia")
set(DUE_DATE      "4-30-2017")
set(PROJECT_NUM   1)
set(INSTRUCTOR    "Daisy Tang")


if (WIN32)
 # dunno
elseif(UNIX)
 #dunno
else()
 message(WARNING "build not garanteed to work on this system.")
endif()


add_subdirectory(Engine)
add_subdirectory(Source)


if (TEST)
  add_subdirectory(Tests)
endif()