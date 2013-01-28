/*
 * SipHash.h:
 *
 * Author(s): objectx
 */

#ifndef siphash_h__34171f9848f6ced9262513a7f77b5d97
#define	siphash_h__34171f9848f6ced9262513a7f77b5d97	1

#include <sys/types.h>
#include <stdint.h>

namespace SipHash {
    /** The key to craete initial vector */
    class Key {
    private:
	uint64_t	k_ [2] ;
    public:
	Key (uint64_t k0, uint64_t k1) {
	    k_ [0] = k0 ;
	    k_ [1] = k1 ;
	}
	Key (const Key &src) {
	    k_ [0] = src.k_ [0] ;
	    k_ [1] = src.k_ [1] ;
	}
	Key (const void *start, size_t length) ;
	const uint64_t *	getKey () const {
	    return k_ ;
	}
	uint64_t	K0 () const {
	    return k_ [0] ;
	}
	uint64_t	K1 () const {
	    return k_ [1] ;
	}
    } ;

    template <size_t C_, size_t D_>
	class Hasher {
	private:
            static inline uint64_t rol (uint64_t val, int32_t cnt) {
#if defined (_MSC_VER)
                return _rotl64 (val, cnt) ;
#else
                return (val << cnt) | (val >> (64 - cnt)) ;
#endif
            }
	    static void	SipRound (uint64_t *v) {
		v [0] += v [1] ; v [2] += v [3] ;
		v [1] = rol (v [1], 13)   ; v [3] = rol (v [3], 16) ;
		v [1] ^= v [0] ; v [3] ^= v [2] ;
		v [0] = rol (v [0], 32) ;
		v [2] += v [1] ; v [0] += v [3] ;
		v [1] = rol (v [1], 17) ; v [3] = rol (v [3], 21) ;
		v [1] ^= v [2] ; v [3] ^= v [0] ;
		v [2] = rol (v [2], 32) ;
	    }
	public:
	    static uint64_t	Compute (const Key &key, const void *values, size_t length) {
		uint64_t	v [4] ;
		v [0] = key.K0 () ^ 0x736f6d6570736575ul ;
		v [1] = key.K1 () ^ 0x646f72616e646f6dul ;
		v [2] = key.K0 () ^ 0x6c7967656e657261ul ;
		v [3] = key.K1 () ^ 0x7465646279746573ul ;

		const uint8_t *	p = static_cast<const uint8_t *> (values) ;

		int_fast64_t	n = static_cast<int_fast64_t> (length) / 8 ;
		// Process full (== 64bits) blocks.
		for (int_fast64_t i = 0 ; i < n ; ++i) {
		    uint_fast64_t	m = ((static_cast<uint64_t> (p [8 * i + 0]) <<  0) |
					     (static_cast<uint64_t> (p [8 * i + 1]) <<  8) |
					     (static_cast<uint64_t> (p [8 * i + 2]) << 16) |
					     (static_cast<uint64_t> (p [8 * i + 3]) << 24) |
					     (static_cast<uint64_t> (p [8 * i + 4]) << 32) |
					     (static_cast<uint64_t> (p [8 * i + 5]) << 40) |
					     (static_cast<uint64_t> (p [8 * i + 6]) << 48) |
					     (static_cast<uint64_t> (p [8 * i + 7]) << 56)) ;
		    v [3] ^= m ;
		    for (int_fast32_t c = 0 ; c < C_ ; ++c) {
			SipRound (v) ;
		    }
		    v [0] ^= m ;
		}
		{
		    uint_fast64_t	lastval = (static_cast<int_fast64_t> (length) & 0xFFu) << 56 ;
		    int_fast64_t	remain = static_cast<int_fast64_t> (length) - (8 * n) ;

		    const uint8_t *	q = &(p [8 * n]) ;
		    switch (remain) {
		    case 7:
			lastval |= static_cast<uint_fast64_t> (q [6]) << 48 ;
			/*FALLTHROUGH*/
		    case 6:
			lastval |= static_cast<uint_fast64_t> (q [5]) << 40 ;
			/*FALLTHROUGH*/
		    case 5:
			lastval |= static_cast<uint_fast64_t> (q [4]) << 32 ;
			/*FALLTHROUGH*/
		    case 4:
			lastval |= static_cast<uint_fast64_t> (q [3]) << 24 ;
			/*FALLTHROUGH*/
		    case 3:
			lastval |= static_cast<uint_fast64_t> (q [2]) << 16 ;
			/*FALLTHROUGH*/
		    case 2:
			lastval |= static_cast<uint_fast64_t> (q [1]) <<  8 ;
			/*FALLTHROUGH*/
		    case 1:
			lastval |= static_cast<uint_fast64_t> (q [0]) <<  0 ;
			/*FALLTHROUGH*/
		    case 0:
		    default:
			break ;
		    }
		    v [3] ^= lastval ;
		    for (int_fast32_t c = 0 ; c < C_ ; ++c) {
			SipRound (v) ;
		    }
		    v [0] ^= lastval ;
		}
		// Finalize
		{
		    v [2] ^= 0xFFu ;
		    for (int_fast32_t d = 0 ; d < D_ ; ++d) {
			SipRound (v) ;
		    }
		}
		return v [0] ^ v [1] ^ v [2] ^ v [3] ;
	    }
        } ;
}	/* [end of namespace SipHash] */

#endif	/* siphash_h__34171f9848f6ced9262513a7f77b5d97 */
/*
 * [END OF FILE]
 */
