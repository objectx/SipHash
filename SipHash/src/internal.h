/*
 * internal.h:
 *
 * Author(s): objectx
 */
#ifndef internal_h__2adc4b88454ac9f67b802e8d0468b288
#define internal_h__2adc4b88454ac9f67b802e8d0468b288    1

#include <sys/types.h>
#include <stdint.h>

namespace SipHash {
    namespace Internal {
        template <typename T_>
            inline T_   rol64 (T_ val, int32_t cnt) {
                return (val << cnt) | (val >> (64 - cnt));
            }

        template <>
            inline uint64_t rol64 <uint64_t> (uint64_t val, int32_t cnt) {
#if defined (_MSC_VER)
                return _rotl64 (val, cnt) ;
#else
                return (val << cnt) | (val >> (64 - cnt)) ;
#endif
            }

        template <typename T_>
            inline void     SipRound (T_ &v0, T_ &v1, T_ &v2, T_ &v3) {
                v0 += v1 ;
                v2 += v3 ;
                v1 = rol64 (v1, 13) ;
                v3 = rol64 (v3, 16) ;
                v1 ^= v0 ;
                v3 ^= v2 ;
                v0 = rol64 (v0, 32) ;
                v2 += v1 ;
                v0 += v3 ;
                v1 = rol64 (v1, 17) ;
                v3 = rol64 (v3, 21) ;
                v1 ^= v2 ;
                v3 ^= v0 ;
                v2 = rol64 (v2, 32) ;
            }

        const uint64_t MASK_0 = 0x736f6d6570736575ul ;
        const uint64_t MASK_1 = 0x646f72616e646f6dul ;
        const uint64_t MASK_2 = 0x6c7967656e657261ul ;
        const uint64_t MASK_3 = 0x7465646279746573ul ;

        inline uint_fast64_t    Read8 (const void *data) {
            const uint8_t *p = static_cast<const uint8_t *> (data);
            return (  (static_cast<uint_fast64_t> (p[0]) <<  0)
                    | (static_cast<uint_fast64_t> (p[1]) <<  8)
                    | (static_cast<uint_fast64_t> (p[2]) << 16)
                    | (static_cast<uint_fast64_t> (p[3]) << 24)
                    | (static_cast<uint_fast64_t> (p[4]) << 32)
                    | (static_cast<uint_fast64_t> (p[5]) << 40)
                    | (static_cast<uint_fast64_t> (p[6]) << 48)
                    | (static_cast<uint_fast64_t> (p[7]) << 56));
        }
    }
}    /* end of [namespace SipHash::Internal] */

#endif	/* internal_h__2adc4b88454ac9f67b802e8d0468b288 */

/*
 * [END OF FILE]
 */
