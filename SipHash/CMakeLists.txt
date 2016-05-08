
cmake_minimum_required (VERSION 3.5)

set (SOURCE_FILES src/IV.cpp src/SipHash.cpp src/SipHash_2_4.cpp src/SipHash_4_8.cpp)
set (HEADER_FILES ${SIPHASH_SOURCE_DIR}/SipHash/include/SipHash.h)

add_library (SipHash ${SOURCE_FILES} ${HEADER_FILES})
    target_include_directories (SipHash PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>)
