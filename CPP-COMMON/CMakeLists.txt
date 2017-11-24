# Define library. Only source files here!
project(CommonLibraries VERSION 0.1)

file( GLOB SRCS
        ./src/util/*.cpp
        ./src/util/*.c
        ./src/SOIL2/*.cpp
        ./src/SOIL2/*.c)

add_library(libcommon SHARED
        ${SRCS})


# find packages and libs
find_package (PkgConfig REQUIRED)
find_package (OpenGL REQUIRED)
find_package (glfw3 REQUIRED NO_MODULE)
find_package (FLTK REQUIRED)
find_package (GLM REQUIRED)
find_package (GLEW REQUIRED STATIC)
find_package (ASSIMP REQUIRED)


# find framework (specific to mac)
if ( APPLE )
    find_library( COCOA_LIBRARY Cocoa )
    find_library( IOKIT_LIBRARY IOKit REQUIRED )
    find_library( COREVID_LIBRARY CoreVideo REQUIRED )
else()
    set( COCOA_LIBRARY " " )
    set( IOKIT_LIBRARY " " )
    set( COREVID_LIBRARY " " )
endif( APPLE )


# setup package headers
include_directories(
        ${OPENGL_INCLUDE_DIR}
        ${FLTK_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIR}
        ${GLM_INCLUDE_DIRS}
)


# force older GLM versions to use radians instead of degrees
add_definitions( -DGLM_FORCE_RADIANS )

# add framework (specific to mac)
target_link_libraries (libcommon
        glfw
        ${FLTK_LIBRARIES}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARY}
        ${COCOA_LIBRARY} ${COREVID_LIBRARY} ${IOKIT_LIBRARY})


# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
target_include_directories(libcommon PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)

# If we have compiler requirements for this library, list them
# here
set_property(TARGET libcommon PROPERTY CXX_STANDARD 17)
#target_compile_features(mem_mngr
#        PUBLIC cxx_auto_type
#        PRIVATE cxx_variadic_templates)

# for cmake_install.cmake:
#   DIRECTORY   the content (directories and files) of this directory will copied to the destination directory
#   DESTINATION if defined relative the full path will be ${CMAKE_INSTALL_PREFIX}/[DESTINATION]
install(DIRECTORY inc/ DESTINATION include/)
