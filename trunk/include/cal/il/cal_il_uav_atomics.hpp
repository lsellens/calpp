/*
 * C++ to IL compiler/generator uav atomic functions
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

#ifndef __CAL_IL_UAV_ATOMICS_H
#define __CAL_IL_UAV_ATOMICS_H

namespace cal {
namespace il {

template<class T, class E, class C, class E1>
void atom_add( const detail::uav_expression_base<T,E,C>& uav, const detail::expression<E1>& e1 )
{
    typedef boost::is_same<T,int_type>                assert_v1;
    typedef boost::is_same<T,uint_type>               assert_v2;
    typedef boost::is_same<T,typename E1::value_type> assert_v3;
    BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && assert_v3::value );

    uav.emit_atomic("uav_add_id(%1%) %2%,%3%\n",e1());
}

template<class T, class E, class C, class E1>
void atom_sub( const detail::uav_expression_base<T,E,C>& uav, const detail::expression<E1>& e1 )
{
    typedef boost::is_same<T,int_type>                assert_v1;
    typedef boost::is_same<T,uint_type>               assert_v2;
    typedef boost::is_same<T,typename E1::value_type> assert_v3;
    BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && assert_v3::value );

    uav.emit_atomic("uav_sub_id(%1%) %2%,%3%\n",e1());
}

template<class E, class C, class E1>
void atom_min( const detail::uav_expression_base<int_type,E,C>& uav, const detail::expression<E1>& e1 )
{
    typedef boost::is_same<typename E1::value_type,int_type>  assert_v1;
    BOOST_STATIC_ASSERT( assert_v1::value );

    uav.emit_atomic("uav_min_id(%1%) %2%,%3%\n",e1());
}

template<class E, class C, class E1>
void atom_max( const detail::uav_expression_base<int_type,E,C>& uav, const detail::expression<E1>& e1 )
{
    typedef boost::is_same<typename E1::value_type,int_type>  assert_v1;
    BOOST_STATIC_ASSERT( assert_v1::value );

    uav.emit_atomic("uav_max_id(%1%) %2%,%3%\n",e1());
}

template<class E, class C, class E1>
void atom_min( const detail::uav_expression_base<uint_type,E,C>& uav, const detail::expression<E1>& e1 )
{
    typedef boost::is_same<typename E1::value_type,uint_type>  assert_v1;
    BOOST_STATIC_ASSERT( assert_v1::value );

    uav.emit_atomic("uav_umin_id(%1%) %2%,%3%\n",e1());
}

template<class E, class C, class E1>
void atom_max( const detail::uav_expression_base<uint_type,E,C>& uav, const detail::expression<E1>& e1 )
{
    typedef boost::is_same<typename E1::value_type,uint_type>  assert_v1;
    BOOST_STATIC_ASSERT( assert_v1::value );

    uav.emit_atomic("uav_umax_id(%1%) %2%,%3%\n",e1());
}

template<class T, class E, class C, class E1>
void atom_and( const detail::uav_expression_base<T,E,C>& uav, const detail::expression<E1>& e1 )
{
    typedef boost::is_same<T,int_type>                assert_v1;
    typedef boost::is_same<T,uint_type>               assert_v2;
    typedef boost::is_same<T,typename E1::value_type> assert_v3;
    BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && assert_v3::value );

    uav.emit_atomic("uav_and_id(%1%) %2%,%3%\n",e1());
}

template<class T, class E, class C, class E1>
void atom_or( const detail::uav_expression_base<T,E,C>& uav, const detail::expression<E1>& e1 )
{
    typedef boost::is_same<T,int_type>                assert_v1;
    typedef boost::is_same<T,uint_type>               assert_v2;
    typedef boost::is_same<T,typename E1::value_type> assert_v3;
    BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && assert_v3::value );

    uav.emit_atomic("uav_or_id(%1%) %2%,%3%\n",e1());
}

template<class T, class E, class C, class E1>
void atom_xor( const detail::uav_expression_base<T,E,C>& uav, const detail::expression<E1>& e1 )
{
    typedef boost::is_same<T,int_type>                assert_v1;
    typedef boost::is_same<T,uint_type>               assert_v2;
    typedef boost::is_same<T,typename E1::value_type> assert_v3;
    BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && assert_v3::value );

    uav.emit_atomic("uav_xor_id(%1%) %2%,%3%\n",e1());
}

template<class T, class E, class C, class E1, class E2>
void atom_cmpxchg( const detail::uav_expression_base<T,E,C>& uav, const detail::expression<E1>& cmp, const detail::expression<E2>& val )
{
    typedef boost::is_same<T,int_type>                assert_v1;
    typedef boost::is_same<T,uint_type>               assert_v2;
    typedef boost::is_same<T,typename E1::value_type> assert_v3;
    typedef boost::is_same<T,typename E2::value_type> assert_v4;
    BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && assert_v3::value && assert_v4::value );

    uav.emit_atomic("uav_cmp_id(%1%) %2%,%3%,%4%\n",val(),cmp());
}

template<class T, class E, class C, class E1>
variable<T> atom_add( const detail::uav_expression_base<T,E,C>& uav, const detail::expression<E1>& e1 )
{
    typedef boost::is_same<T,int_type>                assert_v1;
    typedef boost::is_same<T,uint_type>               assert_v2;
    typedef boost::is_same<T,typename E1::value_type> assert_v3;
    BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && assert_v3::value );

    variable<T> r;
    uav.emit_atomic("uav_read_add_id(%1%) %3%,%2%,%4%\n",r,e1());
    return r;
}

template<class T, class E, class C, class E1>
variable<T> atom_sub( const detail::uav_expression_base<T,E,C>& uav, const detail::expression<E1>& e1 )
{
    typedef boost::is_same<T,int_type>                assert_v1;
    typedef boost::is_same<T,uint_type>               assert_v2;
    typedef boost::is_same<T,typename E1::value_type> assert_v3;
    BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && assert_v3::value );

    variable<T> r;
    uav.emit_atomic("uav_read_sub_id(%1%) %3%,%2%,%4%\n",r,e1());
    return r;
}

template<class T, class E, class C, class E1>
variable<T> atom_xchg( const detail::uav_expression_base<T,E,C>& uav, const detail::expression<E1>& e1 )
{
    typedef boost::is_same<T,int_type>                assert_v1;
    typedef boost::is_same<T,uint_type>               assert_v2;
    typedef boost::is_same<T,typename E1::value_type> assert_v3;
    BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && assert_v3::value );

    variable<T> r;
    uav.emit_atomic("uav_read_xchg_id(%1%) %3%,%2%,%4%\n",r,e1());
    return r;
}

template<class T, class E, class C, class E1>
variable<int_type> atom_min( const detail::uav_expression_base<int_type,E,C>& uav, const detail::expression<E1>& e1 )
{
    typedef boost::is_same<typename E1::value_type,int_type> assert_v1;
    BOOST_STATIC_ASSERT( assert_v1::value );

    variable<int_type> r;
    uav.emit_atomic("uav_read_min_id(%1%) %3%,%2%,%4%\n",r,e1());
    return r;
}

template<class T, class E, class C, class E1>
variable<int_type> atom_max( const detail::uav_expression_base<int_type,E,C>& uav, const detail::expression<E1>& e1 )
{
    typedef boost::is_same<typename E1::value_type,int_type> assert_v1;
    BOOST_STATIC_ASSERT( assert_v1::value );

    variable<int_type> r;
    uav.emit_atomic("uav_read_max_id(%1%) %3%,%2%,%4%\n",r,e1());
    return r;
}

template<class T, class E, class C, class E1>
variable<uint_type> atom_min( const detail::uav_expression_base<uint_type,E,C>& uav, const detail::expression<E1>& e1 )
{
    typedef boost::is_same<typename E1::value_type,uint_type> assert_v1;
    BOOST_STATIC_ASSERT( assert_v1::value );

    variable<uint_type> r;
    uav.emit_atomic("uav_read_umin_id(%1%) %3%,%2%,%4%\n",r,e1());
    return r;
}

template<class T, class E, class C, class E1>
variable<uint_type> atom_max( const detail::uav_expression_base<uint_type,E,C>& uav, const detail::expression<E1>& e1 )
{
    typedef boost::is_same<typename E1::value_type,uint_type> assert_v1;
    BOOST_STATIC_ASSERT( assert_v1::value );

    variable<uint_type> r;
    uav.emit_atomic("uav_read_umax_id(%1%) %3%,%2%,%4%\n",r,e1());
    return r;
}

template<class T, class E, class C, class E1>
variable<T> atom_and( const detail::uav_expression_base<T,E,C>& uav, const detail::expression<E1>& e1 )
{
    typedef boost::is_same<T,int_type>                assert_v1;
    typedef boost::is_same<T,uint_type>               assert_v2;
    typedef boost::is_same<T,typename E1::value_type> assert_v3;
    BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && assert_v3::value );

    variable<T> r;
    uav.emit_atomic("uav_read_and_id(%1%) %3%,%2%,%4%\n",r,e1());
    return r;
}

template<class T, class E, class C, class E1>
variable<T> atom_or( const detail::uav_expression_base<T,E,C>& uav, const detail::expression<E1>& e1 )
{
    typedef boost::is_same<T,int_type>                assert_v1;
    typedef boost::is_same<T,uint_type>               assert_v2;
    typedef boost::is_same<T,typename E1::value_type> assert_v3;
    BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && assert_v3::value );

    variable<T> r;
    uav.emit_atomic("uav_read_or_id(%1%) %3%,%2%,%4%\n",r,e1());
    return r;
}

template<class T, class E, class C, class E1>
variable<T> atom_xor( const detail::uav_expression_base<T,E,C>& uav, const detail::expression<E1>& e1 )
{
    typedef boost::is_same<T,int_type>                assert_v1;
    typedef boost::is_same<T,uint_type>               assert_v2;
    typedef boost::is_same<T,typename E1::value_type> assert_v3;
    BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && assert_v3::value );

    variable<T> r;
    uav.emit_atomic("uav_read_xor_id(%1%) %3%,%2%,%4%\n",r,e1());
    return r;
}

template<class T, class E, class C, class E1, class E2>
variable<T> atom_cmpxchg( const detail::uav_expression_base<T,E,C>& uav, const detail::expression<E1>& cmp, const detail::expression<E2>& val )
{
    typedef boost::is_same<T,int_type>                assert_v1;
    typedef boost::is_same<T,uint_type>               assert_v2;
    typedef boost::is_same<T,typename E1::value_type> assert_v3;
    typedef boost::is_same<T,typename E2::value_type> assert_v4;
    BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && assert_v3::value && assert_v4::value );

    variable<T> r;
    uav.emit_atomic("uav_read_cmp_xchg_id(%1%) %3%,%2%,%4%,%5%\n",r,val(),cmp());
    return r;
}

//
// mixed with C types
//

template<class T, class E, class C>
void atom_add( const detail::uav_expression_base<T,E,C>& uav, const typename T::component_type& v1 )
{
    atom_add(uav,detail::value<T>(v1));
}

template<class T, class E, class C>
void atom_sub( const detail::uav_expression_base<T,E,C>& uav, const typename T::component_type& v1  )
{
    atom_sub(uav,detail::value<T>(v1));
}

template<class T, class E, class C>
void atom_min( const detail::uav_expression_base<T,E,C>& uav, const typename T::component_type& v1 )
{
    atom_min(uav,detail::value<T>(v1));
}

template<class T, class E, class C>
void atom_max( const detail::uav_expression_base<T,E,C>& uav, const typename T::component_type& v1  )
{
    atom_max(uav,detail::value<T>(v1));
}

template<class T, class E, class C>
void atom_and( const detail::uav_expression_base<T,E,C>& uav, const typename T::component_type& v1 )
{
    atom_and(uav,detail::value<T>(v1));
}

template<class T, class E, class C>
void atom_or( const detail::uav_expression_base<T,E,C>& uav, const typename T::component_type& v1  )
{
    atom_or(uav,detail::value<T>(v1));
}

template<class T, class E, class C>
void atom_xor( const detail::uav_expression_base<T,E,C>& uav, const typename T::component_type& v1  )
{
    atom_xor(uav,detail::value<T>(v1));
}

template<class T, class E, class C, class E1>
void atom_cmpxchg( const detail::uav_expression_base<T,E,C>& uav, const detail::expression<E1>& cmp, const typename T::component_type& val )
{
    atom_cmpxchg(uav,cmp(),detail::value<T>(val));
}

template<class T, class E, class C, class E1>
void atom_cmpxchg( const detail::uav_expression_base<T,E,C>& uav, const typename T::component_type& cmp, const detail::expression<E1>& val  )
{
    atom_cmpxchg(uav,detail::value<T>(cmp),val());
}

template<class T, class E, class C>
variable<T> atom_add( const detail::uav_expression_base<T,E,C>& uav, const typename T::component_type& v1 )
{
    return atom_add(uav,detail::value<T>(v1));
}

template<class T, class E, class C>
variable<T> atom_sub( const detail::uav_expression_base<T,E,C>& uav, const typename T::component_type& v1  )
{
    return atom_sub(uav,detail::value<T>(v1));
}

template<class T, class E, class C>
variable<T> atom_min( const detail::uav_expression_base<T,E,C>& uav, const typename T::component_type& v1 )
{
    return atom_min(uav,detail::value<T>(v1));
}

template<class T, class E, class C>
variable<T> atom_max( const detail::uav_expression_base<T,E,C>& uav, const typename T::component_type& v1  )
{
    return atom_max(uav,detail::value<T>(v1));
}

template<class T, class E, class C>
variable<T> atom_and( const detail::uav_expression_base<T,E,C>& uav, const typename T::component_type& v1 )
{
    return atom_and(uav,detail::value<T>(v1));
}

template<class T, class E, class C>
variable<T> atom_or( const detail::uav_expression_base<T,E,C>& uav, const typename T::component_type& v1  )
{
    return atom_or(uav,detail::value<T>(v1));
}

template<class T, class E, class C>
variable<T> atom_xor( const detail::uav_expression_base<T,E,C>& uav, const typename T::component_type& v1  )
{
    return atom_xor(uav,detail::value<T>(v1));
}

template<class T, class E, class C, class E1>
variable<T> atom_cmpxchg( const detail::uav_expression_base<T,E,C>& uav, const detail::expression<E1>& cmp, const typename T::component_type& val )
{
    return atom_cmpxchg(uav,cmp(),detail::value<T>(val));
}

template<class T, class E, class C, class E1>
variable<T> atom_cmpxchg( const detail::uav_expression_base<T,E,C>& uav, const typename T::component_type& cmp, const detail::expression<E1>& val  )
{
    return atom_cmpxchg(uav,detail::value<T>(cmp),val());
}

} // il
} // cal

#endif
