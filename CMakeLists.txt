cmake_minimum_required(VERSION 3.10)
project(RSE)

option(BUILD_EXAMPLES "Build the examples" ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_subdirectory(src)

if (BUILD_EXAMPLES)
    add_subdirectory(example)
endif()
