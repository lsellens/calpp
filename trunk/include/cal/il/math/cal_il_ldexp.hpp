/*
 * C++ to IL compiler/generator ldexp
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

#ifndef __CAL_IL_MATH_LDEXP_H
#define __CAL_IL_MATH_LDEXP_H

namespace cal {
namespace il {

namespace detail {

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

} // detail

template<class E1,class E2>
detail::binary<E1,E2,detail::cal_binary_ldexp<typename E1::value_type,typename E2::value_type> > ldexp( const detail::expression<E1>& e1, const detail::expression<E2>& e2 )
{
    typedef detail::binary<E1,E2,detail::cal_binary_ldexp<typename E1::value_type,typename E2::value_type> > expression_type;
    return expression_type( e1(), e2() );
}

} // il
} // cal

#endif
