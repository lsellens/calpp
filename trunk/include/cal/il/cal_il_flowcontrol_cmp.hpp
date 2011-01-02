/*
 * C++ to IL compiler/generator il code flow control
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

#ifndef __CAL_IL_FLOWCONTROL_CMP_H
#define __CAL_IL_FLOWCONTROL_CMP_H

#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>

namespace cal {
namespace il {
namespace detail {

//
//
//

template<typename T,class E0,class E1,class E2,class S1,class S2>
void emit_cmp_lt( T tt, const detail::expression<E0>& e0, const detail::expression<E1>& e1, const detail::expression<E2>& e2, S1, S2, bool neg )
{
    e0().emitCode(::cal::il::Source::code,::cal::il::Source::code.stream());    
    Source::code << boost::format(neg?T::logicalz:T::logicalnz) % e0().resultCode();
}

template<typename T,class E0,class E1,class E2>
void emit_cmp_lt( T tt, const detail::expression<E0>& e0, const detail::expression<E1>& e1, const detail::expression<E2>& e2, float_type, float_type, bool neg )
{
    e1().emitCode(::cal::il::Source::code,::cal::il::Source::code.stream());
    e2().emitCode(::cal::il::Source::code,::cal::il::Source::code.stream());
    Source::code << boost::format(neg?T::relop_ge:T::relop_lt) % e1().resultCode() % e2().resultCode();
}

template<typename T,class E0,class E1,class E2,class S1,class S2>
void emit_cmp_le( T tt, const detail::expression<E0>& e0, const detail::expression<E1>& e1, const detail::expression<E2>& e2, S1, S2, bool neg )
{
    e0().emitCode(::cal::il::Source::code,::cal::il::Source::code.stream());        
    Source::code << boost::format(neg?T::logicalz:T::logicalnz) % e0().resultCode();
}

template<typename T,class E0,class E1,class E2>
void emit_cmp_le( T tt, const detail::expression<E0>& e0, const detail::expression<E1>& e1, const detail::expression<E2>& e2, float_type, float_type, bool neg )
{
    e1().emitCode(::cal::il::Source::code,::cal::il::Source::code.stream());
    e2().emitCode(::cal::il::Source::code,::cal::il::Source::code.stream());
    Source::code << boost::format(neg?T::relop_gt:T::relop_le) % e1().resultCode() % e2().resultCode();
}

template<typename T,class E0,class E1,class E2,class S1,class S2>
void emit_cmp_ne( T tt, const detail::expression<E0>& e0, const detail::expression<E1>& e1, const detail::expression<E2>& e2, S1, S2, bool neg )
{
    e0().emitCode(::cal::il::Source::code,::cal::il::Source::code.stream());        
    Source::code << boost::format(neg?T::logicalz:T::logicalnz) % e0().resultCode();
}

template<typename T,class E0,class E1,class E2>
void emit_cmp_ne( T tt, const detail::expression<E0>& e0, const detail::expression<E1>& e1, const detail::expression<E2>& e2, float_type, float_type, bool neg )
{
    e1().emitCode(::cal::il::Source::code,::cal::il::Source::code.stream());
    e2().emitCode(::cal::il::Source::code,::cal::il::Source::code.stream());
    Source::code << boost::format(neg?T::relop_eq:T::relop_ne) % e1().resultCode() % e2().resultCode();
}

template<typename T,class E0,class E1,class E2,class S1,class S2>
void emit_cmp_eq( T tt, const detail::expression<E0>& e0, const detail::expression<E1>& e1, const detail::expression<E2>& e2, S1, S2, bool neg )
{
    e0().emitCode(::cal::il::Source::code,::cal::il::Source::code.stream());        
    Source::code << boost::format(neg?T::logicalz:T::logicalnz) % e0().resultCode();
}

template<typename T,class E0,class E1,class E2>
void emit_cmp_eq( T tt, const detail::expression<E0>& e0, const detail::expression<E1>& e1, const detail::expression<E2>& e2, float_type, float_type, bool neg )
{
    e1().emitCode(::cal::il::Source::code,::cal::il::Source::code.stream());
    e2().emitCode(::cal::il::Source::code,::cal::il::Source::code.stream());
    Source::code << boost::format(neg?T::relop_ne:T::relop_eq) % e1().resultCode() % e2().resultCode();
}

template<typename T,class E0,class E1,class E2,class S1,class S2>
void emit_cmp_ge( T tt, const detail::expression<E0>& e0, const detail::expression<E1>& e1, const detail::expression<E2>& e2, S1, S2, bool neg )
{
    e0().emitCode(::cal::il::Source::code,::cal::il::Source::code.stream());        
    Source::code << boost::format(neg?T::logicalz:T::logicalnz) % e0().resultCode();
}

template<typename T,class E0,class E1,class E2>
void emit_cmp_ge( T tt, const detail::expression<E0>& e0, const detail::expression<E1>& e1, const detail::expression<E2>& e2, float_type, float_type, bool neg )
{
    e1().emitCode(::cal::il::Source::code,::cal::il::Source::code.stream());
    e2().emitCode(::cal::il::Source::code,::cal::il::Source::code.stream());
    Source::code << boost::format(neg?T::relop_lt:T::relop_ge) % e1().resultCode() % e2().resultCode();
}

template<typename T,class E0,class E1,class E2,class S1,class S2>
void emit_cmp_gt( T tt, const detail::expression<E0>& e0, const detail::expression<E1>& e1, const detail::expression<E2>& e2, S1, S2, bool neg )
{
    e0().emitCode(::cal::il::Source::code,::cal::il::Source::code.stream());        
    Source::code << boost::format(neg?T::logicalz:T::logicalnz) % e0().resultCode();
}

template<typename T,class E0,class E1,class E2>
void emit_cmp_gt( T tt, const detail::expression<E0>& e0, const detail::expression<E1>& e1, const detail::expression<E2>& e2, float_type, float_type, bool neg )
{
    e1().emitCode(::cal::il::Source::code,::cal::il::Source::code.stream());
    e2().emitCode(::cal::il::Source::code,::cal::il::Source::code.stream());
    Source::code << boost::format(neg?T::relop_le:T::relop_gt) % e1().resultCode() % e2().resultCode();
}

//
//
//

template<typename T,class E1,class E2>
void emit_cmp( T tt, const binary<E1,E2,detail::cal_binary_lt<typename E1::value_type,typename E2::value_type> >& e, uint_type, bool neg )
{
    emit_cmp_lt( tt, e, e._e1, e._e2, typename E1::value_type(), typename E2::value_type(), neg );
}

template<typename T,class E1,class E2>
void emit_cmp( T tt, const binary<E1,E2,detail::cal_binary_le<typename E1::value_type,typename E2::value_type> >& e, uint_type, bool neg )
{
    emit_cmp_le( tt, e, e._e1, e._e2, typename E1::value_type(), typename E2::value_type(), neg );
}

template<typename T,class E1,class E2>
void emit_cmp( T tt, const binary<E1,E2,detail::cal_binary_ne<typename E1::value_type,typename E2::value_type> >& e, uint_type, bool neg )
{
    emit_cmp_ne( tt, e, e._e1, e._e2, typename E1::value_type(), typename E2::value_type(), neg );
}

template<typename T,class E1,class E2>
void emit_cmp( T tt, const binary<E1,E2,detail::cal_binary_eq<typename E1::value_type,typename E2::value_type> >& e, uint_type, bool neg )
{
    emit_cmp_eq( tt, e, e._e1, e._e2, typename E1::value_type(), typename E2::value_type(), neg );
}

template<typename T,class E1,class E2>
void emit_cmp( T tt, const binary<E1,E2,detail::cal_binary_ge<typename E1::value_type,typename E2::value_type> >& e, uint_type, bool neg )
{
    emit_cmp_ge( tt, e, e._e1, e._e2, typename E1::value_type(), typename E2::value_type(), neg );
}

template<typename T,class E1,class E2>
void emit_cmp( T tt, const binary<E1,E2,detail::cal_binary_gt<typename E1::value_type,typename E2::value_type> >& e, uint_type, bool neg )
{
    emit_cmp_gt( tt, e, e._e1, e._e2, typename E1::value_type(), typename E2::value_type(), neg );
}

//
//
//

template<typename T,class E>
void emit_cmp( T tt, const detail::expression<E>& e, uint_type, bool neg )
{
    e().emitCode(::cal::il::Source::code,::cal::il::Source::code.stream());    
    Source::code << boost::format(neg?T::logicalz:T::logicalnz) % e().resultCode();
}

template<typename T,class E>
void emit_cmp( T tt, const detail::expression<E>& e, int_type, bool neg )
{
    e().emitCode(::cal::il::Source::code,::cal::il::Source::code.stream());        
    Source::code << boost::format(neg?T::logicalz:T::logicalnz) % e().resultCode();
}

template<typename T,class E>
void emit_cmp( T tt, const detail::expression<E>& e,  float_type, bool neg )
{
    e().emitCode(::cal::il::Source::code,::cal::il::Source::code.stream());        
    Source::code << boost::format(neg?T::z:T::nz) % e().resultCode();
}

template<typename T,class E>
void emit_cmp( T tt, const unary< E, detail::cal_unary_not<typename E::value_type> >& e, uint_type, bool neg )
{
    emit_cmp( tt, e._e, typename E::value_type(), !neg );
}

template<typename T,class E>
void emit_cmp( T tt, const detail::expression<E>& e, bool neg=false )
{
    typedef boost::is_same<typename E::value_type,float_type> assert_v1;
    typedef boost::is_same<typename E::value_type,uint_type>  assert_v2;
    typedef boost::is_same<typename E::value_type,int_type>   assert_v3;
    BOOST_STATIC_ASSERT( assert_v1::value || assert_v2::value || assert_v3::value );

    emit_cmp( tt, e(), typename E::value_type(), neg );
}

} // detail
} // il
} // cal

#endif
