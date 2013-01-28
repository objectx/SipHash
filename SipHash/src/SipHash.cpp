/*
 * SipHash.cpp:
 *
 * Author(s): objectx
 */
#include <algorithm>
#include <SipHash.h>


namespace SipHash {
    IV::IV (const void *start, size_t length) {
	k_ [0] = 0 ;
	k_ [1] = 0 ;
	uint64_t	v = 0 ;
	int_fast32_t	shift_count = 0 ;
	const uint8_t *	const	p = static_cast<const uint8_t *> (start) ;

	size_t	l = std::min (length, static_cast<size_t> (8)) ;
	for (size_t i = 0 ; i < l ; ++i, shift_count += 8) {
	    v |= static_cast<uint64_t> (p [i]) << shift_count ;
	}
	k_ [0] = v ;

	if (8 < length) {
            l = std::min (length, static_cast<size_t> (16)) ;
	    v = 0 ;
	    shift_count = 0 ;
	    for (size_t i = 8 ; i < l ; ++i, shift_count += 8) {
		v |= static_cast<uint64_t> (p [i]) << shift_count ;
	    }
	    k_ [1] = v ;
	}
    }
}
/*
 * [END OF FILE]
 */
