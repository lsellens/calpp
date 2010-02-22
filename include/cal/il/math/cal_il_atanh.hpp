/*
 * C++ to IL compiler/generator atanh
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

#ifndef __CAL_IL_MATH_ATANH_H
#define __CAL_IL_MATH_ATANH_H

namespace cal {
namespace il {

template<class E1>
variable<typename E1::value_type> atanh( const detail::expression<E1>& x )
{
    typedef typename E1::value_type value_type;    
    variable<value_type>   v1,v2;
    
    v1 = (variable<value_type>(1.)+x());
    v2 = (variable<value_type>(1.)-x());
    return variable<value_type>(0.5)*log(v1/v2);
}

} // il
} // cal

#endif
