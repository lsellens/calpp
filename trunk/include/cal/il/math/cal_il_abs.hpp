/*
 * C++ to IL compiler/generator abs
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

#ifndef __CAL_IL_MATH_ABS_H
#define __CAL_IL_MATH_ABS_H

namespace cal {
namespace il {

namespace detail {

template<class S1>
struct cal_unary_abs {
    typedef invalid_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        BOOST_STATIC_ASSERT(sizeof(S1) != sizeof(S1));
        return std::string();
    }
};

template<>
struct cal_unary_abs<float_type>
{
    typedef float_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("abs %1%,%2%\n") % mask_output(make_swizzle(r,1,0,0,0)) % make_swizzle(s0,1,1,1,1) ).str();
    }
};

template<>
struct cal_unary_abs<float2_type>
{
    typedef float2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("abs  %1%,%2%\n") % mask_output(make_swizzle(r,1,2,0,0)) % make_swizzle(s0,1,2,1,2)).str();
    }
};

template<>
struct cal_unary_abs<float4_type>
{
    typedef float4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("abs %1%,%2%\n") % r % s0).str();
    }
};

template<>
struct cal_unary_abs<double_type>
{
    typedef double_type value_type;
    static const int temp_reg_count=0;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %1%,%2%\n"
                              "mov %3%,%4%_abs\n") % r % s0 % mask_output(make_swizzle(r,2,0,0,0)) % make_swizzle(s0,2,2,2,2)).str();
    }    
};

template<>
struct cal_unary_abs<double2_type>
{
    typedef double2_type value_type;
    static const int temp_reg_count=0;
    
    static std::string emitCode( const std::string& r, const std::string& s0, int t0 )
    {
        return (boost::format("mov %1%,%2%\n"
                              "mov %3%,%4%_abs\n") % r % s0 % mask_output(make_swizzle(r,2,4,0,0)) % make_swizzle(s0,2,2,4,4)).str();
    }
};

} // detail

template<class E1>
detail::unary<E1,detail::cal_unary_abs<typename E1::value_type> > abs( const detail::expression<E1>& e1 )
{
    typedef detail::unary<E1,detail::cal_unary_abs<typename E1::value_type> > expression_type;
    return expression_type( e1() );
}

}
}

#endif
