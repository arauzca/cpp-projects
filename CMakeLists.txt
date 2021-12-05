# CMakeLists for the Project: cpp-projects.
# Builds every project that starts with the prefix "CPP-" and
# each project needs to have its own CMakeLists-file.

# Set the minimum CMake Version to 3.20.
cmake_minimum_required( VERSION 3.20 FATAL_ERROR )

# Set the project name and version.
project( CPP_Projects VERSION 1.0 )

# Specify the C++ standard.
set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_STANDARD_REQUIRED True )

# Assume Debug builds as default.
if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Debug )
endif()

# Set up the CMake default search paths.
set( SOURCE_DIR . )
set( CMAKE_MODULE_PATH_OLD "${CMAKE_MODULE_PATH}" )
set( CMAKE_MODULE_PATH     "${CMAKE_HOME_DIRECTORY}/_CMAKE;${CMAKE_MODULE_PATH}" )
message( "CMAKE_MODULE_PATH = ${CMAKE_MODULE_PATH}" )
set( OS_CMAKE_MODULE_PATH "/usr/local/opt/" )

# Set the required packages for the projects.
set( REQUIRED_PACKAGES
  "assimp"
  "fltk"
  "glew"
  "glfw"
  "glm" )

foreach( package ${REQUIRED_PACKAGES} )
  set( FOUND_REQUIRED_PACKAGES ON CACHE BOOL "" FORCE )
  if( NOT EXISTS "${OS_CMAKE_MODULE_PATH}/${package}" )
    message( "Package \"${package}\" not installed, using project packages" )
    set( FOUND_REQUIRED_PACKAGES OFF CACHE BOOL "" FORCE )
  endif()
endforeach()

if( FOUND_REQUIRED_PACKAGES )
  message( "Found all required packages installed on OS, using them instead of the ones with this project" )
else()
  set( CMAKE_PREFIX_PATH "${CMAKE_HOME_DIRECTORY}/_LIBS;${CMAKE_PREFIX_PATH}" )
endif()

# Macro to force the build directory to be different from the source directory.
include( MACRO_ENSURE_OUT_OF_SOURCE_BUILD )
ENSURE_OUT_OF_SOURCE_BUILD( "${PROJECT_NAME} requires an out of source build." )

# Macro to loop over all project directories.
include( MACRO_GET_DIRECTORIES )
GET_DIRECTORIES( PROJECTS CPP-* ${SOURCE_DIR} )

# MacOS specific settings.
if( APPLE )
  # Set the fixed min. deployment target platform version
  # in the project settings of XCode (for convenience reasons).
  set( CMAKE_OSX_DEPLOYMENT_TARGET 12.0 )
  set( CMAKE_SYSTEM_NAME macOS )
  set( XCODE_CODESIGNIDENTITY "Apple Development: Carlos Arauz (Personal Team)" )
endif()

# Using project's GLFW if not installed on OS.
if( NOT FOUND_REQUIRED_PACKAGES )
  set( GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE )
  set( GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE )
  set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE )
  if ( EXISTS "${CMAKE_HOME_DIRECTORY}/_LIBS/GLFW" )
    add_subdirectory( "${CMAKE_HOME_DIRECTORY}/_LIBS/GLFW" )
    message( STATUS "GLFW_INCLUDE_DIRS = ${GLFW_INCLUDE_DIRS}" )
  else()
    message( "GLFW library was not found!" )
  endif()
endif()

# Process found applications.
foreach( PROJECT ${PROJECTS} )
  message( "Found subproject: ${PROJECT}" )
  if( EXISTS ${PROJECT} )
    add_subdirectory(${PROJECT})
  endif()
endforeach()

