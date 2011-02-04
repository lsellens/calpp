/*
 * C++ to IL compiler/generator lds atomic functions
 * 
 * Copyright (C) 2010, 2011 Artur Kornacki
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

#ifndef __CAL_IL_LDS_ATOMICS_H
#define __CAL_IL_LDS_ATOMICS_H

namespace cal {
namespace il {

template<class T, class E, class E1>
void _atom_add( const detail::lds_expression<T,E>& lds, const detail::expression<E1>& e1 )
{
    typedef boost::is_same<T,int_type>                assert_v1;
    typedef boost::is_same<T,uint_type>               assert_v2;
    typedef boost::is_same<T,typename E1::value_type> assert_v3;
    BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && assert_v3::value );

    lds.emit_atomic("lds_add_id(%1%) %2%,%3%\n",e1());
}

template<class T, class E, class E1>
void _atom_sub( const detail::lds_expression<T,E>& lds, const detail::expression<E1>& e1 )
{
    typedef boost::is_same<T,int_type>                assert_v1;
    typedef boost::is_same<T,uint_type>               assert_v2;
    typedef boost::is_same<T,typename E1::value_type> assert_v3;
    BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && assert_v3::value );

    lds.emit_atomic("lds_sub_id(%1%) %2%,%3%\n",e1());
}

template<class T, class E>
void _atom_inc( const detail::lds_expression<T,E>& lds )
{
    _atom_add(lds,detail::value<T>(1));
}

template<class T, class E>
void _atom_dec( const detail::lds_expression<T,E>& lds )
{
    _atom_sub(lds,detail::value<T>(1));
}

template<class E, class E1>
void _atom_min( const detail::lds_expression<int_type,E>& lds, const detail::expression<E1>& e1 )
{
    typedef boost::is_same<typename E1::value_type,int_type>  assert_v1;
    BOOST_STATIC_ASSERT( assert_v1::value );

    lds.emit_atomic("lds_min_id(%1%) %2%,%3%\n",e1());
}

template<class E, class E1>
void _atom_max( const detail::lds_expression<int_type,E>& lds, const detail::expression<E1>& e1 )
{
    typedef boost::is_same<typename E1::value_type,int_type>  assert_v1;
    BOOST_STATIC_ASSERT( assert_v1::value );

    lds.emit_atomic("lds_max_id(%1%) %2%,%3%\n",e1());
}

template<class E, class E1>
void _atom_min( const detail::lds_expression<uint_type,E>& lds, const detail::expression<E1>& e1 )
{
    typedef boost::is_same<typename E1::value_type,uint_type>  assert_v1;
    BOOST_STATIC_ASSERT( assert_v1::value );

    lds.emit_atomic("lds_umin_id(%1%) %2%,%3%\n",e1());
}

template<class E, class E1>
void _atom_max( const detail::lds_expression<uint_type,E>& lds, const detail::expression<E1>& e1 )
{
    typedef boost::is_same<typename E1::value_type,uint_type>  assert_v1;
    BOOST_STATIC_ASSERT( assert_v1::value );

    lds.emit_atomic("lds_umax_id(%1%) %2%,%3%\n",e1());
}

template<class T, class E, class E1>
void _atom_and( const detail::lds_expression<T,E>& lds, const detail::expression<E1>& e1 )
{
    typedef boost::is_same<T,int_type>                assert_v1;
    typedef boost::is_same<T,uint_type>               assert_v2;
    typedef boost::is_same<T,typename E1::value_type> assert_v3;
    BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && assert_v3::value );

    lds.emit_atomic("lds_and_id(%1%) %2%,%3%\n",e1());
}

template<class T, class E, class E1>
void _atom_or( const detail::lds_expression<T,E>& lds, const detail::expression<E1>& e1 )
{
    typedef boost::is_same<T,int_type>                assert_v1;
    typedef boost::is_same<T,uint_type>               assert_v2;
    typedef boost::is_same<T,typename E1::value_type> assert_v3;
    BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && assert_v3::value );

    lds.emit_atomic("lds_or_id(%1%) %2%,%3%\n",e1());
}

template<class T, class E, class E1>
void _atom_xor( const detail::lds_expression<T,E>& lds, const detail::expression<E1>& e1 )
{
    typedef boost::is_same<T,int_type>                assert_v1;
    typedef boost::is_same<T,uint_type>               assert_v2;
    typedef boost::is_same<T,typename E1::value_type> assert_v3;
    BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && assert_v3::value );

    lds.emit_atomic("lds_xor_id(%1%) %2%,%3%\n",e1());
}

template<class T, class E, class E1, class E2>
void _atom_cmpxchg( const detail::lds_expression<T,E>& lds, const detail::expression<E1>& cmp, const detail::expression<E2>& val )
{
    typedef boost::is_same<T,int_type>                assert_v1;
    typedef boost::is_same<T,uint_type>               assert_v2;
    typedef boost::is_same<T,typename E1::value_type> assert_v3;
    typedef boost::is_same<T,typename E2::value_type> assert_v4;
    BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && assert_v3::value && assert_v4::value );

    lds.emit_atomic("lds_cmp_id(%1%) %2%,%3%,%4%\n",cmp(),val());
}

template<class T, class E, class E1>
variable<T> atom_add( const detail::lds_expression<T,E>& lds, const detail::expression<E1>& e1 )
{
    typedef boost::is_same<T,int_type>                assert_v1;
    typedef boost::is_same<T,uint_type>               assert_v2;
    typedef boost::is_same<T,typename E1::value_type> assert_v3;
    BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && assert_v3::value );

    variable<T> r;
    lds.emit_atomic("lds_read_add_resource(%1%) %3%,%2%,%4%\n",r,e1());
    return r;
}

template<class T, class E, class E1>
variable<T> atom_sub( const detail::lds_expression<T,E>& lds, const detail::expression<E1>& e1 )
{
    typedef boost::is_same<T,int_type>                assert_v1;
    typedef boost::is_same<T,uint_type>               assert_v2;
    typedef boost::is_same<T,typename E1::value_type> assert_v3;
    BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && assert_v3::value );

    variable<T> r;
    lds.emit_atomic("lds_read_sub_resource(%1%) %3%,%2%,%4%\n",r,e1());
    return r;
}

template<class T, class E>
variable<T> atom_inc( const detail::lds_expression<T,E>& lds )
{
    return atom_add(lds,detail::value<T>(1));
}

template<class T, class E>
variable<T> atom_dec( const detail::lds_expression<T,E>& lds )
{
    return atom_sub(lds,detail::value<T>(1));
}

template<class T, class E, class E1>
variable<T> atom_xchg( const detail::lds_expression<T,E>& lds, const detail::expression<E1>& e1 )
{
    typedef boost::is_same<T,int_type>                assert_v1;
    typedef boost::is_same<T,uint_type>               assert_v2;
    typedef boost::is_same<T,typename E1::value_type> assert_v3;
    BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && assert_v3::value );

    variable<T> r;
    lds.emit_atomic("lds_read_xchg_resource(%1%) %3%,%2%,%4%\n",r,e1());
    return r;
}

template<class E, class E1>
variable<int_type> atom_min( const detail::lds_expression<int_type,E>& lds, const detail::expression<E1>& e1 )
{
    typedef boost::is_same<typename E1::value_type,int_type> assert_v1;
    BOOST_STATIC_ASSERT( assert_v1::value );

    variable<int_type> r;
    lds.emit_atomic("lds_read_min_resource(%1%) %3%,%2%,%4%\n",r,e1());
    return r;
}

template<class E, class E1>
variable<int_type> atom_max( const detail::lds_expression<int_type,E>& lds, const detail::expression<E1>& e1 )
{
    typedef boost::is_same<typename E1::value_type,int_type> assert_v1;
    BOOST_STATIC_ASSERT( assert_v1::value );

    variable<int_type> r;
    lds.emit_atomic("lds_read_max_resource(%1%) %3%,%2%,%4%\n",r,e1());
    return r;
}

template<class E, class E1>
variable<uint_type> atom_min( const detail::lds_expression<uint_type,E>& lds, const detail::expression<E1>& e1 )
{
    typedef boost::is_same<typename E1::value_type,uint_type> assert_v1;
    BOOST_STATIC_ASSERT( assert_v1::value );

    variable<uint_type> r;
    lds.emit_atomic("lds_read_umin_resource(%1%) %3%,%2%,%4%\n",r,e1());
    return r;
}

template<class E, class E1>
variable<uint_type> atom_max( const detail::lds_expression<uint_type,E>& lds, const detail::expression<E1>& e1 )
{
    typedef boost::is_same<typename E1::value_type,uint_type> assert_v1;
    BOOST_STATIC_ASSERT( assert_v1::value );

    variable<uint_type> r;
    lds.emit_atomic("lds_read_umax_resource(%1%) %3%,%2%,%4%\n",r,e1());
    return r;
}

template<class T, class E, class E1>
variable<T> atom_and( const detail::lds_expression<T,E>& lds, const detail::expression<E1>& e1 )
{
    typedef boost::is_same<T,int_type>                assert_v1;
    typedef boost::is_same<T,uint_type>               assert_v2;
    typedef boost::is_same<T,typename E1::value_type> assert_v3;
    BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && assert_v3::value );

    variable<T> r;
    lds.emit_atomic("lds_read_and_resource(%1%) %3%,%2%,%4%\n",r,e1());
    return r;
}

template<class T, class E, class E1>
variable<T> atom_or( const detail::lds_expression<T,E>& lds, const detail::expression<E1>& e1 )
{
    typedef boost::is_same<T,int_type>                assert_v1;
    typedef boost::is_same<T,uint_type>               assert_v2;
    typedef boost::is_same<T,typename E1::value_type> assert_v3;
    BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && assert_v3::value );

    variable<T> r;
    lds.emit_atomic("lds_read_or_resource(%1%) %3%,%2%,%4%\n",r,e1());
    return r;
}

template<class T, class E, class E1>
variable<T> atom_xor( const detail::lds_expression<T,E>& lds, const detail::expression<E1>& e1 )
{
    typedef boost::is_same<T,int_type>                assert_v1;
    typedef boost::is_same<T,uint_type>               assert_v2;
    typedef boost::is_same<T,typename E1::value_type> assert_v3;
    BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && assert_v3::value );

    variable<T> r;
    lds.emit_atomic("lds_read_xor_resource(%1%) %3%,%2%,%4%\n",r,e1());
    return r;
}

template<class T, class E, class E1, class E2>
variable<T> atom_cmpxchg( const detail::lds_expression<T,E>& lds, const detail::expression<E1>& cmp, const detail::expression<E2>& val )
{
    typedef boost::is_same<T,int_type>                assert_v1;
    typedef boost::is_same<T,uint_type>               assert_v2;
    typedef boost::is_same<T,typename E1::value_type> assert_v3;
    typedef boost::is_same<T,typename E2::value_type> assert_v4;
    BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && assert_v3::value && assert_v4::value );

    variable<T> r;
    lds.emit_atomic("lds_read_cmp_xchg_resource(%1%) %3%,%2%,%4%,%5%\n",r,cmp(),val());
    return r;
}

template<class T, class E1, class E2, class P1>
void _atom_add( const detail::lds2_expression<T,E1,E2>& lds, const detail::expression<P1>& e1 )
{
    typedef boost::is_same<T,int_type>                assert_v1;
    typedef boost::is_same<T,uint_type>               assert_v2;
    typedef boost::is_same<T,typename P1::value_type> assert_v3;
    BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && assert_v3::value );

    lds.emit_atomic("lds_add_id(%1%) %2%,%3%\n",e1());
}

template<class T, class E1, class E2, class P1>
void _atom_sub( const detail::lds2_expression<T,E1,E2>& lds, const detail::expression<P1>& e1 )
{
    typedef boost::is_same<T,int_type>                assert_v1;
    typedef boost::is_same<T,uint_type>               assert_v2;
    typedef boost::is_same<T,typename P1::value_type> assert_v3;
    BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && assert_v3::value );

    lds.emit_atomic("lds_sub_id(%1%) %2%,%3%\n",e1());
}

template<class T, class E1, class E2>
void _atom_inc( const detail::lds2_expression<T,E1,E2>& lds )
{
    _atom_add(lds,detail::value<T>(1));
}

template<class T, class E1, class E2>
void _atom_dec( const detail::lds2_expression<T,E1,E2>& lds )
{
    _atom_sub(lds,detail::value<T>(1));
}

template<class T, class E1, class E2, class P1>
void _atom_min( const detail::lds2_expression<int_type,E1,E2>& lds, const detail::expression<P1>& e1 )
{
    typedef boost::is_same<typename P1::value_type,int_type>  assert_v1;
    BOOST_STATIC_ASSERT( assert_v1::value );

    lds.emit_atomic("lds_min_id(%1%) %2%,%3%\n",e1());
}

template<class T, class E1, class E2, class P1>
void _atom_max( const detail::lds2_expression<int_type,E1,E2>& lds, const detail::expression<P1>& e1 )
{
    typedef boost::is_same<typename P1::value_type,int_type>  assert_v1;
    BOOST_STATIC_ASSERT( assert_v1::value );

    lds.emit_atomic("lds_max_id(%1%) %2%,%3%\n",e1());
}

template<class T, class E1, class E2, class P1>
void _atom_min( const detail::lds2_expression<uint_type,E1,E2>& lds, const detail::expression<P1>& e1 )
{
    typedef boost::is_same<typename P1::value_type,uint_type>  assert_v1;
    BOOST_STATIC_ASSERT( assert_v1::value );

    lds.emit_atomic("lds_umin_id(%1%) %2%,%3%\n",e1());
}

template<class E1, class E2, class P1>
void _atom_max( const detail::lds2_expression<uint_type,E1,E2>& lds, const detail::expression<P1>& e1 )
{
    typedef boost::is_same<typename P1::value_type,uint_type>  assert_v1;
    BOOST_STATIC_ASSERT( assert_v1::value );

    lds.emit_atomic("lds_umax_id(%1%) %2%,%3%\n",e1());
}

template<class T, class E1, class E2, class P1>
void _atom_and( const detail::lds2_expression<T,E1,E2>& lds, const detail::expression<P1>& e1 )
{
    typedef boost::is_same<T,int_type>                assert_v1;
    typedef boost::is_same<T,uint_type>               assert_v2;
    typedef boost::is_same<T,typename P1::value_type> assert_v3;
    BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && assert_v3::value );

    lds.emit_atomic("lds_and_id(%1%) %2%,%3%\n",e1());
}

template<class T, class E1, class E2, class P1>
void _atom_or( const detail::lds2_expression<T,E1,E2>& lds, const detail::expression<P1>& e1 )
{
    typedef boost::is_same<T,int_type>                assert_v1;
    typedef boost::is_same<T,uint_type>               assert_v2;
    typedef boost::is_same<T,typename P1::value_type> assert_v3;
    BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && assert_v3::value );

    lds.emit_atomic("lds_or_id(%1%) %2%,%3%\n",e1());
}

template<class T, class E1, class E2, class P1>
void _atom_xor( const detail::lds2_expression<T,E1,E2>& lds, const detail::expression<P1>& e1 )
{
    typedef boost::is_same<T,int_type>                assert_v1;
    typedef boost::is_same<T,uint_type>               assert_v2;
    typedef boost::is_same<T,typename P1::value_type> assert_v3;
    BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && assert_v3::value );

    lds.emit_atomic("lds_xor_id(%1%) %2%,%3%\n",e1());
}

template<class T, class E1, class E2, class P1, class P2>
void _atom_cmpxchg( const detail::lds2_expression<T,E1,E2>& lds, const detail::expression<P1>& cmp, const detail::expression<P2>& val )
{
    typedef boost::is_same<T,int_type>                assert_v1;
    typedef boost::is_same<T,uint_type>               assert_v2;
    typedef boost::is_same<T,typename P1::value_type> assert_v3;
    typedef boost::is_same<T,typename P2::value_type> assert_v4;
    BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && assert_v3::value && assert_v4::value );

    lds.emit_atomic("lds_cmp_id(%1%) %2%,%3%,%4%\n",cmp(),val());
}

template<class T, class E1, class E2, class P1>
variable<T> atom_add( const detail::lds2_expression<T,E1,E2>& lds, const detail::expression<P1>& e1 )
{
    typedef boost::is_same<T,int_type>                assert_v1;
    typedef boost::is_same<T,uint_type>               assert_v2;
    typedef boost::is_same<T,typename P1::value_type> assert_v3;
    BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && assert_v3::value );

    variable<T> r;
    lds.emit_atomic("lds_read_add_resource(%1%) %3%,%2%,%4%\n",r,e1());
    return r;
}

template<class T, class E1, class E2, class P1>
variable<T> atom_sub( const detail::lds2_expression<T,E1,E2>& lds, const detail::expression<P1>& e1 )
{
    typedef boost::is_same<T,int_type>                assert_v1;
    typedef boost::is_same<T,uint_type>               assert_v2;
    typedef boost::is_same<T,typename P1::value_type> assert_v3;
    BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && assert_v3::value );

    variable<T> r;
    lds.emit_atomic("lds_read_sub_resource(%1%) %3%,%2%,%4%\n",r,e1());
    return r;
}

template<class T, class E1, class E2>
variable<T> atom_inc( const detail::lds2_expression<T,E1,E2>& lds )
{
    return atom_add(lds,detail::value<T>(1));
}

template<class T, class E1, class E2>
variable<T> atom_dec( const detail::lds2_expression<T,E1,E2>& lds )
{
    return atom_sub(lds,detail::value<T>(1));
}

template<class T, class E1, class E2, class P1>
variable<T> atom_xchg( const detail::lds2_expression<T,E1,E2>& lds, const detail::expression<P1>& e1 )
{
    typedef boost::is_same<T,int_type>                assert_v1;
    typedef boost::is_same<T,uint_type>               assert_v2;
    typedef boost::is_same<T,typename P1::value_type> assert_v3;
    BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && assert_v3::value );

    variable<T> r;
    lds.emit_atomic("lds_read_xchg_resource(%1%) %3%,%2%,%4%\n",r,e1());
    return r;
}

template<class E1, class E2, class P1>
variable<int_type> atom_min( const detail::lds2_expression<int_type,E1,E2>& lds, const detail::expression<P1>& e1 )
{
    typedef boost::is_same<typename P1::value_type,int_type> assert_v1;
    BOOST_STATIC_ASSERT( assert_v1::value );

    variable<int_type> r;
    lds.emit_atomic("lds_read_min_resource(%1%) %3%,%2%,%4%\n",r,e1());
    return r;
}

template<class E1, class E2, class P1>
variable<int_type> atom_max( const detail::lds2_expression<int_type,E1,E2>& lds, const detail::expression<P1>& e1 )
{
    typedef boost::is_same<typename P1::value_type,int_type> assert_v1;
    BOOST_STATIC_ASSERT( assert_v1::value );

    variable<int_type> r;
    lds.emit_atomic("lds_read_max_resource(%1%) %3%,%2%,%4%\n",r,e1());
    return r;
}

template<class E1, class E2, class P1>
variable<uint_type> atom_min( const detail::lds2_expression<uint_type,E1,E2>& lds, const detail::expression<P1>& e1 )
{
    typedef boost::is_same<typename P1::value_type,uint_type> assert_v1;
    BOOST_STATIC_ASSERT( assert_v1::value );

    variable<uint_type> r;
    lds.emit_atomic("lds_read_umin_resource(%1%) %3%,%2%,%4%\n",r,e1());
    return r;
}

template<class E1, class E2, class P1>
variable<uint_type> atom_max( const detail::lds2_expression<uint_type,E1,E2>& lds, const detail::expression<P1>& e1 )
{
    typedef boost::is_same<typename P1::value_type,uint_type> assert_v1;
    BOOST_STATIC_ASSERT( assert_v1::value );

    variable<uint_type> r;
    lds.emit_atomic("lds_read_umax_resource(%1%) %3%,%2%,%4%\n",r,e1());
    return r;
}

template<class T, class E1, class E2, class P1>
variable<T> atom_and( const detail::lds2_expression<T,E1,E2>& lds, const detail::expression<P1>& e1 )
{
    typedef boost::is_same<T,int_type>                assert_v1;
    typedef boost::is_same<T,uint_type>               assert_v2;
    typedef boost::is_same<T,typename P1::value_type> assert_v3;
    BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && assert_v3::value );

    variable<T> r;
    lds.emit_atomic("lds_read_and_resource(%1%) %3%,%2%,%4%\n",r,e1());
    return r;
}

template<class T, class E1, class E2, class P1>
variable<T> atom_or( const detail::lds2_expression<T,E1,E2>& lds, const detail::expression<P1>& e1 )
{
    typedef boost::is_same<T,int_type>                assert_v1;
    typedef boost::is_same<T,uint_type>               assert_v2;
    typedef boost::is_same<T,typename P1::value_type> assert_v3;
    BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && assert_v3::value );

    variable<T> r;
    lds.emit_atomic("lds_read_or_resource(%1%) %3%,%2%,%4%\n",r,e1());
    return r;
}

template<class T, class E1, class E2, class P1>
variable<T> atom_xor( const detail::lds2_expression<T,E1,E2>& lds, const detail::expression<P1>& e1 )
{
    typedef boost::is_same<T,int_type>                assert_v1;
    typedef boost::is_same<T,uint_type>               assert_v2;
    typedef boost::is_same<T,typename P1::value_type> assert_v3;
    BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && assert_v3::value );

    variable<T> r;
    lds.emit_atomic("lds_read_xor_resource(%1%) %3%,%2%,%4%\n",r,e1());
    return r;
}

template<class T, class E1, class E2, class P1, class P2>
variable<T> atom_cmpxchg( const detail::lds2_expression<T,E1,E2>& lds, const detail::expression<P1>& cmp, const detail::expression<P2>& val )
{
    typedef boost::is_same<T,int_type>                assert_v1;
    typedef boost::is_same<T,uint_type>               assert_v2;
    typedef boost::is_same<T,typename P1::value_type> assert_v3;
    typedef boost::is_same<T,typename P2::value_type> assert_v4;
    BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && assert_v3::value && assert_v4::value );

    variable<T> r;
    lds.emit_atomic("lds_read_cmp_xchg_resource(%1%) %3%,%2%,%4%,%5%\n",r,cmp(),val());
    return r;
}

//
// mixed with C types
//

template<class T, class E>
void _atom_add( const detail::lds_expression<T,E>& lds, const typename T::component_type& v1 )
{
    _atom_add(lds,detail::value<T>(v1));
}

template<class T, class E>
void _atom_sub( const detail::lds_expression<T,E>& lds, const typename T::component_type& v1  )
{
    _atom_sub(lds,detail::value<T>(v1));
}

template<class T, class E>
void _atom_min( const detail::lds_expression<T,E>& lds, const typename T::component_type& v1 )
{
    _atom_min(lds,detail::value<T>(v1));
}

template<class T, class E>
void _atom_max( const detail::lds_expression<T,E>& lds, const typename T::component_type& v1  )
{
    _atom_max(lds,detail::value<T>(v1));
}

template<class T, class E>
void _atom_and( const detail::lds_expression<T,E>& lds, const typename T::component_type& v1 )
{
    _atom_and(lds,detail::value<T>(v1));
}

template<class T, class E>
void _atom_or( const detail::lds_expression<T,E>& lds, const typename T::component_type& v1  )
{
    _atom_or(lds,detail::value<T>(v1));
}

template<class T, class E>
void _atom_xor( const detail::lds_expression<T,E>& lds, const typename T::component_type& v1  )
{
    _atom_xor(lds,detail::value<T>(v1));
}

template<class T, class E, class E1>
void _atom_cmpxchg( const detail::lds_expression<T,E>& lds, const detail::expression<E1>& cmp, const typename T::component_type& val )
{
    _atom_cmpxchg(lds,cmp(),detail::value<T>(val));
}

template<class T, class E, class E1>
void _atom_cmpxchg( const detail::lds_expression<T,E>& lds, const typename T::component_type& cmp, const detail::expression<E1>& val  )
{
    _atom_cmpxchg(lds,detail::value<T>(cmp),val());
}

template<class T, class E>
variable<T> atom_add( const detail::lds_expression<T,E>& lds, const typename T::component_type& v1 )
{
    return atom_add(lds,detail::value<T>(v1));
}

template<class T, class E>
variable<T> atom_sub( const detail::lds_expression<T,E>& lds, const typename T::component_type& v1  )
{
    return atom_sub(lds,detail::value<T>(v1));
}

template<class T, class E>
variable<T> atom_min( const detail::lds_expression<T,E>& lds, const typename T::component_type& v1 )
{
    return atom_min(lds,detail::value<T>(v1));
}

template<class T, class E>
variable<T> atom_max( const detail::lds_expression<T,E>& lds, const typename T::component_type& v1  )
{
    return atom_max(lds,detail::value<T>(v1));
}

template<class T, class E>
variable<T> atom_and( const detail::lds_expression<T,E>& lds, const typename T::component_type& v1 )
{
    return atom_and(lds,detail::value<T>(v1));
}

template<class T, class E>
variable<T> atom_or( const detail::lds_expression<T,E>& lds, const typename T::component_type& v1  )
{
    return atom_or(lds,detail::value<T>(v1));
}

template<class T, class E>
variable<T> atom_xor( const detail::lds_expression<T,E>& lds, const typename T::component_type& v1  )
{
    return atom_xor(lds,detail::value<T>(v1));
}

template<class T, class E, class E1>
variable<T> atom_cmpxchg( const detail::lds_expression<T,E>& lds, const detail::expression<E1>& cmp, const typename T::component_type& val )
{
    return atom_cmpxchg(lds,cmp(),detail::value<T>(val));
}

template<class T, class E, class E1>
variable<T> atom_cmpxchg( const detail::lds_expression<T,E>& lds, const typename T::component_type& cmp, const detail::expression<E1>& val  )
{
    return atom_cmpxchg(lds,detail::value<T>(cmp),val());
}

template<class T, class E1, class E2>
void _atom_add( const detail::lds2_expression<T,E1,E2>& lds, const typename T::component_type& v1 )
{
    _atom_add(lds,detail::value<T>(v1));
}

template<class T, class E1, class E2>
void _atom_sub( const detail::lds2_expression<T,E1,E2>& lds, const typename T::component_type& v1  )
{
    _atom_sub(lds,detail::value<T>(v1));
}

template<class T, class E1, class E2>
void _atom_min( const detail::lds2_expression<T,E1,E2>& lds, const typename T::component_type& v1 )
{
    _atom_min(lds,detail::value<T>(v1));
}

template<class T, class E1, class E2>
void _atom_max( const detail::lds2_expression<T,E1,E2>& lds, const typename T::component_type& v1  )
{
    _atom_max(lds,detail::value<T>(v1));
}

template<class T, class E1, class E2>
void _atom_and( const detail::lds2_expression<T,E1,E2>& lds, const typename T::component_type& v1 )
{
    _atom_and(lds,detail::value<T>(v1));
}

template<class T, class E1, class E2>
void _atom_or( const detail::lds2_expression<T,E1,E2>& lds, const typename T::component_type& v1  )
{
    _atom_or(lds,detail::value<T>(v1));
}

template<class T, class E1, class E2>
void _atom_xor( const detail::lds2_expression<T,E1,E2>& lds, const typename T::component_type& v1  )
{
    _atom_xor(lds,detail::value<T>(v1));
}

template<class T, class E1, class E2, class P1>
void _atom_cmpxchg( const detail::lds2_expression<T,E1,E2>& lds, const detail::expression<P1>& cmp, const typename T::component_type& val )
{
    _atom_cmpxchg(lds,cmp(),detail::value<T>(val));
}

template<class T, class E1, class E2, class P1>
void _atom_cmpxchg( const detail::lds2_expression<T,E1,E2>& lds, const typename T::component_type& cmp, const detail::expression<P1>& val  )
{
    _atom_cmpxchg(lds,detail::value<T>(cmp),val());
}

template<class T, class E1, class E2>
variable<T> atom_add( const detail::lds2_expression<T,E1,E2>& lds, const typename T::component_type& v1 )
{
    return atom_add(lds,detail::value<T>(v1));
}

template<class T, class E1, class E2>
variable<T> atom_sub( const detail::lds2_expression<T,E1,E2>& lds, const typename T::component_type& v1  )
{
    return atom_sub(lds,detail::value<T>(v1));
}

template<class T, class E1, class E2>
variable<T> atom_min( const detail::lds2_expression<T,E1,E2>& lds, const typename T::component_type& v1 )
{
    return atom_min(lds,detail::value<T>(v1));
}

template<class T, class E1, class E2>
variable<T> atom_max( const detail::lds2_expression<T,E1,E2>& lds, const typename T::component_type& v1  )
{
    return atom_max(lds,detail::value<T>(v1));
}

template<class T, class E1, class E2>
variable<T> atom_and( const detail::lds2_expression<T,E1,E2>& lds, const typename T::component_type& v1 )
{
    return atom_and(lds,detail::value<T>(v1));
}

template<class T, class E1, class E2>
variable<T> atom_or( const detail::lds2_expression<T,E1,E2>& lds, const typename T::component_type& v1  )
{
    return atom_or(lds,detail::value<T>(v1));
}

template<class T, class E1, class E2>
variable<T> atom_xor( const detail::lds2_expression<T,E1,E2>& lds, const typename T::component_type& v1  )
{
    return atom_xor(lds,detail::value<T>(v1));
}

template<class T, class E1, class E2, class P1>
variable<T> atom_cmpxchg( const detail::lds2_expression<T,E1,E2>& lds, const detail::expression<P1>& cmp, const typename T::component_type& val )
{
    return atom_cmpxchg(lds,cmp(),detail::value<T>(val));
}

template<class T, class E1, class E2, class P1>
variable<T> atom_cmpxchg( const detail::lds2_expression<T,E1,E2>& lds, const typename T::component_type& cmp, const detail::expression<P1>& val  )
{
    return atom_cmpxchg(lds,detail::value<T>(cmp),val());
}

} // il
} // cal

#endif
