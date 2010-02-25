/*
 * C++ to IL compiler/generator expression helper classes
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

#ifndef __CAL_IL_EXPRESSION_TYPES_H
#define __CAL_IL_EXPRESSION_TYPES_H

#include <boost/static_assert.hpp>
#include <boost/format.hpp>
#include <cal/il/cal_il_functors.hpp>
#include <cal/il/cal_il_expression_swizzle.hpp>

namespace cal {
namespace il {

namespace detail {

template<class E, class F>
class unary : public swizzable_expression<unary<E,F> >
{
protected:
    typedef F                                       functor_type;
    typedef swizzable_expression<unary<E,F> >       base_type;
    typedef unary<E,F>                              self_type;
    typedef const E                                 expression_type;
    typedef typename E::const_closure_type          expression_closure_type;
    
public:
    typedef typename F::value_type                  value_type;
    typedef const self_type                         const_closure_type;
    typedef self_type                               closure_type;
    static const int                                temp_reg_count = F::temp_reg_count;

public:
    expression_closure_type _e;

protected:    
    using base_type::index;

public:
    using base_type::resultCode;

public:
    explicit unary( expression_type& e ) : base_type(), _e(e) {}
    unary( const unary<E,F>& rhs ) : base_type(rhs), _e(rhs._e) {}
    ~unary() {}

    void emitCode( Source& prg, std::ostream& _out ) const
    {
        _e.emitCode(prg,_out);        
        _out << F::emitCode(resultCode(),_e.resultCode(),index);
    }
};

template<class E1, class E2, class F>
class binary : public swizzable_expression<binary<E1,E2,F> >
{
protected:
    typedef F                                       functor_type;
    typedef const E1                                expression1_type;
    typedef const E2                                expression2_type;
    typedef typename E1::const_closure_type         expression1_closure_type;
    typedef typename E2::const_closure_type         expression2_closure_type;        
    typedef swizzable_expression<binary<E1,E2,F> >  base_type;
    typedef binary<E1,E2,F>                         self_type;
    
public:
    typedef typename F::value_type                  value_type;    
    typedef const self_type                         const_closure_type;
    typedef self_type                               closure_type;    
    static const int                                temp_reg_count = F::temp_reg_count;

public:
    expression1_closure_type _e1;
    expression2_closure_type _e2;

protected:    
    using base_type::index;

public:
    using base_type::resultCode;

public:
    explicit binary( expression1_type& e1, expression2_type& e2 ) : base_type(), _e1(e1),_e2(e2) {}
    binary( const binary<E1,E2,F>& rhs ) : base_type(rhs), _e1(rhs._e1),_e2(rhs._e2) {}
    ~binary() {}

    void emitCode( Source& prg, std::ostream& _out ) const
    {
        _e1.emitCode(prg,_out);
        _e2.emitCode(prg,_out);

        _out << F::emitCode(resultCode(),_e1.resultCode(),_e2.resultCode(),index);
    }
};

template<class E1, class E2, class E3, class F>
class ternary : public swizzable_expression<ternary<E1,E2,E3,F> >
{
protected:
    typedef F                                           functor_type;
    typedef const E1                                    expression1_type;
    typedef const E2                                    expression2_type;
    typedef const E3                                    expression3_type;
    typedef typename E1::const_closure_type             expression1_closure_type;
    typedef typename E2::const_closure_type             expression2_closure_type;
    typedef typename E3::const_closure_type             expression3_closure_type;
    typedef swizzable_expression<ternary<E1,E2,E3,F> >  base_type;
    typedef ternary<E1,E2,E3,F>                         self_type;

public:
    typedef typename F::value_type                      value_type;    
    typedef const self_type                             const_closure_type;
    typedef self_type                                   closure_type;        
    static const int                                    temp_reg_count = F::temp_reg_count;

public:
    expression1_closure_type _e1;
    expression2_closure_type _e2;
    expression3_closure_type _e3;

protected:    
    using base_type::index;

public:
    using base_type::resultCode;

public:
    explicit ternary( expression1_type& e1, expression2_type& e2, expression3_type& e3 ) : base_type(), _e1(e1), _e2(e2), _e3(e3) {}
    ternary( const ternary<E1,E2,E3,F>& rhs ) : base_type(rhs), _e1(rhs._e1),_e2(rhs._e2),_e3(rhs._e3) {}
    ~ternary() {}

    void emitCode( Source& prg, std::ostream& _out ) const
    {
        _e1.emitCode(prg,_out);
        _e2.emitCode(prg,_out);
        _e3.emitCode(prg,_out);

        _out << F::emitCode(resultCode(),_e1.resultCode(),_e2.resultCode(),_e3.resultCode(),index);
    }
};

template<class E>
class register_address 
{
protected:
    typedef register_address<E>                     self_type;
    typedef const E                                 expression_type;
    typedef typename E::const_closure_type          expression_closure_type;
    
public:
    typedef typename E::value_type                  value_type;
    typedef const self_type                         const_closure_type;
    typedef self_type                               closure_type;

public:
    expression_closure_type _e;
    int                     _offset;

public:
    register_address( expression_type& e ) : _e(e), _offset(0)
    {
        typedef boost::is_same<typename E::value_type,int_type> assert_v1;
        typedef boost::is_same<typename E::value_type,uint_type> assert_v2;
        BOOST_STATIC_ASSERT( assert_v1::value || assert_v2::value );        
    }
    explicit register_address( expression_type& e, int offset ) : _e(e), _offset(offset)
    {
        typedef boost::is_same<typename E::value_type,int_type> assert_v1;
        typedef boost::is_same<typename E::value_type,uint_type> assert_v2;
        BOOST_STATIC_ASSERT( assert_v1::value || assert_v2::value );        
    }
    register_address( const register_address<E>& rhs ) : _e(rhs._e), _offset(rhs._offset) {}
    ~register_address() {}

    void emitCode( Source& prg, std::ostream& _out ) const
    {
        _e.emitCode(prg,_out);                
    }

    std::string resultCode() const
    {
        if( _offset>0 ) return (boost::format("%s+%i") % _e.resultCode() % _offset).str();
        else if( _offset<0 ) return (boost::format("%s-%i") % _e.resultCode() % (-_offset)).str();
        return _e.resultCode();
    }
};

template<>
class register_address<void>
{
protected:
    typedef register_address<void>                  self_type;
    typedef void                                    expression_type;
    typedef void                                    expression_closure_type;
    
public:
    typedef uint_type                               value_type;
    typedef const self_type                         const_closure_type;
    typedef self_type                               closure_type;

public:    
    int                     _offset;

public:
    explicit register_address( int offset ) : _offset(offset) {}
    register_address( const register_address<void>& rhs ) : _offset(rhs._offset) {}
    ~register_address() {}

    void emitCode( Source& prg, std::ostream& _out ) const {}

    std::string resultCode() const
    {
        return (boost::format("%i") % _offset).str();
    }
};


} // detail

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

template<class E1,class E2>
detail::binary<E1,E2,detail::cal_binary_ldexp<typename E1::value_type,typename E2::value_type> > ldexp( const detail::expression<E1>& e1, const detail::expression<E2>& e2 )
{
    typedef detail::binary<E1,E2,detail::cal_binary_ldexp<typename E1::value_type,typename E2::value_type> > expression_type;
    return expression_type( e1(), e2() );
}

template<class E1,class E2>
detail::binary<E1,E2,detail::cal_binary_bitor<typename E1::value_type,typename E2::value_type> > operator|( const detail::expression<E1>& e1, const detail::expression<E2>& e2 )
{
    typedef detail::binary<E1,E2,detail::cal_binary_bitor<typename E1::value_type,typename E2::value_type> > expression_type;
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
    typedef detail::binary<E1,E2,detail::cal_binary_shl<typename E1::value_type,typename E2::value_type> > expression_type;
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

template<class E1,class E2,class E3>
detail::ternary<E1,E2,E3,detail::cal_ternary_cmov_logical<typename E1::value_type,typename E2::value_type,typename E3::value_type> >
select( const detail::expression<E1>& e1, const detail::expression<E2>& e2, const detail::expression<E3>& e3 )
{
    typedef detail::ternary<E1,E2,E3,detail::cal_ternary_cmov_logical<typename E1::value_type,typename E2::value_type,typename E3::value_type> > expression_type;
    return expression_type(e1(),e2(),e3());
}

template<class E>
detail::register_address<E> operator+( const detail::expression<E>& e, int offset )
{
    return detail::register_address<E>(e(),offset);
}

template<class E>
detail::register_address<E> operator-( const detail::expression<E>& e, int offset )
{
    return detail::register_address<E>(e(),-offset);
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

template<class E1>
detail::unary<E1,detail::cal_unary_cast<int1_type,typename E1::value_type> > convert_int1( const detail::expression<E1>& e1 )
{
    return cast_type<int1_type>(e1());
}

template<class E1>
detail::unary<E1,detail::cal_unary_cast<int2_type,typename E1::value_type> > convert_int2( const detail::expression<E1>& e1 )
{
    return cast_type<int2_type>(e1());
}

template<class E1>
detail::unary<E1,detail::cal_unary_cast<int4_type,typename E1::value_type> > convert_int4( const detail::expression<E1>& e1 )
{
    return cast_type<int4_type>(e1());
}

template<class E1>
detail::unary<E1,detail::cal_unary_cast<uint1_type,typename E1::value_type> > convert_uint1( const detail::expression<E1>& e1 )
{
    return cast_type<uint1_type>(e1());
}

template<class E1>
detail::unary<E1,detail::cal_unary_cast<uint2_type,typename E1::value_type> > convert_uint2( const detail::expression<E1>& e1 )
{
    return cast_type<uint2_type>(e1());
}

template<class E1>
detail::unary<E1,detail::cal_unary_cast<uint4_type,typename E1::value_type> > convert_uint4( const detail::expression<E1>& e1 )
{
    return cast_type<uint4_type>(e1());
}

template<class E1>
detail::unary<E1,detail::cal_unary_cast<float1_type,typename E1::value_type> > convert_float1( const detail::expression<E1>& e1 )
{
    return cast_type<float1_type>(e1());
}

template<class E1>
detail::unary<E1,detail::cal_unary_cast<float2_type,typename E1::value_type> > convert_float2( const detail::expression<E1>& e1 )
{
    return cast_type<float2_type>(e1());
}

template<class E1>
detail::unary<E1,detail::cal_unary_cast<float4_type,typename E1::value_type> > convert_float4( const detail::expression<E1>& e1 )
{
    return cast_type<float4_type>(e1());
}

template<class E1>
detail::unary<E1,detail::cal_unary_cast<double1_type,typename E1::value_type> > convert_double1( const detail::expression<E1>& e1 )
{
    return cast_type<double1_type>(e1());
}

template<class E1>
detail::unary<E1,detail::cal_unary_cast<double2_type,typename E1::value_type> > convert_double2( const detail::expression<E1>& e1 )
{
    return cast_type<double2_type>(e1());
}

} // il
} // cal

#endif
