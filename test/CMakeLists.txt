
cmake_minimum_required (VERSION 3.5)

include_directories ("${CMAKE_SOURCE_DIR}/ext/Catch/include")

add_executable (TestSipHash TestKey.cpp TestSipHash.cpp main.cpp)
    target_compile_features (TestSipHash PRIVATE cxx_auto_type)
    target_link_libraries (TestSipHash PRIVATE SipHash)

add_test (NAME TestSipHash
          COMMAND TestSipHash -r compact)
