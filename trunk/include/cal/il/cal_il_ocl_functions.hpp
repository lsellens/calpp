/*
 * C++ to IL OpenCL functions implementation
 * 
 * Copyright (C) 2010 Artur Kornacki
 *
 * This file is part of CAL++.
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

#ifndef __CAL_IL_OCL_FUNCTIONS_H
#define __CAL_IL_OCL_FUNCTIONS_H

#include <boost/static_assert.hpp>
#include <boost/format.hpp>
#include <cal/il/cal_il_expression_types.hpp>
#include <cal/il/cal_il_multimedia.hpp>
#include <cal/il/cal_il_types.hpp>

namespace cal {
namespace il {

template<class E1,class E2,class E3>
detail::ternary<E1,E2,E3,detail::cal_ternary_cmov_logical<typename E1::value_type,typename E2::value_type,typename E3::value_type> >
select( const detail::expression<E1>& e1, const detail::expression<E2>& e2, const detail::expression<E3>& e3 )
{
    typedef detail::ternary<E1,E2,E3,detail::cal_ternary_cmov_logical<typename E1::value_type,typename E2::value_type,typename E3::value_type> > expression_type;
    return expression_type(e1(),e2(),e3());
}

template<class E1>
detail::unary<E1,detail::cal_unary_cast<int1_type,typename E1::value_type> > convert_int1( const detail::expression<E1>& e1 )
{
    return cast_type<int1_type>(e1());
}

template<class E1>
detail::unary<E1,detail::cal_unary_cast<int2_type,typename E1::value_type> > convert_int2( const detail::expression<E1>& e1 )
{
    return cast_type<int2_type>(e1());
}

template<class E1>
detail::unary<E1,detail::cal_unary_cast<int4_type,typename E1::value_type> > convert_int4( const detail::expression<E1>& e1 )
{
    return cast_type<int4_type>(e1());
}

template<class E1>
detail::unary<E1,detail::cal_unary_cast<uint1_type,typename E1::value_type> > convert_uint1( const detail::expression<E1>& e1 )
{
    return cast_type<uint1_type>(e1());
}

template<class E1>
detail::unary<E1,detail::cal_unary_cast<uint2_type,typename E1::value_type> > convert_uint2( const detail::expression<E1>& e1 )
{
    return cast_type<uint2_type>(e1());
}

template<class E1>
detail::unary<E1,detail::cal_unary_cast<uint4_type,typename E1::value_type> > convert_uint4( const detail::expression<E1>& e1 )
{
    return cast_type<uint4_type>(e1());
}

template<class E1>
detail::unary<E1,detail::cal_unary_cast<float1_type,typename E1::value_type> > convert_float1( const detail::expression<E1>& e1 )
{
    return cast_type<float1_type>(e1());
}

template<class E1>
detail::unary<E1,detail::cal_unary_cast<float2_type,typename E1::value_type> > convert_float2( const detail::expression<E1>& e1 )
{
    return cast_type<float2_type>(e1());
}

template<class E1>
detail::unary<E1,detail::cal_unary_cast<float4_type,typename E1::value_type> > convert_float4( const detail::expression<E1>& e1 )
{
    return cast_type<float4_type>(e1());
}

template<class E1>
detail::unary<E1,detail::cal_unary_cast<double1_type,typename E1::value_type> > convert_double1( const detail::expression<E1>& e1 )
{
    return cast_type<double1_type>(e1());
}

template<class E1>
detail::unary<E1,detail::cal_unary_cast<double2_type,typename E1::value_type> > convert_double2( const detail::expression<E1>& e1 )
{
    return cast_type<double2_type>(e1());
}

template<class E1,class E2>
variable<typename detail::cal_binary_shl<typename E1::value_type,typename E2::value_type>::value_type> rotate( const detail::expression<E1>& e1, const detail::expression<E2>& e2 )
{
    return (e1()<<e2()) | (e1() >> (variable<typename E2::value_type>(32)-e2()));
}

template<class E1>
variable<typename E1::value_type> rotate( const detail::expression<E1>& e1, int shift )
{
    return ( e1() << variable<typename detail::resize_base_type<uint_type,E1::value_type::component_count>::value>(shift) ) |
           ( e1() >> variable<typename detail::resize_base_type<uint_type,E1::value_type::component_count>::value>(32-shift) );
}

} // il
} // cal

#endif
