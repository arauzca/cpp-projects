# Define library. Only source files here!
project(MyLibrary VERSION 0.1 LANGUAGES CXX)

add_library(mem_mngr SHARED
        src/MemMngr.cpp)

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
target_include_directories(mem_mngr PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)

# If we have compiler requirements for this library, list them
# here
set_property(TARGET mem_mngr PROPERTY CXX_STANDARD 14)
#target_compile_features(mem_mngr
#        PUBLIC cxx_auto_type
#        PRIVATE cxx_variadic_templates)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
