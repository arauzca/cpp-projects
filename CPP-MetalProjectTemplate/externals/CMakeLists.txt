# Set the minimum CMake Version to 3.24.
cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

include(MACRO_GET_DIRECTORIES)
GET_DIRECTORIES(SUBDIRS * .)

# Process found applications.
foreach(SUBDIR ${SUBDIRS})
  if(EXISTS ${SUBDIR})
    add_subdirectory(${SUBDIR})
  endif()
endforeach()