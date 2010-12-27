/*
 * C++ to IL compiler/generator sqrt
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

#ifndef __CAL_IL_MATH_SQRT_H
#define __CAL_IL_MATH_SQRT_H

#include <cal/il/cal_il_types.hpp>

namespace cal {
namespace il {

namespace detail {

template<class E1>
unary<E1,cal_unary_sqrt<typename E1::value_type> > native_sqrt( const expression<E1>& e1, float_type  )
{
    typedef unary<E1,cal_unary_sqrt<typename E1::value_type> > expression_type;
    return expression_type(e1());
}

template<class E1>
unary<E1,cal_unary_sqrt<typename E1::value_type> > native_sqrt( const expression<E1>& e1, float2_type  )
{
    typedef unary<E1,cal_unary_sqrt<typename E1::value_type> > expression_type;
    return expression_type(e1());
}

template<class E1>
unary<E1,cal_unary_sqrt<typename E1::value_type> > native_sqrt( const expression<E1>& e1, float4_type  )
{
    typedef unary<E1,cal_unary_sqrt<typename E1::value_type> > expression_type;
    return expression_type(e1());
}

template<class E1>
double1 native_sqrt( const expression<E1>& e1, double_type  )
{
    typedef unary<E1,cal_unary_sqrt<typename E1::value_type> > sqrt_type;

#if defined(__CAL_H__)
    if( Source::info.available && Source::info.target>=CAL_TARGET_CYPRESS ) return sqrt_type(e1());
#endif
    double1 w,x;
    int1    e;

    w = e1();
    x = frexp(w,e);
    x = cast_type<double1>( native_sqrt(cast_type<float1>(x),float_type()) );
    x = select( e&int1(0x1), double1(1.41421356237309504880)*x, x );
    x = ldexp(x,e>>int1(1));

    return x;
}

template<class E1>
double2 native_sqrt( const expression<E1>& e1, double2_type  )
{
    typedef unary<E1,cal_unary_sqrt<typename E1::value_type> > sqrt_type;

#if defined(__CAL_H__)
    if( Source::info.available && Source::info.target>=CAL_TARGET_CYPRESS ) return sqrt_type(e1());
#endif
    double2 w,x;
    int2    e;

    w = e1();
    x = frexp(w,e);
    x = cast_type<double2>( native_sqrt(cast_type<float2>(x),float2_type()) );
    x = select( e&int2(0x1), double2(1.41421356237309504880)*x, x );
    x = ldexp(x,e>>int2(1));

    return x;
}

template<class E1>
double1 sqrt( const expression<E1>& a, float_type  )
{
    return native_sqrt(a(),float_type());
}

template<class E1>
double2 sqrt( const expression<E1>& a, float2_type  )
{
    return native_sqrt(a(),float2_type());
}

template<class E1>
double1 sqrt( const expression<E1>& a, float4_type  )
{
    return native_sqrt(a(),float4_type());
}

template<class E1>
double1 sqrt( const expression<E1>& a, double_type  )
{
    double1 w,x;

    w = a();
    x = native_sqrt(w,double_type());

    x = double2(0.5)*(x + w/x);
    x = double2(0.5)*(x + w/x);

    return x;
}

template<class E1>
double2 sqrt( const expression<E1>& a, double2_type  )
{
    double2 w,x;

    w = a();
    x = native_sqrt(w,double2_type());

    x = double2(0.5)*(x + w/x);
    x = double2(0.5)*(x + w/x);

    return x;
}

template<class E1>
double1 fast_sqrt( const expression<E1>& a, float_type  )
{
    return native_sqrt(a(),float_type());
}

template<class E1>
double2 fast_sqrt( const expression<E1>& a, float2_type  )
{
    return native_sqrt(a(),float2_type());
}

template<class E1>
double1 fast_sqrt( const expression<E1>& a, float4_type  )
{
    return native_sqrt(a(),float4_type());
}

template<class E1>
double1 fast_sqrt( const expression<E1>& a, double_type  )
{
    double1 w,x,r;

    w = a();
    x = native_rsqrt(w);
    x = x*mad(x*x,-w,double1(3.));
    r = x*w;
    r = r*mad(double1(-0.0625),r*x,double1(0.75));

    return r;
}

template<class E1>
double2 fast_sqrt( const expression<E1>& a, double2_type  )
{
    double2 w,x,r;

    w = a();
    x = native_rsqrt(w);
    x = x*mad(x*x,-w,double2(3.));
    r = x*w;
    r = r*mad(double2(-0.0625),r*x,double2(0.75));

    return r;
}

} // detail

template<class E1>
variable<typename E1::value_type> native_sqrt( const detail::expression<E1>& e1 )
{
    return detail::native_sqrt(e1(),typename E1::value_type());
}

//
// error for double < 1 ulp ( with few exceptions <= 0.5 ulp )
//
template<class E1>
variable<typename E1::value_type> sqrt( const detail::expression<E1>& e1 )
{
    return detail::sqrt(e1(),typename E1::value_type());
}

//
// error for double < 2 ulp
//
// no divisions used ( huge speed improvement on older GPUs )
//
template<class E1>
variable<typename E1::value_type> fast_sqrt( const detail::expression<E1>& e1 )
{
    return detail::fast_sqrt(e1(),typename E1::value_type());
}


}
}

#endif
