/*
 * C++ to IL compiler/generator rv7xx specific code
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

#ifndef __CAL_IL_RV7XX_H
#define __CAL_IL_RV7XX_H

#include <cal/cal_il.hpp>

#include <cassert>
#include <boost/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/format.hpp>

namespace cal {
namespace il {
namespace rv7xx {

template<class E>
void lds_write( unsigned offset, const detail::expression<E>& e )
{
    BOOST_STATIC_ASSERT( E::value_type::type_size==4 );
    assert( (offset%4)==0 );

    e().emitCode(Source::code,Source::code.stream());
    Source::code << boost::format("lds_write_vec_lOffset(offset) mem.xyzw,%1%\n") % e().resultCode();
}

template<class E>
void lds_write( unsigned offset, const detail::expression<E>& e, const std::string& mask )
{
    assert( (offset%4)==0 );

    e().emitCode(Source::code,Source::code.stream());
    Source::code << boost::format("lds_write_vec_lOffset(offset) mem.%1%,%2%\n") % mask % e().resultCode();
}

template<typename T,class E>
variable<T> lds_read( const detail::expression<E>& e )
{
    typedef boost::is_same<typename E::value_type,uint2_type> assert_v1;
    typedef boost::is_same<typename E::value_type,int2_type> assert_v2;
    BOOST_STATIC_ASSERT( T::type_size==4 );
    BOOST_STATIC_ASSERT( assert_v1::value || assert_v2::values );

    variable<T> r;

    e().emitCode(Source::code,Source::code.stream());    
    Source::code << boost::format("lds_read_vec %1%,%2%\n") % r.resultCode() % e().resultCode();

    return r;
}

template<typename T,class E1,class E2>
variable<T> lds_read( const detail::expression<E1>& tid, const detail::expression<E2>& offset )
{
    typedef boost::is_same<typename E1::value_type,uint_type>   assert_v1;
    typedef boost::is_same<typename E1::value_type,int_type>    assert_v2;
    typedef boost::is_same<typename E2::value_type,uint_type>   assert_v3;
    typedef boost::is_same<typename E2::value_type,int_type>    assert_v4;

    BOOST_STATIC_ASSERT( T::type_size==4 );
    BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && (assert_v3::value || assert_v4::value) );

    return lds_read( merge_types(tid,offset) );
}

} // rv7xx
} // il
} // cal

#endif
