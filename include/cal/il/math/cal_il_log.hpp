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
variable<typename E1::value_type> log( const expression<E1>& a, double_type  )
{
    double1   x;

    x = cast_type<double_type>( log( cast_type<float_type>(a()) ) );

    x = x + a*exp(-x,double_type()) - double1(1.);    
    return x + a*exp(-x,double_type()) - double1(1.);
}

template<class E1>
variable<typename E1::value_type> log( const expression<E1>& a, double2_type  )
{
    double2   x;

    x = cast_type<double2_type>( log( cast_type<float2_type>(a) ) );
   
    x = x + a*exp(-x,double2_type()) - double2(1.);
    return x + a*exp(-x,double2_type()) - double2(1.);
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
