# CMakeLists for the Project: ProjectTemplate.

# Set the minimum CMake Version to 3.24.
cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

# Set the project name and version.
project(ProjectTemplate VERSION 1.0)

# Adjust some global CMake configuration settings.
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_COLOR_MAKEFILE TRUE)
set(CMAKE_SUPPRESS_REGENERATION TRUE)
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/bin")

if(CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_INSTALL_PREFIX "./install")
    set(CMAKE_INSTALL_PREFIX
        "${CMAKE_INSTALL_PREFIX}"
        CACHE STRING "Reset the configurations to what we need" FORCE)
endif()

if(CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_CONFIGURATION_TYPES Debug Release)
    set(CMAKE_CONFIGURATION_TYPES
        "${CMAKE_CONFIGURATION_TYPES}"
        CACHE STRING "Reset the configurations to what we need" FORCE)
endif()

# Check for Linux and make output path adjustments.
if("${CMAKE_SYSTEM}" MATCHES "Linux.*")
    # Set the binary output path to correspond to windows defaults.
    set(EXECUTABLE_OUTPUT_PATH "${EXECUTABLE_OUTPUT_PATH}/${CMAKE_BUILD_TYPE}")
endif()

# Find sources.
file(GLOB SRCS "./src/*.c" "./src/*.cpp")
source_group("source" FILES ${SRCS})

# Find headers (let them show up in the IDEs).
file(GLOB HDRS "./include/*.h" "./include/*.hpp")
source_group("include" FILES ${HDRS})

# Setup package headers.
include_directories("include")

# Setup debug/release libraries.
set(LIBS_DEBUG)

set(LIBS_RELEASE)

# Define target dependencies and build instructions.
set(EXECUTABLE_NAME ${PROJECT_NAME})
set(CMAKE_FOLDER "APPS")
add_executable(${EXECUTABLE_NAME} ${SRCS} ${HDRS})
target_link_libraries(${EXECUTABLE_NAME} ${LIBS_RELEASE} ${LIBS_DEBUG})

if(BUILD_PROJECT_TESTS)
    # Adding tests if available.
    include(FUNCTION_ADD_TESTS)
    add_tests("${CMAKE_CURRENT_SOURCE_DIR}/test")
endif()
