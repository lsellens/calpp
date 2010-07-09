/*
 * C++ to IL compiler/generator top level types
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

#ifndef __CAL_IL_TYPES_H
#define __CAL_IL_TYPES_H

#include <boost/format.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>
#include <cal/il/cal_il_source.hpp>
#include <cal/il/cal_il_swizzle.hpp>
#include <cal/il/cal_il_expression_swizzle.hpp>

namespace cal {
namespace il {

namespace detail {

template<class T,class E,int DIM>
class input_expression : public detail::swizzable_expression<input_expression<T,E,DIM> >
{
protected:
    typedef input_expression<T,E,DIM>                                   self_type;
    typedef detail::swizzable_expression< input_expression<T,E,DIM> >   base_type;
    typedef const E                                                     expression_type;
    typedef typename E::const_closure_type                              expression_closure_type;

public:
    typedef T                                                           value_type;    
    typedef const self_type                                             const_closure_type;
    typedef self_type                                                   closure_type;
    static const int                                                    temp_reg_count=0;
    static const bool                                                   swizzle_has_assign=false;

protected:
    int                     input_index;
    int                     xoffset,yoffset;
    int                     sampler;
    expression_closure_type _e;
    using base_type::index;

public:
    using base_type::resultCode;

public:
    input_expression( int idx, const E& e, int x=0, int y=0, int s=-1 ) : base_type(), input_index(idx), xoffset(x), yoffset(y), sampler(s), _e(e)
    {
    }
    input_expression( const input_expression<T,E,DIM>& rhs ) : base_type(rhs), input_index(rhs.input_index), xoffset(rhs.xoffset), yoffset(rhs.yoffset), sampler(rhs.sampler), _e(rhs._e)
    {
    }
    ~input_expression()
    {
    }

    void emitCode( Source& prg, std::ostream& _out ) const
    {
        _e.emitCode(prg,_out);

        int s = sampler>=0?sampler:input_index;
        if( xoffset!=0 || yoffset!=0 ) _out << boost::format("sample_resource(%1%)_sampler(%2%)_aoffimmi(%3%,%4%,0) %5%,%6%\n") % input_index % s % xoffset % yoffset % resultCode() % _e.resultCode();
        else _out << boost::format("sample_resource(%1%)_sampler(%2%) %3%,%4%\n") % input_index % s % resultCode() % _e.resultCode();
    }
};

template<class T,class E>
class indexed_expression : public detail::swizzable_expression<indexed_expression<T,E> >
{
protected:
    typedef indexed_expression<T,E>                                 self_type;
    typedef detail::swizzable_expression<indexed_expression<T,E> >  base_type;
    typedef const E                                                 expression_type;
    typedef typename E::const_closure_type                          expression_closure_type;
        
public:
    typedef T                                                       value_type;
    typedef const self_type                                         const_closure_type;
    typedef self_type                                               closure_type;
    static const int                                                temp_reg_count=0;
    static const bool                                               swizzle_has_assign=true;

protected:
    expression_closure_type _e;
    std::string             _reg_name;
    using base_type::index;

protected:
    template<class E1>
    void iEmitCode( const E1& e ) const
    {
        e.emitCode(Source::code,Source::code.stream());
        emitCode(Source::code,Source::code.stream());
        Source::code << boost::format("mov %s,%s\n") % resultCode() % e.resultCode();
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

    void emitCode( Source& prg, std::ostream& _out ) const
    {
        _e.emitCode(prg,_out);
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

template<class T,class E>
class lds_expression : public detail::swizzable_expression<lds_expression<T,E> >
{
protected:
    typedef lds_expression<T,E>                                 self_type;
    typedef detail::swizzable_expression< lds_expression<T,E> > base_type;
    typedef const E                                             expression_type;
    typedef typename E::const_closure_type                      expression_closure_type;
        
public:
    typedef T                                                   value_type;
    typedef const self_type                                     const_closure_type;
    typedef self_type                                           closure_type;
    static const int                                            temp_reg_count=0;
    static const bool                                           swizzle_has_assign=false;

protected:
    int                     lds_index;
    expression_closure_type _e;
    using base_type::index;

public:
    using base_type::resultCode;

protected:
    template<class E1>
    void iEmitCode( const E1& e ) const
    {
        e.emitCode(Source::code,Source::code.stream());
        _e.emitCode(Source::code,Source::code.stream());

        if( T::type_size>1 ) {
            if( E::value_type::type_size==1 ) Source::code << boost::format("lds_store_vec_id(%1%) mem.xyzw,%2%,%3%,%4%\n") % lds_index % _e.resultCode() % _e.resultCode() % e.resultCode();
            else Source::code << boost::format("lds_store_vec_id(%1%) mem.xyzw,%2%,%3%,%4%\n") % lds_index % detail::make_swizzle(_e.resultCode(),1,0,0,0) % detail::make_swizzle(_e.resultCode(),2,0,0,0) % e.resultCode();        
        } else Source::code << boost::format("lds_store_id(%1%) %2%,%3%\n") % lds_index % _e.resultCode() % e.resultCode();
    }

public:
    lds_expression( int idx, const E& e ) : base_type(), lds_index(idx), _e(e)
    {
    }
    lds_expression( const lds_expression<T,E>& rhs ) : base_type(rhs), lds_index(rhs.lds_index), _e(rhs._e)
    {
    }
    ~lds_expression()
    {
    }

    void emitCode( Source& prg, std::ostream& _out ) const
    {
        _e.emitCode(prg,_out);
        
        if( T::type_size>1 ) {
            if( E::value_type::type_size==1 ) Source::code << boost::format("lds_load_vec_id(%1%) %2%,%3%,%4%\n") % lds_index % resultCode() % _e.resultCode() % _e.resultCode();
            else Source::code << boost::format("lds_load_vec_id(%1%) %2%,%3%,%4%\n") % lds_index % resultCode() % detail::make_swizzle(_e.resultCode(),1,0,0,0) % detail::make_swizzle(_e.resultCode(),2,0,0,0);
        } else Source::code << boost::format("lds_load_id(%1%) %2%,%3%\n") % lds_index % resultCode() % _e.resultCode();
    }

    lds_expression<T,E>& operator=( const lds_expression<T,E>& v )
    {
        iEmitCode(v);
        return *this;
    }
    
    const lds_expression<T,E>& operator=( const lds_expression<T,E>& v ) const
    {
        iEmitCode(v);
        return *this;
    }    

    template<class E1>
    lds_expression<T,E>& operator=( const detail::expression<E1>& e )
    {
        typedef boost::is_same<typename E1::value_type,value_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );        
        iEmitCode(e());
        return *this;
    }

    template<class E1>
    const lds_expression<T,E>& operator=( const detail::expression<E1>& e ) const
    {
        typedef boost::is_same<typename E1::value_type,value_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );        
        iEmitCode(e());
        return *this;
    }        
};

template<class T,class E1,class E2>
class lds2_expression : public detail::swizzable_expression<lds2_expression<T,E1,E2> >
{
protected:
    typedef lds2_expression<T,E1,E2>                                    self_type;
    typedef detail::swizzable_expression< lds2_expression<T,E1,E2> >    base_type;
    typedef const E1                                                    expression1_type;
    typedef typename E1::const_closure_type                             expression1_closure_type;
    typedef const E2                                                    expression2_type;
    typedef typename E2::const_closure_type                             expression2_closure_type;
        
        
public:
    typedef T                                                   value_type;
    typedef const self_type                                     const_closure_type;
    typedef self_type                                           closure_type;
    static const int                                            temp_reg_count=1;
    static const bool                                           swizzle_has_assign=false;

protected:
    int                         lds_index;
    expression1_closure_type    _e1;
    expression2_closure_type    _e2;
    using base_type::index;

public:
    using base_type::resultCode;

protected:
    template<class E>
    void iEmitCode( const E& e ) const
    {
        e.emitCode(Source::code,Source::code.stream());
        _e1.emitCode(Source::code,Source::code.stream());
        _e2.emitCode(Source::code,Source::code.stream());
        
        if( T::type_size==1 ) {            
            Source::code << boost::format("mov r%5%.x,%2%\n"
                                           "mov r%5%.y,%3%\n"
                                           "lds_store_id(%1%) r%5%,%4%\n") % lds_index % _e1.resultCode() % _e2.resultCode() % e.resultCode() % index;
        } else Source::code << boost::format("lds_store_vec_id(%1%) mem.xyzw,%2%,%3%,%4%\n") % lds_index % _e1.resultCode() % _e2.resultCode() % e.resultCode();
    }
                        
public:
    lds2_expression( int idx, const E1& e1, const E2& e2 ) : base_type(), lds_index(idx), _e1(e1), _e2(e2)
    {
    }
    lds2_expression( const lds2_expression<T,E1,E2>& rhs ) : base_type(rhs), lds_index(rhs.lds_index), _e1(rhs._e1), _e2(rhs._e2)
    {
    }
    ~lds2_expression()
    {
    }

    void emitCode( Source& prg, std::ostream& _out ) const
    {
        _e1.emitCode(prg,_out);
        _e2.emitCode(prg,_out);
        
        if( T::type_size==1 ) {            
            Source::code << boost::format("mov r%5%.x,%3%\n"
                                           "mov r%5%.y,%4%\n"
                                           "lds_load_id(%1%) %2%,r\n") % lds_index % resultCode() % _e1.resultCode() % _e2.resultCode() % index;            
        } else Source::code << boost::format("lds_load_vec_id(%1%) %2%,%3%,%4%\n") % lds_index % resultCode() % _e1.resultCode() % _e2.resultCode();
    }

    lds2_expression<T,E1,E2>& operator=( const lds2_expression<T,E1,E2>& v )
    {
        iEmitCode(v);
        return *this;
    }
    
    const lds2_expression<T,E1,E2>& operator=( const lds2_expression<T,E1,E2>& v ) const
    {
        iEmitCode(v);
        return *this;
    }    

    template<class E>
    lds2_expression<T,E1,E2>& operator=( const detail::expression<E>& e )
    {
        typedef boost::is_same<typename E::value_type,value_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );        
        iEmitCode(e());
        return *this;
    }

    template<class E>
    const lds2_expression<T,E1,E2>& operator=( const detail::expression<E>& e ) const
    {
        typedef boost::is_same<typename E::value_type,value_type> assert_value;
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

    void emitCode( Source& prg, std::ostream& _out ) const
    {
        _e.emitCode(prg,_out);
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
class value : public detail::swizzable_expression<value<T> >
{
protected:
    typedef value<T>                                  self_type;
    typedef detail::swizzable_expression< value<T> >  base_type;
    
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

    void emitCode( Source& prg, std::ostream& _out ) const
    {        
    }

    std::string resultCode() const
    {
        int     idx = Source::code.getLiteral( _data.hex );
        return detail::make_swizzle( (boost::format("l%i") % idx).str(), value_type::type_size );
    }    
};
              
template<class T>
class variable : public detail::swizzable_expression< variable<T> >
{
protected:
    typedef variable<T>                                 self_type;
    typedef detail::swizzable_expression< variable<T> > base_type;
    
public:
    typedef typename detail::base_cal_type<T>::value    value_type;
    typedef detail::variable_clone<self_type>           closure_type;
    typedef const closure_type                          const_closure_type;
    
    static const int                                    temp_reg_count=0;
    static const bool                                   swizzle_has_assign=true;
    
protected:
    typedef typename value_type::component_type         component_type;
    typedef union data_type_union { boost::array<component_type,value_type::component_count> base; boost::array<boost::uint32_t,4> hex; } data_type;
    
protected:
    using base_type::index;

public:
    using base_type::resultCode;

protected:
    template<class E>
    void iEmitCode( const E& e ) const
    {        
        e.emitCode(Source::code,Source::code.stream());
        Source::code << boost::format("mov %s,%s\n") % resultCode() % e.resultCode();
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

    void clone( const variable<T>& rhs ) 
    {
        index     = rhs.index;
    }

    ~variable()
    {
    }

    void emitCode( Source& prg, std::ostream& _out ) const
    {
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

    template<class E>
    variable<T>& operator+=( const detail::expression<E>& e )
    {
        (*this) = (*this) + e();        
        return *this;
    }

    template<class E>
    variable<T>& operator-=( const detail::expression<E>& e )
    {
        (*this) = (*this) - e();
        return *this;
    }

    template<class E>
    variable<T>& operator*=( const detail::expression<E>& e )
    {
        (*this) = (*this) * e();
        return *this;
    }

    template<class E>
    variable<T>& operator/=( const detail::expression<E>& e )
    {
        (*this) = (*this) / e();
        return *this;
    }

    template<class E>
    variable<T>& operator%=( const detail::expression<E>& e )
    {
        (*this) = (*this) % e();
        return *this;
    }

    template<class E>
    variable<T>& operator&=( const detail::expression<E>& e )
    {
        (*this) = (*this) & e();
        return *this;
    }

    template<class E>
    variable<T>& operator|=( const detail::expression<E>& e )
    {
        (*this) = (*this) | e();
        return *this;
    }
};

template<class T>
class named_variable : public detail::swizzable_expression< named_variable<T> >
{
protected:
    typedef named_variable<T>                                   self_type;
    typedef detail::swizzable_expression< named_variable<T> >   base_type;

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
        e.emitCode(Source::code,Source::code.stream());
        Source::code << boost::format("mov %s,%s\n") % detail::mask_output(resultCode()) % detail::match_input_to_output(resultCode(),e.resultCode());
    }

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

    void emitCode( Source& prg, std::ostream& _out ) const
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

    template<class E>
    named_variable<T>& operator+=( const detail::expression<E>& e )
    {
        (*this) = (*this) + e();        
        return *this;
    }

    template<class E>
    named_variable<T>& operator-=( const detail::expression<E>& e )
    {
        (*this) = (*this) - e();
        return *this;
    }

    template<class E>
    named_variable<T>& operator*=( const detail::expression<E>& e )
    {
        (*this) = (*this) * e();
        return *this;
    }

    template<class E>
    named_variable<T>& operator/=( const detail::expression<E>& e )
    {
        (*this) = (*this) / e();
        return *this;
    }

    template<class E>
    named_variable<T>& operator%=( const detail::expression<E>& e )
    {
        (*this) = (*this) % e();
        return *this;
    }

    template<class E>
    named_variable<T>& operator&=( const detail::expression<E>& e )
    {
        (*this) = (*this) & e();
        return *this;
    }

    template<class E>
    named_variable<T>& operator|=( const detail::expression<E>& e )
    {
        (*this) = (*this) | e();
        return *this;
    }
};

template<class T>
class input1d
{
public:
    typedef typename detail::base_cal_type<T>::value    value_type;

protected:
    int     input_index;
    int     input_sampler;

public:
    input1d( int idx, int s=-1 ) 
    {
        input_index = idx;
        input_sampler = s;
        Source::code.registerInput(input_index,2,value_type::type_size);
    }

    template<class E>
    detail::input_expression<value_type,E,1> operator[]( const detail::expression<E>& e ) const
    {
        typedef boost::is_same<typename E::value_type,float_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );

        return detail::input_expression<value_type,E,1>(input_index,e(),0,0,input_sampler);
    }

    input1d<T> operator()( int s ) const
    {
        return input1d<T>(input_index,s);
    }

    template<class E>
    detail::input_expression<value_type,E,1> operator()( const detail::register_address<E>& a ) const
    {
        typedef boost::is_same<typename E::value_type,float_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );

        return detail::input_expression<value_type,E,1>(input_index,a._e,a._offset,0,input_sampler);
    }

    template<class E>
    detail::input_expression<value_type,E,1> operator()( const detail::expression<E>& e ) const
    {
        typedef boost::is_same<typename E::value_type,float_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );

        return detail::input_expression<value_type,E,1>(input_index,e(),0,0,input_sampler);
    }
};

template<class T>
class input2d
{
public:
    typedef typename detail::base_cal_type<T>::value    value_type;

protected:
    int     input_index;
    int     input_sampler;

public:
    input2d( int idx, int s=-1 )
    {
        input_index = idx;
        input_sampler = s;
        Source::code.registerInput(input_index,2,value_type::type_size);
    }

    template<class E>
    detail::input_expression<value_type,E,2> operator[]( const detail::expression<E>& e ) const
    {
        typedef boost::is_same<typename E::value_type,float2_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );

        return detail::input_expression<value_type,E,2>(input_index,e(),0,0,input_sampler);
    }

    input2d<T> operator()( int s ) const
    {
        return input2d<T>(input_index,s);
    }

    template<class E1,class E2>
    detail::input_expression<value_type,detail::binary<E1,E2,detail::cal_binary_cast<typename E1::value_type,typename E2::value_type> >,2> 
    operator()( const detail::expression<E1>& x, const detail::expression<E2>& y ) const
    {
        typedef detail::input_expression<value_type,detail::binary<E1,E2,detail::cal_binary_cast<typename E1::value_type,typename E2::value_type> >,2> expression_type;

        typedef boost::is_same<typename detail::cal_binary_cast<typename E1::value_type,typename E2::value_type>::value_type,float2_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );

        return expression_type(input_index,merge_types(x(),y()),0,0,input_sampler);
    }

    template<class E1,class E2>
    detail::input_expression<value_type, detail::binary<typename E1::closure_type,typename E2::closure_type, detail::cal_binary_cast<typename E1::value_type,typename E2::value_type> >, 2> 
    operator()( const detail::register_address<E1>& x, const detail::register_address<E2>& y ) const
    {
        typedef detail::input_expression<value_type, detail::binary<typename E1::closure_type,typename E2::closure_type, detail::cal_binary_cast<typename E1::value_type,typename E2::value_type> >, 2> expression_type;

        typedef boost::is_same<typename detail::cal_binary_cast<typename E1::value_type,typename E2::value_type>::value_type,float2_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );

        return expression_type(input_index,merge_types(x._e,y._e),x._offset,y._offset,input_sampler);
    }

    template<class E1,class E2>
    detail::input_expression<value_type, detail::binary<E1,typename E2::closure_type, detail::cal_binary_cast<typename E1::value_type,typename E2::value_type> >, 2> 
    operator()( const detail::expression<E1>& x, const detail::register_address<E2>& y ) const
    {
        typedef detail::input_expression<value_type, detail::binary<E1,typename E2::closure_type, detail::cal_binary_cast<typename E1::value_type,typename E2::value_type> >, 2> expression_type;

        typedef boost::is_same<typename detail::cal_binary_cast<typename E1::value_type,typename E2::value_type>::value_type,float2_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );

        return expression_type(input_index,merge_types(x(),y._e),0,y._offset,input_sampler);
    }

    template<class E1,class E2>
    detail::input_expression<value_type, detail::binary<typename E1::closure_type, E2, detail::cal_binary_cast<typename E1::value_type,typename E2::value_type> >, 2> 
    operator()( const detail::register_address<E1>& x, const detail::expression<E2>& y ) const
    {
        typedef detail::input_expression<value_type, detail::binary<typename E1::closure_type, E2, detail::cal_binary_cast<typename E1::value_type,typename E2::value_type> >, 2> expression_type;

        typedef boost::is_same<typename detail::cal_binary_cast<typename E1::value_type,typename E2::value_type>::value_type,float2_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );

        return expression_type(input_index,merge_types(x._e,y()),x._offset,0,input_sampler);
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
    detail::indexed_expression<value_type,detail::register_address<E> > operator[]( const detail::register_address<E>& e ) const
    {
        return detail::indexed_expression<value_type,detail::register_address<E> >(_reg_name,e);
    }

    template<class E>
    detail::indexed_expression<value_type,detail::register_address<E> > operator()( const detail::register_address<E>& e ) const
    {
        return detail::indexed_expression<value_type,detail::register_address<E> >(_reg_name,e);
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

template<class T>
class lds
{
public:
    typedef typename detail::base_cal_type<T>::value    value_type;

protected:
    int     lds_index;

public:
    lds( int idx )
    {
        BOOST_STATIC_ASSERT( value_type::type_size==1 || value_type::type_size==4 );
        lds_index = idx;
    }

    template<class E>        
    detail::lds_expression<value_type,E> operator[]( const detail::expression<E>& e ) const
    {
        typedef boost::is_same<typename E::value_type,uint_type>    assert_v1;
        typedef boost::is_same<typename E::value_type,int_type>     assert_v2;
        typedef boost::is_same<typename E::value_type,uint2_type>   assert_v3;
        typedef boost::is_same<typename E::value_type,int2_type>    assert_v4;
        
        BOOST_STATIC_ASSERT( assert_v1::value || assert_v2::value || assert_v3::value || assert_v4::value );
        
        return detail::lds_expression<value_type,E>(lds_index,e());
    }

    template<class E>        
    detail::lds_expression<value_type,E> operator()( const detail::expression<E>& e ) const
    {
        typedef boost::is_same<typename E::value_type,uint_type>    assert_v1;
        typedef boost::is_same<typename E::value_type,int_type>     assert_v2;
        typedef boost::is_same<typename E::value_type,uint2_type>   assert_v3;
        typedef boost::is_same<typename E::value_type,int2_type>    assert_v4;
        
        BOOST_STATIC_ASSERT( assert_v1::value || assert_v2::value || assert_v3::value || assert_v4::value );
        
        return detail::lds_expression<value_type,E>(lds_index,e());
    }

    template<class E1,class E2>        
    detail::lds2_expression<value_type,E1,E2> operator()( const detail::expression<E1>& idx, const detail::expression<E2>& offset ) const
    {
        typedef detail::lds2_expression<value_type,E1,E2> expression_type;
        typedef boost::is_same<typename E1::value_type,uint_type>    assert_v1;
        typedef boost::is_same<typename E1::value_type,int_type>     assert_v2;
        typedef boost::is_same<typename E2::value_type,uint_type>    assert_v3;
        typedef boost::is_same<typename E2::value_type,int_type>     assert_v4;
        
        BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && (assert_v3::value || assert_v4::value) );
        
        return expression_type(lds_index,idx(),offset());
    }

    template<class E1>
    detail::lds2_expression<value_type,E1,value<uint_type> > operator()( const detail::expression<E1>& idx, int offset ) const
    {
        typedef detail::lds2_expression<value_type,E1,value<uint_type> > expression_type;
        typedef boost::is_same<typename E1::value_type,uint_type>    assert_v1;
        typedef boost::is_same<typename E1::value_type,int_type>     assert_v2;
        
        BOOST_STATIC_ASSERT( assert_v1::value || assert_v2::value );
        
        return expression_type(lds_index,idx(),value<uint_type>(offset));
    }        
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
