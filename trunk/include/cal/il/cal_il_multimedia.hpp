/*
 * C++ to IL compiler/generator multimedia functions
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

#ifndef __CAL_IL_MULTIMEDIA_H
#define __CAL_IL_MULTIMEDIA_H

namespace cal {
namespace il {

template<class E1,class E2,class E3>
detail::ternary<E1,E2,E3,detail::cal_ternary_bitalign<typename E1::value_type,typename E2::value_type,typename E3::value_type> >
bitalign( const detail::expression<E1>& e1, const detail::expression<E2>& e2, const detail::expression<E3>& e3 )
{
    typedef detail::ternary<E1,E2,E3,detail::cal_ternary_bitalign<typename E1::value_type,typename E2::value_type,typename E3::value_type> > expression_type;
    return expression_type(e1(),e2(),e3());
}

template<class E1,class E2,class E3>
detail::ternary<E1,E2,E3,detail::cal_ternary_bytealign<typename E1::value_type,typename E2::value_type,typename E3::value_type> >
bytealign( const detail::expression<E1>& e1, const detail::expression<E2>& e2, const detail::expression<E3>& e3 )
{
    typedef detail::ternary<E1,E2,E3,detail::cal_ternary_bytealign<typename E1::value_type,typename E2::value_type,typename E3::value_type> > expression_type;
    return expression_type(e1(),e2(),e3());
}

} // il
} // cal

#endif

