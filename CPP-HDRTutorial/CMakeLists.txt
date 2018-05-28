cmake_minimum_required(VERSION 3.11)
project( hdr-tutorial )
set(EXECUTABLE_NAME ${PROJECT_NAME})
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( ${EXECUTABLE_NAME} hdr-tutorial.cpp )

add_custom_command(	TARGET ${EXECUTABLE_NAME} PRE_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/images $<TARGET_FILE_DIR:hdr-tutorial>)

target_link_libraries( ${EXECUTABLE_NAME} ${OpenCV_LIBS} )