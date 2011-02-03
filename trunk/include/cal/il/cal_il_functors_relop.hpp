/*
 * C++ to IL compiler/generator operation functors
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

#ifndef __CAL_IL_FUNCTORS_RELOP_H
#define __CAL_IL_FUNCTORS_RELOP_H

#include <boost/format.hpp>
#include <boost/static_assert.hpp>

namespace cal {
namespace il {
namespace detail {

//
// logical not
//

template<class S1>
struct cal_unary_not {
    typedef invalid_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        BOOST_STATIC_ASSERT(sizeof(S1) != sizeof(S1));
        return std::string();
    }    
};

template<>
struct cal_unary_not<int_type>
{
    typedef uint_type value_type;
    static const int temp_reg_count=0;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("cmov_logical %s,%s,l0.x,l1.x\n") % r % s0).str();
    }    
};

template<>
struct cal_unary_not<int2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=0;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("cmov_logical %s,%s,l0.xy,l1.xy\n") % r % s0).str();        
    }    
};

template<>
struct cal_unary_not<int4_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=0;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("cmov_logical %s,%s,l0,l1\n") % r % s0).str();
    }    
};

template<>
struct cal_unary_not<uint_type>
{
    typedef uint_type value_type;
    static const int temp_reg_count=0;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("cmov_logical %s,%s,l0.x,l1.x\n") % r % s0).str();        
    }    
};

template<>
struct cal_unary_not<uint2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=0;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("cmov_logical %s,%s,l0.xy,l1.xy\n") % r % s0).str();
    }    
};

template<>
struct cal_unary_not<uint4_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=0;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("cmov_logical %s,%s,l0,l1\n") % r % s0).str();
    }    
};

template<>
struct cal_unary_not<float_type>
{
    typedef uint_type value_type;
    static const int temp_reg_count=0;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("cmov_logical %s,%s,l0.x,l1.x\n") % r % s0).str();
    }    
};

template<>
struct cal_unary_not<float2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=0;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("cmov_logical %s,%s,l0.xy,l1.xy\n") % r % s0).str();
    }    
};

template<>
struct cal_unary_not<float4_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=0;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("cmov_logical %s,%s,l0,l1\n") % r % s0).str();
    }    
};

//
// compare ==
//

template<class S1,class S2>
struct cal_binary_eq
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
struct cal_binary_eq<int_type,int_type>
{
    typedef uint_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ieq %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_eq<int2_type,int2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ieq %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_eq<int4_type,int4_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ieq %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_eq<uint_type,uint_type>
{
    typedef uint_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ieq %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_eq<uint2_type,uint2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ieq %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_eq<uint4_type,uint4_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ieq %s,%s,%s\n") % r % s0 % s1).str();
    }
};


template<>
struct cal_binary_eq<float_type,float_type>
{
    typedef uint_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("eq %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_eq<float2_type,float2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("eq %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_eq<float4_type,float4_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("eq %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_eq<double_type,double_type>
{
    typedef uint1_type value_type;
    static const int temp_reg_count=1;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("deq r%4%.xy,%2%,%3%\n"
                              "mov %1%,r%4%.x\n") % r % s0 % s1 % t0).str();
    }
};

template<>
struct cal_binary_eq<double2_type,double2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=1;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("deq r%6%.xy,%2%,%4%\n"
                              "deq r%6%.zw,%3%,%5%\n"
                              "mov %1%,r%6%.xz\n") % r
                                                   % make_swizzle(s0,1,2,0,0) % make_swizzle(s0,3,4,0,0)
                                                   % make_swizzle(s1,1,2,0,0) % make_swizzle(s1,3,4,0,0)
                                                   % t0 ).str();
    }
};

//
// compare !=
//

template<class S1,class S2>
struct cal_binary_ne
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
struct cal_binary_ne<int_type,int_type>
{
    typedef uint_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ine %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_ne<int2_type,int2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ine %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_ne<int4_type,int4_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ine %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_ne<uint_type,uint_type>
{
    typedef uint_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ine %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_ne<uint2_type,uint2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ine %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_ne<uint4_type,uint4_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ine %s,%s,%s\n") % r % s0 % s1).str();
    }
};


template<>
struct cal_binary_ne<float_type,float_type>
{
    typedef uint_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ne %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_ne<float2_type,float2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ne %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_ne<float4_type,float4_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ne %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_ne<double_type,double_type>
{
    typedef uint1_type value_type;
    static const int temp_reg_count=1;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("dne r%4%.xy,%2%,%3%\n"
                              "mov %1%,r%4%.x\n") % r % s0 % s1 % t0).str();
    }
};

template<>
struct cal_binary_ne<double2_type,double2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=1;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("dne r%6%.xy,%2%,%4%\n"
                              "dne r%6%.zw,%3%,%5%\n"
                              "mov %1%,r%6%.xz\n") % r 
                                                   % make_swizzle(s0,1,2,0,0) % make_swizzle(s0,3,4,0,0)
                                                   % make_swizzle(s1,1,2,0,0) % make_swizzle(s1,3,4,0,0)
                                                   % t0 ).str();
    }
};

//
// compare >=
//

template<class S1,class S2>
struct cal_binary_ge
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
struct cal_binary_ge<int_type,int_type>
{
    typedef uint_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ige %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_ge<int2_type,int2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ige %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_ge<int4_type,int4_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ige %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_ge<uint_type,uint_type>
{
    typedef uint_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("uge %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_ge<uint2_type,uint2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("uge %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_ge<uint4_type,uint4_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("uge %s,%s,%s\n") % r % s0 % s1).str();
    }
};


template<>
struct cal_binary_ge<float_type,float_type>
{
    typedef uint_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ge %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_ge<float2_type,float2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ge %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_ge<float4_type,float4_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ge %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_ge<double_type,double_type>
{
    typedef uint1_type value_type;
    static const int temp_reg_count=1;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("dge r%4%.xy,%2%,%3%\n"
                              "mov %1%,r%4%.x\n") % r % s0 % s1 % t0).str();
    }
};

template<>
struct cal_binary_ge<double2_type,double2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=1;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("dge r%6%.xy,%2%,%4%\n"
                              "dge r%6%.zw,%3%,%5%\n"
                              "mov %1%,r%6%.xz\n") % r
                                                   % make_swizzle(s0,1,2,0,0) % make_swizzle(s0,3,4,0,0)
                                                   % make_swizzle(s1,1,2,0,0) % make_swizzle(s1,3,4,0,0)
                                                   % t0 ).str();
    }
};

//
// compare <
//

template<class S1,class S2>
struct cal_binary_lt
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
struct cal_binary_lt<int_type,int_type>
{
    typedef uint_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ilt %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_lt<int2_type,int2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ilt %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_lt<int4_type,int4_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ilt %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_lt<uint_type,uint_type>
{
    typedef uint_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ult %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_lt<uint2_type,uint2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ult %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_lt<uint4_type,uint4_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ult %s,%s,%s\n") % r % s0 % s1).str();
    }
};


template<>
struct cal_binary_lt<float_type,float_type>
{
    typedef uint_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("lt %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_lt<float2_type,float2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("lt %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_lt<float4_type,float4_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("lt %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_lt<double_type,double_type>
{
    typedef uint1_type value_type;
    static const int temp_reg_count=1;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("dlt r%4%.xy,%2%,%3%\n"
                              "mov %1%,r%4%.x\n") % r % s0 % s1 % t0).str();
    }
};

template<>
struct cal_binary_lt<double2_type,double2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=1;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("dlt r%6%.xy,%2%,%4%\n"
                              "dlt r%6%.zw,%3%,%5%\n"
                              "mov %1%,r%6%.xz\n") % r
                                                   % make_swizzle(s0,1,2,0,0) % make_swizzle(s0,3,4,0,0)
                                                   % make_swizzle(s1,1,2,0,0) % make_swizzle(s1,3,4,0,0)
                                                   % t0 ).str();
    }
};

//
// compare <=
//

template<class S1,class S2>
struct cal_binary_le
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
struct cal_binary_le<int_type,int_type>
{
    typedef uint_type value_type;
    static const int temp_reg_count=2;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        
        return (boost::format("ilt r%4%.x,%2%,%3%\n"
                              "ieq r%5%.x,%2%,%3%\n"
                              "ior %1%,r%4%.x,r%5%.x\n") % r % s0 % s1 % t0 % (t0+1)).str();
    }
};

template<>
struct cal_binary_le<int2_type,int2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=2;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ilt r%4%.xy,%2%,%3%\n"
                              "ieq r%5%.xy,%2%,%3%\n"
                              "ior %1%,r%4%.xy,r%5%.xy\n") % r % s0 % s1 % t0 % (t0+1)).str();        
    }
};

template<>
struct cal_binary_le<int4_type,int4_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=2;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ilt r%4%,%2%,%3%\n"
                              "ieq r%5%,%2%,%3%\n"
                              "ior %1%,r%4%,r%5%\n") % r % s0 % s1 % t0 % (t0+1)).str();
    }
};

template<>
struct cal_binary_le<uint_type,uint_type>
{
    typedef uint_type value_type;
    static const int temp_reg_count=2;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ult r%4%.x,%2%,%3%\n"
                              "ieq r%5%.x,%2%,%3%\n"
                              "ior %1%,r%4%.x,r%5%.x\n") % r % s0 % s1 % t0 % (t0+1)).str();        
    }
};

template<>
struct cal_binary_le<uint2_type,uint2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=2;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ult r%4%.xy,%2%,%3%\n"
                              "ieq r%5%.xy,%2%,%3%\n"
                              "ior %1%,r%4%.xy,r%5%.xy\n") % r % s0 % s1 % t0 % (t0+1)).str();
    }
};

template<>
struct cal_binary_le<uint4_type,uint4_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=2;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ult r%4%,%2%,%3%\n"
                              "ieq r%5%,%2%,%3%\n"
                              "ior %1%,r%4%,r%5%\n") % r % s0 % s1 % t0 % (t0+1)).str();
    }
};


template<>
struct cal_binary_le<float_type,float_type>
{
    typedef uint_type value_type;
    static const int temp_reg_count=2;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("lt  r%4%.x,%2%,%3%\n"
                              "eq  r%5%.x,%2%,%3%\n"
                              "ior %1%,r%4%.x,r%5%.x\n") % r % s0 % s1 % t0 % (t0+1)).str();
    }
};

template<>
struct cal_binary_le<float2_type,float2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=2;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("lt  r%4%.xy,%2%,%3%\n"
                              "eq  r%5%.xy,%2%,%3%\n"
                              "ior %1%,r%4%.xy,r%5%.xy\n") % r % s0 % s1 % t0 % (t0+1)).str();
    }
};

template<>
struct cal_binary_le<float4_type,float4_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=2;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("lt  r%4%,%2%,%3%\n"
                              "eq  r%5%,%2%,%3%\n"
                              "ior %1%,r%4%,r%5%\n") % r % s0 % s1 % t0 % (t0+1)).str();
    }
};

template<>
struct cal_binary_le<double_type,double_type>
{
    typedef uint1_type value_type;
    static const int temp_reg_count=2;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("dlt r%4%.xy,%2%,%3%\n"
                              "deq r%5%.xy,%2%,%3%\n"
                              "ior %1%,r%4%.x,r%5%.x\n") % r % s0 % s1 % t0 % (t0+1)).str();
    }
};

template<>
struct cal_binary_le<double2_type,double2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=2;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("dlt r%6%.xy,%2%,%4%\n"
                              "dlt r%6%.zw,%3%,%5%\n"
                              "deq r%7%.xy,%2%,%4%\n"
                              "deq r%7%.zw,%3%,%5%\n"
                              "ior %1%,r%6%.xz,r%7%.xz\n" ) % r
                                                      % make_swizzle(s0,1,2,0,0) % make_swizzle(s0,3,4,0,0)
                                                      % make_swizzle(s1,1,2,0,0) % make_swizzle(s1,3,4,0,0)
                                                      % t0 % (t0+1) ).str();
    }
};

//
// compare >
//

template<class S1,class S2>
struct cal_binary_gt
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
struct cal_binary_gt<int_type,int_type>
{
    typedef uint_type value_type;
    static const int temp_reg_count=2;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        
        return (boost::format("ige  r%4%.x,%2%,%3%\n"
                              "ine  r%5%.x,%2%,%3%\n"
                              "iand %1%,r%4%.x,r%5%.x\n") % r % s0 % s1 % t0 % (t0+1)).str();
    }
};

template<>
struct cal_binary_gt<int2_type,int2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=2;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ige r%4%.xy,%2%,%3%\n"
                              "ine r%5%.xy,%2%,%3%\n"
                              "iand %1%,r%4%.xy,r%5%.xy\n") % r % s0 % s1 % t0 % (t0+1)).str();
    }
};

template<>
struct cal_binary_gt<int4_type,int4_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=2;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ige r%4%,%2%,%3%\n"
                              "ine r%5%,%2%,%3%\n"
                              "iand %1%,r%4%,r%5%\n") % r % s0 % s1 % t0 % (t0+1)).str();
    }
};

template<>
struct cal_binary_gt<uint_type,uint_type>
{
    typedef uint_type value_type;
    static const int temp_reg_count=2;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("uge r%4%.x,%2%,%3%\n"
                              "ine r%5%.x,%2%,%3%\n"
                              "iand %1%,r%4%.x,r%5%.x\n") % r % s0 % s1 % t0 % (t0+1)).str();
    }
};

template<>
struct cal_binary_gt<uint2_type,uint2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=2;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("uge r%4%.xy,%2%,%3%\n"
                              "ine r%5%.xy,%2%,%3%\n"
                              "iand %1%,r%4%.xy,r%5%.xy\n") % r % s0 % s1 % t0 % (t0+1)).str();
    }
};

template<>
struct cal_binary_gt<uint4_type,uint4_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=2;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("uge r%4%,%2%,%3%\n"
                              "ine r%5%,%2%,%3%\n"
                              "iand %1%,r%4%,r%5%\n") % r % s0 % s1 % t0 % (t0+1)).str();
    }
};


template<>
struct cal_binary_gt<float_type,float_type>
{
    typedef uint_type value_type;
    static const int temp_reg_count=2;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ge  r%4%.x,%2%,%3%\n"
                              "ne  r%5%.x,%2%,%3%\n"
                              "iand %1%,r%4%.x,r%5%.x\n") % r % s0 % s1 % t0 % (t0+1)).str();
    }
};

template<>
struct cal_binary_gt<float2_type,float2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=2;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ge  r%4%.xy,%2%,%3%\n"
                              "ne  r%5%.xy,%2%,%3%\n"
                              "iand %1%,r%4%.xy,r%5%.xy\n") % r % s0 % s1 % t0 % (t0+1)).str();
    }
};

template<>
struct cal_binary_gt<float4_type,float4_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=2;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ge  r%4%,%2%,%3%\n"
                              "ne  r%5%,%2%,%3%\n"
                              "iand %1%,r%4%,r%5%\n") % r % s0 % s1 % t0 % (t0+1)).str();
    }
};

template<>
struct cal_binary_gt<double_type,double_type>
{
    typedef uint1_type value_type;
    static const int temp_reg_count=2;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("dge r%4%.xy,%2%,%3%\n"
                              "dne r%5%.xy,%2%,%3%\n"
                              "iand %1%,r%4%.x,r%5%.x\n") % r % s0 % s1 % t0 % (t0+1)).str();
    }
};

template<>
struct cal_binary_gt<double2_type,double2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=2;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("dge r%6%.xy,%2%,%4%\n"
                              "dge r%6%.zw,%3%,%5%\n"
                              "dne r%7%.xy,%2%,%4%\n"
                              "dne r%7%.zw,%3%,%5%\n"
                              "iand %1%,r%6%.xz,r%7%.xz\n" ) % r
                                                      % make_swizzle(s0,1,2,0,0) % make_swizzle(s0,3,4,0,0)
                                                      % make_swizzle(s1,1,2,0,0) % make_swizzle(s1,3,4,0,0)
                                                      % t0 % (t0+1) ).str();
    }
};


} // detail
} // il
} // cal


#endif
