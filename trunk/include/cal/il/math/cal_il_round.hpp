/*
 * C++ to IL compiler/generator round
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

#ifndef __CAL_IL_MATH_ROUND_H
#define __CAL_IL_MATH_ROUND_H

#include <cal/il/math/cal_il_fract.hpp>

namespace cal {
namespace il {

namespace detail {

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

template<class E1>
unary<E1,cal_unary_round<typename E1::value_type> > round( const expression<E1>& e1, float_type  )
{
    typedef unary<E1,cal_unary_round<typename E1::value_type> > expression_type;
    return expression_type(e1);
}

template<class E1>
unary<E1,cal_unary_round<typename E1::value_type> > round( const expression<E1>& e1, float2_type  )
{
    typedef unary<E1,cal_unary_round<typename E1::value_type> > expression_type;
    return expression_type(e1);
}

template<class E1>
unary<E1,cal_unary_round<typename E1::value_type> > round( const expression<E1>& e1, float4_type  )
{
    typedef unary<E1,cal_unary_round<typename E1::value_type> > expression_type;
    return expression_type(e1);
}

template<class E1>
variable<typename E1::value_type> round( const expression<E1>& e1, double_type  )
{
    variable<typename E1::value_type>   x;
    x = e1() + 0.5;
    return x-fract(x);
}

template<class E1>
variable<typename E1::value_type> round( const expression<E1>& e1, double2_type  )
{
    variable<typename E1::value_type>   x;
    x = e1() + 0.5;
    return x-fract(x);
}

} // detail

template<class E1>
variable<typename E1::value_type> round( const detail::expression<E1>& e1 )
{
    return detail::round(e1(),typename E1::value_type());
}

} // il
} // cal

#endif
