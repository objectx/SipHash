/* -*- mode: c++; coding: utf-8 -*- */
/*
 * TestKey.cpp:
 *
 * AUTHOR(S): objectx
 */
#include "common.h"
#include "TestSipHash.h"
#include <SipHash.hpp>
#include <catch.hpp>

SCENARIO ("Testing IV creation", "[IV]") {
    GIVEN ("Short length key (< 8) supplied") {
        const char * const k_str = "abc" ;
        size_t const k_len = 3 ;
    WHEN ("Create IV") {
        auto const &    k = SipHash::MakeIV (k_str, k_len) ;
    THEN ("2nd state should be 0") {
        REQUIRE (k [0] == from_string (k_str, k_len)) ;
        REQUIRE (k [1] == 0) ;
    }}}
    GIVEN ("Short length key (== 8) supplied") {
        const char * const k_str = "abcdefgh" ;
        size_t const k_len = 8 ;
    WHEN ("Create IV") {
        auto const &    k = SipHash::MakeIV (k_str, k_len) ;
    THEN ("2nd state should be 0") {
        REQUIRE (k [0] == from_string (k_str, k_len)) ;
        REQUIRE (k [1] == 0) ;
    }}}
    GIVEN ("Long length key (> 8) supplied") {
        const char * const k_str = "abcdefghi" ;
        size_t const k_len = 9 ;
    WHEN ("Create IV") {
        auto const &    k = SipHash::MakeIV (k_str, k_len) ;
    THEN ("State should match") {
        REQUIRE (k [0] == from_string (k_str + 0, 8)) ;
        REQUIRE (k [1] == from_string (k_str + 8, 1)) ;
    }}}
    GIVEN ("Long length key (> 8) supplied") {
        const char * const k_str = "abcdefghijklmnopq" ;
        size_t const k_len = strlen (k_str) ;
    WHEN ("Create IV") {
        auto const &    k = SipHash::MakeIV (k_str, k_len) ;
    THEN ("State should match") {
        REQUIRE (k [0] == from_string (k_str + 0, 8)) ;
        REQUIRE (k [1] == from_string (k_str + 8, 8)) ;
    }}}
}
