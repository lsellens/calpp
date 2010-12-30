/*
 * C++ to IL compiler/generator frexp
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

#ifndef __CAL_IL_MATH_FREXP_H
#define __CAL_IL_MATH_FREXP_H

namespace cal {
namespace il {

namespace detail {

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

template<class E1>
double1 frexp( const expression<E1>& ex, int1& e, double_type  )
{
    typedef unary<E1,cal_unary_frexp<double_type> > expression_type;
    uint4   r0;

    r0 = expression_type(ex());
    e  = cast_type<int1>(r0.y());
    return double1( cast_bits<double1>(r0.zw()) );
}

template<class E1>
double2 frexp( const expression<E1>& ex, int2& e, double2_type  )
{
    int1    e0,e1;
    double2 r,x;

    x = ex();

    r.x() = frexp(x.x(),e0,double_type());
    r.y() = frexp(x.y(),e1,double_type());

    e.x() = e0;
    e.y() = e1;

    return r;
}

} // detail

template<class E1,class E2>
variable<typename E1::value_type> frexp( const detail::expression<E1>& e1, variable<E2>& e2 )
{
    return detail::frexp(e1(),e2,typename E1::value_type());
}

} // il
} // cal

#endif
