/* -*- mode: c++; coding: utf-8 -*- */
/*
 * TestSipHash.cpp:
 *
 * AUTHOR(S): objectx
 */
#include "common.h"
#include "TestSipHash.h"
#include <SipHash.h>
#include <Catch.hpp>

const uint8_t   test_key [16] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
} ;

const uint8_t   test_message [15] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e
} ;

void     TestSipHash () {
    SipHash::IV key (test_key, 16) ;
    assert (key.K0 () == 0x0706050403020100u) ;
    assert (key.K1 () == 0x0f0e0d0c0b0a0908u) ;

    uint8_t tmp [sizeof (test_message)] ;
    memcpy (tmp, test_message, sizeof (test_message)) ;
    uint64_t    val = SipHash::Compute (2, 4, key, tmp, sizeof (test_message)) ;
    assert (val == 0xa129ca6149be45e5u) ;
    std::cerr << "val = 0x" << put_hex (val, 16) << std::endl ;

    uint8_t     testvec [64] ;
    {
        memset (testvec, 0, sizeof (testvec)) ;
        for (int_fast32_t i = 0 ; i < sizeof (testvec) ; ++i) {
            testvec [i] = static_cast<uint8_t> (i) ;
        }
    }
    for (int_fast32_t i = 1 ; i < sizeof (testvec) ; ++i) {
        uint64_t        val24 = SipHash::Compute_2_4 (key, testvec, i) ;
        uint64_t        expected24 = SipHash::Compute (2, 4, key, testvec, i) ;
        assert (val24 == expected24) ;
        std::cerr << "val24 = 0x" << put_hex (val24, 16) << " (len = " << put_dec (i, 5) << ")" <<  std::endl ;
    }
    for (int_fast32_t i = 1 ; i < sizeof (testvec) ; ++i) {
        uint64_t        val48 = SipHash::Compute_4_8 (key, testvec, i) ;
        uint64_t        expected48 = SipHash::Compute (4, 8, key, testvec, i) ;
        assert (val48 == expected48) ;
        std::cerr << "val48 = 0x" << put_hex (val48, 16) << " (len = " << put_dec (i, 5) << ")" <<  std::endl ;
    }
}
