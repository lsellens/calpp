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

#ifndef __CAL_IL_FUNCTORS_MATH_H
#define __CAL_IL_FUNCTORS_MATH_H

#include <boost/format.hpp>
#include <boost/static_assert.hpp>
#include <cal/il/cal_il_base_types.hpp>
#include <cal/il/cal_il_swizzle.hpp>

namespace cal {
namespace il {
namespace detail {

//
// neg
//

template<class S1>
struct cal_unary_neg {
    typedef invalid_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        BOOST_STATIC_ASSERT(sizeof(S1) != sizeof(S1));
        return std::string();
    }    
};

template<>
struct cal_unary_neg<int_type>
{
    typedef int_type value_type;
    static const int temp_reg_count=0;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("inegate %s,%s\n") % r % s0).str();
    }    
};

template<>
struct cal_unary_neg<int2_type>
{
    typedef int2_type value_type;
    static const int temp_reg_count=0;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("inegate %s,%s\n") % r % s0).str();
    }    
};

template<>
struct cal_unary_neg<int4_type>
{
    typedef int4_type value_type;
    static const int temp_reg_count=0;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("inegate %s,%s\n") % r % s0).str();
    }    
};

template<>
struct cal_unary_neg<float_type>
{
    typedef float_type value_type;
    static const int temp_reg_count=0;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %s,%s_neg(x)\n") % r % s0).str();
    }    
};

template<>
struct cal_unary_neg<float2_type>
{
    typedef float2_type value_type;
    static const int temp_reg_count=0;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %s,%s_neg(xy)\n") % r % s0).str();
    }    
};

template<>
struct cal_unary_neg<float4_type>
{
    typedef float4_type value_type;
    static const int temp_reg_count=0;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %s,%s_neg(xyzw)\n") % r % s0).str();
    }    
};

template<>
struct cal_unary_neg<double_type>
{
    typedef double_type value_type;
    static const int temp_reg_count=0;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %s,%s_neg(y)\n") % r % s0).str();
    }    
};

template<>
struct cal_unary_neg<double2_type>
{
    typedef double2_type value_type;
    static const int temp_reg_count=0;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %s,%s_neg(yw)\n") % r % s0).str();
    }
};



//
// log
//

template<class S1>
struct cal_unary_log {
    typedef invalid_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        BOOST_STATIC_ASSERT(sizeof(S1) != sizeof(S1));
        return std::string();
    }    
};

template<>
struct cal_unary_log<float_type>
{
    typedef float_type value_type;
    static const int temp_reg_count=0;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("ln %s,%s\n") % r % s0).str();
    }    
};

template<>
struct cal_unary_log<float2_type>
{
    typedef float2_type value_type;
    static const int temp_reg_count=2;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov r%3%.xy,%2%\n"
                              "ln  r%4%.x,r%3%.x\n"
                              "ln  r%4%.y,r%3%.y\n"
                              "mov %1%,r%4%.xy\n") % r % s0 % t0 % (t0+1)).str();
    }    
};

template<>
struct cal_unary_log<float4_type>
{
    typedef float4_type value_type;
    static const int temp_reg_count=2;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov r%3%,%2%\n"
                              "ln  r%4%.x,%3%.x\n"
                              "ln  r%4%.y,%3%.y\n"
                              "ln  r%4%.z,%3%.z\n"
                              "ln  r%4%.w,%3%.w\n"
                              "mov %1%,r%4%\n") % r % s0 % t0 % (t0+1)).str();
    }    
};

//
// exp
//

template<class S1>
struct cal_unary_exp {
    typedef invalid_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        BOOST_STATIC_ASSERT(sizeof(S1) != sizeof(S1));
        return std::string();
    }    
};

template<>
struct cal_unary_exp<float_type>
{
    typedef float_type value_type;
    static const int temp_reg_count=0;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("exn %s,%s\n") % r % s0).str();
    }    
};

