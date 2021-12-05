# CMakeLists for the Project: ProjectTemplate.

# Set the minimum CMake Version to 3.20.
cmake_minimum_required( VERSION 3.20 FATAL_ERROR )

# Set the project name and version.
project( ProjectTemplate VERSION 1.0 )

# Adjust some global CMake configuration settings.
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_COLOR_MAKEFILE TRUE)
set(CMAKE_SUPPRESS_REGENERATION TRUE)
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/bin")
set(CMAKE_PREFIX_PATH "${CMAKE_HOME_DIRECTORY}/_LIBS;${CMAKE_PREFIX_PATH}")

if(CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_INSTALL_PREFIX ./install)
  set(CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}" CACHE STRING "Reset the configurations to what we need" FORCE)
endif()

if(CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_CONFIGURATION_TYPES Debug Release)
    set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}" CACHE STRING "Reset the configurations to what we need" FORCE)
endif()

# Configure the Visual Studio user file.
if(WIN32)
  if(MSVC)
    # Find user and system name.
    set(VC_USER_SYSTEM_NAME $ENV{USERDOMAIN} CACHE STRING SystemName)
    set(VC_USER_USER_NAME $ENV{USERNAME} CACHE STRING UserName)

    # Configure the template file.
    set(USER_FILE ${PROJECT_NAME}.vcxproj.user)
    set(OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/${USER_FILE})

    # Setup working directories in template file.
    set(USERFILE_WORKING_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin/Debug)
    set(USERFILE_WORKING_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin/Release)
    set(USERFILE_ARGUMENTS_RELEASE "")
    set(USERFILE_ARGUMENTS_DEBUG "")
    configure_file(${CMAKE_HOME_DIRECTORY}/_CMAKE/CPP-PROJECTS.vcxproj.usertemplate ${OUTPUT_PATH} @ONLY)
  endif(MSVC)
endif(WIN32)

# Check for Linux and make output path adjustments.
if ("${CMAKE_SYSTEM}" MATCHES "Linux.*")
  # Set the binary output path to correspond to windows defaults.
  set(EXECUTABLE_OUTPUT_PATH "${EXECUTABLE_OUTPUT_PATH}/${CMAKE_BUILD_TYPE}")
endif()

# Find sources.
file(GLOB SRCS
    ./sources/*.c
    ./sources/*.cpp)
source_group("sources" FILES ${SRCS})

# Find headers (let them show up in the IDEs).
file(GLOB HDRS
    ./include/*.h
    ./include/*.hpp)
source_group("include" FILES ${HDRS})

# Find packages and libs:

# Setup package headers.
include_directories(
  include)

# Setup debug/release libraries.
set(LIBS_DEBUG
)

set(LIBS_RELEASE
)

# Define target dependencies and build instructions.
set(EXECUTABLE_NAME ${PROJECT_NAME})
add_executable(${EXECUTABLE_NAME} ${SRCS} ${HDRS})
target_link_libraries(${EXECUTABLE_NAME} ${LIBS_RELEASE} ${LIBS_DEBUG})
