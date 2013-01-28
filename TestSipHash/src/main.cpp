/*
 * main.cpp:
 *
 * Author(s): objectx
 */
#include "common.h"
#include <SipHash.h>

namespace {

    template <typename T_>
        class put_hex_ {
        private:
            T_ const	v_ ;
            int32_t	w_ ;
        public:
            put_hex_ (const T_ &v, int32_t w) : v_ (v), w_ (w) {
		/* NO-OP */
            }
            std::ostream & write (std::ostream &output) const {
                auto	mask = std::ios::basefield | std::ios::adjustfield ;
                auto	flags = output.setf (std::ios::hex | std::ios::right, mask) ;
                                          
                char	fill = output.fill ('0') ;
                output.width (w_) ;
                output << v_ ;
                output.setf (flags, mask) ;
                output.fill (fill) ;
                return output ;
            }
        } ;

    template<typename T_>
        std::ostream & operator << (std::ostream &out, const put_hex_<T_> &manip) {
            return manip.write (out) ;
        }

    template<typename T_>
        put_hex_<T_> put_hex (const T_ &v, int32_t w = 0) {
            return put_hex_<T_> (v, w) ;
        }
}


static uint64_t	from_string (const void *buf, size_t len) {
    size_t	l = std::min (len, static_cast<size_t> (8)) ;
    uint64_t	v = 0 ;

    const uint8_t *	p = static_cast<const uint8_t *> (buf) ;
    for (size_t i = 0 ; i < l ; ++i) {
	v |= static_cast<uint64_t> (p [i]) << (i * 8) ;
    }
    return v ;
}


static void	TestKey () {
    {
	SipHash::IV	k (1, 2) ;
        const uint64_t *	kp = k.getKey () ;
	assert (kp [0] == 1) ;
	assert (kp [1] == 2) ;

	SipHash::IV	k2 (k) ;

	kp = k2.getKey () ;
	assert (kp [0] == 1) ;
	assert (kp [1] == 2) ;
    }
    {
	const char *	k_str = "abc" ;
        size_t k_len = 3 ;
	SipHash::IV	k (k_str, k_len) ;

        const uint64_t *	kp = k.getKey () ;
	assert (kp [0] == from_string (k_str, k_len)) ;
	assert (kp [1] == 0) ;
        std::cerr << "k0 = 0x" << put_hex (kp [0], 16) << std::endl ;
        std::cerr << "k1 = 0x" << put_hex (kp [1], 16) << std::endl ;
    }
    {
	const char *	k_str = "abcdefgh" ;
        size_t k_len = 8 ;
	SipHash::IV	k (k_str, k_len) ;

        const uint64_t *	kp = k.getKey () ;
	assert (kp [0] == from_string (k_str, k_len)) ;
	assert (kp [1] == 0) ;
        std::cerr << "k0 = 0x" << put_hex (kp [0], 16) << std::endl ;
        std::cerr << "k1 = 0x" << put_hex (kp [1], 16) << std::endl ;
    }
    {
	const char *	k_str = "abcdefghi" ;
        size_t k_len = 9 ;
	SipHash::IV	k (k_str, k_len) ;

        const uint64_t *	kp = k.getKey () ;
	assert (kp [0] == from_string (k_str + 0, 8)) ;
	assert (kp [1] == from_string (k_str + 8, 1)) ;
        std::cerr << "k0 = 0x" << put_hex (kp [0], 16) << std::endl ;
        std::cerr << "k1 = 0x" << put_hex (kp [1], 16) << std::endl ;
    }
    {
	const char *	k_str = "abcdefghijklmnopq" ;
        size_t k_len = strlen (k_str) ;
	SipHash::IV	k (k_str, k_len) ;

        const uint64_t *	kp = k.getKey () ;
	assert (kp [0] == from_string (k_str + 0, 8)) ;
	assert (kp [1] == from_string (k_str + 8, 8)) ;
        std::cerr << "k0 = 0x" << put_hex (kp [0], 16) << std::endl ;
        std::cerr << "k1 = 0x" << put_hex (kp [1], 16) << std::endl ;
    }
}

const uint8_t	test_key [16] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
} ;

const uint8_t	test_message [15] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e
} ;

static void	TestSipHash () {
    SipHash::IV	key (test_key, 16) ;
    assert (key.K0 () == 0x0706050403020100u) ;
    assert (key.K1 () == 0x0f0e0d0c0b0a0908u) ;

    uint8_t tmp [sizeof (test_message)] ;
    memcpy (tmp, test_message, sizeof (test_message)) ;
    uint64_t	val = SipHash::Compute (2, 4, key, tmp, sizeof (test_message)) ;
    assert (val == 0xa129ca6149be45e5u) ;
    std::cerr << "val = 0x" << put_hex (val, 16) << std::endl ;

    uint8_t	testvec [64] ;
    {
	memset (testvec, 0, sizeof (testvec)) ;
	for (int_fast32_t i = 0 ; i < sizeof (testvec) ; ++i) {
	    testvec [i] = static_cast<uint8_t> (i) ;
	}
    }
    for (int_fast32_t i = 1 ; i < sizeof (testvec) ; ++i) {
	uint64_t	val24 = SipHash::Compute_2_4 (key, testvec, i) ;
	uint64_t	expected24 = SipHash::Compute (2, 4, key, testvec, i) ;
	assert (val24 == expected24) ;
	std::cerr << "val24 = 0x" << put_hex (val24, 16) << " (len = " << i << ")" <<  std::endl ;
    }
    for (int_fast32_t i = 1 ; i < sizeof (testvec) ; ++i) {
	uint64_t	val48 = SipHash::Compute_4_8 (key, testvec, i) ;
	uint64_t	expected48 = SipHash::Compute (4, 8, key, testvec, i) ;
	assert (val48 == expected48) ;
	std::cerr << "val48 = 0x" << put_hex (val48, 16) << " (len = " << i << ")" <<  std::endl ;
    }
}

int	main (int argc, char **argv) {
    TestKey () ;
    TestSipHash () ;
    return 0 ;
}

/*
 * [END OF FILE]
 */
