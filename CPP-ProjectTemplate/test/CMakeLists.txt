# Set the minimum CMake Version to 3.24.
cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

# Find sources.
file(GLOB SRCS
  "./src/test*.c"
  "./src/test*.cpp")
source_group("source" FILES ${SRCS})

add_executable(${TEST_PROJECT_NAME})
target_sources(${TEST_PROJECT_NAME} PRIVATE ${SRCS})

# Link GoogleTest libraries
# gtest:      library does not need a main() function.
#             Example: ./src/test.cpp
# gtest_main: library for tests with its own main() function.
#             Example: ./src/test-main.cpp
target_link_libraries(${TEST_PROJECT_NAME} PUBLIC
  gtest
  gtest_main)

include(GoogleTest)
gtest_discover_tests(
  ${TEST_PROJECT_NAME}
  PROPERTIES TIMEOUT 600
  DISCOVERY_MODE PRE_TEST)