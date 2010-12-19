/*
 * C++ to IL compiler/generator tanh
 * 
 * Copyright (C) 2010 Artur Kornacki
 *
 *
 * CAL++ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CAL++ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with CAL++.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __CAL_IL_MATH_DD_H
#define __CAL_IL_MATH_DD_H

#include <cal/il/cal_il_types.hpp>

namespace cal {
namespace il {

namespace dd {

void split( const double1& a, double1& hi, double1& lo )
{
    hi = a & uint2(0xFC000000,0xFFFFFFFF);
    lo = a - hi;
}

void split( const double2& a, double2& hi, double2& lo )
{
    hi = a & uint4(0xFC000000,0xFFFFFFFF,0xFC000000,0xFFFFFFFF);
    lo = a - hi;
}


template<typename D>
variable<D> two_prod( const variable<D>& a, const variable<D>& b, variable<D>& err)
{
    variable<D> a_hi, a_lo, b_hi, b_lo,p;

    if( Source::info.available && Source::info.target>=CAL_TARGET_CYPRESS ) {
        p   = a*b;
        err = mad(a,b,-p);

        return p;
    }

    p = a*b;

    split(a, a_hi, a_lo);
    split(b, b_hi, b_lo);

    //err = ((a_hi * b_hi - p) + a_hi * b_lo + a_lo * b_hi) + a_lo * b_lo;
    err = mad( a_lo,b_lo, mad(a_hi,b_hi,-p) + mad(a_hi,b_lo,a_lo*b_hi) );

    return p;
}

template<typename D>
variable<D> two_sum( const variable<D>& a, const variable<D>& b, variable<D>& err)
{
    variable<D> s,bb;

    s = a + b;
    bb = s - a;
    err = (a - (s - bb)) + (b - bb);

    return s;
}

template<typename D>
variable<D> quick_two_sum( const variable<D>& a, const variable<D>& b, variable<D>& err)
{
    variable<D> s;

    s = a + b;
    err = b - (s - a);
    return s;
}

} // dd

template<typename D>
void dd_prod_dbl( variable<D>& r0, variable<D>& r1, const variable<D>& a0, const variable<D>& a1, const variable<D>& b )
{
    variable<D> p1,p2;

    p1 = dd::two_prod( a0, b, p2 );
    p2 = p2 + a1*b;
    p1 = dd::quick_two_sum( p1, p2, p2 );

    r0 = p1;
    r1 = p2;
}

template<typename D>
void dd_sum_dbl( variable<D>& r0, variable<D>& r1, const variable<D>& a0, const variable<D>& a1, const variable<D>& b )
{
    variable<D> s1,s2;

    s1 = dd::two_sum( a0, b, s2 );
    s2 = s2 + a1;
    s1 = dd::quick_two_sum( s1, s2, s2 );

    r0 = s1;
    r1 = s2;
}

template<typename D>
void dd_from_dbl( variable<D>& r0, variable<D>& r1, const variable<D>& d )
{
    r0 = d;
    r1 = variable<D>(0);
}

template<typename D>
variable<D> dd_to_dbl( const variable<D>& a0, const variable<D>& a1 )
{
    return a0;
}

} // il
} // cal

#endif
