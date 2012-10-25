/*
 * C++ to IL compiler/generator min
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

#ifndef __CAL_IL_MATH_MIN_H
#define __CAL_IL_MATH_MIN_H

namespace cal {
namespace il {

namespace detail {

template<class S1,class S2>
struct cal_binary_min
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
struct cal_binary_min<float_type,float_type>
{
    typedef float_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("min %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_min<float2_type,float2_type>
{
    typedef float2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("min %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_min<float4_type,float4_type>
{
    typedef float4_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("min %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_min<double_type,double_type>
{
    typedef double_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("dmin %s,%s,%s\n") % r % s0 % s1).str();
    }
};

template<>
struct cal_binary_min<double2_type,double2_type>
{
    typedef double2_type value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, int t0 )
    {
        return (boost::format("dmin %1%,%3%,%5%\n"
                              "dmin %2%,%4%,%6%\n") % make_swizzle(r ,1,2,0,0) % make_swizzle(r ,3,4,0,0)
                                                    % make_swizzle(s0,1,2,0,0) % make_swizzle(s0,3,4,0,0)
                                                    % make_swizzle(s1,1,2,0,0) % make_swizzle(s1,3,4,0,0)).str();
    }
};

template<class E1,class E2>
binary<E1,E2,cal_binary_min<typename E1::value_type,typename E2::value_type> > min( const expression<E1>& e1, const expression<E2>& e2, float_type )
{
    typedef binary<E1,E2,cal_binary_min<typename E1::value_type,typename E2::value_type> > expression_type;
    return expression_type( e1(), e2() );
}

template<class E1,class E2>
binary<E1,E2,cal_binary_min<typename E1::value_type,typename E2::value_type> > min( const expression<E1>& e1, const expression<E2>& e2, float2_type )
{
    typedef binary<E1,E2,cal_binary_min<typename E1::value_type,typename E2::value_type> > expression_type;
    return expression_type( e1(), e2() );
}

template<class E1,class E2>
binary<E1,E2,cal_binary_min<typename E1::value_type,typename E2::value_type> > min( const expression<E1>& e1, const expression<E2>& e2, float4_type )
{
    typedef binary<E1,E2,cal_binary_min<typename E1::value_type,typename E2::value_type> > expression_type;
    return expression_type( e1(), e2() );
}

template<class E1,class E2>
double1 min( const expression<E1>& e1, const expression<E2>& e2, double_type )
{
    typedef binary<E1,E2,cal_binary_min<typename E1::value_type,typename E2::value_type> > min_type;
    
#if defined(__CAL_H__)
    if( Source::info().available && Source::info().target>=CAL_TARGET_CYPRESS ) return min_type(e1(),e2());
#endif

    double1 a,b;
    
    a = e1();
    b = e2();
    
    return select(a<b,a,b);
}

template<class E1,class E2>
double2 min( const expression<E1>& e1, const expression<E2>& e2, double2_type )
{
    typedef binary<E1,E2,cal_binary_min<typename E1::value_type,typename E2::value_type> > min_type;
    
#if defined(__CAL_H__)
    if( Source::info().available && Source::info().target>=CAL_TARGET_CYPRESS ) return min_type(e1(),e2());
#endif

    double2 a,b;
    
    a = e1();
    b = e2();
    
    return select(a<b,a,b);
}

} // detail

template<class E1,class E2>
variable<typename E1::value_type> min( const detail::expression<E1>& e1, const detail::expression<E2>& e2 )
{
    return detail::min(e1(),e2(),typename E1::value_type());
}

}
}

#endif