template<>
struct cal_unary_exp<float2_type>
{
    typedef float2_type value_type;
    static const int temp_reg_count=2;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov r%3%.xy,%2%\n"
                              "exn r%4%.x,r%3%.x\n"
                              "exn r%4%.y,r%3%.y\n"
                              "mov %1%,r%4%.xy\n") % r % s0 % t0 % (t0+1)).str();
    }    
};

template<>
struct cal_unary_exp<float4_type>
{
    typedef float4_type value_type;
    static const int temp_reg_count=2;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov r%3%,%2%\n"
                              "exn r%4%.x,%3%.x\n"
                              "exn r%4%.y,%3%.y\n"
                              "exn r%4%.z,%3%.z\n"
                              "exn r%4%.w,%3%.w\n"
                              "mov %1%,r%4%\n") % r % s0 % t0 % (t0+1)).str();
    }
};

//
// log2
//

template<class S1>
struct cal_unary_log2 {
    typedef invalid_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        BOOST_STATIC_ASSERT(sizeof(S1) != sizeof(S1));
        return std::string();
    }    
};

template<>
struct cal_unary_log2<float_type>
{
    typedef float_type value_type;
    static const int temp_reg_count=0;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("log %s,%s\n") % r % s0).str();
    }    
};

template<>
struct cal_unary_log2<float2_type>
{
    typedef float2_type value_type;
    static const int temp_reg_count=2;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov r%3%.xy,%2%\n"
                              "log r%4%.x,r%3%.x\n"
                              "log r%4%.y,r%3%.y\n"
                              "mov %1%,r%4%.xy\n") % r % s0 % t0 % (t0+1)).str();
    }    
};

template<>
struct cal_unary_log2<float4_type>
{
    typedef float4_type value_type;
    static const int temp_reg_count=2;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov r%3%,%2%\n"
                              "log r%4%.x,%3%.x\n"
                              "log r%4%.y,%3%.y\n"
                              "log r%4%.z,%3%.z\n"
                              "log r%4%.w,%3%.w\n"
                              "mov %1%,r%4%\n") % r % s0 % t0 % (t0+1)).str();
    }
};

//
// exp2
//

template<class S1>
struct cal_unary_exp2 {
    typedef invalid_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        BOOST_STATIC_ASSERT(sizeof(S1) != sizeof(S1));
        return std::string();
    }    
};

template<>
struct cal_unary_exp2<float_type>
{
    typedef float_type value_type;
    static const int temp_reg_count=0;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("exp %s,%s\n") % r % s0).str();
    }    
};

template<>
struct cal_unary_exp2<float2_type>
{
    typedef float2_type value_type;
    static const int temp_reg_count=2;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov r%3%.xy,%2%\n"
                              "exp r%4%.x,r%3%.x\n"
                              "exp r%4%.y,r%3%.y\n"
                              "mov %1%,r%4%.xy\n") % r % s0 % t0 % (t0+1)).str();
    }    
};

template<>
struct cal_unary_exp2<float4_type>
{
    typedef float4_type value_type;
    static const int temp_reg_count=2;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov r%3%,%2%\n"
                              "exn r%4%.x,%3%.x\n"
                              "exn r%4%.y,%3%.y\n"
                              "exn r%4%.z,%3%.z\n"
                              "exn r%4%.w,%3%.w\n"
                              "mov %1%,r%4%\n") % r % s0 % t0 % (t0+1)).str();
    }
};

//
// floor
//

template<class S1>
struct cal_unary_floor
{
    typedef invalid_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        BOOST_STATIC_ASSERT(sizeof(S1) != sizeof(S1));
        return std::string();
    }    
};

template<>
struct cal_unary_floor<float_type>
{
    typedef float_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("flr %s,%s\n") % r % s0).str();
    }    
};

template<>
struct cal_unary_floor<float2_type>
{
    typedef float2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("flr %s,%s\n") % r % s0).str();
    }    
};

