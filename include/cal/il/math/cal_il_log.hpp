/*
 * C++ to IL compiler/generator log
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

#ifndef __CAL_IL_MATH_LOG_H
#define __CAL_IL_MATH_LOG_H

#include <cal/il/cal_il_types.hpp>
#include <cal/il/math/cal_il_polevl.hpp>
#include <boost/cstdint.hpp>
#include <boost/limits.hpp>

namespace cal {
namespace il {

namespace detail {

template<class E1>
unary<E1,cal_unary_log<typename E1::value_type> > log( const expression<E1>& e1, float_type  )
{
    typedef unary<E1,cal_unary_log<typename E1::value_type> > expression_type;
    return expression_type(e1());
}

template<class E1>
unary<E1,cal_unary_log<typename E1::value_type> > log( const expression<E1>& e1, float2_type  )
{
    typedef unary<E1,cal_unary_log<typename E1::value_type> > expression_type;
    return expression_type(e1());
}

template<class E1>
unary<E1,cal_unary_log<typename E1::value_type> > log( const expression<E1>& e1, float4_type  )
{
    typedef unary<E1,cal_unary_log<typename E1::value_type> > expression_type;
    return expression_type(e1());
}


template<class E1>
double1 log( const expression<E1>& a, double_type  )
{
    static boost::uint16_t P[] = { 0x1bb0,0x93c3,0xb4c2,0x3f1a,
                                   0x52f2,0x3f56,0xd6f5,0x3fdf,
                                   0x6911,0xed92,0xd2ba,0x4012,
                                   0xeb2e,0xc63e,0xff72,0x402c,
                                   0xc84d,0x924b,0xefd6,0x4031,
                                   0xdcf8,0x7d7e,0xd563,0x401e };
    static boost::uint16_t Q[] = { 0xef8e,0xae97,0x9320,0x4026,
                                   0xc033,0x4e19,0x9d2c,0x4046,
                                   0xbdbd,0xa326,0xbf33,0x4054,
                                   0xae21,0xeb5e,0xc9e2,0x4051,
                                   0x25b2,0x9e1f,0x200a,0x4037 };
    static boost::uint16_t R[12] = { 0x0e84,0xdc6c,0x443d,0xbfe9,
                                     0x7b6b,0x7302,0x62fc,0x4030,
                                     0x2a20,0x1122,0x0906,0xc050 };
    static boost::uint16_t S[12] = { 0x6d0a,0x43ec,0xd60d,0xc041,
                                     0xe40e,0x112a,0x8180,0x4073,
                                     0x3f3b,0x19b3,0x0d89,0xc088 };
    double1 r,r0,r1,_a;
    double1 _x,x,y,z,e;
    int1    _e;
    uint2   t;

    _a = a();
    _x = frexp(_a,_e);
    t  = _x<double1(0.70710678118654752440);
    e  = cast_type<double1>( select( t.x(), _e - int1(1), _e ) );

    /* logarithm using log(x) = z + z**3 P(z)/Q(z),
    * where z = 2(x-1)/x+1)
    */
    z  = select( t, _x - double1(0.5), _x - double1(1) );
    y  = select( t, mad(double1(0.5),_x,double1(0.25)), mad(double1(0.5),_x,double1(0.5)) );
    x  = z / y;
    z  = x*x;
    r0 = x * ( z * detail::polevl( z, (const double*)R, 3 ) / detail::p1evl( z, (const double*)S, 3 ) )
         - e*double1(2.121944400546905827679e-4) + x + e*double1(0.693359375);

    /* logarithm using log(1+x) = x - .5x**2 + x**3 P(x)/Q(x) */
    x  = select( t, mad(double1(2),_x,double1(-1)), _x - double1(1) );
    z  = x*x;
    r1 = x * ( z * polevl( x, (const double*)P, 6 )/p1evl( x, (const double*)Q, 5 ) )
         - e*double1(2.121944400546905827679e-4) - double1(0.5)*z + x + e*double1(0.693359375);

    uint1 t1 = (_e < int2(-2)) | (_e >= int2(3));
    r = select( uint2(t1,t1), r0, r1 );
    r = select( _a == double1(0), double1(-std::numeric_limits<double>::max()), r );
    r = select( _a <  double1(0), double1(std::numeric_limits<double>::quiet_NaN()), r );

    return r;
}

template<class E1>
double2 log( const expression<E1>& a, double2_type  )
{
    static boost::uint16_t P[] = { 0x1bb0,0x93c3,0xb4c2,0x3f1a,
                                   0x52f2,0x3f56,0xd6f5,0x3fdf,
                                   0x6911,0xed92,0xd2ba,0x4012,
                                   0xeb2e,0xc63e,0xff72,0x402c,
                                   0xc84d,0x924b,0xefd6,0x4031,
                                   0xdcf8,0x7d7e,0xd563,0x401e };
    static boost::uint16_t Q[] = { 0xef8e,0xae97,0x9320,0x4026,
                                   0xc033,0x4e19,0x9d2c,0x4046,
                                   0xbdbd,0xa326,0xbf33,0x4054,
                                   0xae21,0xeb5e,0xc9e2,0x4051,
                                   0x25b2,0x9e1f,0x200a,0x4037 };
    static boost::uint16_t R[12] = { 0x0e84,0xdc6c,0x443d,0xbfe9,
                                     0x7b6b,0x7302,0x62fc,0x4030,
                                     0x2a20,0x1122,0x0906,0xc050 };
    static boost::uint16_t S[12] = { /*0x0000,0x0000,0x0000,0x3ff0,*/
                                     0x6d0a,0x43ec,0xd60d,0xc041,
                                     0xe40e,0x112a,0x8180,0x4073,
                                     0x3f3b,0x19b3,0x0d89,0xc088 };
    double2 r,r0,r1,_a;
    double2 _x,x,y,z,e;
    int2    _e;
    uint4   t;

    _a = a();
    _x = frexp(_a,_e);
    t  = _x<double2(0.70710678118654752440);
    e  = cast_type<double2>( select( t.xz(), _e - int2(1), _e ) );

    /* logarithm using log(x) = z + z**3 P(z)/Q(z),
    * where z = 2(x-1)/x+1)
    */
    z  = select( t, _x - double2(0.5), _x - double2(1) );
    y  = select( t, mad(double2(0.5),_x,double2(0.25)), mad(double2(0.5),_x,double2(0.5)) );
    x  = z / y;
    z  = x*x;
    r0 = x * ( z * detail::polevl( z, (const double*)R, 3 ) / detail::p1evl( z, (const double*)S, 3 ) ) 
         - e*double2(2.121944400546905827679e-4) + x + e*double2(0.693359375);

    /* logarithm using log(1+x) = x - .5x**2 + x**3 P(x)/Q(x) */
    x  = select( t, mad(double2(2),_x,double2(-1)), _x - double2(1) );
    z  = x*x;
    r1 = x * ( z * polevl( x, (const double*)P, 6 )/p1evl( x, (const double*)Q, 5 ) )
         - e*double2(2.121944400546905827679e-4) - double2(0.5)*z + x + e*double2(0.693359375);

    uint2 t1 = (_e < int2(-2)) | (_e >= int2(3));
    r = select( uint4(t1.xx(),t1.yy()), r0, r1 );
    r = select( _a == double2(0), double2(-std::numeric_limits<double>::max()), r );
    r = select( _a <  double2(0), double2(std::numeric_limits<double>::quiet_NaN()), r );

    return r;
}

} // detail

template<class E1>
variable<typename E1::value_type> log( const detail::expression<E1>& e1 )
{
    return detail::log(e1(),typename E1::value_type());
}

}
}

#endif
