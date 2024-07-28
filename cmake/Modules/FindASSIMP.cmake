# FindASSIMP.cmake: This file tries to locate the Assimp library and its components

# Locate the Assimp include directory
find_path(
    ASSIMP_INCLUDE_DIR
    NAMES assimp/Importer.hpp
    PATH_SUFFIXES include
    PATHS /usr/local /usr /opt/local ${CMAKE_SOURCE_DIR}/external ENV PATH)

# Locate the Assimp library
find_library(
    ASSIMP_LIBRARY
    NAMES assimp
    PATH_SUFFIXES lib64 lib
    PATHS /usr/local /usr /opt/local ${CMAKE_SOURCE_DIR}/external ENV PATH)

# Set the results to the cache
if(ASSIMP_INCLUDE_DIR AND ASSIMP_LIBRARY)
    set(ASSIMP_FOUND TRUE)
    set(ASSIMP_INCLUDE_DIR
        ${ASSIMP_INCLUDE_DIR}
        CACHE PATH "Assimp include directory")
    set(ASSIMP_LIBRARY
        ${ASSIMP_LIBRARY}
        CACHE FILEPATH "Assimp library")
    message(STATUS "Found ASSIMP: ${ASSIMP_INCLUDE_DIR}")
else()
    set(ASSIMP_FOUND FALSE)
endif()

# Handle the QUIETLY and REQUIRED arguments
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    ASSIMP
    REQUIRED_VARS ASSIMP_INCLUDE_DIR ASSIMP_LIBRARY
    FAIL_MESSAGE "Could not find Assimp")

# Provide the variables for the library and the include directory
mark_as_advanced(ASSIMP_INCLUDE_DIR ASSIMP_LIBRARY)