template<>
struct cal_unary_floor<float4_type>
{
    typedef float4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("flr %s,%s\n") % r % s0).str();
    }    
};


//
// round
//

template<class S1>
struct cal_unary_round
{
    typedef invalid_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        BOOST_STATIC_ASSERT(sizeof(S1) != sizeof(S1));
        return std::string();
    }    
};

template<>
struct cal_unary_round<float_type>
{
    typedef float_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("rnd %s,%s\n") % r % s0).str();
    }    
};

template<>
struct cal_unary_round<float2_type>
{
    typedef float2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("rnd %s,%s\n") % r % s0).str();
    }    
};

template<>
struct cal_unary_round<float4_type>
{
    typedef float4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("rnd %s,%s\n") % r % s0).str();
    }    
};

//
// fractional part
//

template<class S1>
struct cal_unary_frac
{
    typedef invalid_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        BOOST_STATIC_ASSERT(sizeof(S1) != sizeof(S1));
        return std::string();
    }    
};

template<>
struct cal_unary_frac<float_type>
{
    typedef float_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("frc %s,%s\n") % r % s0).str();
    }    
};

template<>
struct cal_unary_frac<float2_type>
{
    typedef float2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("frc %s,%s\n") % r % s0).str();
    }    
};

template<>
struct cal_unary_frac<float4_type>
{
    typedef float4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("frc %s,%s\n") % r % s0).str();
    }    
};

template<>
struct cal_unary_frac<double_type>
{
    typedef double_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("dfrac %s,%s\n") % r % s0).str();
    }    
};

template<>
struct cal_unary_frac<double2_type>
{
    typedef double2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("dfrac %1%,%3%\n"
                              "dfrac %2%,%4%\n") % make_swizzle(r ,1,2,0,0) % make_swizzle(r ,3,4,0,0)
                                                 % make_swizzle(s0,1,2,0,0) % make_swizzle(s0,3,4,0,0)).str();
    }    
};

//
// add
//

