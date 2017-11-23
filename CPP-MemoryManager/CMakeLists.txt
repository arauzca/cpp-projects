# At LEAST 2.8 but newer is better
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(MemoryManager VERSION 0.1 LANGUAGES CXX)

# Must use GNUInstallDirs to install libraries into correct
# locations on all platforms.
include(GNUInstallDirs)

set(MEM_MNGR_INCLUDE_DIR
${CMAKE_CURRENT_SOURCE_DIR}/libs/include)

# Targets that we develop here
enable_testing()
add_subdirectory(libs)

include_directories(${MEM_MNGR_INCLUDE_DIR})

file( GLOB SRCS
        ./src/*.c
        ./src/*.cpp)
source_group( "src" FILES ${SRCS} )

file( GLOB HDRS
        ./libs/include/*.h
        ./libs/include/*.hpp)
source_group( "inc" FILES ${HDRS} )

set(EXEC_NAME ${PROJECT_NAME})
add_executable(${EXEC_NAME} ${SRCS} ${HDRS})

set_property(TARGET ${EXEC_NAME} PROPERTY CXX_STANDARD 14)

# Define the libraries this project depends upon
target_link_libraries(${EXEC_NAME} mem_mngr)
ADD_DEPENDENCIES(${EXEC_NAME} mem_mngr)
