# CMakeLists for the Project: cpp-projects. Builds every project that starts with the
# prefix "CPP-" and each project needs to have its own CMakeLists-file.

cmake_minimum_required(VERSION 3.5...3.30 FATAL_ERROR)

if(APPLE)
    set(CMAKE_MACOSX_RPATH OFF)
endif()

# The FOLDER properties are needed in Visual Studio and XCode generated projects for
# nested folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "TEST")

# Policy correction.
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy((VERSION ${CMAKE_VERSION}))
endif()
message("CMAKE VERSION = ${CMAKE_VERSION}")

# Set the project name and version.
project(
    CPP_Projects
    VERSION 1.0.0
    DESCRIPTION "C++ Projects"
    LANGUAGES CXX)

# Specify the C++ standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_COMPILER /usr/bin/gcc)

# Assume Debug builds as default.
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Set up the CMake default search paths.
set(SOURCE_DIR .)
set(CMAKE_MODULE_PATH_OLD "${CMAKE_MODULE_PATH}")
set(CMAKE_MODULE_PATH
    "${CMAKE_HOME_DIRECTORY}/cmake;${CMAKE_HOME_DIRECTORY}/cmake/Modules;${CMAKE_MODULE_PATH}"
)

# Macro to force the build directory to be different from the source directory.
include(MACRO_ENSURE_OUT_OF_SOURCE_BUILD)
ensure_out_of_source_build("${PROJECT_NAME} requires an out of source build.")

# Macro to loop over all project directories.
include(MACRO_GET_DIRECTORIES)
get_directories(PROJECTS CPP-* ${SOURCE_DIR})

# Supported options.
option(BUILD_PROJECT_TESTS "Build project unit tests" ON)

# MacOS specific settings.
if(APPLE)
    message("Configuring XCode:")
    # Set the fixed min. deployment target platform version in the project settings of
    # XCode (for convenience reasons).
    set(CMAKE_OSX_DEPLOYMENT_TARGET 15.0)
    message("CMAKE_OSX_DEPLOYMENT_TARGET = ${CMAKE_OSX_DEPLOYMENT_TARGET}")

    set(CMAKE_SYSTEM_NAME "macOS")
    message("CMAKE_SYSTEM_NAME = ${CMAKE_SYSTEM_NAME}")

    set(CMAKE_APPLE_SILICON_PROCESSOR "arm64")
    message("CMAKE_APPLE_SILICON_PROCESSOR = ${CMAKE_APPLE_SILICON_PROCESSOR}")

    if(XCODE)
        set(CMAKE_XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER "ch.arauz.cpp-projects")
        message(
            "CMAKE_XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER = ${CMAKE_XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER}"
        )

        if(NOT CMAKE_XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY)
            set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY
                $ENV{CMAKE_XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY})
            message(
                "CMAKE_XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY = ${CMAKE_XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY}"
            )
        endif()

        if(NOT CMAKE_XCODE_ATTRIBUTE_DEVELOPMENT_TEAM)
            set(CMAKE_XCODE_ATTRIBUTE_DEVELOPMENT_TEAM
                $ENV{CMAKE_XCODE_ATTRIBUTE_DEVELOPMENT_TEAM})
            message(
                "CMAKE_XCODE_ATTRIBUTE_DEVELOPMENT_TEAM = ${CMAKE_XCODE_ATTRIBUTE_DEVELOPMENT_TEAM}"
            )
        endif()
    endif()
endif()

if(BUILD_PROJECT_TESTS)
    # enable_testing() should be called from the source directory root. Enables testing
    # for this directory and below.
    enable_testing()
endif()

# Intergrating externals dependencies.
message("Intergrating externals dependencies: ${CMAKE_HOME_DIRECTORY}/externals")
add_subdirectory("${CMAKE_HOME_DIRECTORY}/externals")

# Process found applications.
foreach(PROJECT ${PROJECTS})
    message("Found subproject: ${PROJECT}")
    if(EXISTS ${PROJECT})
        add_subdirectory(${PROJECT})
    endif()
    message(STATUS "Configuring subproject: ${PROJECT} done")
endforeach()
