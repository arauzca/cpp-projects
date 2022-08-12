# CMakeLists for the Project: OpenGLProjectTemplate.

# Set the minimum CMake Version to 3.20.
cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

# Set the project name and version.
project(OpenGLProjectTemplate VERSION 1.0)

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

# Check for Linux and make output path adjustments.
if ("${CMAKE_SYSTEM}" MATCHES "Linux.*")
  # Set the binary output path to correspond to windows defaults.
  set(EXECUTABLE_OUTPUT_PATH "${EXECUTABLE_OUTPUT_PATH}/${CMAKE_BUILD_TYPE}")
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

# find GLSL shaders files (let them show up in the IDEs)
file(GLOB GLSL
  resources/shaders/*.frag
  resources/shaders/*.vert
  resources/shaders/*.geom
  resources/shaders/*.tess
  resources/shaders/*.tecs
  resources/shaders/*.glsl)
source_group("glsl" FILES ${GLSL})


find_package(PkgConfig REQUIRED)

# TODO: find packages in a list.
find_package(ASSIMP)
if(NOT ASSIMP_FOUND)
  set(ASSIMP_LIBRARIES assimp)
endif()

find_package(FLTK)
if(NOT FLTK_FOUND)
  set(FLTK_LIBRARIES fltk)
endif()

find_package(glfw3)
set(GLFW_LIBRARY glfw)

find_package(GLM)
if(GLM_FOUND)
  set(GLM_LIBRARY glm::glm)
else()
  set(GLM_LIBRARY glm)
endif()

# Add external libraries.
set(EXTERN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/extern")
if(IS_DIRECTORY ${EXTERN_DIR})
  if(EXISTS "${EXTERN_DIR}/CMakeLists.txt" AND NOT EXISTS "${EXTERN_DIR}/ignore.cmake")
    add_subdirectory(${EXTERN_DIR})
  endif()
endif()

find_package(GLEW REQUIRED STATIC)

# find framework (specific to mac).
if (APPLE)
  find_library(COCOA_LIBRARY Cocoa)
  find_library(IOKIT_LIBRARY IOKit REQUIRED)
  find_library(COREVID_LIBRARY CoreVideo REQUIRED)
else ()
  set(COCOA_LIBRARY " ")
  set(IOKIT_LIBRARY " ")
  set(COREVID_LIBRARY " ")
endif ()


# Setup package headers.
include_directories(
  include
  ${ASSIMP_INCLUDE_DIRS}
  ${GLM_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  ${OPENGL_INCLUDE_DIR}
  ${GLEW_INCLUDE_DIRS})

# Force older GLM versions to use radians instead of degrees.
add_definitions(-DGLM_FORCE_RADIANS)

# Setup debug/release libraries.
set(LIBS_DEBUG)

set(LIBS_RELEASE)

# Define target dependencies and build instructions.
set(EXECUTABLE_NAME ${PROJECT_NAME})
set(CMAKE_FOLDER "APPS")
add_executable(${EXECUTABLE_NAME} ${SRCS} ${HDRS})
set_property(TARGET ${EXECUTABLE_NAME} PROPERTY CXX_STANDARD 20)

# Copy resources directory.
add_custom_command(TARGET ${EXECUTABLE_NAME}
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_CURRENT_SOURCE_DIR}/resources $<TARGET_FILE_DIR:OpenGLProjectTemplate>)

# Add framework (specific to mac).
target_link_libraries (${EXECUTABLE_NAME}
  ${OpenCV_LIBS}
  ${OPENGL_INCLUDE_DIR}
  ${ASSIMP_LIBRARIES}
  ${FLTK_LIBRARIES}
  GLEW::GLEW
  ${GLFW_LIBRARY}
  ${GLM_LIBRARY}
  ${COCOA_LIBRARY} ${COREVID_LIBRARY} ${IOKIT_LIBRARY})

add_dependencies(${EXECUTABLE_NAME} GLEW::GLEW ${GLFW_LIBRARY} ${GLM_LIBRARY} ${ASSIMP_LIBRARIES})
