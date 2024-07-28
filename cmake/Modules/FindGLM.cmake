# FindGLM.cmake: This file tries to locate the GLM library and its components

# Locate the GLM include directory
find_path(
    GLM_INCLUDE_DIR
    NAMES glm/glm.hpp
    PATH_SUFFIXES include
    PATHS /usr/local /usr /opt/local ${CMAKE_SOURCE_DIR}/external ENV PATH)

# Set the results to the cache
if(GLM_INCLUDE_DIR)
    set(GLM_FOUND TRUE)
    set(GLM_INCLUDE_DIR
        ${GLM_INCLUDE_DIR}
        CACHE PATH "GLM include directory")
    message(STATUS "Found GLM: ${GLM_INCLUDE_DIR}")
else()
    set(GLM_FOUND FALSE)
endif()

# Handle the QUIETLY and REQUIRED arguments
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    GLM
    REQUIRED_VARS GLM_INCLUDE_DIR
    FAIL_MESSAGE "Could not find GLM")

# Provide the variables for the include directory
mark_as_advanced(GLM_INCLUDE_DIR)
