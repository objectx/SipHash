/*
 * SipHash.cpp:
 *
 * Author(s): objectx
 */
#include <algorithm>
#include <SipHash.hpp>
#include "internal.h"

namespace SipHash {

    uint_fast64_t   Compute (size_t cntCompression, size_t cntFinalization,
                             const IV &iv,
                             const void *data, size_t length) {
        uint_fast64_t   v0 = iv.K0 () ^ Internal::MASK_0 ;
        uint_fast64_t   v1 = iv.K1 () ^ Internal::MASK_1 ;
        uint_fast64_t   v2 = iv.K0 () ^ Internal::MASK_2 ;
        uint_fast64_t   v3 = iv.K1 () ^ Internal::MASK_3 ;

        const uint8_t * p = static_cast<const uint8_t *>(data) ;

        int_fast64_t    n = static_cast<int_fast64_t> (length) / 8 ;
        // Process full (== 64bits) blocks.
        for (int_fast64_t i = 0; i < n; ++i) {
            uint_fast64_t m = Internal::Read8 (&p[8 * i]) ;
            v3 ^= m ;
            for (int_fast32_t r = 0; r < cntCompression; ++r) {
                Internal::SipRound (v0, v1, v2, v3);
            }
            v0 ^= m ;
        }
        {
            uint_fast64_t   lastval = (static_cast<int_fast64_t>(length) & 0xFFu) << 56 ;
            int_fast64_t    remain  = static_cast<int_fast64_t>(length) - (8 * n) ;

            const uint8_t * q = &(p[8 * n]) ;
            for (int_fast64_t i = 0; i < remain; ++i) {
                lastval |= static_cast<uint_fast64_t>(q[i]) << (i * 8) ;
            }
            v3 ^= lastval ;
            for (int_fast32_t r = 0; r < cntCompression; ++r) {
                Internal::SipRound (v0, v1, v2, v3) ;
            }
            v0 ^= lastval ;
        }
        // Finalize
        {
            v2 ^= 0xFFu ;
            for (int_fast32_t r = 0; r < cntFinalization; ++r) {
                Internal::SipRound (v0, v1, v2, v3) ;
            }
        }
        return v0 ^ v1 ^ v2 ^ v3 ;
    }
}
/*
 * [END OF FILE]
 */
