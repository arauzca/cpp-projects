# locate header files and put user specified location at beginning of search
message( "USING PROJECT ASSIMP" )

if( ASSIMP_ROOT_DIR )
  set( _ASSIMP_HEADER_SEARCH_DIRS
    "${ASSIMP_ROOT_DIR}"
    "${ASSIMP_ROOT_DIR}/include"
    ${_ASSIMP_HEADER_SEARCH_DIRS} )
endif()

find_path( ASSIMP_INCLUDE_DIR "assimp/Importer.hpp" PATHS ${_ASSIMP_HEADER_SEARCH_DIRS} )

if( WIN32 )
  message( "ASSIMP using WIN32 libs" )
  set( ASSIMP_LIBRARIES_PATH "${ASSIMP_ROOT_DIR}/lib/win" )

  set( ASSIMP_LIBRARY        "${ASSIMP_LIBRARIES_PATH}/assimp-vc140-mt.lib" )
  set( ASSIMP_STATIC_LIBRARY "${ASSIMP_LIBRARIES_PATH}/zlibstaticd.lib" )

  set( ASSIMP_LIBRARY_DEBUG  "${ASSIMP_LIBRARIES_PATH}/assimp-vc140-mt.lib" )
endif()


if( APPLE )
  message( "ASSIMP using MAC libs" )
  set( ASSIMP_ROOT_DIR "${CMAKE_SOURCE_DIR}/_LIBS/ASSIMP" )
  set( ASSIMP_INCLUDE_DIR "${ASSIMP_ROOT_DIR}/include" )

  set( ASSIMP_LIBRARIES_PATH "${ASSIMP_ROOT_DIR}/lib/mac" )

  set( ASSIMP_LIBRARY "${ASSIMP_LIBRARIES_PATH}/libassimp.dylib" )
  set( ASSIMP_LIBRARY_DEBUG "${ASSIMP_LIBRARIES_PATH}/libassimp.dylib" )

  set( ASSIMP_STATIC_LIBRARY "" )
endif()

# handle the QUIETLY and REQUIRED arguments and set ASSIMP_FOUND to TRUE if all listed variables are TRUE
include( "FindPackageHandleStandardArgs" )
FIND_PACKAGE_HANDLE_STANDARD_ARGS( ASSIMP DEFAULT_MSG ASSIMP_LIBRARY ASSIMP_STATIC_LIBRARY ASSIMP_LIBRARY_DEBUG ASSIMP_INCLUDE_DIR )

if( ASSIMP_FOUND )
  set( ASSIMP_INCLUDE_DIRS ${ASSIMP_INCLUDE_DIR} )
  set( ASSIMP_LIBRARIES ${ASSIMP_LIBRARY} ${ASSIMP_STATIC_LIBRARY} )
  set( ASSIMP_LIBRARIES_DEBUG ${ASSIMP_LIBRARY_DEBUG} )
  message( STATUS "ASSIMP_INCLUDE_DIRS = ${ASSIMP_INCLUDE_DIRS}" )
else()
  message( "ASSIMP library was not found!" )
endif()
