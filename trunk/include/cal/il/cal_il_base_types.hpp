/*
 * C++ to IL compiler/generator base types
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

#ifndef __CAL_IL_BASE_TYPES_H
#define __CAL_IL_BASE_TYPES_H

#include <boost/cstdint.hpp>

namespace cal {
namespace il {

struct invalid_type
{
    typedef void   component_type;
    
    static const int type_size  = 0;
    static const int component_count = 0;
    static const int component_size  = 0;
};

struct invalid_swizzle
{
    typedef void   component_type;
    
    static const int type_size  = 0;
    static const int component_count = 0;
    static const int component_size  = 0;
};

struct uint_type
{
    typedef boost::uint32_t  component_type;
    
    static const int type_size  = 1;
    static const int component_count = 1;
    static const int component_size  = 1;
};

struct uint2_type
{
    typedef boost::uint32_t   component_type;
    
    static const int type_size  = 2;
    static const int component_count = 2;
    static const int component_size  = 1;
};

struct uint4_type
{
    typedef boost::uint32_t   component_type;
    
    static const int type_size  = 4;
    static const int component_count = 4;
    static const int component_size  = 1;
};

struct int_type
{
    typedef boost::int32_t   component_type;
    
    static const int type_size  = 1;
    static const int component_count = 1;
    static const int component_size  = 1;
};

struct int2_type
{
    typedef boost::int32_t   component_type;
    
    static const int type_size  = 2;
    static const int component_count = 2;
    static const int component_size  = 1;
};

struct int4_type
{
    typedef boost::int32_t   component_type;
    
    static const int type_size  = 4;
    static const int component_count = 4;
    static const int component_size  = 1;
};

struct float_type
{
    typedef float   component_type;
    
    static const int type_size  = 1;
    static const int component_count = 1;
    static const int component_size  = 1;
    
};

struct float2_type
{
    typedef float   component_type;
    
    static const int type_size  = 2;
    static const int component_count = 2;
    static const int component_size  = 1;
};

struct float4_type
{
    typedef float   component_type;
    
    static const int type_size  = 4;
    static const int component_count = 4;
    static const int component_size  = 1;
};

struct double_type
{
    typedef double   component_type;
    
    static const int type_size  = 2;
    static const int component_count = 1;
    static const int component_size  = 2;
};

struct double2_type
{
    typedef double   component_type;
    
    static const int type_size  = 4;
    static const int component_count = 2;
    static const int component_size  = 2;
};

typedef int_type        int1_type;
typedef uint_type       uint1_type;
typedef float_type      float1_type;
typedef double_type     double1_type;

namespace detail {

template<typename B>
struct base_cal_type
{
    typedef typename B::value_type value;
};

template<> struct base_cal_type<int_type> { typedef int_type value; };
template<> struct base_cal_type<int2_type> { typedef int2_type value; };
template<> struct base_cal_type<int4_type> { typedef int4_type value; };
template<> struct base_cal_type<uint_type> { typedef uint_type value; };
template<> struct base_cal_type<uint2_type> { typedef uint2_type value; };
template<> struct base_cal_type<uint4_type> { typedef uint4_type value; };
template<> struct base_cal_type<float_type> { typedef float_type value; };
template<> struct base_cal_type<float2_type> { typedef float2_type value; };
template<> struct base_cal_type<float4_type> { typedef float4_type value; };
template<> struct base_cal_type<double_type> { typedef double_type value; };
template<> struct base_cal_type<double2_type> { typedef double2_type value; };

template<typename B,int W>
struct resize_base_type {};

template<> struct resize_base_type<int_type,1> { typedef int_type value; };
template<> struct resize_base_type<int_type,2> { typedef int2_type value; };
template<> struct resize_base_type<int_type,4> { typedef int4_type value; };
template<> struct resize_base_type<int2_type,1> { typedef int_type value; };
template<> struct resize_base_type<int2_type,2> { typedef int2_type value; };
template<> struct resize_base_type<int2_type,4> { typedef int4_type value; };
template<> struct resize_base_type<int4_type,1> { typedef int_type value; };
template<> struct resize_base_type<int4_type,2> { typedef int2_type value; };
template<> struct resize_base_type<int4_type,4> { typedef int4_type value; };

template<> struct resize_base_type<uint_type,1> { typedef uint_type value; };
template<> struct resize_base_type<uint_type,2> { typedef uint2_type value; };
template<> struct resize_base_type<uint_type,4> { typedef uint4_type value; };
template<> struct resize_base_type<uint2_type,1> { typedef uint_type value; };
template<> struct resize_base_type<uint2_type,2> { typedef uint2_type value; };
template<> struct resize_base_type<uint2_type,4> { typedef uint4_type value; };
template<> struct resize_base_type<uint4_type,1> { typedef uint_type value; };
template<> struct resize_base_type<uint4_type,2> { typedef uint2_type value; };
template<> struct resize_base_type<uint4_type,4> { typedef uint4_type value; };

template<> struct resize_base_type<float_type,1> { typedef float_type value; };
template<> struct resize_base_type<float_type,2> { typedef float2_type value; };
template<> struct resize_base_type<float_type,4> { typedef float4_type value; };
template<> struct resize_base_type<float2_type,1> { typedef float_type value; };
template<> struct resize_base_type<float2_type,2> { typedef float2_type value; };
template<> struct resize_base_type<float2_type,4> { typedef float4_type value; };
template<> struct resize_base_type<float4_type,1> { typedef float_type value; };
template<> struct resize_base_type<float4_type,2> { typedef float2_type value; };
template<> struct resize_base_type<float4_type,4> { typedef float4_type value; };

template<> struct resize_base_type<double_type,1> { typedef double_type value; };
template<> struct resize_base_type<double_type,2> { typedef double2_type value; };
template<> struct resize_base_type<double2_type,1> { typedef double_type value; };
template<> struct resize_base_type<double2_type,2> { typedef double2_type value; };

} // detail

} // il
} // cal

#endif
