/*
 * C++ to IL compiler/generator reciprocal
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

#ifndef __CAL_IL_MATH_RECIPROCAL_H
#define __CAL_IL_MATH_RECIPROCAL_H

#include <cal/il/math/cal_il_frexp.hpp>
#include <cal/il/math/cal_il_ldexp.hpp>

namespace cal {
namespace il {

namespace detail {

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

template<class E1>
detail::unary<E1,detail::cal_unary_rcp<typename E1::value_type> > native_reciprocal( const detail::expression<E1>& e1, float_type )
{
    typedef detail::unary<E1,detail::cal_unary_rcp<typename E1::value_type> > expression_type;
    return expression_type(e1());
}

template<class E1>
detail::unary<E1,detail::cal_unary_rcp<typename E1::value_type> > native_reciprocal( const detail::expression<E1>& e1, float2_type )
{
    typedef detail::unary<E1,detail::cal_unary_rcp<typename E1::value_type> > expression_type;
    return expression_type(e1());
}

template<class E1>
detail::unary<E1,detail::cal_unary_rcp<typename E1::value_type> > native_reciprocal( const detail::expression<E1>& e1, float4_type )
{
    typedef detail::unary<E1,detail::cal_unary_rcp<typename E1::value_type> > expression_type;
    return expression_type(e1());
}

template<class E1>
variable<typename E1::value_type> native_reciprocal( const detail::expression<E1>& e1, double_type )
{
    typedef detail::unary<E1,detail::cal_unary_rcp<typename E1::value_type> >        rcp_type;

#if defined(__CAL_H__)
    if( Source::info.available && Source::info.target>=CAL_TARGET_CYPRESS ) return rcp_type(e1());
#endif
    double1 s;
    int1    e;

    s = frexp(e1(),e);
    s = cast_type<double1>( native_reciprocal(cast_type<float1>(s),float_type()) );
    s = ldexp(s,-e);

    return s;
}

template<class E1>
variable<typename E1::value_type> native_reciprocal( const detail::expression<E1>& e1, double2_type )
{
    typedef detail::unary<E1,detail::cal_unary_rcp<typename E1::value_type> >        rcp_type;

#if defined(__CAL_H__)
    if( Source::info.available && Source::info.target>=CAL_TARGET_CYPRESS ) return rcp_type(e1());
#endif
    double2 s;
    int2    e;

    s = frexp(e1(),e);
    s = cast_type<double2>( native_reciprocal(cast_type<float2>(s),float2_type()) );
    s = ldexp(s,-e);

    return s;
}

template<class E1>
unary<E1,cal_unary_rcp<typename E1::value_type> > reciprocal( const expression<E1>& e1, float_type  )
{
    typedef unary<E1,cal_unary_rcp<typename E1::value_type> > expression_type;
    return expression_type(e1);
}

template<class E1>
unary<E1,cal_unary_rcp<typename E1::value_type> > reciprocal( const expression<E1>& e1, float2_type  )
{
    typedef unary<E1,cal_unary_rcp<typename E1::value_type> > expression_type;
    return expression_type(e1());
}

template<class E1>
unary<E1,cal_unary_rcp<typename E1::value_type> > reciprocal( const expression<E1>& e1, float4_type  )
{
    typedef unary<E1,cal_unary_rcp<typename E1::value_type> > expression_type;
    return expression_type(e1());
}

template<class E1>
variable<typename E1::value_type> reciprocal( const expression<E1>& ed, double_type  )
{
    double1 d,s,t;

    d = ed();
    s = native_reciprocal(d,double_type());

    // Newton-Raphson iterations
    t = mad( -d, s, 1 );
    s = mad(  s, t, s );
    t = mad( -d, s, 1 );
    s = mad(  s, t, s );

    return s;
}

template<class E1>
variable<typename E1::value_type> reciprocal( const expression<E1>& ed, double2_type  )
{
    double2 d,s,t;

    d = ed();
    s = native_reciprocal(d,double2_type());

    // Newton-Raphson iterations
    t = mad( -d, s, 1 );
    s = mad(  s, t, s );
    t = mad( -d, s, 1 );
    s = mad(  s, t, s );

    return s;
}

} // detail

template<class E1>
variable<typename E1::value_type> native_reciprocal( const detail::expression<E1>& e1 )
{
    return detail::native_reciprocal(e1(),typename E1::value_type());
}

//
// error for double <= 0.5ulp
//
template<class E1>
variable<typename E1::value_type> reciprocal( const detail::expression<E1>& e1 )
{
    return detail::reciprocal(e1(),typename E1::value_type());
}

template<class E1>
variable<typename E1::value_type> native_recip( const detail::expression<E1>& e1 )
{
    return detail::native_reciprocal(e1(),typename E1::value_type());
}

template<class E1>
variable<typename E1::value_type> recip( const detail::expression<E1>& e1 )
{
    return detail::reciprocal(e1(),typename E1::value_type());
}

} // il
} // cal

#endif
