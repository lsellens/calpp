/*
 * C++ to IL compiler/generator operators mul, div, mod
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

#ifndef __CAL_IL_OPERATORS_MULDIV_H
#define __CAL_IL_OPERATORS_MULDIV_H

#if defined(__CAL_USE_IMPROVED_MULDIV)
  #include <cmath>
  #include <cal/il/math/cal_il_ldexp.hpp>
#endif

namespace cal {
namespace il {

namespace detail {

#if defined(__CAL_USE_IMPROVED_MULDIV)
template<class E1>
variable<typename E1::value_type> fast_mul( const E1& a, const boost::int32_t& v1 )
{
    double m;
    int    e;

    m = std::frexp((double)v1,&e);
    if( m==0.5  ) { if( e!=1 ) return a << (e-1); else return a; }
    if( m==-0.5 ) { if( e!=1 ) return -(a << (e-1)); else return -a; }
    return a*value<E1>(v1);
}

template<class E1>
variable<typename E1::value_type> fast_mul( const boost::int32_t& v1, const E1& a )
{
    double m;
    int    e;

    m = std::frexp((double)v1,&e);
    if( m==0.5  ) { if( e!=1 ) return a << (e-1); else return a; }
    if( m==-0.5 ) { if( e!=1 ) return -(a << (e-1)); else -a; }
    return value<E1>(v1)*a;
}

template<class E1>
variable<typename E1::value_type> fast_mul( const E1& a, const boost::uint32_t& v1 )
{
    double m;
    int    e;

    m = std::frexp((double)v1,&e);
    if( m==0.5  ) { if ( e!=1 ) return (a << (e-1)); else return a; }
    return a*value<E1>(v1);
}

template<class E1>
variable<typename E1::value_type> fast_mul( const boost::uint32_t& v1, const E1& a )
{
    double m;
    int    e;

    m = std::frexp((double)v1,&e);
    if( m==0.5  ) { if( e!=1 ) return a << (e-1); else return a; }
    return value<E1>(v1)*a;
}

template<class E1>
variable<typename E1::value_type> fast_mul( const E1& a, const float& v1 )
{
    return a*value<E1>(v1);
}

template<class E1>
variable<typename E1::value_type> fast_mul( const float& v1, const E1& a )
{
    return value<E1>(v1)*a;
}

template<class E1>
variable<typename E1::value_type> fast_mul( const E1& a, const double& v1 )
{
    double m;
    int    e;

    m = std::frexp(v1,&e);
    if( m==0.5  ) { if( e!=1 ) return ldexp(a,e-1); else return a; }
    if( m==-0.5 ) { if( e!=1 ) return -ldexp(a,e-1); else return -a; }
    return a*value<E1>(v1);
}

template<class E1>
variable<typename E1::value_type> fast_mul( const double& v1, const E1& a )
{
    double m;
    int    e;

    m = std::frexp(v1,&e);
    if( m==0.5  ) { if( e!=1 ) return ldexp(a,e-1); else return a; }
    if( m==-0.5 ) { if( e!=1 ) return -ldexp(a,e-1); else return -a; }

    return value<E1>(v1)*a;
}

template<class E1>
variable<typename E1::value_type> fast_div( const E1& a, const boost::int32_t& v1 )
{
    double m;
    int    e;

    m = std::frexp((double)v1,&e);
    if( m==0.5  ) { if( e!=1 ) return a >> (e-1); else return a; }
    if( m==-0.5 ) { if( e!=1 ) return -(a >> (e-1)); else return -a; }
    return a/value<E1>(v1);
}

template<class E1>
variable<typename E1::value_type> fast_div( const boost::int32_t& v1, const E1& a )
{
    return value<E1>(v1)/a;
}

template<class E1>
variable<typename E1::value_type> fast_div( const E1& a, const boost::uint32_t& v1 )
{
    double m;
    int    e;

    m = std::frexp((double)v1,&e);
    if( m==0.5  ) { if( e!=1 ) return a >> (e-1); else return a; }
    return a/value<E1>(v1);
}

template<class E1>
variable<typename E1::value_type> fast_div( const boost::uint32_t& v1, const E1& a )
{
    return value<E1>(v1)/a;
}

template<class E1>
variable<typename E1::value_type> fast_div( const E1& a, const float& v1 )
{
    return a/value<E1>(v1);
}

template<class E1>
variable<typename E1::value_type> fast_div( const float& v1, const E1& a )
{
    return value<E1>(v1)/a;
}

template<class E1>
variable<typename E1::value_type> fast_div( const E1& a, const double& v1 )
{
    double m;
    int    e;

    m = std::frexp(v1,&e);
    if( m==0.5  ) { if( e!=1 ) return ldexp(a,-(e-1)); else return a; }
    if( m==-0.5 ) { if( e!=1 ) return -ldexp(a,-(e-1)); else return -a; }
    return a/value<E1>(v1);
}

template<class E1>
variable<typename E1::value_type> fast_div( const double& v1, const E1& a )
{
    return value<E1>(v1)/a;
}

template<class E1>
variable<typename E1::value_type> fast_mod( const E1& a, const boost::int32_t& v1 )
{
    double m;
    int    e;

    m = std::frexp((double)v1,&e);
    if( m==0.5  ) return a & (v1-1);
    return a%value<E1>(v1);
}

template<class E1>
variable<typename E1::value_type> fast_mod( const boost::int32_t& v1, const E1& a )
{
    return value<E1>(v1)%a;
}

template<class E1>
variable<typename E1::value_type> fast_mod( const E1& a, const boost::uint32_t& v1 )
{
    double m;
    int    e;

    m = std::frexp((double)v1,&e);
    if( m==0.5  ) return a & (v1-1);
    return a%value<E1>(v1);
}

template<class E1>
variable<typename E1::value_type> fast_mod( const boost::uint32_t& v1, const E1& a )
{
    return value<E1>(v1)%a;
}

template<class E1>
variable<typename E1::value_type> fast_mod( const E1& a, const float& v1 )
{
    return a%value<E1>(v1);
}

template<class E1>
variable<typename E1::value_type> fast_mod( const float& v1, const E1& a )
{
    return value<E1>(v1)%a;
}

template<class E1>
variable<typename E1::value_type> fast_mod( const E1& a, const double& v1 )
{
    return a%value<E1>(v1);
}

template<class E1>
variable<typename E1::value_type> fast_mod( const double& v1, const E1& a )
{
    return value<E1>(v1)%a;
}
#endif

} // detail

template<class E1,class E2>
detail::binary<E1,E2,detail::cal_binary_mul<typename E1::value_type,typename E2::value_type> > operator*( const detail::expression<E1>& e1, const detail::expression<E2>& e2 )
{
    typedef detail::binary<E1,E2,detail::cal_binary_mul<typename E1::value_type,typename E2::value_type> > expression_type;
    return expression_type( e1(), e2() );
}

template<class E1,class E2>
detail::binary<E1,E2,detail::cal_binary_div<typename E1::value_type,typename E2::value_type> > operator/( const detail::expression<E1>& e1, const detail::expression<E2>& e2 )
{
    typedef detail::binary<E1,E2,detail::cal_binary_div<typename E1::value_type,typename E2::value_type> > expression_type;
    return expression_type( e1(), e2() );
}

template<class E1,class E2>
detail::binary<E1,E2,detail::cal_binary_mod<typename E1::value_type,typename E2::value_type> > operator%( const detail::expression<E1>& e1, const detail::expression<E2>& e2 )
{
    typedef detail::binary<E1,E2,detail::cal_binary_mod<typename E1::value_type,typename E2::value_type> > expression_type;
    return expression_type( e1(), e2() );
}

//
// mixed CAL IL and C types
//

#if !defined(__CAL_USE_IMPROVED_MULDIV)
template<class E1>
detail::binary<E1,detail::value<E1>,detail::cal_binary_mul<typename E1::value_type,typename E1::value_type> > operator*( const detail::expression<E1>& e1, const typename E1::value_type::component_type& v1 )
{
    typedef detail::binary<E1,detail::value<E1>,detail::cal_binary_mul<typename E1::value_type,typename E1::value_type> > expression_type;
    return expression_type( e1(), detail::value<E1>(v1) );
}
template<class E1>
detail::binary<detail::value<E1>,E1,detail::cal_binary_mul<typename E1::value_type,typename E1::value_type> > operator*( const typename E1::value_type::component_type& v1, const detail::expression<E1>& e1 )
{
    typedef detail::binary<detail::value<E1>,E1,detail::cal_binary_mul<typename E1::value_type,typename E1::value_type> > expression_type;
    return expression_type( detail::value<E1>(v1), e1() );
}

template<class E1>
detail::binary<E1,detail::value<E1>,detail::cal_binary_div<typename E1::value_type,typename E1::value_type> > operator/( const detail::expression<E1>& e1, const typename E1::value_type::component_type& v1 )
{
    typedef detail::binary<E1,detail::value<E1>,detail::cal_binary_div<typename E1::value_type,typename E1::value_type> > expression_type;
    return expression_type( e1(), detail::value<E1>(v1) );
}
template<class E1>
detail::binary<detail::value<E1>,E1,detail::cal_binary_div<typename E1::value_type,typename E1::value_type> > operator/( const typename E1::value_type::component_type& v1, const detail::expression<E1>& e1 )
{
    typedef detail::binary<detail::value<E1>,E1,detail::cal_binary_div<typename E1::value_type,typename E1::value_type> > expression_type;
    return expression_type( detail::value<E1>(v1), e1() );
}

template<class E1>
detail::binary<E1,detail::value<E1>,detail::cal_binary_mod<typename E1::value_type,typename E1::value_type> > operator%( const detail::expression<E1>& e1, const typename E1::value_type::component_type& v1 )
{
    typedef detail::binary<E1,detail::value<E1>,detail::cal_binary_mod<typename E1::value_type,typename E1::value_type> > expression_type;
    return expression_type( e1(), detail::value<E1>(v1) );
}
template<class E1>
detail::binary<detail::value<E1>,E1,detail::cal_binary_mod<typename E1::value_type,typename E1::value_type> > operator%( const typename E1::value_type::component_type& v1, const detail::expression<E1>& e1 )
{
    typedef detail::binary<detail::value<E1>,E1,detail::cal_binary_mod<typename E1::value_type,typename E1::value_type> > expression_type;
    return expression_type( detail::value<E1>(v1), e1() );
}
#else
template<class E1>
variable<typename E1::value_type> operator*( const detail::expression<E1>& e1, const typename E1::value_type::component_type& v1 )
{
    return fast_mul(e1(),v1);
}

template<class E1>
variable<typename E1::value_type> operator*( const typename E1::value_type::component_type& v1, const detail::expression<E1>& e1 )
{
    return fast_mul(v1,e1());
}

template<class E1>
variable<typename E1::value_type> operator/( const detail::expression<E1>& e1, const typename E1::value_type::component_type& v1 )
{
    return fast_div(e1(),v1);
}

template<class E1>
variable<typename E1::value_type> operator/( const typename E1::value_type::component_type& v1, const detail::expression<E1>& e1 )
{
    return fast_div(v1,e1());
}

template<class E1>
variable<typename E1::value_type> operator%( const detail::expression<E1>& e1, const typename E1::value_type::component_type& v1 )
{
    return fast_mod(e1(),v1);
}

template<class E1>
variable<typename E1::value_type> operator%( const typename E1::value_type::component_type& v1, const detail::expression<E1>& e1 )
{
    return fast_mod(v1,e1());
}
#endif

} // il
} // cal

#endif
