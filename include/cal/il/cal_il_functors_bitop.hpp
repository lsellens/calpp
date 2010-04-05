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

#ifndef __CAL_IL_FUNCTORS_BITOP_H
#define __CAL_IL_FUNCTORS_BITOP_H

#include <boost/format.hpp>
#include <boost/static_assert.hpp>
#include <cal/il/cal_il_base_types.hpp>

namespace cal {
namespace il {
namespace detail {

//
// bitwise not
//

template<class S1>
struct cal_unary_bitnot {
    typedef invalid_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        BOOST_STATIC_ASSERT(sizeof(S1) != sizeof(S1));
        return std::string();
    }    
};

template<>
struct cal_unary_bitnot<int_type>
{
    typedef int_type value_type;
    static const int temp_reg_count=0;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("inot %s,%s\n") % r % s0).str();
    }    
};

template<>
struct cal_unary_bitnot<int2_type>
{
    typedef int2_type value_type;
    static const int temp_reg_count=0;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("inot %s,%s\n") % r % s0).str();
    }    
};

template<>
struct cal_unary_bitnot<int4_type>
{
    typedef int4_type value_type;
    static const int temp_reg_count=0;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("inot %s,%s\n") % r % s0).str();
    }    
};

template<>
struct cal_unary_bitnot<uint_type>
{
    typedef uint_type value_type;
    static const int temp_reg_count=0;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("inot %s,%s\n") % r % s0).str();
    }    
};

template<>
struct cal_unary_bitnot<uint2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=0;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("inot %s,%s\n") % r % s0).str();
    }    
};

template<>
struct cal_unary_bitnot<uint4_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=0;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("inot %s,%s\n") % r % s0).str();
    }    
};

template<>
struct cal_unary_bitnot<float_type>
{
    typedef float_type value_type;
    static const int temp_reg_count=0;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("inot %s,%s\n") % r % s0).str();
    }    
};

template<>
struct cal_unary_bitnot<float2_type>
{
    typedef float2_type value_type;
    static const int temp_reg_count=0;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("inot %s,%s\n") % r % s0).str();
    }    
};

template<>
struct cal_unary_bitnot<float4_type>
{
    typedef float4_type value_type;
    static const int temp_reg_count=0;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("inot %s,%s\n") % r % s0).str();
    }    
};

template<>
struct cal_unary_bitnot<double_type>
{
    typedef double_type value_type;
    static const int temp_reg_count=0;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("inot %s,%s\n") % r % s0).str();
    }    
};

template<>
struct cal_unary_bitnot<double2_type>
{
    typedef double2_type value_type;
    static const int temp_reg_count=0;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("inot %s,%s\n") % r % s0).str();
    }
};

//
// shl
//

