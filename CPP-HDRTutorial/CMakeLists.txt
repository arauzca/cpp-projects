cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project( hdr-tutorial VERSION 0.1 LANGUAGES CXX)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

set( EXECUTABLE_NAME ${PROJECT_NAME} )
add_executable( ${EXECUTABLE_NAME} hdr-tutorial.cpp )

add_custom_command(	TARGET ${EXECUTABLE_NAME} PRE_BUILD
										COMMAND ${CMAKE_COMMAND} -E copy_directory
										${CMAKE_CURRENT_SOURCE_DIR}/images $<TARGET_FILE_DIR:hdr-tutorial>)

set_property( TARGET ${EXECUTABLE_NAME} PROPERTY CXX_STANDARD 17 )
target_link_libraries( ${EXECUTABLE_NAME} ${OpenCV_LIBS} )
