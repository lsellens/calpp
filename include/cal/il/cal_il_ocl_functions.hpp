/*
 * C++ to IL OpenCL functions implementation
 * 
 * Copyright (C) 2010, 2011 Artur Kornacki
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

#include <cassert>

namespace cal {
namespace il {

template<class E1,class E2,class E3>
detail::ternary<E1,E2,E3,detail::cal_ternary_select<typename E1::value_type,typename E2::value_type,typename E3::value_type> >
select( const detail::expression<E1>& e1, const detail::expression<E2>& e2, const detail::expression<E3>& e3 )
{
    typedef detail::ternary<E1,E2,E3,detail::cal_ternary_select<typename E1::value_type,typename E2::value_type,typename E3::value_type> > expression_type;
    return expression_type(e1(),e2(),e3());
}

template<class E1,class E2>
detail::ternary<E1,E2,detail::value<E2>,detail::cal_ternary_select<typename E1::value_type,typename E2::value_type,typename E2::value_type> >
select( const detail::expression<E1>& e1, const detail::expression<E2>& e2, const typename E2::value_type::component_type& v1 )
{
    typedef detail::ternary<E1,E2,detail::value<E2>,detail::cal_ternary_select<typename E1::value_type,typename E2::value_type,typename E2::value_type> > expression_type;
    return expression_type(e1(),e2(),detail::value<E2>(v1));
}

template<class E1,class E2>
detail::ternary<E1,detail::value<E2>,E2,detail::cal_ternary_select<typename E1::value_type,typename E2::value_type,typename E2::value_type> >
select( const detail::expression<E1>& e1, const typename E2::value_type::component_type& v1, const detail::expression<E2>& e2 )
{
    typedef detail::ternary<E1,detail::value<E2>,E2,detail::cal_ternary_select<typename E1::value_type,typename E2::value_type,typename E2::value_type> > expression_type;
    return expression_type(e1(),detail::value<E2>(v1),e2());
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

template<class E1>
detail::unary<E1,detail::cal_unary_bitcast<int1_type,typename E1::value_type> > as_int1( const detail::expression<E1>& e1 )
{
    return cast_bits<int1_type>(e1());
}

template<class E1>
detail::unary<E1,detail::cal_unary_bitcast<int2_type,typename E1::value_type> > as_int2( const detail::expression<E1>& e1 )
{
    return cast_bits<int2_type>(e1());
}

template<class E1>
detail::unary<E1,detail::cal_unary_bitcast<int4_type,typename E1::value_type> > as_int4( const detail::expression<E1>& e1 )
{
    return cast_bits<int4_type>(e1());
}

template<class E1>
detail::unary<E1,detail::cal_unary_bitcast<uint1_type,typename E1::value_type> > as_uint1( const detail::expression<E1>& e1 )
{
    return cast_bits<uint1_type>(e1());
}

template<class E1>
detail::unary<E1,detail::cal_unary_bitcast<uint2_type,typename E1::value_type> > as_uint2( const detail::expression<E1>& e1 )
{
    return cast_bits<uint2_type>(e1());
}

template<class E1>
detail::unary<E1,detail::cal_unary_bitcast<uint4_type,typename E1::value_type> > as_uint4( const detail::expression<E1>& e1 )
{
    return cast_bits<uint4_type>(e1());
}

template<class E1>
detail::unary<E1,detail::cal_unary_bitcast<float1_type,typename E1::value_type> > as_float1( const detail::expression<E1>& e1 )
{
    return cast_bits<float1_type>(e1());
}

template<class E1>
detail::unary<E1,detail::cal_unary_bitcast<float2_type,typename E1::value_type> > as_float2( const detail::expression<E1>& e1 )
{
    return cast_bits<float2_type>(e1());
}

template<class E1>
detail::unary<E1,detail::cal_unary_bitcast<float4_type,typename E1::value_type> > as_float4( const detail::expression<E1>& e1 )
{
    return cast_bits<float4_type>(e1());
}

template<class E1>
detail::unary<E1,detail::cal_unary_bitcast<double1_type,typename E1::value_type> > as_double1( const detail::expression<E1>& e1 )
{
    return cast_bits<double1_type>(e1());
}

template<class E1>
detail::unary<E1,detail::cal_unary_bitcast<double2_type,typename E1::value_type> > as_double2( const detail::expression<E1>& e1 )
{
    return cast_bits<double2_type>(e1());
}

template<class E1,class E2>
variable<typename E1::value_type> rotate( const detail::expression<E1>& e1, const detail::expression<E2>& e2 )
{
#if defined(__CAL_H__)
    if( Source::info().available && Source::info().target>=CAL_TARGET_CYPRESS ) {
        if( E1::value_type::component_count>1 && E2::value_type::component_count==1 ) {
            variable<typename E2::value_type> p = value<typename E2::value_type>(32)-e2();

            if( E1::value_type::component_count==2 ) return bitalign(e1(),e1(),p.xx());

            assert( E1::value_type::component_count==4 );
            return bitalign(e1(),e1(),p.xxxx());
        }
        return bitalign(e1(),e1(),value<typename E2::value_type>(32)-e2());
    }
#endif
    return (e1()<<e2()) | (e1() >> (value<typename E2::value_type>(32)-e2()));
}

template<class E1>
variable<typename E1::value_type> rotate( const detail::expression<E1>& e1, int shift )
{
#if defined(__CAL_H__)
    if( Source::info().available && Source::info().target>=CAL_TARGET_CYPRESS ) {
        return bitalign(e1(),e1(),value<typename detail::resize_base_type<uint_type,E1::value_type::component_count>::value>(32-shift));
    }
#endif
    return ( e1() << value<uint_type>(shift) ) |
           ( e1() >> value<uint_type>(32-shift) );
}

template<class E1,class E2,class E3>
variable<typename E1::value_type> bitselect( const detail::expression<E1>& e1, const detail::expression<E2>& e2, const detail::expression<E3>& e3 )
{
#if defined(__CAL_H__)
    typedef detail::ternary<E1,E2,E3,detail::cal_ternary_bfi<typename E1::value_type,typename E2::value_type,typename E3::value_type> > expression_type;
    if( Source::info().available && Source::info().target>=CAL_TARGET_CYPRESS ) {
        return expression_type(e3(),e2(),e1());
    }
#endif
    return (e1() & ~e3()) | (e2() & e3());
}

} // il
} // cal

#endif