template<class S1,class S2>
struct cal_binary_shl
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
struct cal_binary_shl<int_type,int_type>
{
    typedef int_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ishl %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_shl<int2_type,int_type>
{
    typedef int2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ishl %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_shl<int4_type,int_type>
{
    typedef int4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ishl %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_shl<int_type,uint_type>
{
    typedef int_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ishl %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_shl<int2_type,uint_type>
{
    typedef int2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ishl %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_shl<int4_type,uint_type>
{
    typedef int4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ishl %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_shl<uint_type,int_type>
{
    typedef uint_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ishl %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_shl<uint2_type,int_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ishl %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_shl<uint4_type,int_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ishl %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_shl<uint_type,uint_type>
{
    typedef uint_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ishl %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_shl<uint2_type,uint_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ishl %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_shl<uint4_type,uint_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ishl %s,%s,%s\n") % r % s0 % s1).str();
    }
};

//
// shr
//

template<class S1,class S2>
struct cal_binary_shr
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
struct cal_binary_shr<int_type,int_type>
{
    typedef int_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ishr %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_shr<int2_type,int_type>
{
    typedef int2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ishr %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_shr<int4_type,int_type>
{
    typedef int4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ishr %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_shr<int_type,uint_type>
{
    typedef int_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ishr %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_shr<int2_type,uint_type>
{
    typedef int2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ishr %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_shr<int4_type,uint_type>
{
    typedef int4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ishr %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_shr<uint_type,int_type>
{
    typedef int_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ushr %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_shr<uint2_type,int_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ushr %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_shr<uint4_type,int_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ushr %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_shr<uint_type,uint_type>
{
    typedef int_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ushr %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_shr<uint2_type,uint_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ushr %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_shr<uint4_type,uint_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ushr %s,%s,%s\n") % r % s0 % s1).str();
    }
};



//
// bitwise or
//

template<class S1,class S2>
struct cal_binary_bitor
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
struct cal_binary_bitor<int_type,int_type>
{
    typedef int_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ior %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitor<int_type,uint_type>
{
    typedef int_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ior %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitor<int2_type,int2_type>
{
    typedef int2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ior %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitor<int2_type,uint2_type>
{
    typedef int2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ior %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitor<int4_type,int4_type>
{
    typedef int4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ior %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitor<int4_type,uint4_type>
{
    typedef int4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ior %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitor<uint_type,int_type>
{
    typedef uint_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ior %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitor<uint_type,uint_type>
{
    typedef uint_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ior %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitor<uint2_type,int2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ior %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitor<uint2_type,uint2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ior %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitor<uint4_type,int4_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ior %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitor<uint4_type,uint4_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ior %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitor<float_type,int_type>
{
    typedef float_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ior %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitor<float_type,uint_type>
{
    typedef float_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ior %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitor<float2_type,int2_type>
{
    typedef float2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ior %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitor<float2_type,uint2_type>
{
    typedef float2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ior %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitor<float4_type,int4_type>
{
    typedef float4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ior %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitor<float4_type,uint4_type>
{
    typedef float4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ior %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitor<double_type,int2_type>
{
    typedef double_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ior %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitor<double_type,uint2_type>
{
    typedef double_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ior %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitor<double2_type,int4_type>
{
    typedef double2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ior %1%,%2%,%3%\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitor<double2_type,uint4_type>
{
    typedef double2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ior %1%,%2%,%3%\n") % r % s0 % s1).str();
    }
};

//
// bitwise xor
//

template<class S1,class S2>
struct cal_binary_bitxor
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
struct cal_binary_bitxor<int_type,int_type>
{
    typedef int_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ixor %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitxor<int_type,uint_type>
{
    typedef int_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ixor %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitxor<int2_type,int2_type>
{
    typedef int2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ixor %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitxor<int2_type,uint2_type>
{
    typedef int2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ixor %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitxor<int4_type,int4_type>
{
    typedef int4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ixor %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitxor<int4_type,uint4_type>
{
    typedef int4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ixor %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitxor<uint_type,int_type>
{
    typedef uint_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ixor %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitxor<uint_type,uint_type>
{
    typedef uint_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ixor %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitxor<uint2_type,int2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ixor %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitxor<uint2_type,uint2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ixor %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitxor<uint4_type,int4_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ixor %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitxor<uint4_type,uint4_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ixor %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitxor<float_type,int_type>
{
    typedef float_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ixor %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitxor<float_type,uint_type>
{
    typedef float_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ixor %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitxor<float2_type,int2_type>
{
    typedef float2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ixor %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitxor<float2_type,uint2_type>
{
    typedef float2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ixor %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitxor<float4_type,int4_type>
{
    typedef float4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ixor %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitxor<float4_type,uint4_type>
{
    typedef float4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ixor %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitxor<double_type,int2_type>
{
    typedef double_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ixor %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitxor<double_type,uint2_type>
{
    typedef double_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ixor %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitxor<double2_type,int4_type>
{
    typedef double2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ixor %1%,%2%,%3%\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitxor<double2_type,uint4_type>
{
    typedef double2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ixor %1%,%2%,%3%\n") % r % s0 % s1).str();
    }
};


//
// bitwise and
//

template<class S1,class S2>
struct cal_binary_bitand
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
struct cal_binary_bitand<int_type,int_type>
{
    typedef int_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("iand %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitand<int_type,uint_type>
{
    typedef int_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("iand %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitand<int2_type,int2_type>
{
    typedef int2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("iand %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitand<int2_type,uint2_type>
{
    typedef int2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("iand %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitand<int4_type,int4_type>
{
    typedef int4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("iand %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitand<int4_type,uint4_type>
{
    typedef int4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("iand %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitand<uint_type,int_type>
{
    typedef uint_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("iand %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitand<uint_type,uint_type>
{
    typedef uint_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("iand %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitand<uint2_type,int2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("iand %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitand<uint2_type,uint2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("iand %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitand<uint4_type,int4_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("iand %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitand<uint4_type,uint4_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("iand %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitand<float_type,int_type>
{
    typedef float_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("iand %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitand<float_type,uint_type>
{
    typedef float_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("iand %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitand<float2_type,int2_type>
{
    typedef float2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("iand %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitand<float2_type,uint2_type>
{
    typedef float2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("iand %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitand<float4_type,int4_type>
{
    typedef float4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("iand %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitand<float4_type,uint4_type>
{
    typedef float4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("iand %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitand<double_type,int2_type>
{
    typedef double_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("iand %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitand<double_type,uint2_type>
{
    typedef double_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("iand %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitand<double2_type,int4_type>
{
    typedef double2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("iand %1%,%2%,%3%\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_bitand<double2_type,uint4_type>
{
    typedef double2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("iand %1%,%2%,%3%\n") % r % s0 % s1).str();
    }
};

} // detail
} // il
} // cal

#endif
