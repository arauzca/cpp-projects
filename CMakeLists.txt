#Build list of all CPP project directories
cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)

project(CPP_Projects VERSION 0.1 LANGUAGES CXX)

#Assume Debug builds as default
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	add_compile_options(${CMAKE_CXX_FLAGS_DEBUG})
	add_definitions(-D_DEBUG)
endif()

# setup CMAKE default search paths
set(SOURCE_DIR .)
set(CMAKE_MODULE_PATH "${CMAKE_HOME_DIRECTORY}/_CMAKE;${CMAKE_MODULE_PATH}")

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

# process found applications
foreach(PROJECT ${PROJECTS})
	message("Found Subproject: " ${PROJECT})
	if(EXISTS ${PROJECT})
		add_subdirectory(${PROJECT})
	endif(EXISTS ${PROJECT})
endforeach(PROJECT ${PROJECTS})
