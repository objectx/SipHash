
cmake_minimum_required (VERSION 3.0)

include_directories ("${CMAKE_SOURCE_DIR}/SipHash/include" "${CMAKE_SOURCE_DIR}/Catch/include")

add_executable (TestSipHash src/main.cpp src/TestKey.cpp src/TestSipHash.cpp)
target_compile_features (TestSipHash PRIVATE cxx_auto_type)
target_link_libraries (TestSipHash SipHash)

add_test (NAME TestSipHash
          COMMAND TestSipHash)
