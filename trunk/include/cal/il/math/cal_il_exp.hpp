/*
 * C++ to IL compiler/generator exp
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

#ifndef __CAL_IL_MATH_EXP_H
#define __CAL_IL_MATH_EXP_H

#include <cal/il/math/cal_il_dd.hpp>
#include <boost/limits.hpp>
#include <cmath>

namespace cal {
namespace il {

namespace detail {

template<class E1>
unary<E1,cal_unary_exp<typename E1::value_type> > native_exp( const expression<E1>& e1, float_type  )
{
    typedef unary<E1,cal_unary_exp<typename E1::value_type> > expression_type;
    return expression_type(e1);
}

template<class E1>
unary<E1,cal_unary_exp<typename E1::value_type> > native_exp( const expression<E1>& e1, float2_type  )
{
    typedef unary<E1,cal_unary_exp<typename E1::value_type> > expression_type;
    return expression_type(e1());
}

template<class E1>
unary<E1,cal_unary_exp<typename E1::value_type> > native_exp( const expression<E1>& e1, float4_type  )
{
    typedef unary<E1,cal_unary_exp<typename E1::value_type> > expression_type;
    return expression_type(e1());
}

template<class E1>
variable<typename E1::value_type> native_exp( const expression<E1>& x, double_type  )
{
    double1    cinv_log2((long double)1/(long double)std::log((long double)2)),
               cmlog2(-std::log((long double)2));
    double1    s,r,m,_x;

    _x = x();
    m  = round( cinv_log2*_x );
    r  = mad(cmlog2,m,_x);

    s  = cast_type<double1>(native_exp(cast_type<float1>(r),float_type()));

    return ldexp(s,cast_type<int1>(m));
}

template<class E1>
variable<typename E1::value_type> native_exp( const expression<E1>& x, double2_type  )
{
    double2    cinv_log2((long double)1/(long double)std::log((long double)2)),
               cmlog2(-std::log((long double)2));
    double2    s,r,m,_x;

    _x = x();
    m  = round( cinv_log2*_x );
    r  = mad(cmlog2,m,_x);

    s  = cast_type<double2>(native_exp(cast_type<float2>(r),float2_type()));

    return ldexp(s,cast_type<int2>(m));
}

template<class E1>
unary<E1,cal_unary_exp<typename E1::value_type> > exp( const expression<E1>& e1, float_type  )
{
    typedef unary<E1,cal_unary_exp<typename E1::value_type> > expression_type;
    return expression_type(e1);
}

template<class E1>
unary<E1,cal_unary_exp<typename E1::value_type> > exp( const expression<E1>& e1, float2_type  )
{
    typedef unary<E1,cal_unary_exp<typename E1::value_type> > expression_type;
    return expression_type(e1());
}

template<class E1>
unary<E1,cal_unary_exp<typename E1::value_type> > exp( const expression<E1>& e1, float4_type  )
{
    typedef unary<E1,cal_unary_exp<typename E1::value_type> > expression_type;
    return expression_type(e1());
}

template<class E1>
variable<typename E1::value_type> exp( const expression<E1>& x, double_type  )
{
    double1    cinv_log2((long double)1/(long double)std::log((long double)2)),
               cmln20(-6.931471805599452862e-01), cmln21(-2.319046813846299558e-17),
               cinv_k(1./32.),cmaxlog(7.09782712893383996843E2),cminlog(-7.08396418532264106224E2);
    double1    s,r,m,p0,p1,r0,r1,_x;

    _x = x();
    m  = round( cinv_log2*_x );

    //r = cinv_k*(x() - log(2)*m);
    dd_prod_dbl( p0, p1, cmln20, cmln21, m );
    dd_sum_dbl( r0, r1, p0, p1, _x );
    r = cinv_k*r0;

    // taylor series expansion
    s = double1((long double)1/(long double)5040);
    s = mad(s,r,double1((long double)1/(long double)720));
    s = mad(s,r,double1((long double)1/(long double)120));
    s = mad(s,r,double1((long double)1/(long double)24));
    s = mad(s,r,double1((long double)1/(long double)6));
    s = mad(s,r,double1((long double)1/(long double)2));
    s = mad(s,r,double1((long double)1/(long double)1));
    s = s*r;

    // s = (1+s)^32
    s = mad(s,s,s+s);
    s = mad(s,s,s+s);
    s = mad(s,s,s+s);
    s = mad(s,s,s+s);
    s = mad(s,s,s+s);
    s = s + double1(1);

    r = ldexp(s,cast_type<int_type>(m));
    r = select(_x>=cmaxlog,double1(std::numeric_limits<double>::max()),r);
    r = select(_x<cminlog,double1(0),r);

    return r;
}

template<class E1>
variable<typename E1::value_type> exp( const expression<E1>& x, double2_type  )
{
    double2     cinv_log2((long double)1/(long double)std::log((long double)2)),
                cmln20(-6.931471805599452862e-01), cmln21(-2.319046813846299558e-17),
                cinv_k(1./32.),cmaxlog(7.09782712893383996843E2),cminlog(-7.08396418532264106224E2);
    double2     s,r,m,p0,p1,r0,r1,_x;

    _x = x();
    m  = round( cinv_log2*_x );

    //r = cinv_k*(x() - log(2)*m);
    dd_prod_dbl( p0, p1, cmln20, cmln21, m );
    dd_sum_dbl( r0, r1, p0, p1, _x );
    r = cinv_k*r0;

    // taylor series expansion
    s = double2((long double)1/(long double)5040);
    s = mad(s,r,double2((long double)1/(long double)720));
    s = mad(s,r,double2((long double)1/(long double)120));
    s = mad(s,r,double2((long double)1/(long double)24));
    s = mad(s,r,double2((long double)1/(long double)6));
    s = mad(s,r,double2((long double)1/(long double)2));
    s = mad(s,r,double2((long double)1/(long double)1));
    s = s*r;

    // s = (1+s)^32
    s = mad(s,s,s+s);
    s = mad(s,s,s+s);
    s = mad(s,s,s+s);
    s = mad(s,s,s+s);
    s = mad(s,s,s+s);
    s = s + double2(1);

    r = ldexp(s,cast_type<int2_type>(m));
    r = select(_x>=cmaxlog,double2(std::numeric_limits<double>::max()),r);
    r = select(_x<cminlog,double2(0),r);

    return r;
}

} // detail

template<class E1>
variable<typename E1::value_type> native_exp( const detail::expression<E1>& e1 )
{
    return detail::native_exp(e1(),typename E1::value_type());
}

//
// error for double <1ulp
//
template<class E1>
variable<typename E1::value_type> exp( const detail::expression<E1>& e1 )
{
    return detail::exp(e1(),typename E1::value_type());
}

} // il
} // cal

#endif
