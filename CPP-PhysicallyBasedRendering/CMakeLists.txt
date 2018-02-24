# CMake file for Physically Based Rendering Project
cmake_minimum_required( VERSION 3.10.0 FATAL_ERROR )


# Name and version of the project
project( PBR VERSION 1.0 )


# adjust some global CMake configuration settings
set( CMAKE_VERBOSE_MAKEFILE       TRUE )
set( CMAKE_COLOR_MAKEFILE         TRUE )
set( CMAKE_SUPPRESS_REGENERATION  TRUE )
set( EXECUTABLE_OUTPUT_PATH       "${CMAKE_CURRENT_BINARY_DIR}/bin" )

# setup package root directories
if(FOUND_REQUIRED_PACKAGES)
  set( CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH_OLD};/usr/local/lib/cmake" )
  set( CMAKE_PREFIX_PATH "/usr/local/lib/cmake/glfw3;${CMAKE_PREFIX_PATH}" )
  set( CMAKE_PREFIX_PATH "/usr/local/lib/cmake/assimp-4.1;${CMAKE_PREFIX_PATH}" )
  unset( FLTK_ROOT_DIR )
  unset( GLEW_ROOT_DIR )
  unset( GLM_ROOT_DIR )
  unset( ASSIMP_ROOT_DIR )
else()
  set( GLEW_ROOT_DIR "${CMAKE_HOME_DIRECTORY}/_LIBS/GLEW" )
  set( GLM_ROOT_DIR  "${CMAKE_HOME_DIRECTORY}/_LIBS/GLM" )
endif()

if( WIN32 )
    if( MSVC )
        add_definitions( -DGLEW_STATIC )
        set( CMAKE_EXE_LINKER_FLAGS_RELEASE "/INCREMENTAL:NO ${CMAKE_EXE_LINKER_FLAGS}" )
        set( CMAKE_EXE_LINKER_FLAGS_DEBUG   "/DEBUG /NODEFAULTLIB:MSVCRT ${CMAKE_EXE_LINKER_FLAGS}" )
    endif( MSVC )
endif( WIN32 )


if( CMAKE_CONFIGURATION_TYPES )
    set( CMAKE_INSTALL_PREFIX ./install )
    set( CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}" CACHE STRING
                              "Reset the configurations to what we need"
                              FORCE )
endif( CMAKE_CONFIGURATION_TYPES )

if( CMAKE_CONFIGURATION_TYPES )
    set( CMAKE_CONFIGURATION_TYPES Debug Release )
    set( CMAKE_CONFIGURATION_TYPES  "${CMAKE_CONFIGURATION_TYPES}" CACHE STRING
                                    "Reset the configurations to what we need"
                                    FORCE )
endif( CMAKE_CONFIGURATION_TYPES )


# configure the Visual Studio user file
if( WIN32 )
    if( MSVC )
        # find user and system name
        set( VC_USER_SYSTEM_NAME $ENV{USERDOMAIN} CACHE STRING SystemName )
        set( VC_USER_USER_NAME $ENV{USERNAME}     CACHE STRING UserName )

        # configure the template file
        set( USER_FILE    ${PROJECT_NAME}.vcxproj.user )
        set( OUTPUT_PATH  ${CMAKE_CURRENT_BINARY_DIR}/${USER_FILE} )

        # setup working directories in template file
        set( USERFILE_WORKING_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin/Debug )
        set( USERFILE_WORKING_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin/Release )
        set( USERFILE_ARGUMENTS_RELEASE "" )
        set( USERFILE_ARGUMENTS_DEBUG "" )
        configure_file(${CMAKE_HOME_DIRECTORY}/_CMAKE/CG-PROJECTS.vcxproj.usertemplate ${OUTPUT_PATH} @ONLY )
    endif( MSVC )
endif( WIN32 )


# check for Linux and make output path adjustments
if ( "${CMAKE_SYSTEM}" MATCHES "Linux.*" )
    #Set the binary output path to correspond to windows defaults
    set( EXECUTABLE_OUTPUT_PATH "${EXECUTABLE_OUTPUT_PATH}/${CMAKE_BUILD_TYPE}" )
endif( "${CMAKE_SYSTEM}" MATCHES "Linux.*" )


# find sources
file( GLOB SRCS
        ../_COMMON/src/*.c
        ../_COMMON/src/*.cpp
        ./src/*.c
        ./src/*.cpp
        ./src/SOIL2/*.c
        ./src/SOIL2/*.cpp
        )
source_group( "src" FILES ${SRCS} )


# find headers (let them show up in the IDEs)
file( GLOB HDRS
        ../CPP-COMMON/inc/util/*.h
        ../CPP-COMMON/inc/util/*.hpp
        ../CPP-COMMON/inc/SOIL2/*.h
        ../CPP-COMMON/inc/SOIL2/*.hpp
        ./inc/*.h
        ./inc/*.hpp
        )
source_group( "inc" FILES ${HDRS} )


# find GLSL shaders files (let them show up in the IDEs)
file( GLOB GLSL
        resources/shaders/*.frag
        resources/shaders/*.vert
        resources/shaders/*.geom
        resources/shaders/*.tess
        resources/shaders/*.tecs
        resources/shaders/*.glsl
        )
source_group( "glsl" FILES ${GLSL} )


# find packages and libs
if(FOUND_REQUIRED_PACKAGES)
  find_package(PkgConfig REQUIRED)
  find_package(glfw3     REQUIRED NO_MODULE)
endif()

find_package(OpenGL    REQUIRED)
find_package(GLEW      REQUIRED STATIC)
find_package(GLM       REQUIRED)


# find framework (specific to mac)
if ( APPLE )
    find_library( COCOA_LIBRARY Cocoa )
    find_library( IOKIT_LIBRARY IOKit REQUIRED )
    find_library( COREVID_LIBRARY CoreVideo REQUIRED )
else ()
    set( COCOA_LIBRARY " " )
    set( IOKIT_LIBRARY " " )
    set( COREVID_LIBRARY " " )
endif ( APPLE )


# setup package headers
include_directories(
        ${OPENGL_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIRS}
        ${GLM_INCLUDE_DIRS}
        ${GLFW_INCLUDE_DIRS}
)


# force older GLM versions to use radians instead of degrees
add_definitions( -DGLM_FORCE_RADIANS )


# define target dependencies and build instructions
set(EXECUTABLE_NAME ${PROJECT_NAME})
add_executable(${EXECUTABLE_NAME} ${SRCS} ${HDRS} ${GLSL})
set_property(TARGET ${EXECUTABLE_NAME} PROPERTY CXX_STANDARD 17)


# copy resources directory
add_custom_command( TARGET ${EXECUTABLE_NAME}
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_CURRENT_SOURCE_DIR}/resources $<TARGET_FILE_DIR:PBR>)


# add framework (specific to mac)
target_link_libraries (${EXECUTABLE_NAME}
        commonlibs
        glfw
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARY}
        ${COCOA_LIBRARY} ${COREVID_LIBRARY} ${IOKIT_LIBRARY})
add_dependencies(${EXECUTABLE_NAME} commonlibs glfw)
