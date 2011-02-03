/*
 * C++ to IL compiler/generator floor
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

#ifndef __CAL_IL_MATH_FLOOR_H
#define __CAL_IL_MATH_FLOOR_H

namespace cal {
namespace il {

namespace detail {

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

} // detail

template<class E1>
detail::unary<E1,detail::cal_unary_floor<typename E1::value_type> > floor( const detail::expression<E1>& e1 )
{
    typedef detail::unary<E1,detail::cal_unary_floor<typename E1::value_type> > expression_type;
    return expression_type( e1() );
}

} // il
} // cal

#endif
