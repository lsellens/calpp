/*
 * C++ to IL compiler/generator operation functors
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

#ifndef __CAL_IL_FUNCTORS_CAST_H
#define __CAL_IL_FUNCTORS_CAST_H

#include <boost/format.hpp>
#include <boost/static_assert.hpp>
#include <cal/il/cal_il_base_types.hpp>
#include <cal/il/cal_il_swizzle.hpp>

namespace cal {
namespace il {
namespace detail {

//
// type conversion
//

template<class S1,class S2>
struct cal_unary_cast {
    typedef invalid_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        BOOST_STATIC_ASSERT(sizeof(S1) != sizeof(S1));
        return std::string();
    }    
};

template<>
struct cal_unary_cast<int_type,uint_type>
{
    typedef int_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_cast<int_type,float_type>
{
    typedef int_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("ftoi %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_cast<int_type,double_type>
{
    typedef int_type value_type;
    static const int temp_reg_count=1;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("d2f r%3%.x, %2%\n"
                              "ftoi %1%,r%3%.x\n") % r % s0 % t0).str();
    }
};

template<>
struct cal_unary_cast<int2_type,uint2_type>
{
    typedef int2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_cast<int2_type,float2_type>
{
    typedef int2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("ftoi %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_cast<int2_type,double2_type>
{
    typedef int2_type value_type;
    static const int temp_reg_count=1;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("d2f r%4%.x, %2%\n"
                              "d2f r%4%.y, %3%\n"
                              "ftoi %1%,r%4%.xy\n") % r % make_swizzle(s0,1,2,0,0) % make_swizzle(s0,3,4,0,0) % t0).str();
    }
};

template<>
struct cal_unary_cast<int4_type,uint4_type>
{
    typedef int4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_cast<int4_type,float4_type>
{
    typedef int4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("ftoi %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_cast<uint_type,int_type>
{
    typedef uint_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_cast<uint_type,float_type>
{
    typedef uint_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("ftou %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_cast<uint_type,double_type>
{
    typedef uint_type value_type;
    static const int temp_reg_count=1;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("d2f r%3%.x, %2%\n"
                              "ftou %1%,r%3%.x\n") % r % s0 % t0).str();
    }
};

template<>
struct cal_unary_cast<uint2_type,int2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_cast<uint2_type,float2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("ftou %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_cast<uint2_type,double2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=1;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("d2f r%4%.x, %2%\n"
                              "d2f r%4%.y, %3%\n"
                              "ftou %1%,r%4%.xy\n") % r % make_swizzle(s0,1,2,0,0) % make_swizzle(s0,3,4,0,0) % t0).str();
    }
};

template<>
struct cal_unary_cast<uint4_type,int4_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_cast<uint4_type,float4_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("ftou %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_cast<float_type,int_type>
{
    typedef float_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("itof %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_cast<float_type,uint_type>
{
    typedef float_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("utof %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_cast<float_type,double_type>
{
    typedef float_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("dtof %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_cast<float2_type,int2_type>
{
    typedef float2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("itof %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_cast<float2_type,uint2_type>
{
    typedef float2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("utof %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_cast<float2_type,double2_type>
{
    typedef float2_type value_type;
    static const int temp_reg_count=1;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("d2f r%4%.x, %2%\n"
                              "d2f r%4%.y, %3%\n"
                              "mov %1%,r%4%.xy\n") % r % make_swizzle(s0,1,2,0,0) % make_swizzle(s0,3,4,0,0) % t0).str();
    }
};

template<>
struct cal_unary_cast<float4_type,int4_type>
{
    typedef float4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("itof %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_cast<float4_type,uint4_type>
{
    typedef float4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("utof %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_cast<double_type,int_type>
{
    typedef double_type value_type;
    static const int temp_reg_count=1;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("itof r%3%.x,%2%\n"
                              "f2d %1%,r%3%.x\n") % r % s0 % t0).str();
    }
};

template<>
struct cal_unary_cast<double_type,uint_type>
{
    typedef double_type value_type;
    static const int temp_reg_count=1;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("utof r%3%.x,%2%\n"
                              "f2d %1%,r%3%.x\n") % r % s0 % t0).str();
    }
};

template<>
struct cal_unary_cast<double_type,float_type>
{
    typedef double_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("f2d %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_cast<double2_type,int2_type>
{
    typedef double2_type value_type;
    static const int temp_reg_count=1;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("itof r%4%.xy,%3%\n"
                              "f2d %1%,r%4%.x\n"
                              "f2d %2%,r%4%.y\n") % make_swizzle(r,1,2,0,0) % make_swizzle(r,3,4,0,0) % s0 % t0).str();
    }
};

template<>
struct cal_unary_cast<double2_type,uint2_type>
{
    typedef double2_type value_type;
    static const int temp_reg_count=1;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("utof r%4%.xy,%3%\n"
                              "f2d %1%,r%4%.x\n"
                              "f2d %2%,r%4%.y\n") % make_swizzle(r,1,2,0,0) % make_swizzle(r,3,4,0,0) % s0 % t0).str();
    }
};

template<>
struct cal_unary_cast<double2_type,float2_type>
{
    typedef double2_type value_type;
    static const int temp_reg_count=1;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov r%4%.xy,%3%\n"
                              "f2d %1%,r%4%.x\n"
                              "f2d %2%,r%4%.y\n") % make_swizzle(r,1,2,0,0) % make_swizzle(r,3,4,0,0) % s0 % t0).str();
    }
};

//
// bit (as) conversion
//

template<class S1,class S2>
struct cal_unary_bitcast {
    typedef invalid_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        BOOST_STATIC_ASSERT(sizeof(S1) != sizeof(S1));
        return std::string();
    }
};

template<>
struct cal_unary_bitcast<int_type,uint_type>
{
    typedef int_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_bitcast<int_type,float_type>
{
    typedef int_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_bitcast<int2_type,uint2_type>
{
    typedef int2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_bitcast<int2_type,float2_type>
{
    typedef int2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_bitcast<int2_type,double_type>
{
    typedef int2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_bitcast<int4_type,uint4_type>
{
    typedef int4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_bitcast<int4_type,float4_type>
{
    typedef int4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_bitcast<int4_type,double2_type>
{
    typedef int4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_bitcast<uint_type,int_type>
{
    typedef uint_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_bitcast<uint_type,float_type>
{
    typedef uint_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_bitcast<uint2_type,int2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_bitcast<uint2_type,float2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_bitcast<uint2_type,double_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_bitcast<uint4_type,int4_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_bitcast<uint4_type,float4_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_bitcast<uint4_type,double2_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_bitcast<float_type,int_type>
{
    typedef float_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_bitcast<float_type,uint_type>
{
    typedef float_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_bitcast<float2_type,int2_type>
{
    typedef float2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_bitcast<float2_type,uint2_type>
{
    typedef float2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_bitcast<float2_type,double_type>
{
    typedef float2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_bitcast<float4_type,int4_type>
{
    typedef float4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_bitcast<float4_type,uint4_type>
{
    typedef float4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_bitcast<float4_type,double2_type>
{
    typedef float4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_bitcast<double_type,int2_type>
{
    typedef double_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_bitcast<double_type,uint2_type>
{
    typedef double_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_bitcast<double_type,float2_type>
{
    typedef double_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_bitcast<double2_type,int4_type>
{
    typedef double2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_bitcast<double2_type,uint4_type>
{
    typedef double2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %s,%s\n") % r % s0).str();
    }
};

template<>
struct cal_unary_bitcast<double2_type,float4_type>
{
    typedef double2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %s,%s\n") % r % s0).str();
    }
};

//
// merge 2 values into 1
//

template<class S1,class S2>
struct cal_binary_cast
{
    typedef invalid_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        BOOST_STATIC_ASSERT(sizeof(S1) != sizeof(S1));
        return std::string();
    }    
};

template<>
struct cal_binary_cast<int_type,int_type>
{
    typedef int2_type value_type;
    static const int temp_reg_count=1;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("mov r%4%.x,%2%\n"
                              "mov r%4%._y__,%3%\n"
                              "mov %1%,r%4%.xy\n") % r % s0 % make_swizzle(s1,1,1,1,1) % t0).str();
    }
};

template<>
struct cal_binary_cast<int2_type,int2_type>
{
    typedef int4_type value_type;
    static const int temp_reg_count=1;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("mov r%4%.xy,%2%\n"
                              "mov r%4%.__zw,%3%\n"
                              "mov %1%,r%4%\n") % r % s0 % make_swizzle(s1,1,2,1,2) % t0).str();
    }
};

template<>
struct cal_binary_cast<uint_type,uint_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=1;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("mov r%4%.x,%2%\n"
                              "mov r%4%._y__,%3%\n"
                              "mov %1%,r%4%.xy\n") % r % s0 % make_swizzle(s1,1,1,1,1) % t0).str();
    }
};

template<>
struct cal_binary_cast<uint2_type,uint2_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=1;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("mov r%4%.xy,%2%\n"
                              "mov r%4%.__zw,%3%\n"
                              "mov %1%,r%4%\n") % r % s0 % make_swizzle(s1,1,2,1,2) % t0).str();
    }
};

template<>
struct cal_binary_cast<float_type,float_type>
{
    typedef float2_type value_type;
    static const int temp_reg_count=1;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("mov r%4%.x,%2%\n"
                              "mov r%4%._y__,%3%\n"
                              "mov %1%,r%4%.xy\n") % r % s0 % make_swizzle(s1,1,1,1,1) % t0).str();
    }
};

template<>
struct cal_binary_cast<float2_type,float2_type>
{
    typedef float4_type value_type;
    static const int temp_reg_count=1;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("mov r%4%.xy,%2%\n"
                              "mov r%4%.__zw,%3%\n"
                              "mov %1%,r%4%\n") % r % s0 % make_swizzle(s1,1,2,1,2) % t0).str();
    }
};

template<>
struct cal_binary_cast<double_type,double_type>
{
    typedef double2_type value_type;
    static const int temp_reg_count=1;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("mov r%4%.xy,%2%\n"
                              "mov r%4%.__zw,%3%\n"
                              "mov %1%,r%4%\n") % r % s0 % make_swizzle(s1,1,2,1,2) % t0).str();
    }
};

} // detail 
} // il
} // cal

#endif
