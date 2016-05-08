
cmake_minimum_required (VERSION 3.5)

project (SIPHASH
         VERSION 1.0.0
         LANGUAGES CXX)

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

enable_testing ()

add_subdirectory (SipHash)
add_subdirectory (TestSipHash)
