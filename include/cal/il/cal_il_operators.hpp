/*
 * C++ to IL compiler/generator operators
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

#ifndef __CAL_IL_OPERATORS_H
#define __CAL_IL_OPERATORS_H

namespace cal {
namespace il {

template<class E1>
detail::unary<E1,detail::cal_unary_neg<typename E1::value_type> > operator-( const detail::expression<E1>& e1 )
{
    typedef detail::unary<E1,detail::cal_unary_neg<typename E1::value_type> > expression_type;
    return expression_type( e1() );
}

template<class E1>
detail::unary<E1,detail::cal_unary_bitnot<typename E1::value_type> > operator~( const detail::expression<E1>& e1 )
{
    typedef detail::unary<E1,detail::cal_unary_bitnot<typename E1::value_type> > expression_type;
    return expression_type( e1() );
}

template<class E1,class E2>
detail::binary<E1,E2,detail::cal_binary_add<typename E1::value_type,typename E2::value_type> > operator+( const detail::expression<E1>& e1, const detail::expression<E2>& e2 )
{
    typedef detail::binary<E1,E2,detail::cal_binary_add<typename E1::value_type,typename E2::value_type> > expression_type;
    return expression_type( e1(), e2() );
}

template<class E1,class E2>
detail::binary<E1,E2,detail::cal_binary_sub<typename E1::value_type,typename E2::value_type> > operator-( const detail::expression<E1>& e1, const detail::expression<E2>& e2 )
{
    typedef detail::binary<E1,E2,detail::cal_binary_sub<typename E1::value_type,typename E2::value_type> > expression_type;
    return expression_type( e1(), e2() );
}

template<class E1,class E2>
detail::binary<E1,E2,detail::cal_binary_bitor<typename E1::value_type,typename E2::value_type> > operator|( const detail::expression<E1>& e1, const detail::expression<E2>& e2 )
{
    typedef detail::binary<E1,E2,detail::cal_binary_bitor<typename E1::value_type,typename E2::value_type> > expression_type;
    return expression_type( e1(), e2() );
}

template<class E1,class E2>
detail::binary<E1,E2,detail::cal_binary_bitxor<typename E1::value_type,typename E2::value_type> > operator^( const detail::expression<E1>& e1, const detail::expression<E2>& e2 )
{
    typedef detail::binary<E1,E2,detail::cal_binary_bitxor<typename E1::value_type,typename E2::value_type> > expression_type;
    return expression_type( e1(), e2() );
}

template<class E1,class E2>
detail::binary<E1,E2,detail::cal_binary_bitand<typename E1::value_type,typename E2::value_type> > operator&( const detail::expression<E1>& e1, const detail::expression<E2>& e2 )
{
    typedef detail::binary<E1,E2,detail::cal_binary_bitand<typename E1::value_type,typename E2::value_type> > expression_type;
    return expression_type( e1(), e2() );
}

template<class E1,class E2>
detail::binary<E1,E2,detail::cal_binary_shl<typename E1::value_type,typename E2::value_type> > operator<<( const detail::expression<E1>& e1, const detail::expression<E2>& e2 )
{
    typedef detail::binary<E1,E2,detail::cal_binary_shl<typename E1::value_type,typename E2::value_type> > expression_type;
    return expression_type( e1(), e2() );
}

template<class E1,class E2>
detail::binary<E1,E2,detail::cal_binary_shr<typename E1::value_type,typename E2::value_type> > operator>>( const detail::expression<E1>& e1, const detail::expression<E2>& e2 )
{
    typedef detail::binary<E1,E2,detail::cal_binary_shr<typename E1::value_type,typename E2::value_type> > expression_type;
    return expression_type( e1(), e2() );
}

template<class E>
detail::unary<E,detail::cal_unary_not<typename E::value_type> > operator!( const detail::expression<E>& e )
{
    typedef detail::unary<E,detail::cal_unary_not<typename E::value_type> > expression_type;
    return expression_type(e());
}

template<class E1,class E2>
detail::binary<E1,E2,detail::cal_binary_bitor<typename E1::value_type,typename E2::value_type> > operator||( const detail::expression<E1>& e1, const detail::expression<E2>& e2 )
{
    typedef detail::binary<E1,E2,detail::cal_binary_bitor<typename E1::value_type,typename E2::value_type> > expression_type;
    return expression_type( e1(), e2() );
}

template<class E1,class E2>
detail::binary<E1,E2,detail::cal_binary_bitand<typename E1::value_type,typename E2::value_type> > operator&&( const detail::expression<E1>& e1, const detail::expression<E2>& e2 )
{
    typedef detail::binary<E1,E2,detail::cal_binary_bitand<typename E1::value_type,typename E2::value_type> > expression_type;
    return expression_type( e1(), e2() );
}

template<class E1,class E2>
detail::binary<E1,E2,detail::cal_binary_eq<typename E1::value_type,typename E2::value_type> > operator==( const detail::expression<E1>& e1, const detail::expression<E2>& e2 )
{
    typedef detail::binary<E1,E2,detail::cal_binary_eq<typename E1::value_type,typename E2::value_type> > expression_type;
    return expression_type( e1(), e2() );
}

template<class E1,class E2>
detail::binary<E1,E2,detail::cal_binary_ne<typename E1::value_type,typename E2::value_type> > operator!=( const detail::expression<E1>& e1, const detail::expression<E2>& e2 )
{
    typedef detail::binary<E1,E2,detail::cal_binary_ne<typename E1::value_type,typename E2::value_type> > expression_type;
    return expression_type( e1(), e2() );
}

template<class E1,class E2>
detail::binary<E1,E2,detail::cal_binary_gt<typename E1::value_type,typename E2::value_type> > operator>( const detail::expression<E1>& e1, const detail::expression<E2>& e2 )
{
    typedef detail::binary<E1,E2,detail::cal_binary_gt<typename E1::value_type,typename E2::value_type> > expression_type;
    return expression_type( e1(), e2() );
}

template<class E1,class E2>
detail::binary<E1,E2,detail::cal_binary_ge<typename E1::value_type,typename E2::value_type> > operator>=( const detail::expression<E1>& e1, const detail::expression<E2>& e2 )
{
    typedef detail::binary<E1,E2,detail::cal_binary_ge<typename E1::value_type,typename E2::value_type> > expression_type;
    return expression_type( e1(), e2() );
}

template<class E1,class E2>
detail::binary<E1,E2,detail::cal_binary_lt<typename E1::value_type,typename E2::value_type> > operator<( const detail::expression<E1>& e1, const detail::expression<E2>& e2 )
{
    typedef detail::binary<E1,E2,detail::cal_binary_lt<typename E1::value_type,typename E2::value_type> > expression_type;
    return expression_type( e1(), e2() );
}

template<class E1,class E2>
detail::binary<E1,E2,detail::cal_binary_le<typename E1::value_type,typename E2::value_type> > operator<=( const detail::expression<E1>& e1, const detail::expression<E2>& e2 )
{
    typedef detail::binary<E1,E2,detail::cal_binary_le<typename E1::value_type,typename E2::value_type> > expression_type;
    return expression_type( e1(), e2() );
}


template<class T,class E1>
detail::unary<E1,detail::cal_unary_cast<typename detail::base_cal_type<T>::value,typename E1::value_type> > cast_type( const detail::expression<E1>& e1 )
{
    typedef detail::unary<E1,detail::cal_unary_cast<typename detail::base_cal_type<T>::value,typename E1::value_type> > expression_type;
    return expression_type(e1());
}

template<class T,class E1>
detail::unary<E1,detail::cal_unary_bitcast<typename detail::base_cal_type<T>::value,typename E1::value_type> > cast_bits( const detail::expression<E1>& e1 )
{
    typedef detail::unary<E1,detail::cal_unary_bitcast<typename detail::base_cal_type<T>::value,typename E1::value_type> > expression_type;
    return expression_type(e1());
}

template<class E1, class E2>
detail::binary<E1,E2,detail::cal_binary_cast<typename E1::value_type,typename E2::value_type> > merge_types( const detail::expression<E1>& e1, const detail::expression<E2>& e2 )
{
    typedef detail::binary<E1,E2,detail::cal_binary_cast<typename E1::value_type,typename E2::value_type> > expression_type;
    return expression_type(e1(),e2());
}

template<class E1, class E2, class E3, class E4>
detail::binary< detail::binary<E1,E2,detail::cal_binary_cast<typename E1::value_type,typename E2::value_type> >,
        detail::binary<E3,E4,detail::cal_binary_cast<typename E3::value_type,typename E4::value_type> >,
        detail::cal_binary_cast<typename detail::binary<E1,E2,detail::cal_binary_cast<typename E1::value_type,typename E2::value_type> >::value_type,
                                typename detail::binary<E3,E4,detail::cal_binary_cast<typename E3::value_type,typename E4::value_type> >::value_type
                               >
      > merge_types( const detail::expression<E1>& e1, const detail::expression<E2>& e2, const detail::expression<E3>& e3, const detail::expression<E4>& e4 )
{
    return merge_types( merge_types(e1(),e2()), merge_types(e3(),e4()) );
}

template<class E1,class E2,class E3>
detail::ternary<E1,E2,E3,detail::cal_ternary_mad<typename E1::value_type,typename E2::value_type,typename E3::value_type> >
mad( const detail::expression<E1>& e1, const detail::expression<E2>& e2, const detail::expression<E3>& e3 )
{
    typedef detail::ternary<E1,E2,E3,detail::cal_ternary_mad<typename E1::value_type,typename E2::value_type,typename E3::value_type> > expression_type;
    return expression_type(e1(),e2(),e3());
}

//
// mixed CAL++ IL and C types
//

template<class E1>
detail::binary<E1,detail::value<E1>,detail::cal_binary_add<typename E1::value_type,typename E1::value_type> > operator+( const detail::expression<E1>& e1, const typename E1::value_type::component_type& v1 )
{
    typedef detail::binary<E1,detail::value<E1>,detail::cal_binary_add<typename E1::value_type,typename E1::value_type> > expression_type;
    return expression_type( e1(), detail::value<E1>(v1) );
}
template<class E1>
detail::binary<detail::value<E1>,E1,detail::cal_binary_add<typename E1::value_type,typename E1::value_type> > operator+( const typename E1::value_type::component_type& v1, const detail::expression<E1>& e1 )
{
    typedef detail::binary<detail::value<E1>,E1,detail::cal_binary_add<typename E1::value_type,typename E1::value_type> > expression_type;
    return expression_type( detail::value<E1>(v1), e1() );
}

template<class E1>
detail::binary<E1,detail::value<E1>,detail::cal_binary_sub<typename E1::value_type,typename E1::value_type> > operator-( const detail::expression<E1>& e1, const typename E1::value_type::component_type& v1 )
{
    typedef detail::binary<E1,detail::value<E1>,detail::cal_binary_sub<typename E1::value_type,typename E1::value_type> > expression_type;
    return expression_type( e1(), detail::value<E1>(v1) );
}
template<class E1>
detail::binary<detail::value<E1>,E1,detail::cal_binary_sub<typename E1::value_type,typename E1::value_type> > operator-( const typename E1::value_type::component_type& v1, const detail::expression<E1>& e1 )
{
    typedef detail::binary<detail::value<E1>,E1,detail::cal_binary_sub<typename E1::value_type,typename E1::value_type> > expression_type;
    return expression_type( detail::value<E1>(v1), e1() );
}

template<class E1>
detail::binary<E1,detail::value<E1>,detail::cal_binary_bitor<typename E1::value_type,typename E1::value_type> > operator|( const detail::expression<E1>& e1, const typename E1::value_type::component_type& v1 )
{
    typedef detail::binary<E1,detail::value<E1>,detail::cal_binary_bitor<typename E1::value_type,typename E1::value_type> > expression_type;
    return expression_type( e1(), detail::value<E1>(v1) );
}
template<class E1>
detail::binary<detail::value<E1>,E1,detail::cal_binary_bitor<typename E1::value_type,typename E1::value_type> > operator|( const typename E1::value_type::component_type& v1, const detail::expression<E1>& e1 )
{
    typedef detail::binary<detail::value<E1>,E1,detail::cal_binary_bitor<typename E1::value_type,typename E1::value_type> > expression_type;
    return expression_type( detail::value<E1>(v1), e1() );
}

template<class E1>
detail::binary<E1,detail::value<E1>,detail::cal_binary_bitxor<typename E1::value_type,typename E1::value_type> > operator^( const detail::expression<E1>& e1, const typename E1::value_type::component_type& v1 )
{
    typedef detail::binary<E1,detail::value<E1>,detail::cal_binary_bitxor<typename E1::value_type,typename E1::value_type> > expression_type;
    return expression_type( e1(), detail::value<E1>(v1) );
}
template<class E1>
detail::binary<detail::value<E1>,E1,detail::cal_binary_bitxor<typename E1::value_type,typename E1::value_type> > operator^( const typename E1::value_type::component_type& v1, const detail::expression<E1>& e1 )
{
    typedef detail::binary<detail::value<E1>,E1,detail::cal_binary_bitxor<typename E1::value_type,typename E1::value_type> > expression_type;
    return expression_type( detail::value<E1>(v1), e1() );
}

template<class E1>
detail::binary<E1,detail::value<E1>,detail::cal_binary_bitand<typename E1::value_type,typename E1::value_type> > operator&( const detail::expression<E1>& e1, const typename E1::value_type::component_type& v1 )
{
    typedef detail::binary<E1,detail::value<E1>,detail::cal_binary_bitand<typename E1::value_type,typename E1::value_type> > expression_type;
    return expression_type( e1(), detail::value<E1>(v1) );
}
template<class E1>
detail::binary<detail::value<E1>,E1,detail::cal_binary_bitand<typename E1::value_type,typename E1::value_type> > operator&( const typename E1::value_type::component_type& v1, const detail::expression<E1>& e1 )
{
    typedef detail::binary<detail::value<E1>,E1,detail::cal_binary_bitand<typename E1::value_type,typename E1::value_type> > expression_type;
    return expression_type( detail::value<E1>(v1), e1() );
}

template<class E1>
detail::binary<E1,detail::value<E1>,detail::cal_binary_shl<typename E1::value_type,typename E1::value_type> > operator<<( const detail::expression<E1>& e1, const typename E1::value_type::component_type& v1 )
{
    typedef detail::binary<E1,detail::value<E1>,detail::cal_binary_shl<typename E1::value_type,typename E1::value_type> > expression_type;
    return expression_type( e1(), detail::value<E1>(v1) );
}
template<class E1>
detail::binary<detail::value<E1>,E1,detail::cal_binary_shl<typename E1::value_type,typename E1::value_type> > operator<<( const typename E1::value_type::component_type& v1, const detail::expression<E1>& e1 )
{
    typedef detail::binary<detail::value<E1>,E1,detail::cal_binary_shl<typename E1::value_type,typename E1::value_type> > expression_type;
    return expression_type( detail::value<E1>(v1), e1() );
}

template<class E1>
detail::binary<E1,detail::value<E1>,detail::cal_binary_shr<typename E1::value_type,typename E1::value_type> > operator>>( const detail::expression<E1>& e1, const typename E1::value_type::component_type& v1 )
{
    typedef detail::binary<E1,detail::value<E1>,detail::cal_binary_shr<typename E1::value_type,typename E1::value_type> > expression_type;
    return expression_type( e1(), detail::value<E1>(v1) );
}
template<class E1>
detail::binary<detail::value<E1>,E1,detail::cal_binary_shr<typename E1::value_type,typename E1::value_type> > operator>>( const typename E1::value_type::component_type& v1, const detail::expression<E1>& e1 )
{
    typedef detail::binary<detail::value<E1>,E1,detail::cal_binary_shr<typename E1::value_type,typename E1::value_type> > expression_type;
    return expression_type( detail::value<E1>(v1), e1() );
}

template<class E1>
detail::binary<E1,detail::value<E1>,detail::cal_binary_eq<typename E1::value_type,typename E1::value_type> > operator==( const detail::expression<E1>& e1, const typename E1::value_type::component_type& v1 )
{
    typedef detail::binary<E1,detail::value<E1>,detail::cal_binary_eq<typename E1::value_type,typename E1::value_type> > expression_type;
    return expression_type( e1(), detail::value<E1>(v1) );
}
template<class E1>
detail::binary<detail::value<E1>,E1,detail::cal_binary_eq<typename E1::value_type,typename E1::value_type> > operator==( const typename E1::value_type::component_type& v1, const detail::expression<E1>& e1 )
{
    typedef detail::binary<detail::value<E1>,E1,detail::cal_binary_eq<typename E1::value_type,typename E1::value_type> > expression_type;
    return expression_type( detail::value<E1>(v1), e1() );
}

template<class E1>
detail::binary<E1,detail::value<E1>,detail::cal_binary_ne<typename E1::value_type,typename E1::value_type> > operator!=( const detail::expression<E1>& e1, const typename E1::value_type::component_type& v1 )
{
    typedef detail::binary<E1,detail::value<E1>,detail::cal_binary_ne<typename E1::value_type,typename E1::value_type> > expression_type;
    return expression_type( e1(), detail::value<E1>(v1) );
}
template<class E1>
detail::binary<detail::value<E1>,E1,detail::cal_binary_ne<typename E1::value_type,typename E1::value_type> > operator!=( const typename E1::value_type::component_type& v1, const detail::expression<E1>& e1 )
{
    typedef detail::binary<detail::value<E1>,E1,detail::cal_binary_ne<typename E1::value_type,typename E1::value_type> > expression_type;
    return expression_type( detail::value<E1>(v1), e1() );
}

template<class E1>
detail::binary<E1,detail::value<E1>,detail::cal_binary_gt<typename E1::value_type,typename E1::value_type> > operator>( const detail::expression<E1>& e1, const typename E1::value_type::component_type& v1 )
{
    typedef detail::binary<E1,detail::value<E1>,detail::cal_binary_gt<typename E1::value_type,typename E1::value_type> > expression_type;
    return expression_type( e1(), detail::value<E1>(v1) );
}
template<class E1>
detail::binary<detail::value<E1>,E1,detail::cal_binary_gt<typename E1::value_type,typename E1::value_type> > operator>( const typename E1::value_type::component_type& v1, const detail::expression<E1>& e1 )
{
    typedef detail::binary<detail::value<E1>,E1,detail::cal_binary_gt<typename E1::value_type,typename E1::value_type> > expression_type;
    return expression_type( detail::value<E1>(v1), e1() );
}

template<class E1>
detail::binary<E1,detail::value<E1>,detail::cal_binary_ge<typename E1::value_type,typename E1::value_type> > operator>=( const detail::expression<E1>& e1, const typename E1::value_type::component_type& v1 )
{
    typedef detail::binary<E1,detail::value<E1>,detail::cal_binary_ge<typename E1::value_type,typename E1::value_type> > expression_type;
    return expression_type( e1(), detail::value<E1>(v1) );
}
template<class E1>
detail::binary<detail::value<E1>,E1,detail::cal_binary_ge<typename E1::value_type,typename E1::value_type> > operator>=( const typename E1::value_type::component_type& v1, const detail::expression<E1>& e1 )
{
    typedef detail::binary<detail::value<E1>,E1,detail::cal_binary_ge<typename E1::value_type,typename E1::value_type> > expression_type;
    return expression_type( detail::value<E1>(v1), e1() );
}

template<class E1>
detail::binary<E1,detail::value<E1>,detail::cal_binary_lt<typename E1::value_type,typename E1::value_type> > operator<( const detail::expression<E1>& e1, const typename E1::value_type::component_type& v1 )
{
    typedef detail::binary<E1,detail::value<E1>,detail::cal_binary_lt<typename E1::value_type,typename E1::value_type> > expression_type;
    return expression_type( e1(), detail::value<E1>(v1) );
}
template<class E1>
detail::binary<detail::value<E1>,E1,detail::cal_binary_lt<typename E1::value_type,typename E1::value_type> > operator<( const typename E1::value_type::component_type& v1, const detail::expression<E1>& e1 )
{
    typedef detail::binary<detail::value<E1>,E1,detail::cal_binary_lt<typename E1::value_type,typename E1::value_type> > expression_type;
    return expression_type( detail::value<E1>(v1), e1() );
}

template<class E1>
detail::binary<E1,detail::value<E1>,detail::cal_binary_le<typename E1::value_type,typename E1::value_type> > operator<=( const detail::expression<E1>& e1, const typename E1::value_type::component_type& v1 )
{
    typedef detail::binary<E1,detail::value<E1>,detail::cal_binary_le<typename E1::value_type,typename E1::value_type> > expression_type;
    return expression_type( e1(), detail::value<E1>(v1) );
}
template<class E1>
detail::binary<detail::value<E1>,E1,detail::cal_binary_le<typename E1::value_type,typename E1::value_type> > operator<=( const typename E1::value_type::component_type& v1, const detail::expression<E1>& e1 )
{
    typedef detail::binary<detail::value<E1>,E1,detail::cal_binary_le<typename E1::value_type,typename E1::value_type> > expression_type;
    return expression_type( detail::value<E1>(v1), e1() );
}

template<class E1,class E2>
detail::ternary<detail::value<E1>,E1,E2,detail::cal_ternary_mad<typename E1::value_type,typename E1::value_type,typename E2::value_type> >
mad( const typename E1::value_type::component_type& v1, const detail::expression<E1>& e1, const detail::expression<E2>& e2 )
{
    typedef detail::ternary<detail::value<E1>,E1,E2,detail::cal_ternary_mad<typename E1::value_type,typename E1::value_type,typename E2::value_type> > expression_type;
    return expression_type(detail::value<E1>(v1),e1(),e2());
}
template<class E1,class E2>
detail::ternary<E1,detail::value<E1>,E2,detail::cal_ternary_mad<typename E1::value_type,typename E1::value_type,typename E2::value_type> >
mad( const detail::expression<E1>& e1, const typename E1::value_type::component_type& v1, const detail::expression<E2>& e2 )
{
    typedef detail::ternary<E1,detail::value<E1>,E2,detail::cal_ternary_mad<typename E1::value_type,typename E1::value_type,typename E2::value_type> > expression_type;
    return expression_type(e1(),detail::value<E1>(v1),e2());
}
template<class E1,class E2>
detail::ternary<E1,E2,detail::value<E1>,detail::cal_ternary_mad<typename E1::value_type,typename E2::value_type,typename E1::value_type> >
mad( const detail::expression<E1>& e1, const detail::expression<E2>& e2, const typename E1::value_type::component_type& v1 )
{
    typedef detail::ternary<E1,E2,detail::value<E1>,detail::cal_ternary_mad<typename E1::value_type,typename E2::value_type,typename E1::value_type> > expression_type;
    return expression_type(e1(),e2(),detail::value<E1>(v1));
}

template<class E1>
detail::ternary<detail::value<E1>,detail::value<E1>,E1,detail::cal_ternary_mad<typename E1::value_type,typename E1::value_type,typename E1::value_type> >
mad( const typename E1::value_type::component_type& v1, const typename E1::value_type::component_type& v2, const detail::expression<E1>& e1 )
{
    typedef detail::ternary<detail::value<E1>,detail::value<E1>,E1,detail::cal_ternary_mad<typename E1::value_type,typename E1::value_type,typename E1::value_type> > expression_type;
    return expression_type(detail::value<E1>(v1),detail::value<E1>(v2),e1());
}
template<class E1>
detail::ternary<detail::value<E1>,E1,detail::value<E1>,detail::cal_ternary_mad<typename E1::value_type,typename E1::value_type,typename E1::value_type> >
mad( const typename E1::value_type::component_type& v1, const detail::expression<E1>& e1, const typename E1::value_type::component_type& v2 )
{
    typedef detail::ternary<detail::value<E1>,E1,detail::value<E1>,detail::cal_ternary_mad<typename E1::value_type,typename E1::value_type,typename E1::value_type> > expression_type;
    return expression_type(detail::value<E1>(v1),e1(),detail::value<E1>(v2));
}
template<class E1>
detail::ternary<E1,detail::value<E1>,detail::value<E1>,detail::cal_ternary_mad<typename E1::value_type,typename E1::value_type,typename E1::value_type> >
mad( const detail::expression<E1>& e1, const typename E1::value_type::component_type& v1, const typename E1::value_type::component_type& v2 )
{
    typedef detail::ternary<E1,detail::value<E1>,detail::value<E1>,detail::cal_ternary_mad<typename E1::value_type,typename E1::value_type,typename E1::value_type> > expression_type;
    return expression_type(e1(),detail::value<E1>(v1),detail::value<E1>(v2));
}

template<class E>
detail::register_address<E> operator+( const detail::register_address<E>& r, int offset )
{
    return detail::register_address<E>(r._e,r._offset+offset);
}

template<class E>
detail::register_address<E> operator-( const detail::register_address<E>& r, int offset )
{
    return detail::register_address<E>(r._e,r._offset-offset);
}

} // il
} // cal

#endif
