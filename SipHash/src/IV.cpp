/*
 * IV.cpp: SipHash initial vector.
 *
 * Author(s): objectx
 */
#include <algorithm>
#include <SipHash.hpp>

namespace SipHash {

    iv_t MakeIV (const void *data, size_t size) {
        const uint8_t *const    p = static_cast<const uint8_t *>(data) ;

        uint_fast64_t   k_0 = 0 ;
        uint_fast64_t   k_1 = 0 ;
        {
            for (size_t i = 0, n = std::min<size_t> (size, 8); i < n; ++i) {
                k_0 |= static_cast<uint64_t> (p [i + 0]) << (8 * i) ;
            }
        }
        if (8 < size) {
            for (size_t i = 0, n = std::min<size_t> (size, 16) - 8; i < n; ++i) {
                k_1 |= static_cast<uint64_t> (p [i + 8]) << (8 * i) ;
            }
        }
        return iv_t { { k_0, k_1 } };
    }
}    /* end of [namespace SipHash] */

/*
 * [END OF FILE]
 */
