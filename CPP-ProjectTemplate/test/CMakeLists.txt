# Set the minimum CMake Version to 3.20.
cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

# Test project: <ProjectName>Tests
project(${TEST_PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)

# Find sources.
file(GLOB SRCS
  "./src/test*.c"
  "./src/test*.cpp")
source_group("source" FILES ${SRCS})


include(FetchContent)

# ------------------------------------------------------------------------------
# Unit testing library for the C++ programming language, based on the xUnit
# architecture.
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${SRCS})
target_link_libraries(${PROJECT_NAME} PRIVATE gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})