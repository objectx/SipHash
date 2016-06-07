/* -*- mode: c++; coding: utf-8 -*- */
/*
 * TestSipHash.h:
 *
 * AUTHOR(S): objectx
 */
#pragma once
#ifndef TestSipHash_h_2FB3E16A_8CA2_4E9A_87EA_0B19458006CC
#define TestSipHash_h_2FB3E16A_8CA2_4E9A_87EA_0B19458006CC  1

#include "common.h"

template <typename T_>
    class put_hex_ {
    private:
        T_ const    v_ ;
        int32_t     w_ ;
    public:
        put_hex_ (const T_ &v, int32_t w) : v_ (v), w_ (w) {
            /* NO-OP */
        }
        std::ostream & write (std::ostream &output) const {
            auto    mask = std::ios::basefield | std::ios::adjustfield ;
            auto    flags = output.setf (std::ios::hex | std::ios::right, mask) ;

            char    fill = output.fill ('0') ;
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

template <typename T_>
    class put_dec_ {
    private:
        T_ const    v_ ;
        int32_t     w_ ;
    public:
        put_dec_ (const T_ &v, int32_t w) : v_ (v), w_ (w) {
            /* NO-OP */
        }
        std::ostream & write (std::ostream &output) const {
            auto    mask = std::ios::adjustfield ;
            auto    flags = output.setf (std::ios::right, mask) ;

            char    fill = output.fill (' ') ;
            output.width (w_) ;
            output << v_ ;
            output.setf (flags, mask) ;
            output.fill (fill) ;
            return output ;
        }
    };

template<typename T_>
    std::ostream & operator << (std::ostream &out, const put_dec_<T_> &manip) {
        return manip.write (out) ;
    }

template<typename T_>
    put_dec_<T_> put_dec (const T_ &v, int32_t w = 0) {
        return put_dec_<T_> (v, w) ;
    }

extern uint64_t from_string (const void *buf, size_t len) ;

#endif  /* TestSipHash_h_2FB3E16A_8CA2_4E9A_87EA_0B19458006CC */
