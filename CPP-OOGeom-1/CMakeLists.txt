# At LEAST 3.2 but newer is better
cmake_minimum_required( VERSION 3.10.0 FATAL_ERROR )
project( Aufgabe1 VERSION 0.1 LANGUAGES CXX )
set( EXECUTABLE_NAME ${PROJECT_NAME} )

# Add OpenCV Libraries
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# Must use GNUInstallDirs to install libraries into correct
# locations on all platforms.
include( GNUInstallDirs )

# find headers (let them show up in the IDEs)
file(GLOB HDRS
        ./inc/*.h
        ./inc/*.hpp
        )
source_group("inc" FILES ${HDRS})

include_directories(
        inc
)

# find sources
file( GLOB SRCS
        ./src/*.c
        ./src/*.cpp
        )
source_group("src" FILES ${SRCS})

# Targets that we develop here
enable_testing()
add_executable( ${EXECUTABLE_NAME}
                ${SRCS}
                ${HDRS} )

# CXX_STANDARD 17
set_property( TARGET ${EXECUTABLE_NAME} PROPERTY CXX_STANDARD 17 )

# Define the libraries this project depends upon
target_link_libraries( ${EXECUTABLE_NAME} ${OpenCV_LIBS} )
