# Set the minimum CMake Version to 3.24.
cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

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
  GIT_TAG        release-1.12.1)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

# enable_testing()
add_executable(${TEST_PROJECT_NAME})
target_sources(${TEST_PROJECT_NAME} PRIVATE ${SRCS})
target_link_libraries(${TEST_PROJECT_NAME} PUBLIC
  gtest_main
  gtest)

include(GoogleTest)
gtest_discover_tests(
  ${TEST_PROJECT_NAME}
  PROPERTIES TIMEOUT 600
  DISCOVERY_MODE PRE_TEST)