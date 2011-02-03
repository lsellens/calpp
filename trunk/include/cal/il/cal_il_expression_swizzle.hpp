/*
 * C++ to IL compiler/generator swizzle expresion
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

#ifndef __CAL_IL_EXPRESSION_SWIZZLE_H
#define __CAL_IL_EXPRESSION_SWIZZLE_H

#include <boost/format.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>
#include <cal/il/cal_il_swizzle_traits.hpp>

namespace cal {
namespace il {
namespace detail {

template<class E,int P0,int P1,int P2,int P3>
class swizzle : public assignable_expression<typename E::value_type,swizzle<E,P0,P1,P2,P3> >
{
protected:
    typedef assignable_expression<typename E::value_type,swizzle<E,P0,P1,P2,P3> > base_type;
    typedef swizzle<E,P0,P1,P2,P3>                                                self_type;
    typedef const E                                                               expression_type;
    typedef typename E::const_closure_type                                        expression_closure_type;
    typedef swizzle_traits<typename E::value_type,P0,P1,P2,P3>                    swizzle_trait;

public:
    typedef typename swizzle_trait::value_type                                    value_type;
    typedef const self_type                                                       const_closure_type;
    typedef self_type                                                             closure_type;
    static const int                                                              temp_reg_count = 0;

protected:
    expression_closure_type _e;
    using base_type::index;

public:
    using base_type::operator=;

protected:
    template<class E1>
    void iEmitCode( const E1& e ) const
    {
        e.emitCode(Source::code,Source::code.stream());
        _e.emitCode(Source::code,Source::code.stream());
        Source::code << boost::format("mov %s,%s\n") % mask_output(resultCode()) % match_input_to_output(resultCode(),e.resultCode());
    }

public:
    swizzle( const E& e ) : base_type(), _e(e)
    {
        typedef boost::is_same<value_type,invalid_swizzle> assert_value;
        BOOST_STATIC_ASSERT( !assert_value::value );
    }
    swizzle( const swizzle<E,P0,P1,P2,P3>& rhs ) : base_type(rhs), _e(rhs._e)
    {
    }
    ~swizzle()
    {
    }

    void emitCode( Source& prg, std::ostream& _out ) const
    {
        _e.emitCode(prg,_out);
    }

    std::string resultCode() const
    {
        BOOST_STATIC_ASSERT( value_type::type_size==1 || value_type::type_size==2 || value_type::type_size==4 );
        return make_swizzle(_e.resultCode(),swizzle_trait::i0,swizzle_trait::i1,swizzle_trait::i2,swizzle_trait::i3);
    }

    self_type& operator=( const self_type& v )
    {
        BOOST_STATIC_ASSERT( E::swizzle_has_assign );
        iEmitCode(v);
        return *this;
    }

    const self_type& operator=( const self_type& v ) const
    {
        BOOST_STATIC_ASSERT( E::swizzle_has_assign );
        iEmitCode(v);
        return *this;
    }

    template<class E1>
    self_type& operator=( const detail::expression<E1>& e )
    {
        typedef boost::is_same<typename E1::value_type,value_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );
        BOOST_STATIC_ASSERT( E::swizzle_has_assign );
        iEmitCode(e());
        return *this;
    }

    template<class E1>
    const self_type& operator=( const detail::expression<E1>& e ) const
    {
        typedef boost::is_same<typename E1::value_type,value_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );
        BOOST_STATIC_ASSERT( E::swizzle_has_assign );
        iEmitCode(e());
        return *this;
    }
};

template<class T,class E>
class swizzable_expression : public assignable_expression<T,E>
{
protected:
    using expression<E>::index;

public:
    using assignable_expression<T,E>::operator=;

public:
    swizzable_expression() : assignable_expression<T,E>() {}
    swizzable_expression( const swizzable_expression& rhs ) : assignable_expression<T,E>(rhs) {}
    ~swizzable_expression() {}

    std::string resultCode() const
    {
        BOOST_STATIC_ASSERT( E::value_type::type_size==1 || E::value_type::type_size==2 || E::value_type::type_size==4 );

        int     idx = index+E::temp_reg_count;

        return make_swizzle( (boost::format("r%i") % idx).str(), E::value_type::type_size );
    }

    swizzle<E,1,0,0,0> x() const
    {
        return swizzle<E,1,0,0,0>(*static_cast<const E*>(this));
    }
    swizzle<E,2,0,0,0> y() const
    {
        return swizzle<E,2,0,0,0>(*static_cast<const E*>(this));
    }
    swizzle<E,3,0,0,0> z() const
    {
        return swizzle<E,3,0,0,0>(*static_cast<const E*>(this));
    }
    swizzle<E,4,0,0,0> w() const
    {
        return swizzle<E,4,0,0,0>(*static_cast<const E*>(this));
    }

    swizzle<E,1,1,0,0> xx() const
    {
        return swizzle<E,1,1,0,0>(*static_cast<const E*>(this));
    }
    swizzle<E,1,2,0,0> xy() const
    {
        return swizzle<E,1,2,0,0>(*static_cast<const E*>(this));
    }
    swizzle<E,1,3,0,0> xz() const
    {
        return swizzle<E,1,3,0,0>(*static_cast<const E*>(this));
    }
    swizzle<E,1,4,0,0> xw() const
    {
        return swizzle<E,1,4,0,0>(*static_cast<const E*>(this));
    }
    swizzle<E,2,1,0,0> yx() const
    {
        return swizzle<E,2,1,0,0>(*static_cast<const E*>(this));
    }
    swizzle<E,2,2,0,0> yy() const
    {
        return swizzle<E,2,2,0,0>(*static_cast<const E*>(this));
    }
    swizzle<E,2,3,0,0> yz() const
    {
        return swizzle<E,2,3,0,0>(*static_cast<const E*>(this));
    }
    swizzle<E,2,4,0,0> yw() const
    {
        return swizzle<E,2,4,0,0>(*static_cast<const E*>(this));
    }
    swizzle<E,3,1,0,0> zx() const
    {
        return swizzle<E,3,1,0,0>(*static_cast<const E*>(this));
    }
    swizzle<E,3,2,0,0> zy() const
    {
        return swizzle<E,3,2,0,0>(*static_cast<const E*>(this));
    }
    swizzle<E,3,3,0,0> zz() const
    {
        return swizzle<E,3,3,0,0>(*static_cast<const E*>(this));
    }
    swizzle<E,3,4,0,0> zw() const
    {
        return swizzle<E,3,4,0,0>(*static_cast<const E*>(this));
    }
    swizzle<E,4,1,0,0> wx() const
    {
        return swizzle<E,4,1,0,0>(*static_cast<const E*>(this));
    }
    swizzle<E,4,2,0,0> wy() const
    {
        return swizzle<E,4,2,0,0>(*static_cast<const E*>(this));
    }
    swizzle<E,4,3,0,0> wz() const
    {
        return swizzle<E,4,3,0,0>(*static_cast<const E*>(this));
    }
    swizzle<E,4,4,0,0> ww() const
    {
        return swizzle<E,4,4,0,0>(*static_cast<const E*>(this));
    }

    swizzle<E,1,1,1,1> xxxx() const
    {
        return swizzle<E,1,1,1,1>(*static_cast<const E*>(this));
    }
    swizzle<E,1,1,1,2> xxxy() const
    {
        return swizzle<E,1,1,1,2>(*static_cast<const E*>(this));
    }
    swizzle<E,1,1,1,3> xxxz() const
    {
        return swizzle<E,1,1,1,3>(*static_cast<const E*>(this));
    }
    swizzle<E,1,1,1,4> xxxw() const
    {
        return swizzle<E,1,1,1,4>(*static_cast<const E*>(this));
    }
    swizzle<E,1,1,2,1> xxyx() const
    {
        return swizzle<E,1,1,2,1>(*static_cast<const E*>(this));
    }
    swizzle<E,1,1,2,2> xxyy() const
    {
        return swizzle<E,1,1,2,2>(*static_cast<const E*>(this));
    }
    swizzle<E,1,1,2,3> xxyz() const
    {
        return swizzle<E,1,1,2,3>(*static_cast<const E*>(this));
    }
    swizzle<E,1,1,2,4> xxyw() const
    {
        return swizzle<E,1,1,2,4>(*static_cast<const E*>(this));
    }
    swizzle<E,1,1,3,1> xxzx() const
    {
        return swizzle<E,1,1,3,1>(*static_cast<const E*>(this));
    }
    swizzle<E,1,1,3,2> xxzy() const
    {
        return swizzle<E,1,1,3,2>(*static_cast<const E*>(this));
    }
    swizzle<E,1,1,3,3> xxzz() const
    {
        return swizzle<E,1,1,3,3>(*static_cast<const E*>(this));
    }
    swizzle<E,1,1,3,4> xxzw() const
    {
        return swizzle<E,1,1,3,4>(*static_cast<const E*>(this));
    }
    swizzle<E,1,1,4,1> xxwx() const
    {
        return swizzle<E,1,1,4,1>(*static_cast<const E*>(this));
    }
    swizzle<E,1,1,4,2> xxwy() const
    {
        return swizzle<E,1,1,4,2>(*static_cast<const E*>(this));
    }
    swizzle<E,1,1,4,3> xxwz() const
    {
        return swizzle<E,1,1,4,3>(*static_cast<const E*>(this));
    }
    swizzle<E,1,1,4,4> xxww() const
    {
        return swizzle<E,1,1,4,4>(*static_cast<const E*>(this));
    }
    swizzle<E,1,2,1,1> xyxx() const
    {
        return swizzle<E,1,2,1,1>(*static_cast<const E*>(this));
    }
    swizzle<E,1,2,1,2> xyxy() const
    {
        return swizzle<E,1,2,1,2>(*static_cast<const E*>(this));
    }
    swizzle<E,1,2,1,3> xyxz() const
    {
        return swizzle<E,1,2,1,3>(*static_cast<const E*>(this));
    }
    swizzle<E,1,2,1,4> xyxw() const
    {
        return swizzle<E,1,2,1,4>(*static_cast<const E*>(this));
    }
    swizzle<E,1,2,2,1> xyyx() const
    {
        return swizzle<E,1,2,2,1>(*static_cast<const E*>(this));
    }
    swizzle<E,1,2,2,2> xyyy() const
    {
        return swizzle<E,1,2,2,2>(*static_cast<const E*>(this));
    }
    swizzle<E,1,2,2,3> xyyz() const
    {
        return swizzle<E,1,2,2,3>(*static_cast<const E*>(this));
    }
    swizzle<E,1,2,2,4> xyyw() const
    {
        return swizzle<E,1,2,2,4>(*static_cast<const E*>(this));
    }
    swizzle<E,1,2,3,1> xyzx() const
    {
        return swizzle<E,1,2,3,1>(*static_cast<const E*>(this));
    }
    swizzle<E,1,2,3,2> xyzy() const
    {
        return swizzle<E,1,2,3,2>(*static_cast<const E*>(this));
    }
    swizzle<E,1,2,3,3> xyzz() const
    {
        return swizzle<E,1,2,3,3>(*static_cast<const E*>(this));
    }
    swizzle<E,1,2,3,4> xyzw() const
    {
        return swizzle<E,1,2,3,4>(*static_cast<const E*>(this));
    }
    swizzle<E,1,2,4,1> xywx() const
    {
        return swizzle<E,1,2,4,1>(*static_cast<const E*>(this));
    }
    swizzle<E,1,2,4,2> xywy() const
    {
        return swizzle<E,1,2,4,2>(*static_cast<const E*>(this));
    }
    swizzle<E,1,2,4,3> xywz() const
    {
        return swizzle<E,1,2,4,3>(*static_cast<const E*>(this));
    }
    swizzle<E,1,2,4,4> xyww() const
    {
        return swizzle<E,1,2,4,4>(*static_cast<const E*>(this));
    }
    swizzle<E,1,3,1,1> xzxx() const
    {
        return swizzle<E,1,3,1,1>(*static_cast<const E*>(this));
    }
    swizzle<E,1,3,1,2> xzxy() const
    {
        return swizzle<E,1,3,1,2>(*static_cast<const E*>(this));
    }
    swizzle<E,1,3,1,3> xzxz() const
    {
        return swizzle<E,1,3,1,3>(*static_cast<const E*>(this));
    }
    swizzle<E,1,3,1,4> xzxw() const
    {
        return swizzle<E,1,3,1,4>(*static_cast<const E*>(this));
    }
    swizzle<E,1,3,2,1> xzyx() const
    {
        return swizzle<E,1,3,2,1>(*static_cast<const E*>(this));
    }
    swizzle<E,1,3,2,2> xzyy() const
    {
        return swizzle<E,1,3,2,2>(*static_cast<const E*>(this));
    }
    swizzle<E,1,3,2,3> xzyz() const
    {
        return swizzle<E,1,3,2,3>(*static_cast<const E*>(this));
    }
    swizzle<E,1,3,2,4> xzyw() const
    {
        return swizzle<E,1,3,2,4>(*static_cast<const E*>(this));
    }
    swizzle<E,1,3,3,1> xzzx() const
    {
        return swizzle<E,1,3,3,1>(*static_cast<const E*>(this));
    }
    swizzle<E,1,3,3,2> xzzy() const
    {
        return swizzle<E,1,3,3,2>(*static_cast<const E*>(this));
    }
    swizzle<E,1,3,3,3> xzzz() const
    {
        return swizzle<E,1,3,3,3>(*static_cast<const E*>(this));
    }
    swizzle<E,1,3,3,4> xzzw() const
    {
        return swizzle<E,1,3,3,4>(*static_cast<const E*>(this));
    }
    swizzle<E,1,3,4,1> xzwx() const
    {
        return swizzle<E,1,3,4,1>(*static_cast<const E*>(this));
    }
    swizzle<E,1,3,4,2> xzwy() const
    {
        return swizzle<E,1,3,4,2>(*static_cast<const E*>(this));
    }
    swizzle<E,1,3,4,3> xzwz() const
    {
        return swizzle<E,1,3,4,3>(*static_cast<const E*>(this));
    }
    swizzle<E,1,3,4,4> xzww() const
    {
        return swizzle<E,1,3,4,4>(*static_cast<const E*>(this));
    }
    swizzle<E,1,4,1,1> xwxx() const
    {
        return swizzle<E,1,4,1,1>(*static_cast<const E*>(this));
    }
    swizzle<E,1,4,1,2> xwxy() const
    {
        return swizzle<E,1,4,1,2>(*static_cast<const E*>(this));
    }
    swizzle<E,1,4,1,3> xwxz() const
    {
        return swizzle<E,1,4,1,3>(*static_cast<const E*>(this));
    }
    swizzle<E,1,4,1,4> xwxw() const
    {
        return swizzle<E,1,4,1,4>(*static_cast<const E*>(this));
    }
    swizzle<E,1,4,2,1> xwyx() const
    {
        return swizzle<E,1,4,2,1>(*static_cast<const E*>(this));
    }
    swizzle<E,1,4,2,2> xwyy() const
    {
        return swizzle<E,1,4,2,2>(*static_cast<const E*>(this));
    }
    swizzle<E,1,4,2,3> xwyz() const
    {
        return swizzle<E,1,4,2,3>(*static_cast<const E*>(this));
    }
    swizzle<E,1,4,2,4> xwyw() const
    {
        return swizzle<E,1,4,2,4>(*static_cast<const E*>(this));
    }
    swizzle<E,1,4,3,1> xwzx() const
    {
        return swizzle<E,1,4,3,1>(*static_cast<const E*>(this));
    }
    swizzle<E,1,4,3,2> xwzy() const
    {
        return swizzle<E,1,4,3,2>(*static_cast<const E*>(this));
    }
    swizzle<E,1,4,3,3> xwzz() const
    {
        return swizzle<E,1,4,3,3>(*static_cast<const E*>(this));
    }
    swizzle<E,1,4,3,4> xwzw() const
    {
        return swizzle<E,1,4,3,4>(*static_cast<const E*>(this));
    }
    swizzle<E,1,4,4,1> xwwx() const
    {
        return swizzle<E,1,4,4,1>(*static_cast<const E*>(this));
    }
    swizzle<E,1,4,4,2> xwwy() const
    {
        return swizzle<E,1,4,4,2>(*static_cast<const E*>(this));
    }
    swizzle<E,1,4,4,3> xwwz() const
    {
        return swizzle<E,1,4,4,3>(*static_cast<const E*>(this));
    }
    swizzle<E,1,4,4,4> xwww() const
    {
        return swizzle<E,1,4,4,4>(*static_cast<const E*>(this));
    }
    swizzle<E,2,1,1,1> yxxx() const
    {
        return swizzle<E,2,1,1,1>(*static_cast<const E*>(this));
    }
    swizzle<E,2,1,1,2> yxxy() const
    {
        return swizzle<E,2,1,1,2>(*static_cast<const E*>(this));
    }
    swizzle<E,2,1,1,3> yxxz() const
    {
        return swizzle<E,2,1,1,3>(*static_cast<const E*>(this));
    }
    swizzle<E,2,1,1,4> yxxw() const
    {
        return swizzle<E,2,1,1,4>(*static_cast<const E*>(this));
    }
    swizzle<E,2,1,2,1> yxyx() const
    {
        return swizzle<E,2,1,2,1>(*static_cast<const E*>(this));
    }
    swizzle<E,2,1,2,2> yxyy() const
    {
        return swizzle<E,2,1,2,2>(*static_cast<const E*>(this));
    }
    swizzle<E,2,1,2,3> yxyz() const
    {
        return swizzle<E,2,1,2,3>(*static_cast<const E*>(this));
    }
    swizzle<E,2,1,2,4> yxyw() const
    {
        return swizzle<E,2,1,2,4>(*static_cast<const E*>(this));
    }
    swizzle<E,2,1,3,1> yxzx() const
    {
        return swizzle<E,2,1,3,1>(*static_cast<const E*>(this));
    }
    swizzle<E,2,1,3,2> yxzy() const
    {
        return swizzle<E,2,1,3,2>(*static_cast<const E*>(this));
    }
    swizzle<E,2,1,3,3> yxzz() const
    {
        return swizzle<E,2,1,3,3>(*static_cast<const E*>(this));
    }
    swizzle<E,2,1,3,4> yxzw() const
    {
        return swizzle<E,2,1,3,4>(*static_cast<const E*>(this));
    }
    swizzle<E,2,1,4,1> yxwx() const
    {
        return swizzle<E,2,1,4,1>(*static_cast<const E*>(this));
    }
    swizzle<E,2,1,4,2> yxwy() const
    {
        return swizzle<E,2,1,4,2>(*static_cast<const E*>(this));
    }
    swizzle<E,2,1,4,3> yxwz() const
    {
        return swizzle<E,2,1,4,3>(*static_cast<const E*>(this));
    }
    swizzle<E,2,1,4,4> yxww() const
    {
        return swizzle<E,2,1,4,4>(*static_cast<const E*>(this));
    }
    swizzle<E,2,2,1,1> yyxx() const
    {
        return swizzle<E,2,2,1,1>(*static_cast<const E*>(this));
    }
    swizzle<E,2,2,1,2> yyxy() const
    {
        return swizzle<E,2,2,1,2>(*static_cast<const E*>(this));
    }
    swizzle<E,2,2,1,3> yyxz() const
    {
        return swizzle<E,2,2,1,3>(*static_cast<const E*>(this));
    }
    swizzle<E,2,2,1,4> yyxw() const
    {
        return swizzle<E,2,2,1,4>(*static_cast<const E*>(this));
    }
    swizzle<E,2,2,2,1> yyyx() const
    {
        return swizzle<E,2,2,2,1>(*static_cast<const E*>(this));
    }
    swizzle<E,2,2,2,2> yyyy() const
    {
        return swizzle<E,2,2,2,2>(*static_cast<const E*>(this));
    }
    swizzle<E,2,2,2,3> yyyz() const
    {
        return swizzle<E,2,2,2,3>(*static_cast<const E*>(this));
    }
    swizzle<E,2,2,2,4> yyyw() const
    {
        return swizzle<E,2,2,2,4>(*static_cast<const E*>(this));
    }
    swizzle<E,2,2,3,1> yyzx() const
    {
        return swizzle<E,2,2,3,1>(*static_cast<const E*>(this));
    }
    swizzle<E,2,2,3,2> yyzy() const
    {
        return swizzle<E,2,2,3,2>(*static_cast<const E*>(this));
    }
    swizzle<E,2,2,3,3> yyzz() const
    {
        return swizzle<E,2,2,3,3>(*static_cast<const E*>(this));
    }
    swizzle<E,2,2,3,4> yyzw() const
    {
        return swizzle<E,2,2,3,4>(*static_cast<const E*>(this));
    }
    swizzle<E,2,2,4,1> yywx() const
    {
        return swizzle<E,2,2,4,1>(*static_cast<const E*>(this));
    }
    swizzle<E,2,2,4,2> yywy() const
    {
        return swizzle<E,2,2,4,2>(*static_cast<const E*>(this));
    }
    swizzle<E,2,2,4,3> yywz() const
    {
        return swizzle<E,2,2,4,3>(*static_cast<const E*>(this));
    }
    swizzle<E,2,2,4,4> yyww() const
    {
        return swizzle<E,2,2,4,4>(*static_cast<const E*>(this));
    }
    swizzle<E,2,3,1,1> yzxx() const
    {
        return swizzle<E,2,3,1,1>(*static_cast<const E*>(this));
    }
    swizzle<E,2,3,1,2> yzxy() const
    {
        return swizzle<E,2,3,1,2>(*static_cast<const E*>(this));
    }
    swizzle<E,2,3,1,3> yzxz() const
    {
        return swizzle<E,2,3,1,3>(*static_cast<const E*>(this));
    }
    swizzle<E,2,3,1,4> yzxw() const
    {
        return swizzle<E,2,3,1,4>(*static_cast<const E*>(this));
    }
    swizzle<E,2,3,2,1> yzyx() const
    {
        return swizzle<E,2,3,2,1>(*static_cast<const E*>(this));
    }
    swizzle<E,2,3,2,2> yzyy() const
    {
        return swizzle<E,2,3,2,2>(*static_cast<const E*>(this));
    }
    swizzle<E,2,3,2,3> yzyz() const
    {
        return swizzle<E,2,3,2,3>(*static_cast<const E*>(this));
    }
    swizzle<E,2,3,2,4> yzyw() const
    {
        return swizzle<E,2,3,2,4>(*static_cast<const E*>(this));
    }
    swizzle<E,2,3,3,1> yzzx() const
    {
        return swizzle<E,2,3,3,1>(*static_cast<const E*>(this));
    }
    swizzle<E,2,3,3,2> yzzy() const
    {
        return swizzle<E,2,3,3,2>(*static_cast<const E*>(this));
    }
    swizzle<E,2,3,3,3> yzzz() const
    {
        return swizzle<E,2,3,3,3>(*static_cast<const E*>(this));
    }
    swizzle<E,2,3,3,4> yzzw() const
    {
        return swizzle<E,2,3,3,4>(*static_cast<const E*>(this));
    }
    swizzle<E,2,3,4,1> yzwx() const
    {
        return swizzle<E,2,3,4,1>(*static_cast<const E*>(this));
    }
    swizzle<E,2,3,4,2> yzwy() const
    {
        return swizzle<E,2,3,4,2>(*static_cast<const E*>(this));
    }
    swizzle<E,2,3,4,3> yzwz() const
    {
        return swizzle<E,2,3,4,3>(*static_cast<const E*>(this));
    }
    swizzle<E,2,3,4,4> yzww() const
    {
        return swizzle<E,2,3,4,4>(*static_cast<const E*>(this));
    }
    swizzle<E,2,4,1,1> ywxx() const
    {
        return swizzle<E,2,4,1,1>(*static_cast<const E*>(this));
    }
    swizzle<E,2,4,1,2> ywxy() const
    {
        return swizzle<E,2,4,1,2>(*static_cast<const E*>(this));
    }
    swizzle<E,2,4,1,3> ywxz() const
    {
        return swizzle<E,2,4,1,3>(*static_cast<const E*>(this));
    }
    swizzle<E,2,4,1,4> ywxw() const
    {
        return swizzle<E,2,4,1,4>(*static_cast<const E*>(this));
    }
    swizzle<E,2,4,2,1> ywyx() const
    {
        return swizzle<E,2,4,2,1>(*static_cast<const E*>(this));
    }
    swizzle<E,2,4,2,2> ywyy() const
    {
        return swizzle<E,2,4,2,2>(*static_cast<const E*>(this));
    }
    swizzle<E,2,4,2,3> ywyz() const
    {
        return swizzle<E,2,4,2,3>(*static_cast<const E*>(this));
    }
    swizzle<E,2,4,2,4> ywyw() const
    {
        return swizzle<E,2,4,2,4>(*static_cast<const E*>(this));
    }
    swizzle<E,2,4,3,1> ywzx() const
    {
        return swizzle<E,2,4,3,1>(*static_cast<const E*>(this));
    }
    swizzle<E,2,4,3,2> ywzy() const
    {
        return swizzle<E,2,4,3,2>(*static_cast<const E*>(this));
    }
    swizzle<E,2,4,3,3> ywzz() const
    {
        return swizzle<E,2,4,3,3>(*static_cast<const E*>(this));
    }
    swizzle<E,2,4,3,4> ywzw() const
    {
        return swizzle<E,2,4,3,4>(*static_cast<const E*>(this));
    }
    swizzle<E,2,4,4,1> ywwx() const
    {
        return swizzle<E,2,4,4,1>(*static_cast<const E*>(this));
    }
    swizzle<E,2,4,4,2> ywwy() const
    {
        return swizzle<E,2,4,4,2>(*static_cast<const E*>(this));
    }
    swizzle<E,2,4,4,3> ywwz() const
    {
        return swizzle<E,2,4,4,3>(*static_cast<const E*>(this));
    }
    swizzle<E,2,4,4,4> ywww() const
    {
        return swizzle<E,2,4,4,4>(*static_cast<const E*>(this));
    }
    swizzle<E,3,1,1,1> zxxx() const
    {
        return swizzle<E,3,1,1,1>(*static_cast<const E*>(this));
    }
    swizzle<E,3,1,1,2> zxxy() const
    {
        return swizzle<E,3,1,1,2>(*static_cast<const E*>(this));
    }
    swizzle<E,3,1,1,3> zxxz() const
    {
        return swizzle<E,3,1,1,3>(*static_cast<const E*>(this));
    }
    swizzle<E,3,1,1,4> zxxw() const
    {
        return swizzle<E,3,1,1,4>(*static_cast<const E*>(this));
    }
    swizzle<E,3,1,2,1> zxyx() const
    {
        return swizzle<E,3,1,2,1>(*static_cast<const E*>(this));
    }
    swizzle<E,3,1,2,2> zxyy() const
    {
        return swizzle<E,3,1,2,2>(*static_cast<const E*>(this));
    }
    swizzle<E,3,1,2,3> zxyz() const
    {
        return swizzle<E,3,1,2,3>(*static_cast<const E*>(this));
    }
    swizzle<E,3,1,2,4> zxyw() const
    {
        return swizzle<E,3,1,2,4>(*static_cast<const E*>(this));
    }
    swizzle<E,3,1,3,1> zxzx() const
    {
        return swizzle<E,3,1,3,1>(*static_cast<const E*>(this));
    }
    swizzle<E,3,1,3,2> zxzy() const
    {
        return swizzle<E,3,1,3,2>(*static_cast<const E*>(this));
    }
    swizzle<E,3,1,3,3> zxzz() const
    {
        return swizzle<E,3,1,3,3>(*static_cast<const E*>(this));
    }
    swizzle<E,3,1,3,4> zxzw() const
    {
        return swizzle<E,3,1,3,4>(*static_cast<const E*>(this));
    }
    swizzle<E,3,1,4,1> zxwx() const
    {
        return swizzle<E,3,1,4,1>(*static_cast<const E*>(this));
    }
    swizzle<E,3,1,4,2> zxwy() const
    {
        return swizzle<E,3,1,4,2>(*static_cast<const E*>(this));
    }
    swizzle<E,3,1,4,3> zxwz() const
    {
        return swizzle<E,3,1,4,3>(*static_cast<const E*>(this));
    }
    swizzle<E,3,1,4,4> zxww() const
    {
        return swizzle<E,3,1,4,4>(*static_cast<const E*>(this));
    }
    swizzle<E,3,2,1,1> zyxx() const
    {
        return swizzle<E,3,2,1,1>(*static_cast<const E*>(this));
    }
    swizzle<E,3,2,1,2> zyxy() const
    {
        return swizzle<E,3,2,1,2>(*static_cast<const E*>(this));
    }
    swizzle<E,3,2,1,3> zyxz() const
    {
        return swizzle<E,3,2,1,3>(*static_cast<const E*>(this));
    }
    swizzle<E,3,2,1,4> zyxw() const
    {
        return swizzle<E,3,2,1,4>(*static_cast<const E*>(this));
    }
    swizzle<E,3,2,2,1> zyyx() const
    {
        return swizzle<E,3,2,2,1>(*static_cast<const E*>(this));
    }
    swizzle<E,3,2,2,2> zyyy() const
    {
        return swizzle<E,3,2,2,2>(*static_cast<const E*>(this));
    }
    swizzle<E,3,2,2,3> zyyz() const
    {
        return swizzle<E,3,2,2,3>(*static_cast<const E*>(this));
    }
    swizzle<E,3,2,2,4> zyyw() const
    {
        return swizzle<E,3,2,2,4>(*static_cast<const E*>(this));
    }
    swizzle<E,3,2,3,1> zyzx() const
    {
        return swizzle<E,3,2,3,1>(*static_cast<const E*>(this));
    }
    swizzle<E,3,2,3,2> zyzy() const
    {
        return swizzle<E,3,2,3,2>(*static_cast<const E*>(this));
    }
    swizzle<E,3,2,3,3> zyzz() const
    {
        return swizzle<E,3,2,3,3>(*static_cast<const E*>(this));
    }
    swizzle<E,3,2,3,4> zyzw() const
    {
        return swizzle<E,3,2,3,4>(*static_cast<const E*>(this));
    }
    swizzle<E,3,2,4,1> zywx() const
    {
        return swizzle<E,3,2,4,1>(*static_cast<const E*>(this));
    }
    swizzle<E,3,2,4,2> zywy() const
    {
        return swizzle<E,3,2,4,2>(*static_cast<const E*>(this));
    }
    swizzle<E,3,2,4,3> zywz() const
    {
        return swizzle<E,3,2,4,3>(*static_cast<const E*>(this));
    }
    swizzle<E,3,2,4,4> zyww() const
    {
        return swizzle<E,3,2,4,4>(*static_cast<const E*>(this));
    }
    swizzle<E,3,3,1,1> zzxx() const
    {
        return swizzle<E,3,3,1,1>(*static_cast<const E*>(this));
    }
    swizzle<E,3,3,1,2> zzxy() const
    {
        return swizzle<E,3,3,1,2>(*static_cast<const E*>(this));
    }
    swizzle<E,3,3,1,3> zzxz() const
    {
        return swizzle<E,3,3,1,3>(*static_cast<const E*>(this));
    }
    swizzle<E,3,3,1,4> zzxw() const
    {
        return swizzle<E,3,3,1,4>(*static_cast<const E*>(this));
    }
    swizzle<E,3,3,2,1> zzyx() const
    {
        return swizzle<E,3,3,2,1>(*static_cast<const E*>(this));
    }
    swizzle<E,3,3,2,2> zzyy() const
    {
        return swizzle<E,3,3,2,2>(*static_cast<const E*>(this));
    }
    swizzle<E,3,3,2,3> zzyz() const
    {
        return swizzle<E,3,3,2,3>(*static_cast<const E*>(this));
    }
    swizzle<E,3,3,2,4> zzyw() const
    {
        return swizzle<E,3,3,2,4>(*static_cast<const E*>(this));
    }
    swizzle<E,3,3,3,1> zzzx() const
    {
        return swizzle<E,3,3,3,1>(*static_cast<const E*>(this));
    }
    swizzle<E,3,3,3,2> zzzy() const
    {
        return swizzle<E,3,3,3,2>(*static_cast<const E*>(this));
    }
    swizzle<E,3,3,3,3> zzzz() const
    {
        return swizzle<E,3,3,3,3>(*static_cast<const E*>(this));
    }
    swizzle<E,3,3,3,4> zzzw() const
    {
        return swizzle<E,3,3,3,4>(*static_cast<const E*>(this));
    }
    swizzle<E,3,3,4,1> zzwx() const
    {
        return swizzle<E,3,3,4,1>(*static_cast<const E*>(this));
    }
    swizzle<E,3,3,4,2> zzwy() const
    {
        return swizzle<E,3,3,4,2>(*static_cast<const E*>(this));
    }
    swizzle<E,3,3,4,3> zzwz() const
    {
        return swizzle<E,3,3,4,3>(*static_cast<const E*>(this));
    }
    swizzle<E,3,3,4,4> zzww() const
    {
        return swizzle<E,3,3,4,4>(*static_cast<const E*>(this));
    }
    swizzle<E,3,4,1,1> zwxx() const
    {
        return swizzle<E,3,4,1,1>(*static_cast<const E*>(this));
    }
    swizzle<E,3,4,1,2> zwxy() const
    {
        return swizzle<E,3,4,1,2>(*static_cast<const E*>(this));
    }
    swizzle<E,3,4,1,3> zwxz() const
    {
        return swizzle<E,3,4,1,3>(*static_cast<const E*>(this));
    }
    swizzle<E,3,4,1,4> zwxw() const
    {
        return swizzle<E,3,4,1,4>(*static_cast<const E*>(this));
    }
    swizzle<E,3,4,2,1> zwyx() const
    {
        return swizzle<E,3,4,2,1>(*static_cast<const E*>(this));
    }
    swizzle<E,3,4,2,2> zwyy() const
    {
        return swizzle<E,3,4,2,2>(*static_cast<const E*>(this));
    }
    swizzle<E,3,4,2,3> zwyz() const
    {
        return swizzle<E,3,4,2,3>(*static_cast<const E*>(this));
    }
    swizzle<E,3,4,2,4> zwyw() const
    {
        return swizzle<E,3,4,2,4>(*static_cast<const E*>(this));
    }
    swizzle<E,3,4,3,1> zwzx() const
    {
        return swizzle<E,3,4,3,1>(*static_cast<const E*>(this));
    }
    swizzle<E,3,4,3,2> zwzy() const
    {
        return swizzle<E,3,4,3,2>(*static_cast<const E*>(this));
    }
    swizzle<E,3,4,3,3> zwzz() const
    {
        return swizzle<E,3,4,3,3>(*static_cast<const E*>(this));
    }
    swizzle<E,3,4,3,4> zwzw() const
    {
        return swizzle<E,3,4,3,4>(*static_cast<const E*>(this));
    }
    swizzle<E,3,4,4,1> zwwx() const
    {
        return swizzle<E,3,4,4,1>(*static_cast<const E*>(this));
    }
    swizzle<E,3,4,4,2> zwwy() const
    {
        return swizzle<E,3,4,4,2>(*static_cast<const E*>(this));
    }
    swizzle<E,3,4,4,3> zwwz() const
    {
        return swizzle<E,3,4,4,3>(*static_cast<const E*>(this));
    }
    swizzle<E,3,4,4,4> zwww() const
    {
        return swizzle<E,3,4,4,4>(*static_cast<const E*>(this));
    }
    swizzle<E,4,1,1,1> wxxx() const
    {
        return swizzle<E,4,1,1,1>(*static_cast<const E*>(this));
    }
    swizzle<E,4,1,1,2> wxxy() const
    {
        return swizzle<E,4,1,1,2>(*static_cast<const E*>(this));
    }
    swizzle<E,4,1,1,3> wxxz() const
    {
        return swizzle<E,4,1,1,3>(*static_cast<const E*>(this));
    }
    swizzle<E,4,1,1,4> wxxw() const
    {
        return swizzle<E,4,1,1,4>(*static_cast<const E*>(this));
    }
    swizzle<E,4,1,2,1> wxyx() const
    {
        return swizzle<E,4,1,2,1>(*static_cast<const E*>(this));
    }
    swizzle<E,4,1,2,2> wxyy() const
    {
        return swizzle<E,4,1,2,2>(*static_cast<const E*>(this));
    }
    swizzle<E,4,1,2,3> wxyz() const
    {
        return swizzle<E,4,1,2,3>(*static_cast<const E*>(this));
    }
    swizzle<E,4,1,2,4> wxyw() const
    {
        return swizzle<E,4,1,2,4>(*static_cast<const E*>(this));
    }
    swizzle<E,4,1,3,1> wxzx() const
    {
        return swizzle<E,4,1,3,1>(*static_cast<const E*>(this));
    }
    swizzle<E,4,1,3,2> wxzy() const
    {
        return swizzle<E,4,1,3,2>(*static_cast<const E*>(this));
    }
    swizzle<E,4,1,3,3> wxzz() const
    {
        return swizzle<E,4,1,3,3>(*static_cast<const E*>(this));
    }
    swizzle<E,4,1,3,4> wxzw() const
    {
        return swizzle<E,4,1,3,4>(*static_cast<const E*>(this));
    }
    swizzle<E,4,1,4,1> wxwx() const
    {
        return swizzle<E,4,1,4,1>(*static_cast<const E*>(this));
    }
    swizzle<E,4,1,4,2> wxwy() const
    {
        return swizzle<E,4,1,4,2>(*static_cast<const E*>(this));
    }
    swizzle<E,4,1,4,3> wxwz() const
    {
        return swizzle<E,4,1,4,3>(*static_cast<const E*>(this));
    }
    swizzle<E,4,1,4,4> wxww() const
    {
        return swizzle<E,4,1,4,4>(*static_cast<const E*>(this));
    }
    swizzle<E,4,2,1,1> wyxx() const
    {
        return swizzle<E,4,2,1,1>(*static_cast<const E*>(this));
    }
    swizzle<E,4,2,1,2> wyxy() const
    {
        return swizzle<E,4,2,1,2>(*static_cast<const E*>(this));
    }
    swizzle<E,4,2,1,3> wyxz() const
    {
        return swizzle<E,4,2,1,3>(*static_cast<const E*>(this));
    }
    swizzle<E,4,2,1,4> wyxw() const
    {
        return swizzle<E,4,2,1,4>(*static_cast<const E*>(this));
    }
    swizzle<E,4,2,2,1> wyyx() const
    {
        return swizzle<E,4,2,2,1>(*static_cast<const E*>(this));
    }
    swizzle<E,4,2,2,2> wyyy() const
    {
        return swizzle<E,4,2,2,2>(*static_cast<const E*>(this));
    }
    swizzle<E,4,2,2,3> wyyz() const
    {
        return swizzle<E,4,2,2,3>(*static_cast<const E*>(this));
    }
    swizzle<E,4,2,2,4> wyyw() const
    {
        return swizzle<E,4,2,2,4>(*static_cast<const E*>(this));
    }
    swizzle<E,4,2,3,1> wyzx() const
    {
        return swizzle<E,4,2,3,1>(*static_cast<const E*>(this));
    }
    swizzle<E,4,2,3,2> wyzy() const
    {
        return swizzle<E,4,2,3,2>(*static_cast<const E*>(this));
    }
    swizzle<E,4,2,3,3> wyzz() const
    {
        return swizzle<E,4,2,3,3>(*static_cast<const E*>(this));
    }
    swizzle<E,4,2,3,4> wyzw() const
    {
        return swizzle<E,4,2,3,4>(*static_cast<const E*>(this));
    }
    swizzle<E,4,2,4,1> wywx() const
    {
        return swizzle<E,4,2,4,1>(*static_cast<const E*>(this));
    }
    swizzle<E,4,2,4,2> wywy() const
    {
        return swizzle<E,4,2,4,2>(*static_cast<const E*>(this));
    }
    swizzle<E,4,2,4,3> wywz() const
    {
        return swizzle<E,4,2,4,3>(*static_cast<const E*>(this));
    }
    swizzle<E,4,2,4,4> wyww() const
    {
        return swizzle<E,4,2,4,4>(*static_cast<const E*>(this));
    }
    swizzle<E,4,3,1,1> wzxx() const
    {
        return swizzle<E,4,3,1,1>(*static_cast<const E*>(this));
    }
    swizzle<E,4,3,1,2> wzxy() const
    {
        return swizzle<E,4,3,1,2>(*static_cast<const E*>(this));
    }
    swizzle<E,4,3,1,3> wzxz() const
    {
        return swizzle<E,4,3,1,3>(*static_cast<const E*>(this));
    }
    swizzle<E,4,3,1,4> wzxw() const
    {
        return swizzle<E,4,3,1,4>(*static_cast<const E*>(this));
    }
    swizzle<E,4,3,2,1> wzyx() const
    {
        return swizzle<E,4,3,2,1>(*static_cast<const E*>(this));
    }
    swizzle<E,4,3,2,2> wzyy() const
    {
        return swizzle<E,4,3,2,2>(*static_cast<const E*>(this));
    }
    swizzle<E,4,3,2,3> wzyz() const
    {
        return swizzle<E,4,3,2,3>(*static_cast<const E*>(this));
    }
    swizzle<E,4,3,2,4> wzyw() const
    {
        return swizzle<E,4,3,2,4>(*static_cast<const E*>(this));
    }
    swizzle<E,4,3,3,1> wzzx() const
    {
        return swizzle<E,4,3,3,1>(*static_cast<const E*>(this));
    }
    swizzle<E,4,3,3,2> wzzy() const
    {
        return swizzle<E,4,3,3,2>(*static_cast<const E*>(this));
    }
    swizzle<E,4,3,3,3> wzzz() const
    {
        return swizzle<E,4,3,3,3>(*static_cast<const E*>(this));
    }
    swizzle<E,4,3,3,4> wzzw() const
    {
        return swizzle<E,4,3,3,4>(*static_cast<const E*>(this));
    }
    swizzle<E,4,3,4,1> wzwx() const
    {
        return swizzle<E,4,3,4,1>(*static_cast<const E*>(this));
    }
    swizzle<E,4,3,4,2> wzwy() const
    {
        return swizzle<E,4,3,4,2>(*static_cast<const E*>(this));
    }
    swizzle<E,4,3,4,3> wzwz() const
    {
        return swizzle<E,4,3,4,3>(*static_cast<const E*>(this));
    }
    swizzle<E,4,3,4,4> wzww() const
    {
        return swizzle<E,4,3,4,4>(*static_cast<const E*>(this));
    }
    swizzle<E,4,4,1,1> wwxx() const
    {
        return swizzle<E,4,4,1,1>(*static_cast<const E*>(this));
    }
    swizzle<E,4,4,1,2> wwxy() const
    {
        return swizzle<E,4,4,1,2>(*static_cast<const E*>(this));
    }
    swizzle<E,4,4,1,3> wwxz() const
    {
        return swizzle<E,4,4,1,3>(*static_cast<const E*>(this));
    }
    swizzle<E,4,4,1,4> wwxw() const
    {
        return swizzle<E,4,4,1,4>(*static_cast<const E*>(this));
    }
    swizzle<E,4,4,2,1> wwyx() const
    {
        return swizzle<E,4,4,2,1>(*static_cast<const E*>(this));
    }
    swizzle<E,4,4,2,2> wwyy() const
    {
        return swizzle<E,4,4,2,2>(*static_cast<const E*>(this));
    }
    swizzle<E,4,4,2,3> wwyz() const
    {
        return swizzle<E,4,4,2,3>(*static_cast<const E*>(this));
    }
    swizzle<E,4,4,2,4> wwyw() const
    {
        return swizzle<E,4,4,2,4>(*static_cast<const E*>(this));
    }
    swizzle<E,4,4,3,1> wwzx() const
    {
        return swizzle<E,4,4,3,1>(*static_cast<const E*>(this));
    }
    swizzle<E,4,4,3,2> wwzy() const
    {
        return swizzle<E,4,4,3,2>(*static_cast<const E*>(this));
    }
    swizzle<E,4,4,3,3> wwzz() const
    {
        return swizzle<E,4,4,3,3>(*static_cast<const E*>(this));
    }
    swizzle<E,4,4,3,4> wwzw() const
    {
        return swizzle<E,4,4,3,4>(*static_cast<const E*>(this));
    }
    swizzle<E,4,4,4,1> wwwx() const
    {
        return swizzle<E,4,4,4,1>(*static_cast<const E*>(this));
    }
    swizzle<E,4,4,4,2> wwwy() const
    {
        return swizzle<E,4,4,4,2>(*static_cast<const E*>(this));
    }
    swizzle<E,4,4,4,3> wwwz() const
    {
        return swizzle<E,4,4,4,3>(*static_cast<const E*>(this));
    }
    swizzle<E,4,4,4,4> wwww() const
    {
        return swizzle<E,4,4,4,4>(*static_cast<const E*>(this));
    }
};

} // detail
} // il
} // cal

#endif
