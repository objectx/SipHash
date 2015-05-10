/*
 * main.cpp:
 *
 * Author(s): objectx
 */
#include "common.h"
#include "TestSipHash.h"
#include <SipHash.h>
#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

uint64_t from_string (const void *buf, size_t len) {
    size_t      l = std::min (len, static_cast<size_t> (8)) ;
    uint64_t    v = 0 ;

    const uint8_t *     p = static_cast<const uint8_t *> (buf) ;
    for (size_t i = 0 ; i < l ; ++i) {
        v |= static_cast<uint64_t> (p [i]) << (i * 8) ;
    }
    return v ;
}

int main (int argc, char* const argv []) {
    Catch::Session session ;    // There must be exactly once instance

    // writing to session.configData() here sets defaults
    // this is the preferred way to set them

    int returnCode = session.applyCommandLine (argc, argv) ;
    if (returnCode != 0) {
        // Indicates a command line error
        return returnCode ;
    }

    // writing to session.configData() or session.Config() here
    // overrides command line args
    // only do this if you know you need to

    return session.run () ;
}

/*
 * [END OF FILE]
 */
