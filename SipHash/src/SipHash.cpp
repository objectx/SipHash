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
}
/*
 * [END OF FILE]
 */
