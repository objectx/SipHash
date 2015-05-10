/*
 * main.cpp:
 *
 * Author(s): objectx
 */
#include "common.h"
#include "TestSipHash.h"
#include <SipHash.h>
#include <Catch.hpp>

extern void TestKey () ;
extern void TestSipHash () ;

uint64_t from_string (const void *buf, size_t len) {
    size_t      l = std::min (len, static_cast<size_t> (8)) ;
    uint64_t    v = 0 ;

    const uint8_t *     p = static_cast<const uint8_t *> (buf) ;
    for (size_t i = 0 ; i < l ; ++i) {
        v |= static_cast<uint64_t> (p [i]) << (i * 8) ;
    }
    return v ;
}


int     main (int argc, char **argv) {
    TestKey () ;
    TestSipHash () ;
    return 0 ;
}

/*
 * [END OF FILE]
 */
