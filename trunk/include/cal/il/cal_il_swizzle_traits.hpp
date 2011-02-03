/*
 * C++ to IL compiler/generator register swizzle traits
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

#ifndef __CAL_IL_SWIZZLE_TRAITS_H
#define __CAL_IL_SWIZZLE_TRAITS_H

namespace cal {
namespace il {
namespace detail {

template<class T,int P0,int P1,int P2,int P3> struct swizzle_traits
{
    typedef invalid_swizzle value_type;
};

#define __SWIZZLE_TRAITS_FOR_TYPE(TYPE) \
template<> struct swizzle_traits< TYPE##_type,1,0,0,0> { typedef TYPE##_type value_type; static const int i0=1; static const int i1=0; static const int i2=0; static const int i3=0; }; \
template<> struct swizzle_traits< TYPE##2_type,1,0,0,0> { typedef TYPE##_type value_type; static const int i0=1; static const int i1=0; static const int i2=0; static const int i3=0; }; \
template<> struct swizzle_traits< TYPE##2_type,2,0,0,0> { typedef TYPE##_type value_type; static const int i0=2; static const int i1=0; static const int i2=0; static const int i3=0; }; \
template<> struct swizzle_traits< TYPE##2_type,1,1,0,0> { typedef TYPE##2_type value_type; static const int i0=1; static const int i1=1; static const int i2=0; static const int i3=0; }; \
template<> struct swizzle_traits< TYPE##2_type,1,2,0,0> { typedef TYPE##2_type value_type; static const int i0=1; static const int i1=2; static const int i2=0; static const int i3=0; }; \
template<> struct swizzle_traits< TYPE##2_type,2,1,0,0> { typedef TYPE##2_type value_type; static const int i0=2; static const int i1=1; static const int i2=0; static const int i3=0; }; \
template<> struct swizzle_traits< TYPE##2_type,2,2,0,0> { typedef TYPE##2_type value_type; static const int i0=2; static const int i1=2; static const int i2=0; static const int i3=0; }; \
template<> struct swizzle_traits< TYPE##4_type,1,0,0,0> { typedef TYPE##_type value_type; static const int i0=1; static const int i1=0; static const int i2=0; static const int i3=0; }; \
template<> struct swizzle_traits< TYPE##4_type,2,0,0,0> { typedef TYPE##_type value_type; static const int i0=2; static const int i1=0; static const int i2=0; static const int i3=0; }; \
template<> struct swizzle_traits< TYPE##4_type,3,0,0,0> { typedef TYPE##_type value_type; static const int i0=3; static const int i1=0; static const int i2=0; static const int i3=0; }; \
template<> struct swizzle_traits< TYPE##4_type,4,0,0,0> { typedef TYPE##_type value_type; static const int i0=4; static const int i1=0; static const int i2=0; static const int i3=0; }; \
template<> struct swizzle_traits< TYPE##4_type,1,1,0,0> { typedef TYPE##2_type value_type; static const int i0=1; static const int i1=1; static const int i2=0; static const int i3=0; }; \
template<> struct swizzle_traits< TYPE##4_type,1,2,0,0> { typedef TYPE##2_type value_type; static const int i0=1; static const int i1=2; static const int i2=0; static const int i3=0; }; \
template<> struct swizzle_traits< TYPE##4_type,1,3,0,0> { typedef TYPE##2_type value_type; static const int i0=1; static const int i1=3; static const int i2=0; static const int i3=0; }; \
template<> struct swizzle_traits< TYPE##4_type,1,4,0,0> { typedef TYPE##2_type value_type; static const int i0=1; static const int i1=4; static const int i2=0; static const int i3=0; }; \
template<> struct swizzle_traits< TYPE##4_type,2,1,0,0> { typedef TYPE##2_type value_type; static const int i0=2; static const int i1=1; static const int i2=0; static const int i3=0; }; \
template<> struct swizzle_traits< TYPE##4_type,2,2,0,0> { typedef TYPE##2_type value_type; static const int i0=2; static const int i1=2; static const int i2=0; static const int i3=0; }; \
template<> struct swizzle_traits< TYPE##4_type,2,3,0,0> { typedef TYPE##2_type value_type; static const int i0=2; static const int i1=3; static const int i2=0; static const int i3=0; }; \
template<> struct swizzle_traits< TYPE##4_type,2,4,0,0> { typedef TYPE##2_type value_type; static const int i0=2; static const int i1=4; static const int i2=0; static const int i3=0; }; \
template<> struct swizzle_traits< TYPE##4_type,3,1,0,0> { typedef TYPE##2_type value_type; static const int i0=3; static const int i1=1; static const int i2=0; static const int i3=0; }; \
template<> struct swizzle_traits< TYPE##4_type,3,2,0,0> { typedef TYPE##2_type value_type; static const int i0=3; static const int i1=2; static const int i2=0; static const int i3=0; }; \
template<> struct swizzle_traits< TYPE##4_type,3,3,0,0> { typedef TYPE##2_type value_type; static const int i0=3; static const int i1=3; static const int i2=0; static const int i3=0; }; \
template<> struct swizzle_traits< TYPE##4_type,3,4,0,0> { typedef TYPE##2_type value_type; static const int i0=3; static const int i1=4; static const int i2=0; static const int i3=0; }; \
template<> struct swizzle_traits< TYPE##4_type,4,1,0,0> { typedef TYPE##2_type value_type; static const int i0=4; static const int i1=1; static const int i2=0; static const int i3=0; }; \
template<> struct swizzle_traits< TYPE##4_type,4,2,0,0> { typedef TYPE##2_type value_type; static const int i0=4; static const int i1=2; static const int i2=0; static const int i3=0; }; \
template<> struct swizzle_traits< TYPE##4_type,4,3,0,0> { typedef TYPE##2_type value_type; static const int i0=4; static const int i1=3; static const int i2=0; static const int i3=0; }; \
template<> struct swizzle_traits< TYPE##4_type,4,4,0,0> { typedef TYPE##2_type value_type; static const int i0=4; static const int i1=4; static const int i2=0; static const int i3=0; }; \
template<> struct swizzle_traits< TYPE##4_type,1,1,1,1> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=1; static const int i2=1; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,1,1,1,2> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=1; static const int i2=1; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,1,1,1,3> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=1; static const int i2=1; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,1,1,1,4> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=1; static const int i2=1; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,1,1,2,1> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=1; static const int i2=2; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,1,1,2,2> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=1; static const int i2=2; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,1,1,2,3> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=1; static const int i2=2; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,1,1,2,4> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=1; static const int i2=2; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,1,1,3,1> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=1; static const int i2=3; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,1,1,3,2> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=1; static const int i2=3; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,1,1,3,3> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=1; static const int i2=3; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,1,1,3,4> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=1; static const int i2=3; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,1,1,4,1> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=1; static const int i2=4; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,1,1,4,2> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=1; static const int i2=4; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,1,1,4,3> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=1; static const int i2=4; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,1,1,4,4> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=1; static const int i2=4; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,1,2,1,1> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=2; static const int i2=1; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,1,2,1,2> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=2; static const int i2=1; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,1,2,1,3> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=2; static const int i2=1; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,1,2,1,4> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=2; static const int i2=1; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,1,2,2,1> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=2; static const int i2=2; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,1,2,2,2> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=2; static const int i2=2; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,1,2,2,3> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=2; static const int i2=2; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,1,2,2,4> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=2; static const int i2=2; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,1,2,3,1> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=2; static const int i2=3; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,1,2,3,2> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=2; static const int i2=3; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,1,2,3,3> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=2; static const int i2=3; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,1,2,3,4> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=2; static const int i2=3; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,1,2,4,1> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=2; static const int i2=4; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,1,2,4,2> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=2; static const int i2=4; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,1,2,4,3> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=2; static const int i2=4; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,1,2,4,4> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=2; static const int i2=4; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,1,3,1,1> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=3; static const int i2=1; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,1,3,1,2> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=3; static const int i2=1; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,1,3,1,3> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=3; static const int i2=1; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,1,3,1,4> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=3; static const int i2=1; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,1,3,2,1> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=3; static const int i2=2; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,1,3,2,2> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=3; static const int i2=2; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,1,3,2,3> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=3; static const int i2=2; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,1,3,2,4> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=3; static const int i2=2; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,1,3,3,1> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=3; static const int i2=3; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,1,3,3,2> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=3; static const int i2=3; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,1,3,3,3> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=3; static const int i2=3; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,1,3,3,4> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=3; static const int i2=3; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,1,3,4,1> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=3; static const int i2=4; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,1,3,4,2> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=3; static const int i2=4; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,1,3,4,3> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=3; static const int i2=4; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,1,3,4,4> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=3; static const int i2=4; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,1,4,1,1> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=4; static const int i2=1; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,1,4,1,2> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=4; static const int i2=1; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,1,4,1,3> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=4; static const int i2=1; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,1,4,1,4> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=4; static const int i2=1; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,1,4,2,1> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=4; static const int i2=2; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,1,4,2,2> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=4; static const int i2=2; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,1,4,2,3> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=4; static const int i2=2; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,1,4,2,4> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=4; static const int i2=2; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,1,4,3,1> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=4; static const int i2=3; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,1,4,3,2> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=4; static const int i2=3; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,1,4,3,3> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=4; static const int i2=3; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,1,4,3,4> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=4; static const int i2=3; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,1,4,4,1> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=4; static const int i2=4; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,1,4,4,2> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=4; static const int i2=4; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,1,4,4,3> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=4; static const int i2=4; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,1,4,4,4> { typedef TYPE##4_type value_type; static const int i0=1; static const int i1=4; static const int i2=4; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,2,1,1,1> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=1; static const int i2=1; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,2,1,1,2> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=1; static const int i2=1; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,2,1,1,3> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=1; static const int i2=1; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,2,1,1,4> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=1; static const int i2=1; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,2,1,2,1> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=1; static const int i2=2; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,2,1,2,2> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=1; static const int i2=2; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,2,1,2,3> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=1; static const int i2=2; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,2,1,2,4> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=1; static const int i2=2; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,2,1,3,1> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=1; static const int i2=3; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,2,1,3,2> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=1; static const int i2=3; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,2,1,3,3> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=1; static const int i2=3; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,2,1,3,4> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=1; static const int i2=3; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,2,1,4,1> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=1; static const int i2=4; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,2,1,4,2> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=1; static const int i2=4; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,2,1,4,3> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=1; static const int i2=4; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,2,1,4,4> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=1; static const int i2=4; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,2,2,1,1> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=2; static const int i2=1; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,2,2,1,2> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=2; static const int i2=1; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,2,2,1,3> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=2; static const int i2=1; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,2,2,1,4> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=2; static const int i2=1; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,2,2,2,1> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=2; static const int i2=2; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,2,2,2,2> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=2; static const int i2=2; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,2,2,2,3> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=2; static const int i2=2; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,2,2,2,4> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=2; static const int i2=2; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,2,2,3,1> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=2; static const int i2=3; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,2,2,3,2> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=2; static const int i2=3; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,2,2,3,3> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=2; static const int i2=3; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,2,2,3,4> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=2; static const int i2=3; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,2,2,4,1> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=2; static const int i2=4; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,2,2,4,2> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=2; static const int i2=4; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,2,2,4,3> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=2; static const int i2=4; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,2,2,4,4> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=2; static const int i2=4; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,2,3,1,1> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=3; static const int i2=1; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,2,3,1,2> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=3; static const int i2=1; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,2,3,1,3> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=3; static const int i2=1; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,2,3,1,4> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=3; static const int i2=1; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,2,3,2,1> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=3; static const int i2=2; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,2,3,2,2> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=3; static const int i2=2; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,2,3,2,3> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=3; static const int i2=2; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,2,3,2,4> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=3; static const int i2=2; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,2,3,3,1> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=3; static const int i2=3; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,2,3,3,2> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=3; static const int i2=3; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,2,3,3,3> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=3; static const int i2=3; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,2,3,3,4> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=3; static const int i2=3; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,2,3,4,1> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=3; static const int i2=4; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,2,3,4,2> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=3; static const int i2=4; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,2,3,4,3> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=3; static const int i2=4; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,2,3,4,4> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=3; static const int i2=4; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,2,4,1,1> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=4; static const int i2=1; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,2,4,1,2> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=4; static const int i2=1; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,2,4,1,3> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=4; static const int i2=1; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,2,4,1,4> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=4; static const int i2=1; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,2,4,2,1> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=4; static const int i2=2; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,2,4,2,2> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=4; static const int i2=2; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,2,4,2,3> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=4; static const int i2=2; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,2,4,2,4> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=4; static const int i2=2; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,2,4,3,1> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=4; static const int i2=3; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,2,4,3,2> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=4; static const int i2=3; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,2,4,3,3> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=4; static const int i2=3; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,2,4,3,4> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=4; static const int i2=3; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,2,4,4,1> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=4; static const int i2=4; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,2,4,4,2> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=4; static const int i2=4; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,2,4,4,3> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=4; static const int i2=4; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,2,4,4,4> { typedef TYPE##4_type value_type; static const int i0=2; static const int i1=4; static const int i2=4; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,3,1,1,1> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=1; static const int i2=1; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,3,1,1,2> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=1; static const int i2=1; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,3,1,1,3> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=1; static const int i2=1; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,3,1,1,4> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=1; static const int i2=1; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,3,1,2,1> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=1; static const int i2=2; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,3,1,2,2> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=1; static const int i2=2; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,3,1,2,3> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=1; static const int i2=2; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,3,1,2,4> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=1; static const int i2=2; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,3,1,3,1> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=1; static const int i2=3; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,3,1,3,2> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=1; static const int i2=3; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,3,1,3,3> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=1; static const int i2=3; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,3,1,3,4> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=1; static const int i2=3; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,3,1,4,1> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=1; static const int i2=4; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,3,1,4,2> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=1; static const int i2=4; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,3,1,4,3> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=1; static const int i2=4; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,3,1,4,4> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=1; static const int i2=4; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,3,2,1,1> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=2; static const int i2=1; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,3,2,1,2> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=2; static const int i2=1; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,3,2,1,3> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=2; static const int i2=1; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,3,2,1,4> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=2; static const int i2=1; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,3,2,2,1> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=2; static const int i2=2; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,3,2,2,2> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=2; static const int i2=2; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,3,2,2,3> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=2; static const int i2=2; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,3,2,2,4> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=2; static const int i2=2; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,3,2,3,1> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=2; static const int i2=3; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,3,2,3,2> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=2; static const int i2=3; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,3,2,3,3> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=2; static const int i2=3; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,3,2,3,4> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=2; static const int i2=3; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,3,2,4,1> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=2; static const int i2=4; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,3,2,4,2> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=2; static const int i2=4; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,3,2,4,3> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=2; static const int i2=4; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,3,2,4,4> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=2; static const int i2=4; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,3,3,1,1> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=3; static const int i2=1; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,3,3,1,2> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=3; static const int i2=1; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,3,3,1,3> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=3; static const int i2=1; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,3,3,1,4> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=3; static const int i2=1; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,3,3,2,1> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=3; static const int i2=2; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,3,3,2,2> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=3; static const int i2=2; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,3,3,2,3> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=3; static const int i2=2; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,3,3,2,4> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=3; static const int i2=2; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,3,3,3,1> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=3; static const int i2=3; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,3,3,3,2> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=3; static const int i2=3; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,3,3,3,3> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=3; static const int i2=3; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,3,3,3,4> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=3; static const int i2=3; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,3,3,4,1> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=3; static const int i2=4; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,3,3,4,2> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=3; static const int i2=4; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,3,3,4,3> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=3; static const int i2=4; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,3,3,4,4> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=3; static const int i2=4; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,3,4,1,1> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=4; static const int i2=1; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,3,4,1,2> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=4; static const int i2=1; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,3,4,1,3> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=4; static const int i2=1; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,3,4,1,4> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=4; static const int i2=1; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,3,4,2,1> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=4; static const int i2=2; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,3,4,2,2> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=4; static const int i2=2; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,3,4,2,3> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=4; static const int i2=2; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,3,4,2,4> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=4; static const int i2=2; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,3,4,3,1> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=4; static const int i2=3; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,3,4,3,2> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=4; static const int i2=3; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,3,4,3,3> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=4; static const int i2=3; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,3,4,3,4> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=4; static const int i2=3; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,3,4,4,1> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=4; static const int i2=4; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,3,4,4,2> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=4; static const int i2=4; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,3,4,4,3> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=4; static const int i2=4; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,3,4,4,4> { typedef TYPE##4_type value_type; static const int i0=3; static const int i1=4; static const int i2=4; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,4,1,1,1> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=1; static const int i2=1; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,4,1,1,2> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=1; static const int i2=1; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,4,1,1,3> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=1; static const int i2=1; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,4,1,1,4> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=1; static const int i2=1; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,4,1,2,1> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=1; static const int i2=2; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,4,1,2,2> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=1; static const int i2=2; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,4,1,2,3> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=1; static const int i2=2; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,4,1,2,4> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=1; static const int i2=2; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,4,1,3,1> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=1; static const int i2=3; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,4,1,3,2> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=1; static const int i2=3; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,4,1,3,3> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=1; static const int i2=3; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,4,1,3,4> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=1; static const int i2=3; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,4,1,4,1> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=1; static const int i2=4; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,4,1,4,2> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=1; static const int i2=4; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,4,1,4,3> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=1; static const int i2=4; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,4,1,4,4> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=1; static const int i2=4; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,4,2,1,1> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=2; static const int i2=1; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,4,2,1,2> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=2; static const int i2=1; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,4,2,1,3> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=2; static const int i2=1; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,4,2,1,4> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=2; static const int i2=1; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,4,2,2,1> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=2; static const int i2=2; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,4,2,2,2> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=2; static const int i2=2; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,4,2,2,3> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=2; static const int i2=2; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,4,2,2,4> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=2; static const int i2=2; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,4,2,3,1> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=2; static const int i2=3; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,4,2,3,2> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=2; static const int i2=3; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,4,2,3,3> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=2; static const int i2=3; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,4,2,3,4> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=2; static const int i2=3; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,4,2,4,1> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=2; static const int i2=4; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,4,2,4,2> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=2; static const int i2=4; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,4,2,4,3> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=2; static const int i2=4; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,4,2,4,4> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=2; static const int i2=4; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,4,3,1,1> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=3; static const int i2=1; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,4,3,1,2> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=3; static const int i2=1; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,4,3,1,3> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=3; static const int i2=1; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,4,3,1,4> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=3; static const int i2=1; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,4,3,2,1> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=3; static const int i2=2; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,4,3,2,2> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=3; static const int i2=2; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,4,3,2,3> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=3; static const int i2=2; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,4,3,2,4> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=3; static const int i2=2; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,4,3,3,1> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=3; static const int i2=3; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,4,3,3,2> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=3; static const int i2=3; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,4,3,3,3> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=3; static const int i2=3; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,4,3,3,4> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=3; static const int i2=3; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,4,3,4,1> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=3; static const int i2=4; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,4,3,4,2> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=3; static const int i2=4; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,4,3,4,3> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=3; static const int i2=4; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,4,3,4,4> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=3; static const int i2=4; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,4,4,1,1> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=4; static const int i2=1; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,4,4,1,2> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=4; static const int i2=1; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,4,4,1,3> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=4; static const int i2=1; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,4,4,1,4> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=4; static const int i2=1; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,4,4,2,1> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=4; static const int i2=2; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,4,4,2,2> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=4; static const int i2=2; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,4,4,2,3> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=4; static const int i2=2; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,4,4,2,4> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=4; static const int i2=2; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,4,4,3,1> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=4; static const int i2=3; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,4,4,3,2> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=4; static const int i2=3; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,4,4,3,3> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=4; static const int i2=3; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,4,4,3,4> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=4; static const int i2=3; static const int i3=4; }; \
template<> struct swizzle_traits< TYPE##4_type,4,4,4,1> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=4; static const int i2=4; static const int i3=1; }; \
template<> struct swizzle_traits< TYPE##4_type,4,4,4,2> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=4; static const int i2=4; static const int i3=2; }; \
template<> struct swizzle_traits< TYPE##4_type,4,4,4,3> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=4; static const int i2=4; static const int i3=3; }; \
template<> struct swizzle_traits< TYPE##4_type,4,4,4,4> { typedef TYPE##4_type value_type; static const int i0=4; static const int i1=4; static const int i2=4; static const int i3=4; }; 

__SWIZZLE_TRAITS_FOR_TYPE(float);
__SWIZZLE_TRAITS_FOR_TYPE(int);
__SWIZZLE_TRAITS_FOR_TYPE(uint);

#undef __SWIZZLE_TRAITS_FOR_TYPE

template<> struct swizzle_traits<double_type,1,0,0,0> { typedef double_type value_type; static const int i0=1; static const int i1=2; static const int i2=0; static const int i3=0; };

template<> struct swizzle_traits<double2_type,1,0,0,0> { typedef double_type value_type; static const int i0=1; static const int i1=2; static const int i2=0; static const int i3=0; };
template<> struct swizzle_traits<double2_type,2,0,0,0> { typedef double_type value_type; static const int i0=3; static const int i1=4; static const int i2=0; static const int i3=0; };

template<> struct swizzle_traits<double2_type,1,1,0,0> { typedef double2_type value_type; static const int i0=1; static const int i1=2; static const int i2=1; static const int i3=2; };
template<> struct swizzle_traits<double2_type,1,2,0,0> { typedef double2_type value_type; static const int i0=1; static const int i1=2; static const int i2=3; static const int i3=4; };
template<> struct swizzle_traits<double2_type,2,1,0,0> { typedef double2_type value_type; static const int i0=3; static const int i1=4; static const int i2=1; static const int i3=2; };
template<> struct swizzle_traits<double2_type,2,2,0,0> { typedef double2_type value_type; static const int i0=3; static const int i1=4; static const int i2=3; static const int i3=4; };

} // detail

} // il
} // cal

#endif
