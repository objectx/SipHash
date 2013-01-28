/*
 * SipHash.h: Implements SipHash.
 *
 * Author(s): objectx
 */

#ifndef siphash_h__34171f9848f6ced9262513a7f77b5d97
#define	siphash_h__34171f9848f6ced9262513a7f77b5d97	1

#include <sys/types.h>
#include <stdint.h>

namespace SipHash {
    /** The key to create initial vector */
    class IV {
    private:
	uint64_t	k_ [2] ;
    public:
	IV (uint64_t k0, uint64_t k1) {
	    k_ [0] = k0 ;
	    k_ [1] = k1 ;
	}
	IV (const IV &src) {
	    k_ [0] = src.k_ [0] ;
	    k_ [1] = src.k_ [1] ;
	}
	IV (const void *start, size_t length) ;
	IV &	Assign (const IV &src) {
	    k_ [0] = src.k_ [0] ;
	    k_ [1] = src.k_ [1] ;
	    return *this ;
	}
	IV &	Assign (const void *start, size_t length) ;

	IV &	operator = (const IV &src) {
	    return Assign (src) ;
	}
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

    /** Generic version of SipHash.  */
    uint_fast64_t	Compute (size_t cntCompression, size_t cntFinalization,
				 const IV &iv, const void *data, size_t length) ;

    /** Equivalent to Compute (2, 4, iv, data, length) */
    uint_fast64_t	Compute_2_4 (const IV &iv, const void *data, size_t length) ;
    /** Equivalent to Compute (4, 8, iv, data, length) */
    uint_fast64_t	Compute_4_8 (const IV &iv, const void *data, size_t length) ;
}	/* [end of namespace SipHash] */

#endif	/* siphash_h__34171f9848f6ced9262513a7f77b5d97 */
/*
 * [END OF FILE]
 */
