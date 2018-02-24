#Build list of all CPP project directories
cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)


project(CPP_Projects VERSION 1.0 LANGUAGES CXX)


#Assume Debug builds as default
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()


if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	add_compile_options(${CMAKE_CXX_FLAGS_DEBUG})
	add_definitions(-D_DEBUG)
endif()


# setup CMAKE default search paths
set( SOURCE_DIR . )
set( CMAKE_MODULE_PATH_OLD "${CMAKE_MODULE_PATH}" )
set( CMAKE_MODULE_PATH     "${CMAKE_HOME_DIRECTORY}/_CMAKE;${CMAKE_MODULE_PATH}" )
set( OS_CMAKE_MODULES_PATH "/usr/local/opt/" )
set( REQUIRED_PACKAGES
  "assimp"
  "fltk"
  "glew"
  "glfw"
  "glm"
)

foreach(package ${REQUIRED_PACKAGES})
  set(FOUND_REQUIRED_PACKAGES ON CACHE BOOL "" FORCE)
  if(NOT EXISTS "${OS_CMAKE_MODULES_PATH}/${package}")
    message("Package \"${package}\" not installed using project packages.")
    set(FOUND_REQUIRED_PACKAGES OFF CACHE BOOL "" FORCE)
  endif()
endforeach()

if(FOUND_REQUIRED_PACKAGES)
  message("Found all required packages installed on OS, using them instead of the ones with this project")
else()
  set( CMAKE_PREFIX_PATH "${CMAKE_HOME_DIRECTORY}/_LIBS;${CMAKE_PREFIX_PATH}" )
endif()


# macro to force the build directory to be different from source directory
include(MACRO_ENSURE_OUT_OF_SOURCE_BUILD)
ENSURE_OUT_OF_SOURCE_BUILD("${PROJECT_NAME} requires an out of source build.")


# macro to loop over all project directories
include(MACRO_GET_DIRECTORIES)
GET_DIRECTORIES(PROJECTS CPP-* ${SOURCE_DIR})


if(APPLE)
  # we fix the min. deployment target platform version
  # (for convenience reasons) in the project settings of Xcode
  set(CMAKE_OSX_DEPLOYMENT_TARGET 10.13)
endif()

# Using Project's GLFW if not installed on OS
if(NOT FOUND_REQUIRED_PACKAGES)
  set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
  add_subdirectory("${CMAKE_HOME_DIRECTORY}/_LIBS/GLFW")
endif()


# process found applications
foreach(PROJECT ${PROJECTS})
	message("Found Subproject: " ${PROJECT})
	if(EXISTS ${PROJECT})
		add_subdirectory(${PROJECT})
	endif(EXISTS ${PROJECT})
endforeach(PROJECT ${PROJECTS})
