/*
 * C++ to IL compiler/generator rsqrt
 * 
 * Copyright (C) 2010 Artur Kornacki
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

#ifndef __CAL_IL_MATH_RSQRT_H
#define __CAL_IL_MATH_RSQRT_H

#include <cal/il/math/cal_il_frexp.hpp>
#include <cal/il/math/cal_il_ldexp.hpp>

namespace cal {
namespace il {

namespace detail {

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

template<class E1>
unary<E1,cal_unary_rsq<typename E1::value_type> > native_rsqrt( const expression<E1>& e1, float_type  )
{
    typedef unary<E1,cal_unary_rsq<typename E1::value_type> > expression_type;
    return expression_type(e1());
}

template<class E1>
unary<E1,cal_unary_rsq<typename E1::value_type> > native_rsqrt( const expression<E1>& e1, float2_type  )
{
    typedef unary<E1,cal_unary_rsq<typename E1::value_type> > expression_type;
    return expression_type(e1());
}

template<class E1>
unary<E1,cal_unary_rsq<typename E1::value_type> > native_rsqrt( const expression<E1>& e1, float4_type  )
{
    typedef unary<E1,cal_unary_rsq<typename E1::value_type> > expression_type;
    return expression_type(e1());
}

template<class E1>
double1 native_rsqrt( const expression<E1>& e1, double_type  )
{
    typedef unary<E1,cal_unary_rsq<typename E1::value_type> > rsq_type;

#if defined(__CAL_H__)
    if( Source::info.available && Source::info.target>=CAL_TARGET_CYPRESS ) return rsq_type(e1());
#endif
    double1 w,x;
    int1    e;

    w = e1();
    x = frexp(w,e);
    x = cast_type<double1>( native_rsqrt(cast_type<float1>(x),float_type()) );
    x = select( e&0x1, 0.70710678118654752440*x, x );
    x = ldexp(x,-(e>>1));

    return x;
}

template<class E1>
double2 native_rsqrt( const expression<E1>& e1, double2_type  )
{
    typedef unary<E1,cal_unary_rsq<typename E1::value_type> > rsq_type;

#if defined(__CAL_H__)
    if( Source::info.available && Source::info.target>=CAL_TARGET_CYPRESS ) return rsq_type(e1());
#endif
    double2 w,x;
    int2    e;

    w = e1();
    x = frexp(w,e);
    x = cast_type<double2>( native_rsqrt(cast_type<float2>(x),float2_type()) );
    x = select( e&0x1, 0.70710678118654752440*x, x );
    x = ldexp(x,-(e>>1));

    return x;
}

template<class E1>
unary<E1,cal_unary_rsq<typename E1::value_type> > rsqrt( const expression<E1>& a, float_type  )
{
    return native_rsqrt(a(),float_type());
}

template<class E1>
unary<E1,cal_unary_rsq<typename E1::value_type> > rsqrt( const expression<E1>& a, float2_type  )
{
    return native_rsqrt(a(),float2_type());
}

template<class E1>
unary<E1,cal_unary_rsq<typename E1::value_type> > rsqrt( const expression<E1>& a, float4_type  )
{
    return native_rsqrt(a(),float4_type());
}

template<class E1>
double1 rsqrt( const expression<E1>& a, double_type  )
{
    double1 w,w2,x;

    w  = a();
    w2 = -0.5*w;
    x  = native_rsqrt(w,double_type());

    x  = x*mad( x*x, w2, 1.5 );
    x  = x*mad( x*x, w2, 1.5 );

    return x;
}

template<class E1>
double2 rsqrt( const expression<E1>& a, double2_type  )
{
    double2 w,w2,x;

    w  = a();
    w2 = -0.5*w;
    x  = native_rsqrt(w,double2_type());

    x  = x*mad( x*x, w2, 1.5 );
    x  = x*mad( x*x, w2, 1.5 );

    return x;
}

} // detail

template<class E1>
variable<typename E1::value_type> native_rsqrt( const detail::expression<E1>& e1 )
{
    return detail::native_rsqrt(e1(),typename E1::value_type());
}

//
// error for double < 2 ulp
//
template<class E1>
variable<typename E1::value_type> rsqrt( const detail::expression<E1>& e1 )
{
    return detail::rsqrt(e1(),typename E1::value_type());
}

}
}

#endif
