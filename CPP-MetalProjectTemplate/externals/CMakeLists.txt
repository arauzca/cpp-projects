# Set the minimum CMake Version to 3.24.
cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

set(ALLOW_DUPLICATE_CUSTOM_TARGETS FALSE)
include(FetchContent)

# Get the cmake-metal-cpp project.
FetchContent_Declare(
        metal-cpp
        GIT_REPOSITORY https://github.com/arauzca/cmake-metal-cpp.git
        GIT_TAG v1.0.0)

# Disable beta metal-cpp.
set(ENABLE_BETA
    OFF
    CACHE BOOL "" FORCE)

# Single header file.
set(MAKE_METAL_SINGLE_HEADER
    ON
    CACHE BOOL "" FORCE)

# Include extension: AppKit.
set(INCLUDE_APPKIT_EXTENSION
    ON
    CACHE BOOL "" FORCE)

# Include extension: MetalKit.
set(INCLUDE_METALKIT_EXTENSION
    ON
    CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(metal-cpp)
