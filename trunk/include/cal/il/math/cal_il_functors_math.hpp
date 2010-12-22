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
// frexp
//

template<class S1>
struct cal_unary_frexp
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
struct cal_unary_frexp<double_type>
{
    typedef uint4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("dfrexp %s,%s\n") % r % s0).str();
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

//
// rcp
//

template<class S1>
struct cal_unary_rcp {
    typedef invalid_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        BOOST_STATIC_ASSERT(sizeof(S1) != sizeof(S1));
        return std::string();
    }
};

template<>
struct cal_unary_rcp<float_type>
{
    typedef float_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("rcp %1%,%2%\n") % mask_output(make_swizzle(r,1,0,0,0)) % make_swizzle(s0,1,1,1,1) ).str();
    }
};

template<>
struct cal_unary_rcp<float2_type>
{
    typedef float2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("rcp %1%,%2%\n"
                              "rcp %3%,%4%\n") % mask_output(make_swizzle(r,1,0,0,0)) % make_swizzle(s0,1,1,1,1)
                                               % mask_output(make_swizzle(r,2,0,0,0)) % make_swizzle(s0,2,2,2,2) ).str();
    }
};

template<>
struct cal_unary_rcp<float4_type>
{
    typedef float4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("rcp %1%,%2%\n"
                              "rcp %3%,%4%\n"
                              "rcp %5%,%6%\n"
                              "rcp %7%,%8%\n" ) % mask_output(make_swizzle(r,1,0,0,0)) % make_swizzle(s0,1,1,1,1)
                                                % mask_output(make_swizzle(r,2,0,0,0)) % make_swizzle(s0,2,2,2,2)
                                                % mask_output(make_swizzle(r,3,0,0,0)) % make_swizzle(s0,3,3,3,3)
                                                % mask_output(make_swizzle(r,4,0,0,0)) % make_swizzle(s0,4,4,4,4) ).str();
    }
};

template<>
struct cal_unary_rcp<double_type>
{
    typedef double_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("drcp %1%,%2%\n") % r % make_swizzle(s0,1,2,1,2) ).str();
    }
};

template<>
struct cal_unary_rcp<double2_type>
{
    typedef double2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("drcp %1%,%2%\n"
                              "drcp %3%,%4%\n") % make_swizzle(r,1,2,0,0) % make_swizzle(s0,1,2,1,2)
                                                % make_swizzle(r,3,4,0,0) % make_swizzle(s0,3,4,3,4) ).str();
    }
};

//
// sqrt
//

template<class S1>
struct cal_unary_sqrt {
    typedef invalid_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        BOOST_STATIC_ASSERT(sizeof(S1) != sizeof(S1));
        return std::string();
    }
};

template<>
struct cal_unary_sqrt<float_type>
{
    typedef float_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("sqrt %1%,%2%\n") % mask_output(make_swizzle(r,1,0,0,0)) % make_swizzle(s0,1,1,1,1) ).str();
    }
};

template<>
struct cal_unary_sqrt<float2_type>
{
    typedef float2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("sqrt %1%,%2%\n"
                              "sqrt %3%,%4%\n") % mask_output(make_swizzle(r,1,0,0,0)) % make_swizzle(s0,1,1,1,1)
                                                % mask_output(make_swizzle(r,2,0,0,0)) % make_swizzle(s0,2,2,2,2) ).str();
    }
};

template<>
struct cal_unary_sqrt<float4_type>
{
    typedef float4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("sqrt %1%,%2%\n"
                              "sqrt %3%,%4%\n"
                              "sqrt %5%,%6%\n"
                              "sqrt %7%,%8%\n" ) % mask_output(make_swizzle(r,1,0,0,0)) % make_swizzle(s0,1,1,1,1)
                                                 % mask_output(make_swizzle(r,2,0,0,0)) % make_swizzle(s0,2,2,2,2)
                                                 % mask_output(make_swizzle(r,3,0,0,0)) % make_swizzle(s0,3,3,3,3)
                                                 % mask_output(make_swizzle(r,4,0,0,0)) % make_swizzle(s0,4,4,4,4) ).str();
    }
};

template<>
struct cal_unary_sqrt<double_type>
{
    typedef double_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("dsqrt %1%,%2%\n") % make_swizzle(r,1,2,0,0) % make_swizzle(s0,1,2,1,2) ).str();
    }
};

template<>
struct cal_unary_sqrt<double2_type>
{
    typedef double2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("dsqrt %1%,%2%\n"
                              "dsqrt %3%,%4%\n") % make_swizzle(r,1,2,0,0) % make_swizzle(s0,1,2,1,2)
                                                 % make_swizzle(r,3,4,0,0) % make_swizzle(s0,3,4,3,4) ).str();
    }
};


} // detail
} // il
} // cal

#endif
