/*
 * SipHash.h: Implements SipHash.
 *
 * Author(s): objectx
 */
#pragma once
#ifndef siphash_hpp__818E62D2_123A_4477_B550_25D22685FD72
#define siphash_hpp__818E62D2_123A_4477_B550_25D22685FD72   1

#include <sys/types.h>
#include <stdint.h>
#include <array>

namespace SipHash {
    /** The key to create initial vector */
    using iv_t = std::array<uint64_t, 2> ;

    /**
     * Constructs the InitialVector from data [0..(size - 1)]
     */
    iv_t    MakeIV (const void *data, size_t size) ;

    /**
     * Generic version of SipHash.
     *
     * @param cntCompression
     *               # of compression round.
     * @param cntFinalization
     *               # of finalization round.
     * @param iv     The initial vector.
     * @param data   Data to compute the hash.
     * @param length # of bytes to process.
     *
     * @return Computed hash.
     */
    uint_fast64_t   Compute ( size_t cntCompression
                            , size_t cntFinalization
                            , const iv_t &iv
                            , const void *data
                            , size_t length);

    /** Equivalent to Compute (2, 4, iv, data, length). */
    uint_fast64_t   Compute_2_4 ( const iv_t &iv
                                , const void *data
                                , size_t length);

    /** Equivalent to Compute (4, 8, iv, data, length). */
    uint_fast64_t   Compute_4_8 ( const iv_t &iv
                                , const void *data
                                , size_t length);
}    /* end of [namespace SipHash] */

#endif	/* siphash_hpp__818E62D2_123A_4477_B550_25D22685FD72 */
/*
 * [END OF FILE]
 */
