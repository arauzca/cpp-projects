# locate header files and put user specified location at beginning of search
if(ASSIMP_ROOT_DIR)
    set(_GLEW_HEADER_SEARCH_DIRS "${ASSIMP_ROOT_DIR}"
                                "${ASSIMP_ROOT_DIR}/include"
                                 ${_ASSIMP_HEADER_SEARCH_DIRS})
endif(ASSIMP_ROOT_DIR)

find_path(ASSIMP_INCLUDE_DIR "assimp/Importer.hpp" PATHS ${_GLEW_HEADER_SEARCH_DIRS})

if(APPLE)
   message("ASSIMP using mac libs")
   set(ASSIMP_ROOT_DIR "${CMAKE_SOURCE_DIR}/_LIBS/ASSIMP")
   set(ASSIMP_INCLUDE_DIR "${ASSIMP_ROOT_DIR}/include")

   set(ASSIMP_LIBRARIES_PATH "${ASSIMP_ROOT_DIR}/lib/mac")

   set(ASSIMP_LIBRARY "${ASSIMP_LIBRARIES_PATH}/libIrrXML.a")
   set(ASSIMP_LIBRARY_DEBUG "${ASSIMP_LIBRARIES_PATH}/libIrrXML.a")
endif()

# handle the QUIETLY and REQUIRED arguments and set ASSIMP_FOUND to TRUE if all listed variables are TRUE
include("FindPackageHandleStandardArgs")
FIND_PACKAGE_HANDLE_STANDARD_ARGS(ASSIMP DEFAULT_MSG ASSIMP_LIBRARY ASSIMP_LIBRARY_DEBUG ASSIMP_INCLUDE_DIR)

if(ASSIMP_FOUND)
   set(ASSIMP_INCLUDE_DIRS ${GLEW_INCLUDE_DIR})
   set(ASSIMP_LIBRARIES ${GLEW_LIBRARY})
   set(ASSIMP_LIBRARIES_DEBUG ${GLEW_LIBRARY_DEBUG})
endif(ASSIMP_FOUND)
