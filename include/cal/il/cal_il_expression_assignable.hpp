/*
 * C++ to IL compiler/generator assignable expresion
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

#ifndef __CAL_IL_EXPRESSION_ASSIGNABLE_H
#define __CAL_IL_EXPRESSION_ASSIGNABLE_H

#include <boost/format.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>

namespace cal {
namespace il {
namespace detail {

template<class T>
class value : public expression<value<T> >
{
protected:
    typedef value<T>                                 self_type;
    typedef detail::expression<value<T> >            base_type;

public:
    typedef typename detail::base_cal_type<T>::value        value_type;
    typedef const self_type                                 const_closure_type;
    typedef self_type                                       closure_type;
    static const int                                        temp_reg_count=0;

protected:
    typedef typename value_type::component_type         component_type;
    typedef union data_type_union { boost::array<component_type,value_type::component_count> base; boost::array<boost::uint32_t,4> hex; } data_type;

protected:
    data_type _data;
    using base_type::index;

public:
    explicit value( const component_type& v0 ) : base_type()
    {
        _data.hex.assign(0);
        _data.base[0] = v0;
        if( _data.base.size()>1 ) _data.base[1] = v0;
        if( _data.base.size()>2 ) _data.base[2] = v0;
        if( _data.base.size()>3 ) _data.base[3] = v0;      
    }

    explicit value( const component_type& v0, const component_type& v1 ) : base_type()
    {
        BOOST_STATIC_ASSERT( value_type::component_count>1 );
        _data.hex.assign(0);        
        _data.base[0] = v0;
        _data.base[1] = v1;
        if( _data.base.size()>2 ) _data.base[2] = v0;
        if( _data.base.size()>3 ) _data.base[3] = v1;
    }

    explicit value( const component_type& v0, const component_type& v1, const component_type& v2, const component_type& v3 ) : base_type()
    {
        BOOST_STATIC_ASSERT( value_type::component_count==4 );
        _data.hex.assign(0);
        _data.base[0] = v0;
        _data.base[1] = v1;
        _data.base[2] = v2;
        _data.base[3] = v3;
    }
    value( const value<T>& rhs ) : base_type(rhs), _data(rhs._data)
    {
    }
    ~value()
    {
    }

    void emitCode() const
    {
    }

    std::string resultCode() const
    {
        int     idx = Source::code.getLiteral( _data.hex );
        return detail::make_swizzle( (boost::format("l%i") % idx).str(), value_type::type_size );
    }

    component_type getValue() const { return _data.base[0]; }
};


template<class T,class E>
class assignable_expression : public expression<E>
{
protected:
    typedef typename detail::base_cal_type<T>::value                 value_type;
    typedef typename detail::base_cal_type<T>::value::component_type component_type;

public:
    using expression<E>::operator();

public:
    assignable_expression() : expression<E>() {}
    assignable_expression( const assignable_expression& rhs ) : expression<E>(rhs) {}
    ~assignable_expression() {}

    E& operator=( const component_type& v )
    {
        return ((*this)() = value<value_type>(v));
    }

    template<class E1>
    E& operator+=( const detail::expression<E1>& e )
    {
        typedef boost::is_same<value_type,typename E1::value_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );

        return ((*this)() = (*this)() + e());
    }

    template<class E1>
    E& operator-=( const detail::expression<E1>& e )
    {
        typedef boost::is_same<value_type,typename E1::value_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );

        return ((*this)() = (*this)() - e());
    }

    template<class E1>
    E& operator*=( const detail::expression<E1>& e )
    {
        typedef boost::is_same<value_type,typename E1::value_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );

        return ((*this)() = (*this)() * e());
    }

    template<class E1>
    E& operator/=( const detail::expression<E1>& e )
    {
        typedef boost::is_same<value_type,typename E1::value_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );

        return ((*this)() = (*this)() / e());
    }

    template<class E1>
    E& operator%=( const detail::expression<E1>& e )
    {
        typedef boost::is_same<value_type,typename E1::value_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );

        return ((*this)() = (*this)() % e());
    }

    template<class E1>
    E& operator|=( const detail::expression<E1>& e )
    {
        typedef boost::is_same<value_type,typename E1::value_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );

        return ((*this)() = (*this)() | e());
    }

    template<class E1>
    E& operator&=( const detail::expression<E1>& e )
    {
        typedef boost::is_same<value_type,typename E1::value_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );

        return ((*this)() = (*this)() & e());
    }

    template<class E1>
    E& operator^=( const detail::expression<E1>& e )
    {
        typedef boost::is_same<value_type,typename E1::value_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );

        return ((*this)() = (*this)() ^ e());
    }

    E& operator+=( const component_type& v )
    {
        return ((*this)() = (*this)() + value<value_type>(v));
    }

    E& operator-=( const component_type& v )
    {
        return ((*this)() = (*this)() - value<value_type>(v));
    }

    E& operator*=( const component_type& v )
    {
        return ((*this)() = (*this)() * value<value_type>(v));
    }

    E& operator/=( const component_type& v )
    {
        return ((*this)() = (*this)() / value<value_type>(v));
    }

    E& operator%=( const component_type& v )
    {
        return ((*this)() = (*this)() % value<value_type>(v));
    }

    E& operator|=( const component_type& v )
    {
        return ((*this)() = (*this)() | value<value_type>(v));
    }

    E& operator&=( const component_type& v )
    {
        return ((*this)() = (*this)() & value<value_type>(v));
    }

    E& operator^=( const component_type& v )
    {
        return ((*this)() = (*this)() ^ value<value_type>(v));
    }
};

} // detail
} // il
} // cal

#endif
