/*
 * C++ to IL compiler/generator polevl
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

#ifndef __CAL_IL_MATH_POLEVL_H
#define __CAL_IL_MATH_POLEVL_H

namespace cal {
namespace il {

namespace detail {

template<class E1>
variable<typename E1::value_type> polevl( const detail::expression<E1>& x, const typename E1::value_type::component_type* coef, int N )
{
    typedef typename E1::value_type value_type;
    variable<value_type> _x,r;

    _x = x();

    r = coef[0];

    for(int i=1;i<N;i++) {
        r = mad( r, _x, coef[i] );
    }

    return r;
}

template<class E1>
variable<typename E1::value_type> p1evl( const detail::expression<E1>& x, const typename E1::value_type::component_type* coef, int N )
{
    typedef typename E1::value_type value_type;
    variable<value_type> _x,r;

    _x = x();

    r = _x + coef[0];

    for(int i=1;i<N;i++) {
        r = mad( r, _x, coef[i] );
    }

    return r;
}

} // detail

}
}

#endif
