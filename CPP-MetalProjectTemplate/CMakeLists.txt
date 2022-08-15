# CMakeLists for the Project: MetalProjectTemplate.

# Set the minimum CMake Version to 3.24.
cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

# Set the project name and version.
project(MetalProjectTemplate VERSION 1.0)

# Adjust some global CMake configuration settings.
set(CMAKE_VERBOSE_MAKEFILE      TRUE)
set(CMAKE_COLOR_MAKEFILE        TRUE)
set(CMAKE_SUPPRESS_REGENERATION TRUE)
set(EXECUTABLE_OUTPUT_PATH      "${CMAKE_CURRENT_BINARY_DIR}/bin")

if(CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_INSTALL_PREFIX "./install")
  set(CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}" CACHE STRING "Reset the configurations to what we need" FORCE)
endif()

if(CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_CONFIGURATION_TYPES Debug Release)
  set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}" CACHE STRING "Reset the configurations to what we need" FORCE)
endif()

# Find sources.
file(GLOB SRCS
  ./src/*.c
  ./src/*.cpp)
source_group("source" FILES ${SRCS})

# Find headers (let them show up in the IDEs).
file(GLOB HDRS
  ./include/*.h
  ./include/*.hpp)
source_group("include" FILES ${HDRS})

set(MAKE_METAL_SINGLE_HEADER ON CACHE BOOL "")

# Add externals subdirectory.
add_subdirectory(externals)

# Define target dependencies and build instructions.
set(EXECUTABLE_NAME ${PROJECT_NAME})
set(CMAKE_FOLDER "APPS")
add_executable(${EXECUTABLE_NAME} ${SRCS} ${HDRS})
set_property(TARGET ${EXECUTABLE_NAME} PROPERTY CXX_STANDARD 17)
target_compile_definitions(${EXECUTABLE_NAME} PUBLIC ${METAL_CPP_COMPILE_DEFS})
target_link_libraries (${EXECUTABLE_NAME}
  METAL_CPP)