template<class S1,class S2>
struct cal_binary_add
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
struct cal_binary_add<int_type,int_type>
{
    typedef int_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("iadd %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_add<int2_type,int2_type>
{
    typedef int2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("iadd %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_add<int4_type,int4_type>
{
    typedef int4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("iadd %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_add<uint_type,uint_type>
{
    typedef uint_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("iadd %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_add<uint2_type,uint2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("iadd %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_add<uint4_type,uint4_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("iadd %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_add<float_type,float_type>
{
    typedef float_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("add %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_add<float2_type,float2_type>
{
    typedef float2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("add %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_add<float4_type,float4_type>
{
    typedef float4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("add %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_add<double_type,double_type>
{
    typedef double_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("dadd %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_add<double2_type,double2_type>
{
    typedef double2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("dadd %1%,%3%,%5%\n"
                              "dadd %2%,%4%,%6%\n") % make_swizzle(r ,1,2,0,0) % make_swizzle(r ,3,4,0,0)
                                                    % make_swizzle(s0,1,2,0,0) % make_swizzle(s0,3,4,0,0)
                                                    % make_swizzle(s1,1,2,0,0) % make_swizzle(s1,3,4,0,0)).str();
    }
};

//
// sub
//

template<class S1,class S2>
struct cal_binary_sub
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
struct cal_binary_sub<int_type,int_type>
{
    typedef int_type value_type;
    static const int temp_reg_count=1;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("inegate r%4%.x,%3%\n"
                              "iadd %1%,%2%,r%4%.x\n"
                             ) % r % s0 % s1 % t0).str();
    }
};

template<>
struct cal_binary_sub<int2_type,int2_type>
{
    typedef int2_type value_type;
    static const int temp_reg_count=1;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("inegate r%4%.xy,%3%\n"
                              "iadd %1%,%2%,r%4%.xy\n"
                             ) % r % s0 % s1 % t0).str();        
    }
};

template<>
struct cal_binary_sub<int4_type,int4_type>
{
    typedef int4_type value_type;
    static const int temp_reg_count=1;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("inegate r%4%,%3%\n"
                              "iadd %1%,%2%,r%4%\n"
                             ) % r % s0 % s1 % t0).str();                
    }
};

template<>
struct cal_binary_sub<uint_type,uint_type>
{
    typedef uint_type value_type;
    static const int temp_reg_count=1;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("inegate r%4%.x,%3%\n"
                              "iadd %1%,%2%,r%4%.x\n"
                             ) % r % s0 % s1 % t0).str();
    }
};

template<>
struct cal_binary_sub<uint2_type,uint2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=1;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("inegate r%4%.xy,%3%\n"
                              "iadd %1%,%2%,r%4%.xy\n"
                             ) % r % s0 % s1 % t0).str();        
    }
};

template<>
struct cal_binary_sub<uint4_type,uint4_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=1;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("inegate r%4%,%3%\n"
                              "iadd %1%,%2%,r%4%\n"
                             ) % r % s0 % s1 % t0).str();                
    }
};

template<>
struct cal_binary_sub<float_type,float_type>
{
    typedef float_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("sub %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_sub<float2_type,float2_type>
{
    typedef float2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("sub %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_sub<float4_type,float4_type>
{
    typedef float4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("sub %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_sub<double_type,double_type>
{
    typedef double_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("dadd %s,%s,%s_neg(y)\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_sub<double2_type,double2_type>
{
    typedef double2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("dadd %1%,%3%,%5%_neg(y)\n"
                              "dadd %2%,%4%,%6%_neg(y)\n") % make_swizzle(r ,1,2,0,0) % make_swizzle(r ,3,4,0,0)
                                                           % make_swizzle(s0,1,2,0,0) % make_swizzle(s0,3,4,0,0)
                                                           % make_swizzle(s1,1,2,0,0) % make_swizzle(s1,3,4,0,0)).str();
    }
};

//
// mul
//

template<class S1,class S2>
struct cal_binary_mul
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
struct cal_binary_mul<int_type,int_type>
{
    typedef int_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("imul %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_mul<int2_type,int2_type>
{
    typedef int2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("imul %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_mul<int4_type,int4_type>
{
    typedef int4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("imul %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_mul<uint_type,uint_type>
{
    typedef uint_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("umul %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_mul<uint2_type,uint2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("umul %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_mul<uint4_type,uint4_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("umul %s,%s,%s\n") % r % s0 % s1).str();
    }
};


template<>
struct cal_binary_mul<float_type,float_type>
{
    typedef float_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("mul %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_mul<float2_type,float2_type>
{
    typedef float2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("mul %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_mul<float4_type,float4_type>
{
    typedef float4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("mul %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_mul<double_type,double_type>
{
    typedef double_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("dmul %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_mul<double2_type,double2_type>
{
    typedef double2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("dmul %1%,%3%,%5%\n"
                              "dmul %2%,%4%,%6%\n") % make_swizzle(r ,1,2,0,0) % make_swizzle(r ,3,4,0,0)
                                                    % make_swizzle(s0,1,2,0,0) % make_swizzle(s0,3,4,0,0)
                                                    % make_swizzle(s1,1,2,0,0) % make_swizzle(s1,3,4,0,0)).str();
    }
};

//
// div
//

template<class S1,class S2>
struct cal_binary_div
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
struct cal_binary_div<uint_type,uint_type>
{
    typedef uint_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("udiv %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_div<uint2_type,uint2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("udiv %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_div<uint4_type,uint4_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("udiv %s,%s,%s\n") % r % s0 % s1).str();
    }
};


template<>
struct cal_binary_div<float_type,float_type>
{
    typedef float_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("div %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_div<float2_type,float2_type>
{
    typedef float2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("div %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_div<float4_type,float4_type>
{
    typedef float4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("div %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_div<double_type,double_type>
{
    typedef double_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ddiv %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_div<double2_type,double2_type>
{
    typedef double2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("ddiv %1%,%3%,%5%\n"
                              "ddiv %2%,%4%,%6%\n") % make_swizzle(r ,1,2,0,0) % make_swizzle(r ,3,4,0,0)
                                                    % make_swizzle(s0,1,2,0,0) % make_swizzle(s0,3,4,0,0)
                                                    % make_swizzle(s1,1,2,0,0) % make_swizzle(s1,3,4,0,0)).str();
    }
};

//
// binary mod
//

template<class S1,class S2>
struct cal_binary_mod
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
struct cal_binary_mod<uint_type,uint_type>
{
    typedef uint_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("umod %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_mod<uint2_type,uint2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("umod %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_mod<uint4_type,uint4_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("umod %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_mod<float_type,float_type>
{
    typedef float_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("mod %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_mod<float2_type,float2_type>
{
    typedef float2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("mod %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_mod<float4_type,float4_type>
{
    typedef float4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("mod %s,%s,%s\n") % r % s0 % s1).str();
    }
};


//
// ldexp
//

template<class S1,class S2>
struct cal_binary_ldexp
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
struct cal_binary_ldexp<double_type,int_type>
{
    typedef double_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("dldexp %1%,%2%,%3%\n") % r % s0 % s1).str();
    }    
};

template<>
struct cal_binary_ldexp<double2_type,int2_type>
{
    typedef double2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("dldexp %1%,%3%,%5%\n"
                              "dldexp %2%,%4%,%6%\n") % make_swizzle(r ,1,2,0,0) % make_swizzle(r ,3,4,0,0)
                                                      % make_swizzle(s0,1,2,0,0) % make_swizzle(s0,3,4,0,0)
                                                      % make_swizzle(s1,1,0,0,0) % make_swizzle(s1,2,0,0,0)).str();
    }
};

//
// mad
//

template<class S1, class S2, class S3>
struct cal_ternary_mad {
    typedef invalid_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, const std::string& s2, int t0 )
    {
        BOOST_STATIC_ASSERT(sizeof(S1) != sizeof(S1));
        return std::string();
    }    
};

template<>
struct cal_ternary_mad<int_type,int_type,int_type>
{
    typedef int_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, const std::string& s2, int t0 )
    {
        return (boost::format("imad %1%,%2%,%3%,%4%\n") % r % s0 % s1 % s2).str();
    }
};

template<>
struct cal_ternary_mad<int2_type,int2_type,int2_type>
{
    typedef int2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, const std::string& s2, int t0 )
    {
        return (boost::format("imad %1%,%2%,%3%,%4%\n") % r % s0 % s1 % s2).str();
    }
};

template<>
struct cal_ternary_mad<int4_type,int4_type,int4_type>
{
    typedef int4_type value_type;
    static const int temp_reg_count=0; 

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, const std::string& s2, int t0 )
    {
        return (boost::format("imad %1%,%2%,%3%,%4%\n") % r % s0 % s1 % s2).str();
    }
};

template<>
struct cal_ternary_mad<uint_type,uint_type,uint_type>
{
    typedef uint_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, const std::string& s2, int t0 )
    {
        return (boost::format("umad %1%,%2%,%3%,%4%\n") % r % s0 % s1 % s2).str();
    }
};

template<>
struct cal_ternary_mad<uint2_type,uint2_type,uint2_type>
{
    typedef uint2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, const std::string& s2, int t0 )
    {
        return (boost::format("umad %1%,%2%,%3%,%4%\n") % r % s0 % s1 % s2).str();
    }
};

template<>
struct cal_ternary_mad<uint4_type,uint4_type,uint4_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=0; 

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, const std::string& s2, int t0 )
    {
        return (boost::format("umad %1%,%2%,%3%,%4%\n") % r % s0 % s1 % s2).str();
    }
};

template<>
struct cal_ternary_mad<float_type,float_type,float_type>
{
    typedef float_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, const std::string& s2, int t0 )
    {
        return (boost::format("mad %1%,%2%,%3%,%4%\n") % r % s0 % s1 % s2).str();
    }
};

template<>
struct cal_ternary_mad<float2_type,float2_type,float2_type>
{
    typedef float2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, const std::string& s2, int t0 )
    {
        return (boost::format("mad %1%,%2%,%3%,%4%\n") % r % s0 % s1 % s2).str();
    }
};

template<>
struct cal_ternary_mad<float4_type,float4_type,float4_type>
{
    typedef float4_type value_type;
    static const int temp_reg_count=0; 

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, const std::string& s2, int t0 )
    {
        return (boost::format("mad %1%,%2%,%3%,%4%\n") % r % s0 % s1 % s2).str();
    }
};

template<>
struct cal_ternary_mad<double_type,double_type,double_type>
{
    typedef double_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, const std::string& s2, int t0 )
    {
        return (boost::format("dmad %1%,%2%,%3%,%4%\n") % r % s0 % s1 % s2).str();
    }
};

template<>
struct cal_ternary_mad<double2_type,double2_type,double2_type>
{
    typedef double2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, const std::string& s2, int t0 )
    {
        return (boost::format("dmad %1%,%3%,%5%,%7%\n"
                              "dmad %2%,%4%,%6%,%8%\n") % make_swizzle(r ,1,2,0,0) % make_swizzle(r ,3,4,0,0)
                                                        % make_swizzle(s0,1,2,0,0) % make_swizzle(s0,3,4,0,0)
                                                        % make_swizzle(s1,1,2,0,0) % make_swizzle(s1,3,4,0,0)
                                                        % make_swizzle(s2,1,2,0,0) % make_swizzle(s2,3,4,0,0)).str();
    }
};

//
// rsq
//

template<class S1>
struct cal_unary_rsq {
    typedef invalid_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        BOOST_STATIC_ASSERT(sizeof(S1) != sizeof(S1));
        return std::string();
    }
};

template<>
struct cal_unary_rsq<float_type>
{
    typedef float_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("rsq %1%,%2%\n") % mask_output(make_swizzle(r,1,0,0,0)) % make_swizzle(s0,1,1,1,1) ).str();
    }
};

template<>
struct cal_unary_rsq<float2_type>
{
    typedef float2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("rsq %1%,%2%\n"
                              "rsq %3%,%4%\n") % mask_output(make_swizzle(r,1,0,0,0)) % make_swizzle(s0,1,1,1,1)
                                               % mask_output(make_swizzle(r,2,0,0,0)) % make_swizzle(s0,2,2,2,2) ).str();
    }
};

template<>
struct cal_unary_rsq<float4_type>
{
    typedef float4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("rsq %1%,%2%\n"
                              "rsq %3%,%4%\n"
                              "rsq %5%,%6%\n"
                              "rsq %7%,%8%\n" ) % mask_output(make_swizzle(r,1,0,0,0)) % make_swizzle(s0,1,1,1,1)
                                                % mask_output(make_swizzle(r,2,0,0,0)) % make_swizzle(s0,2,2,2,2)
                                                % mask_output(make_swizzle(r,3,0,0,0)) % make_swizzle(s0,3,3,3,3)
                                                % mask_output(make_swizzle(r,4,0,0,0)) % make_swizzle(s0,4,4,4,4) ).str();
    }
};

template<>
struct cal_unary_rsq<double_type>
{
    typedef double_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("drsq %1%,%2%\n") % mask_output(make_swizzle(r,1,2,0,0)) % make_swizzle(s0,1,2,1,2) ).str();
    }
};

template<>
struct cal_unary_rsq<double2_type>
{
    typedef double2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("drsq %1%,%2%\n"
                              "drsq %3%,%4%\n") % mask_output(make_swizzle(r,1,2,0,0)) % make_swizzle(s0,1,2,1,2)
                                                % mask_output(make_swizzle(r,3,4,0,0)) % make_swizzle(s0,3,4,3,4) ).str();
    }
};

} // detail
} // il
} // cal

#endif
