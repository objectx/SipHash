
cmake_minimum_required (VERSION 3.0)

set (SOURCE_FILES src/IV.cpp src/SipHash.cpp src/SipHash_2_4.cpp src/SipHash_4_8.cpp)

add_library (SipHash ${SOURCE_FILES})
target_include_directories (SipHash PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)
