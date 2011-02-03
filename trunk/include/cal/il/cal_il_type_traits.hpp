/*
 * C++ to IL compiler/generator type traits
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

#ifndef __CAL_IL_TYPE_TRAITS_H
#define __CAL_IL_TYPE_TRAITS_H

#include <boost/cstdint.hpp>
#include <boost/type_traits.hpp>

namespace cal {
namespace il {

namespace detail {

template<typename T> struct is_floating_point : public boost::false_type {};
template<> struct is_floating_point<float_type> : public boost::true_type {};
template<> struct is_floating_point<float2_type> : public boost::true_type {};
template<> struct is_floating_point<float4_type> : public boost::true_type {};
template<> struct is_floating_point<double_type> : public boost::true_type {};
template<> struct is_floating_point<double2_type> : public boost::true_type {};

} // detail

template<typename T>
struct component_type
{
    typedef typename detail::base_cal_type<T>::value::component_type value;
};

template<typename T,int W>
struct resize_type
{
    typedef variable<typename detail::resize_base_type<typename detail::base_cal_type<T>::value,W>::value> value;
};

template<typename T>
struct component_count
{
    static const int value = detail::base_cal_type<T>::value::component_count;
};

template<typename T> struct is_floating_point : public detail::is_floating_point<typename detail::base_cal_type<T>::value> {};

template<typename T,int W>
struct make_cal_type {};

template<> struct make_cal_type<boost::uint32_t,1> { typedef uint1   value; };
template<> struct make_cal_type<boost::uint32_t,2> { typedef uint2   value; };
template<> struct make_cal_type<boost::uint32_t,4> { typedef uint4   value; };
template<> struct make_cal_type<boost::int32_t,1>  { typedef int1    value; };
template<> struct make_cal_type<boost::int32_t,2>  { typedef int2    value; };
template<> struct make_cal_type<boost::int32_t,4>  { typedef int4    value; };
template<> struct make_cal_type<float,1>           { typedef float1  value; };
template<> struct make_cal_type<float,2>           { typedef float2  value; };
template<> struct make_cal_type<float,4>           { typedef float4  value; };
template<> struct make_cal_type<double,1>          { typedef double1 value; };
template<> struct make_cal_type<double,2>          { typedef double2 value; };
template<> struct make_cal_type<double,4>          { typedef double2 value; };

} // il
} // cal

#endif
