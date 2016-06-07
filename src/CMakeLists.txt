
cmake_minimum_required (VERSION 3.5)

set (SOURCE_FILES IV.cpp SipHash.cpp SipHash_2_4.cpp SipHash_4_8.cpp)
set (HEADER_FILES internal.h ${SIPHASH_SOURCE_DIR}/include/SipHash.hpp)

add_library (SipHash ${SOURCE_FILES} ${HEADER_FILES})
    target_compile_features (SipHash PUBLIC cxx_auto_type cxx_alias_templates)
    target_include_directories (SipHash PUBLIC
            $<BUILD_INTERFACE:${SIPHASH_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>)
