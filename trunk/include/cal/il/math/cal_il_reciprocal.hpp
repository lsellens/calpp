/*
 * C++ to IL compiler/generator reciprocal
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

#ifndef __CAL_IL_MATH_RECIPROCAL_H
#define __CAL_IL_MATH_RECIPROCAL_H

namespace cal {
namespace il {

namespace detail {

template<class E1>
detail::unary<E1,detail::cal_unary_rcp<typename E1::value_type> > native_reciprocal( const detail::expression<E1>& e1, float_type )
{
    typedef detail::unary<E1,detail::cal_unary_rcp<typename E1::value_type> > expression_type;
    return expression_type(e1());
}

template<class E1>
detail::unary<E1,detail::cal_unary_rcp<typename E1::value_type> > native_reciprocal( const detail::expression<E1>& e1, float2_type )
{
    typedef detail::unary<E1,detail::cal_unary_rcp<typename E1::value_type> > expression_type;
    return expression_type(e1());
}

template<class E1>
detail::unary<E1,detail::cal_unary_rcp<typename E1::value_type> > native_reciprocal( const detail::expression<E1>& e1, float4_type )
{
    typedef detail::unary<E1,detail::cal_unary_rcp<typename E1::value_type> > expression_type;
    return expression_type(e1());
}

template<class E1>
variable<typename E1::value_type> native_reciprocal( const detail::expression<E1>& e1, double_type )
{
    typedef detail::unary<E1,detail::cal_unary_rcp<typename E1::value_type> >        rcp_type;

#if defined(__CAL_H__)
    if( Source::info.available && Source::info.target>=CAL_TARGET_CYPRESS ) return rcp_type(e1());
#endif
    double1 s;
    int1    e;

    s = frexp(e1(),e);
    s = cast_type<double1>( native_reciprocal(cast_type<float1>(s),float_type()) );
    s = ldexp(s,-e);

    return s;
}

template<class E1>
variable<typename E1::value_type> native_reciprocal( const detail::expression<E1>& e1, double2_type )
{
    typedef detail::unary<E1,detail::cal_unary_rcp<typename E1::value_type> >        rcp_type;

#if defined(__CAL_H__)
    if( Source::info.available && Source::info.target>=CAL_TARGET_CYPRESS ) return rcp_type(e1());
#endif
    double2 s;
    int2    e;

    s = frexp(e1(),e);
    s = cast_type<double2>( native_reciprocal(cast_type<float2>(s),float2_type()) );
    s = ldexp(s,-e);

    return s;
}

template<class E1>
unary<E1,cal_unary_rcp<typename E1::value_type> > reciprocal( const expression<E1>& e1, float_type  )
{
    typedef unary<E1,cal_unary_rcp<typename E1::value_type> > expression_type;
    return expression_type(e1);
}

template<class E1>
unary<E1,cal_unary_rcp<typename E1::value_type> > reciprocal( const expression<E1>& e1, float2_type  )
{
    typedef unary<E1,cal_unary_rcp<typename E1::value_type> > expression_type;
    return expression_type(e1());
}

template<class E1>
unary<E1,cal_unary_rcp<typename E1::value_type> > reciprocal( const expression<E1>& e1, float4_type  )
{
    typedef unary<E1,cal_unary_rcp<typename E1::value_type> > expression_type;
    return expression_type(e1());
}

template<class E1>
variable<typename E1::value_type> reciprocal( const expression<E1>& ed, double_type  )
{
    double1 d,s,t;

    d = ed();
    s = native_reciprocal(d,double_type());

    // Newton-Raphson iterations
    t = mad( -d, s, double1(1) );
    s = mad(  s, t, s );
    t = mad( -d, s, double1(1) );
    s = mad(  s, t, s );

    return s;
}

template<class E1>
variable<typename E1::value_type> reciprocal( const expression<E1>& ed, double2_type  )
{
    double2 d,s,t;

    d = ed();
    s = native_reciprocal(d,double2_type());

    // Newton-Raphson iterations
    t = mad( -d, s, double2(1) );
    s = mad(  s, t, s );
    t = mad( -d, s, double2(1) );
    s = mad(  s, t, s );

    return s;
}

} // detail

template<class E1>
variable<typename E1::value_type> native_reciprocal( const detail::expression<E1>& e1 )
{
    return detail::native_reciprocal(e1(),typename E1::value_type());
}

//
// error for double <= 0.5ulp
//
template<class E1>
variable<typename E1::value_type> reciprocal( const detail::expression<E1>& e1 )
{
    return detail::reciprocal(e1(),typename E1::value_type());
}

} // il
} // cal

#endif
