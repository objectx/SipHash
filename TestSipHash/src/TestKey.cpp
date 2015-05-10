/* -*- mode: c++; coding: utf-8 -*- */
/*
 * TestKey.cpp:
 *
 * AUTHOR(S): objectx
 */
#include "common.h"
#include "TestSipHash.h"
#include <SipHash.h>
#include <catch.hpp>

SCENARIO ("Testing IV creation", "[IV]") {
    GIVEN ("IV = (1, 2) supplied") {
        SipHash::IV k (1, 2) ;
    WHEN ("Retrieve states") {
        const uint64_t * kp = k.getKey () ;
    THEN ("1st state should be 1") {
        REQUIRE (kp [0] == 1) ;
    AND_THEN ("2nd state should be 2") {
        REQUIRE (kp [1] == 2) ;
    }}}
    WHEN ("Copy states") {
        SipHash::IV k2 (k) ;
    AND_WHEN ("Retrieve states") {
        const uint64_t * kp2 = k2.getKey () ;
    THEN ("State should match") {
        const uint64_t * kp = k.getKey () ;
        REQUIRE (kp2 [0] == kp [0]) ;
        REQUIRE (kp2 [1] == kp [1]) ;
    }}}}
    GIVEN ("Short length key (< 8) supplied") {
        const char * const k_str = "abc" ;
        size_t const k_len = 3 ;
    WHEN ("Create IV") {
        SipHash::IV k (k_str, k_len) ;
    THEN ("2nd state should be 0") {
        const uint64_t * kp = k.getKey () ;
        REQUIRE (kp [0] == from_string (k_str, k_len)) ;
        REQUIRE (kp [1] == 0) ;
    }}}
    GIVEN ("Short length key (== 8) supplied") {
        const char * const k_str = "abcdefgh" ;
        size_t const k_len = 8 ;
    WHEN ("Create IV") {
        SipHash::IV k (k_str, k_len) ;
    THEN ("2nd state should be 0") {
        const uint64_t * kp = k.getKey () ;
        REQUIRE (kp [0] == from_string (k_str, k_len)) ;
        REQUIRE (kp [1] == 0) ;
    }}}
    GIVEN ("Long length key (> 8) supplied") {
        const char * const k_str = "abcdefghi" ;
        size_t const k_len = 9 ;
    WHEN ("Create IV") {
        SipHash::IV k (k_str, k_len) ;
    THEN ("State should match") {
        const uint64_t * kp = k.getKey () ;
        REQUIRE (kp [0] == from_string (k_str + 0, 8)) ;
        REQUIRE (kp [1] == from_string (k_str + 8, 1)) ;
    }}}
    GIVEN ("Long length key (> 8) supplied") {
        const char * const k_str = "abcdefghijklmnopq" ;
        size_t const k_len = strlen (k_str) ;
    WHEN ("Create IV") {
        SipHash::IV k (k_str, k_len) ;
    THEN ("State should match") {
        const uint64_t * kp = k.getKey () ;
        REQUIRE (kp [0] == from_string (k_str + 0, 8)) ;
        REQUIRE (kp [1] == from_string (k_str + 8, 8)) ;
    }}}
}
