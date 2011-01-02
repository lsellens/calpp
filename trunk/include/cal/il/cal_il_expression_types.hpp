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
#include <boost/type_traits.hpp>
#include <boost/format.hpp>

namespace cal {
namespace il {

namespace detail {

template<class E, class F>
class unary : public swizzable_expression<F,unary<E,F> >
{
protected:
    typedef F                                    functor_type;
    typedef swizzable_expression<F,unary<E,F> >  base_type;
    typedef unary<E,F>                           self_type;
    typedef const E                              expression_type;
    typedef typename E::const_closure_type       expression_closure_type;

public:
    typedef typename F::value_type               value_type;
    typedef const self_type                      const_closure_type;
    typedef self_type                            closure_type;
    static const int                             temp_reg_count = F::temp_reg_count;

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
class binary : public swizzable_expression<F,binary<E1,E2,F> >
{
protected:
    typedef F                                         functor_type;
    typedef const E1                                  expression1_type;
    typedef const E2                                  expression2_type;
    typedef typename E1::const_closure_type           expression1_closure_type;
    typedef typename E2::const_closure_type           expression2_closure_type;
    typedef swizzable_expression<F,binary<E1,E2,F> >  base_type;
    typedef binary<E1,E2,F>                           self_type;

public:
    typedef typename F::value_type                    value_type;
    typedef const self_type                           const_closure_type;
    typedef self_type                                 closure_type;
    static const int                                  temp_reg_count = F::temp_reg_count;

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
class ternary : public swizzable_expression<F,ternary<E1,E2,E3,F> >
{
protected:
    typedef F                                             functor_type;
    typedef const E1                                      expression1_type;
    typedef const E2                                      expression2_type;
    typedef const E3                                      expression3_type;
    typedef typename E1::const_closure_type               expression1_closure_type;
    typedef typename E2::const_closure_type               expression2_closure_type;
    typedef typename E3::const_closure_type               expression3_closure_type;
    typedef swizzable_expression<F,ternary<E1,E2,E3,F> >  base_type;
    typedef ternary<E1,E2,E3,F>                           self_type;

public:
    typedef typename F::value_type                        value_type;
    typedef const self_type                               const_closure_type;
    typedef self_type                                     closure_type;
    static const int                                      temp_reg_count = F::temp_reg_count;

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

public:
    typedef const E                                 expression_type;
    typedef typename E::const_closure_type          expression_closure_type;

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
        typedef boost::is_same<typename E::value_type,float_type> assert_v3;
        BOOST_STATIC_ASSERT( assert_v1::value || assert_v2::value || assert_v3::value );
    }
    explicit register_address( expression_type& e, int offset ) : _e(e), _offset(offset)
    {
        typedef boost::is_same<typename E::value_type,int_type> assert_v1;
        typedef boost::is_same<typename E::value_type,uint_type> assert_v2;
        typedef boost::is_same<typename E::value_type,float_type> assert_v3;
        BOOST_STATIC_ASSERT( assert_v1::value || assert_v2::value || assert_v3::value );
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

} // il
} // cal

#endif
