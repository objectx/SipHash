/*
 * SipHash.cpp:
 *
 * Author(s): objectx
 */
#include <algorithm>
#include <SipHash.h>


namespace SipHash {
    IV::IV (const void *start, size_t length) {
	Assign (start, length) ;
    }

    IV &	IV::Assign (const void *start, size_t length) {
	const uint8_t *	const	p = static_cast<const uint8_t *> (start) ;

	uint_fast64_t	k_0 = 0 ;
	uint_fast64_t	k_1 = 0 ;
	{
	    for (size_t i = 0, n = std::min (length, static_cast<size_t> (8)) ; i < n ; ++i) {
		k_0 |= static_cast<uint64_t> (p [i + 0]) << (8 * i) ;
	    }
	}
	if (8 < length) {
	    for (size_t i = 0, n = std::min (length, static_cast<size_t> (16)) - 8 ; i < n ; ++i) {
		k_1 |= static_cast<uint64_t> (p [i + 8]) << (8 * i) ;
	    }
	}
	k_ [0] = k_0 ;
	k_ [1] = k_1 ;
	return *this ;
    }

    static inline uint64_t rol (uint64_t val, int32_t cnt) {
#if defined (_MSC_VER)
	return _rotl64 (val, cnt) ;
#else
	return (val << cnt) | (val >> (64 - cnt)) ;
#endif
    }

#define	SIP_ROUND	do {				\
	v0 += v1            ; v2 += v3 ;		\
	v1 = rol (v1, 13)   ; v3 = rol (v3, 16) ;	\
	v1 ^= v0            ; v3 ^= v2 ;		\
	v0 = rol (v0, 32) ;				\
	v2 += v1            ; v0 += v3 ;		\
	v1 = rol (v1, 17)   ; v3 = rol (v3, 21) ;	\
	v1 ^= v2            ; v3 ^= v0 ;		\
	v2 = rol (v2, 32) ;				\
    } while (false)

    uint_fast64_t	Compute (size_t cntCompression, size_t cntFinalization,
				 const IV &iv,
				 const void *data, size_t length) {
	uint_fast64_t	v0 = iv.K0 () ^ 0x736f6d6570736575ul ;
	uint_fast64_t	v1 = iv.K1 () ^ 0x646f72616e646f6dul ;
	uint_fast64_t	v2 = iv.K0 () ^ 0x6c7967656e657261ul ;
	uint_fast64_t	v3 = iv.K1 () ^ 0x7465646279746573ul ;

	const uint8_t *	p = static_cast<const uint8_t *> (data) ;

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
	    v3 ^= m ;
	    for (int_fast32_t r = 0 ; r < cntCompression ; ++r) {
		SIP_ROUND ;
	    }
	    v0 ^= m ;
	}
	{
	    uint_fast64_t	lastval = (static_cast<int_fast64_t> (length) & 0xFFu) << 56 ;
	    int_fast64_t	remain = static_cast<int_fast64_t> (length) - (8 * n) ;

	    const uint8_t *	q = &(p [8 * n]) ;
	    for (int_fast64_t i = 0 ; i < remain ; ++i) {
		lastval |= static_cast<uint_fast64_t> (q [i]) << (i * 8) ;
	    }
	    v3 ^= lastval ;
	    for (int_fast32_t r = 0 ; r < cntCompression ; ++r) {
		SIP_ROUND ;
	    }
	    v0 ^= lastval ;
	}
	// Finalize
	{
	    v2 ^= 0xFFu ;
	    for (int_fast32_t r = 0 ; r < cntFinalization ; ++r) {
		SIP_ROUND ;
	    }
	}
	return v0 ^ v1 ^ v2 ^ v3 ;
    }

    uint_fast64_t	Compute_2_4 (const IV &iv, const void *data, size_t length) {
	uint_fast64_t	v0 = iv.K0 () ^ 0x736f6d6570736575ul ;
	uint_fast64_t	v1 = iv.K1 () ^ 0x646f72616e646f6dul ;
	uint_fast64_t	v2 = iv.K0 () ^ 0x6c7967656e657261ul ;
	uint_fast64_t	v3 = iv.K1 () ^ 0x7465646279746573ul ;

	const uint8_t *	p = static_cast<const uint8_t *> (data) ;

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
	    v3 ^= m ;
	    SIP_ROUND ;
	    SIP_ROUND ;
	    v0 ^= m ;
	}
	{
	    uint_fast64_t	lastval = (static_cast<int_fast64_t> (length) & 0xFFu) << 56 ;
	    int_fast64_t	remain = static_cast<int_fast64_t> (length) - (8 * n) ;

	    const uint8_t *	q = &(p [8 * n]) ;
	    for (int_fast64_t i = 0 ; i < remain ; ++i) {
		lastval |= static_cast<uint_fast64_t> (q [i]) << (i * 8) ;
	    }
	    v3 ^= lastval ;
	    SIP_ROUND ;
	    SIP_ROUND ;
	    v0 ^= lastval ;
	}
	// Finalize
	{
	    v2 ^= 0xFFu ;
	    SIP_ROUND ;
	    SIP_ROUND ;
	    SIP_ROUND ;
	    SIP_ROUND ;
	}
	return v0 ^ v1 ^ v2 ^ v3 ;
    }

    uint_fast64_t	Compute_4_8 (const IV &iv, const void *data, size_t length) {
	uint_fast64_t	v0 = iv.K0 () ^ 0x736f6d6570736575ul ;
	uint_fast64_t	v1 = iv.K1 () ^ 0x646f72616e646f6dul ;
	uint_fast64_t	v2 = iv.K0 () ^ 0x6c7967656e657261ul ;
	uint_fast64_t	v3 = iv.K1 () ^ 0x7465646279746573ul ;

	const uint8_t *	p = static_cast<const uint8_t *> (data) ;

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
	    v3 ^= m ;
	    SIP_ROUND ;
	    SIP_ROUND ;
	    SIP_ROUND ;
	    SIP_ROUND ;
	    v0 ^= m ;
	}
	{
	    uint_fast64_t	lastval = (static_cast<int_fast64_t> (length) & 0xFFu) << 56 ;
	    int_fast64_t	remain = static_cast<int_fast64_t> (length) - (8 * n) ;

	    const uint8_t *	q = &(p [8 * n]) ;
	    for (int_fast64_t i = 0 ; i < remain ; ++i) {
		lastval |= static_cast<uint_fast64_t> (q [i]) << (i * 8) ;
	    }
	    v3 ^= lastval ;
	    SIP_ROUND ;
	    SIP_ROUND ;
	    SIP_ROUND ;
	    SIP_ROUND ;
	    v0 ^= lastval ;
	}
	// Finalize
	{
	    v2 ^= 0xFFu ;
	    SIP_ROUND ;
	    SIP_ROUND ;
	    SIP_ROUND ;
	    SIP_ROUND ;
	    SIP_ROUND ;
	    SIP_ROUND ;
	    SIP_ROUND ;
	    SIP_ROUND ;
	}
	return v0 ^ v1 ^ v2 ^ v3 ;
    }
}
/*
 * [END OF FILE]
 */
