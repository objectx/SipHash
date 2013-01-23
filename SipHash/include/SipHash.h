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
    } ;
}	/* [end of namespace SipHash] */

#endif	/* siphash_h__34171f9848f6ced9262513a7f77b5d97 */
/*
 * [END OF FILE]
 */
