/*
 * C++ to IL compiler/generator top level types
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

#ifndef __CAL_IL_TYPES_H
#define __CAL_IL_TYPES_H

#include <boost/format.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>

namespace cal {
namespace il {

namespace detail {

template<class T,class E>
class indexed_expression : public detail::swizzable_expression<T,indexed_expression<T,E> >
{
protected:
    typedef indexed_expression<T,E>                                  self_type;
    typedef detail::swizzable_expression<T,indexed_expression<T,E> > base_type;
    typedef const E                                                  expression_type;
    typedef typename E::const_closure_type                           expression_closure_type;

public:
    typedef T                                                        value_type;
    typedef const self_type                                          const_closure_type;
    typedef self_type                                                closure_type;
    static const int                                                 temp_reg_count=0;
    static const bool                                                swizzle_has_assign=true;

public:
    using base_type::operator=;

protected:
    expression_closure_type _e;
    std::string             _reg_name;
    using base_type::index;


protected:
    template<class E1>
    void iEmitCode( const E1& e ) const
    {
        e.emitCode();
        emitCode();
        Source::code() << boost::format("mov %s,%s\n") % resultCode() % e.resultCode();
    }

public:
    explicit indexed_expression( const std::string& name, expression_type& e ) : base_type(), _e(e), _reg_name(name)
    {
    }
    indexed_expression( const indexed_expression<T,E>& rhs ) : base_type(rhs), _e(rhs._e), _reg_name(rhs._reg_name)
    {
    }
    ~indexed_expression()
    {
    }

    void emitCode() const
    {
        _e.emitCode();
    }

    std::string resultCode() const
    {
        return (boost::format("%s[%s]") % _reg_name % _e.resultCode()).str();
    }

    indexed_expression<T,E>& operator=( const indexed_expression<T,E>& v )
    {
        iEmitCode(v);
        return *this;
    }

    const indexed_expression<T,E>& operator=( const indexed_expression<T,E>& v ) const
    {
        iEmitCode(v);
        return *this;
    }

    template<class E1>
    indexed_expression<T,E>& operator=( const detail::expression<E1>& e )
    {
        typedef boost::is_same<typename E1::value_type,value_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );        
        iEmitCode(e());
        return *this;
    }

    template<class E1>
    const indexed_expression<T,E>& operator=( const detail::expression<E1>& e ) const
    {
        typedef boost::is_same<typename E1::value_type,value_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );        
        iEmitCode(e());
        return *this;
    }
};

template<class E>
class variable_clone : public expression<variable_clone<E> >
{
protected:
    typedef variable_clone<E>               self_type;
    typedef expression<variable_clone<E> >  base_type;
    typedef const E                         expression_type;
    
public:
    typedef typename E::value_type      value_type;
    typedef const self_type             const_closure_type;
    typedef self_type                   closure_type;
    static const int                    temp_reg_count=E::temp_reg_count;
    static const bool                   swizzle_has_assign=E::swizzle_has_assign;

public:
    explicit variable_clone( expression_type& e ) : base_type(), _e() { _e.clone(e); }
    variable_clone( const variable_clone<E>& rhs ) : base_type(rhs), _e() { _e.clone(rhs._e); }
    ~variable_clone() {}

    void emitCode() const
    {
        _e.emitCode();
    }

    std::string resultCode() const
    {
        return _e.resultCode();
    }

private:
    E       _e;
};

} // detail

template<class T>
class value : public detail::swizzable_expression<T,value<T> >
{
protected:
    typedef value<T>                                        self_type;
    typedef detail::swizzable_expression<T,value<T> >       base_type;

public:
    typedef typename detail::base_cal_type<T>::value        value_type;
    typedef const self_type                                 const_closure_type;
    typedef self_type                                       closure_type;
    static const int                                        temp_reg_count=0;
    static const bool                                       swizzle_has_assign=false;

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
        int     idx = Source::code().getLiteral( _data.hex );
        return detail::make_swizzle( (boost::format("l%i") % idx).str(), value_type::type_size );
    }
};

template<class T>
class variable : public detail::swizzable_expression<T,variable<T> >
{
protected:
    typedef variable<T>                                  self_type;
    typedef detail::swizzable_expression<T,variable<T> > base_type;

public:
    typedef typename detail::base_cal_type<T>::value     value_type;
    typedef detail::variable_clone<self_type>            closure_type;
    typedef const closure_type                           const_closure_type;

    static const int                                     temp_reg_count=0;
    static const bool                                    swizzle_has_assign=true;

protected:
    typedef typename value_type::component_type         component_type;
    typedef union data_type_union { boost::array<component_type,value_type::component_count> base; boost::array<boost::uint32_t,4> hex; } data_type;

protected:
    using base_type::index;

public:
    using base_type::resultCode;
    using base_type::operator=;

protected:
    template<class E>
    void iEmitCode( const E& e ) const
    {
        e.emitCode();
        Source::code() << boost::format("mov %s,%s\n") % resultCode() % e.resultCode();
    }

public:
    variable() : base_type()
    {
    }
    variable( const variable<T>& rhs ) : base_type()
    {
        iEmitCode(rhs);
    }

    template<class E>
    variable( const detail::expression<E>& e ) : base_type()
    {
        typedef boost::is_same<typename E::value_type,value_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );
        iEmitCode(e());
    }
    template<class E1,class E2>
    explicit variable( const detail::expression<E1>& e1, const detail::expression<E2>& e2 ) : base_type()
    {
        typedef boost::is_same<typename detail::cal_binary_cast<typename E1::value_type,typename E2::value_type>::value_type, value_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );
        iEmitCode(merge_types(e1(),e2()));
    }
    template<class E1,class E2,class E3,class E4>
    explicit variable( const detail::expression<E1>& e1, const detail::expression<E2>& e2, const detail::expression<E3>& e3, const detail::expression<E4>& e4 ) : base_type()
    {
        typedef typename detail::cal_binary_cast<typename E1::value_type,typename E2::value_type>::value_type value1_type;
        typedef typename detail::cal_binary_cast<typename E3::value_type,typename E4::value_type>::value_type value2_type;
        typedef boost::is_same<typename detail::cal_binary_cast<value1_type,value2_type>::value_type, value_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );
        iEmitCode(merge_types(e1(),e2(),e3(),e4()));
    }

    explicit variable( const component_type& v0 ) : base_type()
    {
        iEmitCode(value<value_type>(v0));
    }
    explicit variable( const component_type& v0, const component_type& v1 ) : base_type()
    {
        iEmitCode(value<value_type>(v0,v1));
    }
    explicit variable( const component_type& v0, const component_type& v1, const component_type& v2, const component_type& v3 ) : base_type()
    {
        iEmitCode(value<value_type>(v0,v1,v2,v3));
    }

    template<class E1>
    explicit variable( const detail::expression<E1>& e1, const component_type& v1 ) : base_type()
    {
        typedef boost::is_same<typename detail::cal_binary_cast<typename E1::value_type,typename E1::value_type>::value_type, value_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );
        iEmitCode(merge_types(e1(),value<typename E1::value_type>(v1)));
    }
    template<class E1>
    explicit variable( const component_type& v1, const detail::expression<E1>& e1 ) : base_type()
    {
        typedef boost::is_same<typename detail::cal_binary_cast<typename E1::value_type,typename E1::value_type>::value_type, value_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );
        iEmitCode(merge_types(value<typename E1::value_type>(v1),e1()));
    }

    template<class E1,class E2,class E3>
    explicit variable( const detail::expression<E1>& e1, const detail::expression<E2>& e2, const detail::expression<E3>& e3, const component_type& v1 ) : base_type()
    {
        typedef typename detail::cal_binary_cast<typename E1::value_type,typename E2::value_type>::value_type value1_type;
        typedef typename detail::cal_binary_cast<typename E3::value_type,typename E1::value_type>::value_type value2_type;
        typedef boost::is_same<typename detail::cal_binary_cast<value1_type,value2_type>::value_type, value_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );
        iEmitCode(merge_types(e1(),e2(),e3(),value<typename E1::value_type>(v1)));
    }
    template<class E1,class E2,class E3>
    explicit variable( const detail::expression<E1>& e1, const detail::expression<E2>& e2, const component_type& v1, const detail::expression<E3>& e3  ) : base_type()
    {
        typedef typename detail::cal_binary_cast<typename E1::value_type,typename E2::value_type>::value_type value1_type;
        typedef typename detail::cal_binary_cast<typename E1::value_type,typename E3::value_type>::value_type value2_type;
        typedef boost::is_same<typename detail::cal_binary_cast<value1_type,value2_type>::value_type, value_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );
        iEmitCode(merge_types(e1(),e2(),value<typename E1::value_type>(v1),e3()));
    }
    template<class E1,class E2,class E3>
    explicit variable( const detail::expression<E1>& e1, const component_type& v1, const detail::expression<E2>& e2, const detail::expression<E3>& e3 ) : base_type()
    {
        typedef typename detail::cal_binary_cast<typename E1::value_type,typename E1::value_type>::value_type value1_type;
        typedef typename detail::cal_binary_cast<typename E2::value_type,typename E3::value_type>::value_type value2_type;
        typedef boost::is_same<typename detail::cal_binary_cast<value1_type,value2_type>::value_type, value_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );
        iEmitCode(merge_types(e1(),value<typename E1::value_type>(v1),e2(),e3()));
    }
    template<class E1,class E2,class E3>
    explicit variable( const component_type& v1, const detail::expression<E1>& e1, const detail::expression<E2>& e2, const detail::expression<E3>& e3 ) : base_type()
    {
        typedef typename detail::cal_binary_cast<typename E1::value_type,typename E1::value_type>::value_type value1_type;
        typedef typename detail::cal_binary_cast<typename E2::value_type,typename E3::value_type>::value_type value2_type;
        typedef boost::is_same<typename detail::cal_binary_cast<value1_type,value2_type>::value_type, value_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );
        iEmitCode(merge_types(value<typename E1::value_type>(v1),e1(),e2(),e3()));
    }

    template<class E1,class E2>
    explicit variable( const component_type& v1, const component_type& v2, const detail::expression<E1>& e1, const detail::expression<E2>& e2 ) : base_type()
    {
        typedef typename detail::cal_binary_cast<typename E1::value_type,typename E1::value_type>::value_type value1_type;
        typedef typename detail::cal_binary_cast<typename E1::value_type,typename E2::value_type>::value_type value2_type;
        typedef boost::is_same<typename detail::cal_binary_cast<value1_type,value2_type>::value_type, value_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );
        iEmitCode(merge_types(value<typename E1::value_type>(v1),value<typename E1::value_type>(v2),e1(),e2()));
    }
    template<class E1,class E2>
    explicit variable( const component_type& v1, const detail::expression<E1>& e1, const component_type& v2, const detail::expression<E2>& e2 ) : base_type()
    {
        typedef typename detail::cal_binary_cast<typename E1::value_type,typename E1::value_type>::value_type value1_type;
        typedef typename detail::cal_binary_cast<typename E1::value_type,typename E2::value_type>::value_type value2_type;
        typedef boost::is_same<typename detail::cal_binary_cast<value1_type,value2_type>::value_type, value_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );
        iEmitCode(merge_types(value<typename E1::value_type>(v1),e1(),value<typename E1::value_type>(v2),e2()));
    }
    template<class E1,class E2>
    explicit variable( const component_type& v1, const detail::expression<E1>& e1, const detail::expression<E2>& e2, const component_type& v2 ) : base_type()
    {
        typedef typename detail::cal_binary_cast<typename E1::value_type,typename E1::value_type>::value_type value1_type;
        typedef typename detail::cal_binary_cast<typename E2::value_type,typename E1::value_type>::value_type value2_type;
        typedef boost::is_same<typename detail::cal_binary_cast<value1_type,value2_type>::value_type, value_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );
        iEmitCode(merge_types(value<typename E1::value_type>(v1),e1(),e2(),value<typename E1::value_type>(v2)));
    }
    template<class E1,class E2>
    explicit variable( const detail::expression<E1>& e1, const component_type& v1, const component_type& v2, const detail::expression<E2>& e2 ) : base_type()
    {
        typedef typename detail::cal_binary_cast<typename E1::value_type,typename E1::value_type>::value_type value1_type;
        typedef typename detail::cal_binary_cast<typename E1::value_type,typename E2::value_type>::value_type value2_type;
        typedef boost::is_same<typename detail::cal_binary_cast<value1_type,value2_type>::value_type, value_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );
        iEmitCode(merge_types(e1(),value<typename E1::value_type>(v1),value<typename E1::value_type>(v2),e2()));
    }
    template<class E1,class E2>
    explicit variable( const detail::expression<E1>& e1, const component_type& v1, const detail::expression<E2>& e2, const component_type& v2 ) : base_type()
    {
        typedef typename detail::cal_binary_cast<typename E1::value_type,typename E1::value_type>::value_type value1_type;
        typedef typename detail::cal_binary_cast<typename E2::value_type,typename E1::value_type>::value_type value2_type;
        typedef boost::is_same<typename detail::cal_binary_cast<value1_type,value2_type>::value_type, value_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );
        iEmitCode(merge_types(e1(),value<typename E1::value_type>(v1),e2(),value<typename E1::value_type>(v2)));
    }
    template<class E1,class E2>
    explicit variable( const detail::expression<E1>& e1, const detail::expression<E2>& e2, const component_type& v1, const component_type& v2 ) : base_type()
    {
        typedef typename detail::cal_binary_cast<typename E1::value_type,typename E2::value_type>::value_type value1_type;
        typedef typename detail::cal_binary_cast<typename E1::value_type,typename E1::value_type>::value_type value2_type;
        typedef boost::is_same<typename detail::cal_binary_cast<value1_type,value2_type>::value_type, value_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );
        iEmitCode(merge_types(e1(),e2(),value<typename E1::value_type>(v1),value<typename E1::value_type>(v2)));
    }

    template<class E1>
    explicit variable( const component_type& v1, const component_type& v2, const component_type& v3, const detail::expression<E1>& e1 ) : base_type()
    {
        typedef typename detail::cal_binary_cast<typename E1::value_type,typename E1::value_type>::value_type value1_type;
        typedef typename detail::cal_binary_cast<typename E1::value_type,typename E1::value_type>::value_type value2_type;
        typedef boost::is_same<typename detail::cal_binary_cast<value1_type,value2_type>::value_type, value_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );
        iEmitCode(merge_types(value<typename E1::value_type>(v1),value<typename E1::value_type>(v2),value<typename E1::value_type>(v3),e1()));
    }
    template<class E1>
    explicit variable( const component_type& v1, const component_type& v2, const detail::expression<E1>& e1, const component_type& v3 ) : base_type()
    {
        typedef typename detail::cal_binary_cast<typename E1::value_type,typename E1::value_type>::value_type value1_type;
        typedef typename detail::cal_binary_cast<typename E1::value_type,typename E1::value_type>::value_type value2_type;
        typedef boost::is_same<typename detail::cal_binary_cast<value1_type,value2_type>::value_type, value_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );
        iEmitCode(merge_types(value<typename E1::value_type>(v1),value<typename E1::value_type>(v2),e1(),value<typename E1::value_type>(v3)));
    }
    template<class E1>
    explicit variable( const component_type& v1, const detail::expression<E1>& e1, const component_type& v2, const component_type& v3 ) : base_type()
    {
        typedef typename detail::cal_binary_cast<typename E1::value_type,typename E1::value_type>::value_type value1_type;
        typedef typename detail::cal_binary_cast<typename E1::value_type,typename E1::value_type>::value_type value2_type;
        typedef boost::is_same<typename detail::cal_binary_cast<value1_type,value2_type>::value_type, value_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );
        iEmitCode(merge_types(value<typename E1::value_type>(v1),e1(),value<typename E1::value_type>(v2),value<typename E1::value_type>(v3)));
    }
    template<class E1>
    explicit variable( const detail::expression<E1>& e1, const component_type& v1, const component_type& v2, const component_type& v3 ) : base_type()
    {
        typedef typename detail::cal_binary_cast<typename E1::value_type,typename E1::value_type>::value_type value1_type;
        typedef typename detail::cal_binary_cast<typename E1::value_type,typename E1::value_type>::value_type value2_type;
        typedef boost::is_same<typename detail::cal_binary_cast<value1_type,value2_type>::value_type, value_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );
        iEmitCode(merge_types(e1(),value<typename E1::value_type>(v1),value<typename E1::value_type>(v2),value<typename E1::value_type>(v3)));
    }

    void clone( const variable<T>& rhs ) 
    {
        index = rhs.index;
    }

    ~variable()
    {
    }

    void emitCode() const
    {
    }
    
    unsigned getID() const 
    {
        return index;
    }
    
    void setNewID( unsigned id ) 
    {
        index = id;
    }
        
    variable<T> operator=( const variable<T>& v )
    {
        iEmitCode(v);
        return *this;
    }

    template<class E>
    variable<T>& operator=( const detail::expression<E>& e )
    {
        typedef boost::is_same<typename E::value_type,value_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );
        iEmitCode(e());
        return *this;
    }
};

template<class T>
class named_variable : public detail::swizzable_expression<T,named_variable<T> >
{
protected:
    typedef named_variable<T>                                   self_type;
    typedef detail::swizzable_expression<T,named_variable<T> >  base_type;

public:
    typedef typename detail::base_cal_type<T>::value            value_type;
    typedef const self_type                                     const_closure_type;
    typedef self_type                                           closure_type;
    static const int                                            temp_reg_count=0;
    static const bool                                           swizzle_has_assign=true;

protected:
    std::string _name;
    using base_type::index;

protected:
    template<class E>
    void iEmitCode( const E& e ) const
    {
        e.emitCode();
        Source::code() << boost::format("mov %s,%s\n") % detail::mask_output(resultCode()) % detail::match_input_to_output(resultCode(),e.resultCode());
    }

public:
    using base_type::operator=;

public:
    named_variable( const std::string& name ) : base_type(), _name(name)
    {
    }
    named_variable( const named_variable<T>& rhs ) : base_type(rhs), _name(rhs._name)
    {
    }
    ~named_variable()
    {
    }

    void emitCode() const
    {
    }

    std::string resultCode() const
    {
        BOOST_STATIC_ASSERT( value_type::type_size==1 || value_type::type_size==2 || value_type::type_size==4 );
        return detail::make_swizzle( _name, value_type::type_size );
    }

    named_variable<T> operator=( const named_variable<T>& v )
    {
        iEmitCode(v);
        return *this;
    }

    template<class E>
    named_variable<T>& operator=( const detail::expression<E>& e )
    {
        typedef boost::is_same<typename E::value_type,value_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );        
        iEmitCode(e());
        return *this;
    }
};

template<class T>
class indexed_register
{
public:
    typedef typename detail::base_cal_type<T>::value    value_type;    

protected:
    std::string _reg_name;

public:
    indexed_register( const std::string& name ) : _reg_name(name)
    {
    }
    ~indexed_register() {}

    detail::indexed_expression<value_type,detail::register_address<void> > operator[]( int offset ) const
    {
        return detail::indexed_expression<value_type,detail::register_address<void> >(_reg_name,detail::register_address<void>(offset));
    }

    detail::indexed_expression<value_type,detail::register_address<void> > operator()( int offset ) const
    {
        return detail::indexed_expression<value_type,detail::register_address<void> >(_reg_name,detail::register_address<void>(offset));
    }

    template<class E>
    detail::indexed_expression<value_type,detail::register_address<E> > operator[]( const detail::binary<E,detail::value<E>,detail::cal_binary_add<typename E::value_type,typename E::value_type> >& e ) const
    {
        typedef boost::is_same<typename E::value_type,int_type> assert_v1;
        typedef boost::is_same<typename E::value_type,uint_type> assert_v2;
        BOOST_STATIC_ASSERT( assert_v1::value || assert_v2::value );

        return detail::indexed_expression<value_type,detail::register_address<E> >( _reg_name, detail::register_address<E>(e._e1, e._e2.getValue()) );
    }

    template<class E>
    detail::indexed_expression<value_type,detail::register_address<E> > operator()( const detail::binary<E,detail::value<E>,detail::cal_binary_add<typename E::value_type,typename E::value_type> >& e ) const
    {
        typedef boost::is_same<typename E::value_type,int_type> assert_v1;
        typedef boost::is_same<typename E::value_type,uint_type> assert_v2;
        BOOST_STATIC_ASSERT( assert_v1::value || assert_v2::value );

        return detail::indexed_expression<value_type,detail::register_address<E> >( _reg_name, detail::register_address<E>(e._e1, e._e2.getValue()) );
    }

    template<class E>
    detail::indexed_expression<value_type,E> operator[]( const detail::expression<E>& e ) const
    {
        typedef boost::is_same<typename E::value_type,int_type> assert_v1;
        typedef boost::is_same<typename E::value_type,uint_type> assert_v2;
        BOOST_STATIC_ASSERT( assert_v1::value || assert_v2::value );

        return detail::indexed_expression<value_type,E>(_reg_name,e());
    }

    template<class E>
    detail::indexed_expression<value_type,E> operator()( const detail::expression<E>& e ) const
    {
        typedef boost::is_same<typename E::value_type,int_type> assert_v1;
        typedef boost::is_same<typename E::value_type,uint_type> assert_v2;
        BOOST_STATIC_ASSERT( assert_v1::value || assert_v2::value );

        return detail::indexed_expression<value_type,E>(_reg_name,e());
    }
};

template<class T>
class global : public indexed_register<T>
{
public:
    global() : indexed_register<T>("g")
    {
        BOOST_STATIC_ASSERT( indexed_register<T>::value_type::type_size==4 );
    }
    ~global() {}
};

typedef variable<int_type>      int1;
typedef variable<int2_type>     int2;
typedef variable<int4_type>     int4;
typedef variable<uint_type>     uint1;
typedef variable<uint2_type>    uint2;
typedef variable<uint4_type>    uint4;
typedef variable<float_type>    float1;
typedef variable<float2_type>   float2;
typedef variable<float4_type>   float4;
typedef variable<double_type>   double1;
typedef variable<double2_type>  double2;

} // il
} // cal

#endif
