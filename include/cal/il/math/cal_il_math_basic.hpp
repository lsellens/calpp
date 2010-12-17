/*
 * C++ to IL compiler/generator math basic operations
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

#ifndef __CAL_IL_MATH_BASIC_H
#define __CAL_IL_MATH_BASIC_H

#include <cal/il/cal_il_expression_types.hpp>
#include <cal/il/cal_il_types.hpp>

namespace cal {
namespace il {

template<class E1>
detail::unary<E1,detail::cal_unary_frac<typename E1::value_type> > fract( const detail::expression<E1>& e1 );

namespace detail {

template<class E1>
unary<E1,cal_unary_round<typename E1::value_type> > round( const expression<E1>& e1, float_type  )
{
    typedef unary<E1,cal_unary_round<typename E1::value_type> > expression_type;
    return expression_type(e1);
}

template<class E1>
unary<E1,cal_unary_round<typename E1::value_type> > round( const expression<E1>& e1, float2_type  )
{
    typedef unary<E1,cal_unary_round<typename E1::value_type> > expression_type;
    return expression_type(e1);
}

template<class E1>
unary<E1,cal_unary_round<typename E1::value_type> > round( const expression<E1>& e1, float4_type  )
{
    typedef unary<E1,cal_unary_round<typename E1::value_type> > expression_type;
    return expression_type(e1);
}

template<class E1>
variable<typename E1::value_type> round( const expression<E1>& e1, double_type  )
{
    variable<typename E1::value_type>   x;
    x = e1() + variable<double_type>(0.5);
    return x-fract(x);
}

template<class E1>
variable<typename E1::value_type> round( const expression<E1>& e1, double2_type  )
{
    variable<typename E1::value_type>   x;
    x = e1() + variable<double2_type>(0.5);
    return x-fract(x);
}

template<class E1>
double1 frexp( const expression<E1>& ex, int1& e, double_type  )
{
    typedef unary<E1,cal_unary_frexp<double_type> > expression_type;
    uint4   r0;

    r0 = expression_type(ex());
    e  = cast_type<int1>(r0.y());
    return double1( cast_bits<double1>(r0.zw()) );
}

template<class E1>
double2 frexp( const expression<E1>& ex, int2& e, double2_type  )
{
    int1    e0,e1;
    double2 r,x;

    x = ex();

    r.x() = frexp(x.x(),e0,double_type());
    r.y() = frexp(x.y(),e1,double_type());

    e.x() = e0;
    e.y() = e1;

    return r;
}

} // detail

template<class E1>
detail::unary<E1,detail::cal_unary_frac<typename E1::value_type> > fract( const detail::expression<E1>& e1 )
{
    typedef detail::unary<E1,detail::cal_unary_frac<typename E1::value_type> > expression_type;
    return expression_type( e1() );
}

template<class E1>
detail::unary<E1,detail::cal_unary_floor<typename E1::value_type> > floor( const detail::expression<E1>& e1 )
{
    typedef detail::unary<E1,detail::cal_unary_floor<typename E1::value_type> > expression_type;
    return expression_type( e1() );
}

template<class E1>
variable<typename E1::value_type> round( const detail::expression<E1>& e1 )
{
    return detail::round(e1(),typename E1::value_type());
}

template<class E1,class E2>
detail::binary<E1,E2,detail::cal_binary_ldexp<typename E1::value_type,typename E2::value_type> > ldexp( const detail::expression<E1>& e1, const detail::expression<E2>& e2 )
{
    typedef detail::binary<E1,E2,detail::cal_binary_ldexp<typename E1::value_type,typename E2::value_type> > expression_type;
    return expression_type( e1(), e2() );
}

template<class E1,class E2>
variable<typename E1::value_type> frexp( const detail::expression<E1>& e1, variable<E2>& e2 )
{
    return detail::frexp(e1(),e2,typename E1::value_type());
}

template<class E1>
detail::unary<E1,detail::cal_unary_rsq<typename E1::value_type> > rsqrt( const detail::expression<E1>& e1  )
{
    typedef detail::unary<E1,detail::cal_unary_rsq<typename E1::value_type> > expression_type;
    return expression_type(e1);
}

} // il
} // cal

#endif
