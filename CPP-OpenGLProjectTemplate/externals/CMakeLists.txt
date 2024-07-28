# Set the minimum CMake Version to 3.24.
cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

set(ALLOW_DUPLICATE_CUSTOM_TARGETS FALSE)
include(FetchContent)

# A library to import and export various 3d-model-formats including scene-post-processing
# to generate missing render data.
if(NOT ASSIMP_FOUND)
    FetchContent_Declare(
        assimp
        GIT_REPOSITORY https://github.com/assimp/assimp.git
        GIT_TAG v5.4.2)

    set(BUILD_SHARED_LIBS
        OFF
        CACHE BOOL "" FORCE)
    set(ASSIMP_INSTALL
        OFF
        CACHE BOOL "" FORCE)
    set(ASSIMP_BUILD_TESTS
        OFF
        CACHE BOOL "" FORCE)
    set(ASSIMP_INSTALL_PDB
        OFF
        CACHE BOOL "" FORCE)

    FetchContent_MakeAvailable(assimp)
endif()

if(NOT FLTK_FOUND)
    FetchContent_Declare(
        fltk
        GIT_REPOSITORY https://github.com/fltk/fltk.git
        GIT_TAG release-1.3.9)

    set(OPTION_USE_SYSTEM_LIBPNG
        OFF
        CACHE BOOL "" FORCE)

    set(OPTION_USE_SYSTEM_LIBJPEG
        OFF
        CACHE BOOL "" FORCE)

    set(FLTK_BUILD_FLUID
        OFF
        CACHE BOOL "" FORCE)

    set(FLTK_BUILD_TEST
        OFF
        CACHE BOOL "" FORCE)

    FetchContent_MakeAvailable(fltk)
endif()

# A multi-platform library for OpenGL, OpenGL ES, Vulkan, window and input
# http://www.glfw.org/
if(NOT GLFW3_FOUND)
    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.3.10)

    set(GLFW_BUILD_DOCS
        OFF
        CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS
        OFF
        CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES
        OFF
        CACHE BOOL "" FORCE)

    FetchContent_MakeAvailable(glfw)
endif()

if(NOT GLM_FOUND)
    FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.1)

    FetchContent_MakeAvailable(glm)
endif()

FetchContent_Declare(
    gl3w
    GIT_REPOSITORY https://github.com/skaslev/gl3w.git
    GIT_TAG origin/master)

FetchContent_MakeAvailable(gl3w)

# https://devblogs.nvidia.com/linking-opengl-server-side-rendering/
find_package(OpenGL REQUIRED COMPONENTS OpenGL)
