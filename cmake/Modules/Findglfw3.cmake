# FindGLFW3.cmake: This file tries to locate GLFW3 library and its components

# Find the GLFW3 library
find_path(
    GLFW3_INCLUDE_DIR
    NAMES GLFW/glfw3.h
    PATH_SUFFIXES include
    PATHS /usr/local /usr /opt/local ENV PATH)

find_library(
    GLFW3_LIBRARY
    NAMES glfw glfw3
    PATH_SUFFIXES lib64 lib
    PATHS /usr/local /usr /opt/local ENV PATH)

# Set the results to the cache
if(GLFW3_INCLUDE_DIR AND GLFW3_LIBRARY)
    set(GLFW3_FOUND TRUE)
    set(GLFW3_INCLUDE_DIR
        ${GLFW3_INCLUDE_DIR}
        CACHE PATH "GLFW3 include directory")
    set(GLFW3_LIBRARY
        ${GLFW3_LIBRARY}
        CACHE FILEPATH "GLFW3 library")
    message(STATUS "Found glfw3: ${GLFW3_INCLUDE_DIR}")
else()
    set(GLFW3_FOUND FALSE)
endif()

# Handle the QUIETLY and REQUIRED arguments
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    glfw3
    REQUIRED_VARS GLFW3_INCLUDE_DIR GLFW3_LIBRARY
    FAIL_MESSAGE "Could not find GLFW3")

# Provide the variables for the library and the include directory
mark_as_advanced(GLFW3_INCLUDE_DIR GLFW3_LIBRARY)
