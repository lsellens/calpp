/*
 * C++ to IL compiler/generator sqrt
 * 
 * Copyright (C) 2010, 2011 Artur Kornacki
 *
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

#ifndef __CAL_IL_MATH_SQRT_H
#define __CAL_IL_MATH_SQRT_H

#include <cal/il/math/cal_il_frexp.hpp>
#include <cal/il/math/cal_il_ldexp.hpp>
#include <cal/il/math/cal_il_rsqrt.hpp>

namespace cal {
namespace il {

namespace detail {

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

template<class E1>
unary<E1,cal_unary_sqrt<typename E1::value_type> > native_sqrt( const expression<E1>& e1, float_type  )
{
    typedef unary<E1,cal_unary_sqrt<typename E1::value_type> > expression_type;
    return expression_type(e1());
}

template<class E1>
unary<E1,cal_unary_sqrt<typename E1::value_type> > native_sqrt( const expression<E1>& e1, float2_type  )
{
    typedef unary<E1,cal_unary_sqrt<typename E1::value_type> > expression_type;
    return expression_type(e1());
}

template<class E1>
unary<E1,cal_unary_sqrt<typename E1::value_type> > native_sqrt( const expression<E1>& e1, float4_type  )
{
    typedef unary<E1,cal_unary_sqrt<typename E1::value_type> > expression_type;
    return expression_type(e1());
}

template<class E1>
double1 native_sqrt( const expression<E1>& e1, double_type  )
{
    typedef unary<E1,cal_unary_sqrt<typename E1::value_type> > sqrt_type;

#if defined(__CAL_H__)
    if( Source::info().available && Source::info().target>=CAL_TARGET_CYPRESS ) return sqrt_type(e1());
#endif
    double1 w,x;
    int1    e;

    w = e1();
    x = frexp(w,e);
    x = cast_type<double1>( native_sqrt(cast_type<float1>(x),float_type()) );
    x = select( e&0x1, 1.41421356237309504880*x, x );
    x = ldexp(x,e>>1);

    return x;
}

template<class E1>
double2 native_sqrt( const expression<E1>& e1, double2_type  )
{
    typedef unary<E1,cal_unary_sqrt<typename E1::value_type> > sqrt_type;

#if defined(__CAL_H__)
    if( Source::info().available && Source::info().target>=CAL_TARGET_CYPRESS ) return sqrt_type(e1());
#endif
    double2 w,x;
    int2    e;

    w = e1();
    x = frexp(w,e);
    x = cast_type<double2>( native_sqrt(cast_type<float2>(x),float2_type()) );
    x = select( e&0x1, 1.41421356237309504880*x, x );
    x = ldexp(x,e>>1);

    return x;
}

template<class E1>
double1 sqrt( const expression<E1>& a, float_type  )
{
    return native_sqrt(a(),float_type());
}

template<class E1>
double2 sqrt( const expression<E1>& a, float2_type  )
{
    return native_sqrt(a(),float2_type());
}

template<class E1>
double1 sqrt( const expression<E1>& a, float4_type  )
{
    return native_sqrt(a(),float4_type());
}

template<class E1>
double1 sqrt( const expression<E1>& a, double_type  )
{
    double1 w,x;

    w = a();
    x = native_sqrt(w,double_type());

    x = 0.5*(x + w/x);
    x = 0.5*(x + w/x);

    return x;
}

template<class E1>
double2 sqrt( const expression<E1>& a, double2_type  )
{
    double2 w,x;

    w = a();
    x = native_sqrt(w,double2_type());

    x = 0.5*(x + w/x);
    x = 0.5*(x + w/x);

    return x;
}

template<class E1>
double1 fast_sqrt( const expression<E1>& a, float_type  )
{
    return native_sqrt(a(),float_type());
}

template<class E1>
double2 fast_sqrt( const expression<E1>& a, float2_type  )
{
    return native_sqrt(a(),float2_type());
}

template<class E1>
double1 fast_sqrt( const expression<E1>& a, float4_type  )
{
    return native_sqrt(a(),float4_type());
}

template<class E1>
double1 fast_sqrt( const expression<E1>& a, double_type  )
{
    double1 w,x,r;

    w = a();
    x = native_rsqrt(w);
    x = x*mad(x*x,-w,3);
    r = x*w;
    r = r*mad(-0.0625,r*x,0.75);

    return r;
}

template<class E1>
double2 fast_sqrt( const expression<E1>& a, double2_type  )
{
    double2 w,x,r;

    w = a();
    x = native_rsqrt(w);
    x = x*mad(x*x,-w,3);
    r = x*w;
    r = r*mad(-0.0625,r*x,0.75);

    return r;
}

} // detail

template<class E1>
variable<typename E1::value_type> native_sqrt( const detail::expression<E1>& e1 )
{
    return detail::native_sqrt(e1(),typename E1::value_type());
}

//
// error for double < 1 ulp ( with few exceptions <= 0.5 ulp )
//
template<class E1>
variable<typename E1::value_type> sqrt( const detail::expression<E1>& e1 )
{
    return detail::sqrt(e1(),typename E1::value_type());
}

//
// error for double < 2 ulp
//
// no divisions used ( huge speed improvement on older GPUs )
//
template<class E1>
variable<typename E1::value_type> fast_sqrt( const detail::expression<E1>& e1 )
{
    return detail::fast_sqrt(e1(),typename E1::value_type());
}


}
}

#endif
