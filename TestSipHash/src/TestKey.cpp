/* -*- mode: c++; coding: utf-8 -*- */
/*
 * TestKey.cpp:
 *
 * AUTHOR(S): objectx
 */
#include "common.h"
#include "TestSipHash.h"
#include <SipHash.h>
#include <Catch.hpp>

void TestKey () {
    {
        SipHash::IV     k (1, 2) ;
        const uint64_t *        kp = k.getKey () ;
        assert (kp [0] == 1) ;
        assert (kp [1] == 2) ;

        SipHash::IV     k2 (k) ;

        kp = k2.getKey () ;
        assert (kp [0] == 1) ;
        assert (kp [1] == 2) ;
    }
    {
        const char *    k_str = "abc" ;
        size_t k_len = 3 ;
        SipHash::IV     k (k_str, k_len) ;

        const uint64_t *        kp = k.getKey () ;
        assert (kp [0] == from_string (k_str, k_len)) ;
        assert (kp [1] == 0) ;
        std::cerr << "k0 = 0x" << put_hex (kp [0], 16) << std::endl ;
        std::cerr << "k1 = 0x" << put_hex (kp [1], 16) << std::endl ;
    }
    {
        const char *    k_str = "abcdefgh" ;
        size_t k_len = 8 ;
        SipHash::IV     k (k_str, k_len) ;

        const uint64_t *        kp = k.getKey () ;
        assert (kp [0] == from_string (k_str, k_len)) ;
        assert (kp [1] == 0) ;
        std::cerr << "k0 = 0x" << put_hex (kp [0], 16) << std::endl ;
        std::cerr << "k1 = 0x" << put_hex (kp [1], 16) << std::endl ;
    }
    {
        const char *    k_str = "abcdefghi" ;
        size_t k_len = 9 ;
        SipHash::IV     k (k_str, k_len) ;

        const uint64_t *        kp = k.getKey () ;
        assert (kp [0] == from_string (k_str + 0, 8)) ;
        assert (kp [1] == from_string (k_str + 8, 1)) ;
        std::cerr << "k0 = 0x" << put_hex (kp [0], 16) << std::endl ;
        std::cerr << "k1 = 0x" << put_hex (kp [1], 16) << std::endl ;
    }
    {
        const char *    k_str = "abcdefghijklmnopq" ;
        size_t k_len = strlen (k_str) ;
        SipHash::IV     k (k_str, k_len) ;

        const uint64_t *        kp = k.getKey () ;
        assert (kp [0] == from_string (k_str + 0, 8)) ;
        assert (kp [1] == from_string (k_str + 8, 8)) ;
        std::cerr << "k0 = 0x" << put_hex (kp [0], 16) << std::endl ;
        std::cerr << "k1 = 0x" << put_hex (kp [1], 16) << std::endl ;
    }
}
