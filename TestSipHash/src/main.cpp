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
	SipHash::Key	k (1, 2) ;
        const uint64_t *	kp = k.getKey () ;
	assert (kp [0] == 1) ;
	assert (kp [1] == 2) ;

	SipHash::Key	k2 (k) ;

	kp = k2.getKey () ;
	assert (kp [0] == 1) ;
	assert (kp [1] == 2) ;
    }
    {
	const char *	k_str = "abc" ;
        size_t k_len = 3 ;
	SipHash::Key	k (k_str, k_len) ;

        const uint64_t *	kp = k.getKey () ;
	assert (kp [0] == from_string (k_str, k_len)) ;
	assert (kp [1] == 0) ;
        std::cerr << "k0 = 0x" << put_hex (kp [0], 16) << std::endl ;
        std::cerr << "k1 = 0x" << put_hex (kp [1], 16) << std::endl ;
    }
    {
	const char *	k_str = "abcdefgh" ;
        size_t k_len = 8 ;
	SipHash::Key	k (k_str, k_len) ;

        const uint64_t *	kp = k.getKey () ;
	assert (kp [0] == from_string (k_str, k_len)) ;
	assert (kp [1] == 0) ;
        std::cerr << "k0 = 0x" << put_hex (kp [0], 16) << std::endl ;
        std::cerr << "k1 = 0x" << put_hex (kp [1], 16) << std::endl ;
    }
    {
	const char *	k_str = "abcdefghi" ;
        size_t k_len = 9 ;
	SipHash::Key	k (k_str, k_len) ;

        const uint64_t *	kp = k.getKey () ;
	assert (kp [0] == from_string (k_str, 8)) ;
	assert (kp [1] == from_string (k_str + 8, 1)) ;
        std::cerr << "k0 = 0x" << put_hex (kp [0], 16) << std::endl ;
        std::cerr << "k1 = 0x" << put_hex (kp [1], 16) << std::endl ;
    }
    {
	const char *	k_str = "abcdefghijklmnopq" ;
        size_t k_len = strlen (k_str) ;
	SipHash::Key	k (k_str, k_len) ;

        const uint64_t *	kp = k.getKey () ;
	assert (kp [0] == from_string (k_str, 8)) ;
	assert (kp [1] == from_string (k_str + 8, 8)) ;
        std::cerr << "k0 = 0x" << put_hex (kp [0], 16) << std::endl ;
        std::cerr << "k1 = 0x" << put_hex (kp [1], 16) << std::endl ;
    }
}

int	main (int argc, char **argv) {
    TestKey () ;
    return 0 ;
}

/*
 * [END OF FILE]
 */
