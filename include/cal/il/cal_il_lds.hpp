/*
 * C++ to IL compiler/generator lds support
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

#ifndef __CAL_IL_LDS_H
#define __CAL_IL_LDS_H

#include <boost/format.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>
#include <string>

namespace cal {
namespace il {

namespace detail {

template<class T,class E>
class lds_expression : public detail::swizzable_expression<T,lds_expression<T,E> >
{
protected:
    typedef lds_expression<T,E>                                  self_type;
    typedef detail::swizzable_expression<T,lds_expression<T,E> > base_type;
    typedef const E                                              expression_type;
    typedef typename E::const_closure_type                       expression_closure_type;

public:
    typedef T                                                    value_type;
    typedef const self_type                                      const_closure_type;
    typedef self_type                                            closure_type;
    static const int                                             temp_reg_count=1;
    static const bool                                            swizzle_has_assign=false;


protected:
    int                     lds_index;
    expression_closure_type _e;
    using base_type::index;

public:
    using base_type::resultCode;
    using base_type::operator=;

protected:
    template<class E1>
    void iEmitCode( const E1& e ) const
    {
        e.emitCode(Source::code,Source::code.stream());
        _e.emitCode(Source::code,Source::code.stream());

        switch( T::type_size ) {
        case 1:
            Source::code << boost::format("lds_store_id(%1%) %2%,%3%\n") % lds_index % _e.resultCode() % e.resultCode();
            break;
        case 2:
            if( E::value_type::type_size==1 ) Source::code << boost::format("lds_store_vec_id(%1%) mem.xy,%2%,%3%,%4%\n") % lds_index % _e.resultCode() % _e.resultCode() % e.resultCode();
            else Source::code << boost::format("lds_store_vec_id(%1%) mem.xy,%2%,%3%,%4%\n") % lds_index % detail::make_swizzle(_e.resultCode(),1,0,0,0) % detail::make_swizzle(_e.resultCode(),2,0,0,0) % e.resultCode();
            break;
        case 3:
            if( E::value_type::type_size==1 ) Source::code << boost::format("lds_store_vec_id(%1%) mem.xyz,%2%,%3%,%4%\n") % lds_index % _e.resultCode() % _e.resultCode() % e.resultCode();
            else Source::code << boost::format("lds_store_vec_id(%1%) mem.xyz,%2%,%3%,%4%\n") % lds_index % detail::make_swizzle(_e.resultCode(),1,0,0,0) % detail::make_swizzle(_e.resultCode(),2,0,0,0) % e.resultCode();
            break;
        default:
            if( E::value_type::type_size==1 ) Source::code << boost::format("lds_store_vec_id(%1%) mem.xyzw,%2%,%3%,%4%\n") % lds_index % _e.resultCode() % _e.resultCode() % e.resultCode();
            else Source::code << boost::format("lds_store_vec_id(%1%) mem.xyzw,%2%,%3%,%4%\n") % lds_index % detail::make_swizzle(_e.resultCode(),1,0,0,0) % detail::make_swizzle(_e.resultCode(),2,0,0,0) % e.resultCode();
        }
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
        std::string rout = (boost::format("r%i") % index).str();

        _e.emitCode(prg,_out);

        switch( T::type_size ) {
        case 1:
            Source::code << boost::format("lds_load_id(%1%) r%4%,%3%\n"
                                          "mov %2%,r%4%.xxxx\n") % lds_index % detail::mask_output(resultCode()) % _e.resultCode() % index;
            break;
        case 2:
            if( E::value_type::type_size==1 ) {
                Source::code << boost::format("lds_load_vec_id(%1%) r%5%.xy__,%3%,%4%\n"
                                              "mov %2%,%6%\n") % lds_index % detail::mask_output(resultCode()) % _e.resultCode() % _e.resultCode() % index % detail::match_input_to_output(resultCode(),rout+".xy");
            } else {
                Source::code << boost::format("lds_load_vec_id(%1%) r%5%.xy__,%3%,%4%\n"
                                              "mov %2%,%6%\n") % lds_index % detail::mask_output(resultCode()) % detail::make_swizzle(_e.resultCode(),1,0,0,0) % detail::make_swizzle(_e.resultCode(),2,0,0,0) % index % detail::match_input_to_output(resultCode(),rout+".xy");
            }
            break;
        case 3:
            if( E::value_type::type_size==1 ) {
                Source::code << boost::format("lds_load_vec_id(%1%) r%5%.xyz_,%3%,%4%\n"
                                              "mov %2%,%6%\n") % lds_index % detail::mask_output(resultCode()) % _e.resultCode() % _e.resultCode() % index % detail::match_input_to_output(resultCode(),rout+".xyz");
            } else {
                Source::code << boost::format("lds_load_vec_id(%1%) r%5%.xyz_,%3%,%4%\n"
                                              "mov %2%,%6%\n") % lds_index % detail::mask_output(resultCode()) % detail::make_swizzle(_e.resultCode(),1,0,0,0) % detail::make_swizzle(_e.resultCode(),2,0,0,0) % index % detail::match_input_to_output(resultCode(),rout+".xyz");
            }
        default:
            if( E::value_type::type_size==1 ) {
                Source::code << boost::format("lds_load_vec_id(%1%) r%5%.xyzw,%3%,%4%\n"
                                              "mov %2%,%6%\n") % lds_index % detail::mask_output(resultCode()) % _e.resultCode() % _e.resultCode() % index % detail::match_input_to_output(resultCode(),rout+".xyzw");
            } else {
                Source::code << boost::format("lds_load_vec_id(%1%) r%5%.xyzw,%3%,%4%\n"
                                              "mov %2%,%6%\n") % lds_index % detail::mask_output(resultCode()) % detail::make_swizzle(_e.resultCode(),1,0,0,0) % detail::make_swizzle(_e.resultCode(),2,0,0,0) % index % detail::match_input_to_output(resultCode(),rout+".xyzw");
            }
        }
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

    template<class E1>
    void emit_atomic( const std::string& src, const E1& e1 ) const
    {
        e1.emitCode(Source::code,Source::code.stream());
        _e.emitCode(Source::code,Source::code.stream());
        Source::code << boost::format(src) % lds_index % _e.resultCode() % e1.resultCode();
    }

    template<class E1,class E2>
    void emit_atomic( const std::string& src, const E1& e1, const E2& e2 ) const
    {
        e1.emitCode(Source::code,Source::code.stream());
        e2.emitCode(Source::code,Source::code.stream());
        _e.emitCode(Source::code,Source::code.stream());
        Source::code << boost::format(src) % lds_index % _e.resultCode() % e1.resultCode() % e2.resultCode();
    }

    template<class E1,class E2,class E3>
    void emit_atomic( const std::string& src, const E1& e1, const E2& e2, const E3& e3 ) const
    {
        e1.emitCode(Source::code,Source::code.stream());
        e2.emitCode(Source::code,Source::code.stream());
        e3.emitCode(Source::code,Source::code.stream());
        _e.emitCode(Source::code,Source::code.stream());
        Source::code << boost::format(src) % lds_index % _e.resultCode() % e1.resultCode() % e2.resultCode() % e3.resultCode();
    }
};

template<class T,class E1,class E2>
class lds2_expression : public detail::swizzable_expression<T,lds2_expression<T,E1,E2> >
{
protected:
    typedef lds2_expression<T,E1,E2>                                    self_type;
    typedef detail::swizzable_expression<T,lds2_expression<T,E1,E2> >   base_type;
    typedef const E1                                                    expression1_type;
    typedef typename E1::const_closure_type                             expression1_closure_type;
    typedef const E2                                                    expression2_type;
    typedef typename E2::const_closure_type                             expression2_closure_type;

public:
    typedef T                                                           value_type;
    typedef const self_type                                             const_closure_type;
    typedef self_type                                                   closure_type;
    static const int                                                    temp_reg_count=2;
    static const bool                                                   swizzle_has_assign=false;

protected:
    int                         lds_index;
    expression1_closure_type    _e1;
    expression2_closure_type    _e2;
    using base_type::index;

public:
    using base_type::resultCode;
    using base_type::operator=;

protected:
    template<class E>
    void iEmitCode( const E& e ) const
    {
        e.emitCode(Source::code,Source::code.stream());
        _e1.emitCode(Source::code,Source::code.stream());
        _e2.emitCode(Source::code,Source::code.stream());

        switch(T::type_size) {
        case 1:
            Source::code << boost::format("mov r%5%.x___,%2%\n"
                                          "mov r%5%._y__,%3%\n"
                                          "lds_store_id(%1%) r%5%,%4%\n") % lds_index % _e1.resultCode() % _e2.resultCode() % e.resultCode() % index;
            break;
        case 2:
            Source::code << boost::format("lds_store_vec_id(%1%) mem.xy__,%2%,%3%,%4%\n") % lds_index % _e1.resultCode() % _e2.resultCode() % e.resultCode();
            break;
        case 3:
            Source::code << boost::format("lds_store_vec_id(%1%) mem.xyz_,%2%,%3%,%4%\n") % lds_index % _e1.resultCode() % _e2.resultCode() % e.resultCode();
            break;
        default:
            Source::code << boost::format("lds_store_vec_id(%1%) mem.xyzw,%2%,%3%,%4%\n") % lds_index % _e1.resultCode() % _e2.resultCode() % e.resultCode();
        }
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
        std::string rout = (boost::format("r%i") % index).str();

        _e1.emitCode(prg,_out);
        _e2.emitCode(prg,_out);

        switch(T::type_size) {
        case 1:
            Source::code << boost::format("mov r%5%.x___,%3%\n"
                                          "mov r%5%._y__,%4%\n"
                                          "lds_load_id(%1%) r%6%,r%5%\n"
                                          "mov %2%,r%6%.xxxx\n") % lds_index % detail::mask_output(resultCode()) % _e1.resultCode() % _e2.resultCode() % index % (index+1);
            break;
        case 2:
            Source::code << boost::format("lds_load_vec_id(%1%) r%5%.xy__,%3%,%4%\n"
                                          "mov %2%,%6%\n") % lds_index % detail::mask_output(resultCode()) % _e1.resultCode() % _e2.resultCode() % index % detail::match_input_to_output(resultCode(),rout+".xy");
            break;
        case 3:
            Source::code << boost::format("lds_load_vec_id(%1%) r%5%.xyz_,%3%,%4%\n"
                                          "mov %2%,%6%\n") % lds_index % detail::mask_output(resultCode()) % _e1.resultCode() % _e2.resultCode() % index % detail::match_input_to_output(resultCode(),rout+".xyz");
            break;
        default:
            Source::code << boost::format("lds_load_vec_id(%1%) r%5%.xyzw,%3%,%4%\n"
                                          "mov %2%,%6%\n") % lds_index % detail::mask_output(resultCode()) % _e1.resultCode() % _e2.resultCode() % index % detail::match_input_to_output(resultCode(),rout+".xyzw");
        }
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

    template<class P1>
    void emit_atomic( const std::string& src, const P1& e1 ) const
    {
        std::string tmp((boost::format("r%") % index).str());
        e1.emitCode(Source::code,Source::code.stream());
        _e1.emitCode(Source::code,Source::code.stream());
        _e2.emitCode(Source::code,Source::code.stream());
        Source::code << boost::format("mov %1%.x___,%2%\nmov r%1%._y__,%3%\n") % tmp % _e1.resultCode() % _e2.resultCode();
        Source::code << boost::format(src) % lds_index % tmp % e1.resultCode();
    }

    template<class P1,class P2>
    void emit_atomic( const std::string& src, const P1& e1, const P2& e2 ) const
    {
        std::string tmp((boost::format("r%") % index).str());
        e1.emitCode(Source::code,Source::code.stream());
        e2.emitCode(Source::code,Source::code.stream());
        _e1.emitCode(Source::code,Source::code.stream());
        _e2.emitCode(Source::code,Source::code.stream());
        Source::code << boost::format("mov %1%.x___,%2%\nmov r%1%._y__,%3%\n") % tmp % _e1.resultCode() % _e2.resultCode();
        Source::code << boost::format(src) % lds_index % tmp % e1.resultCode() % e2.resultCode();
    }

    template<class P1,class P2,class P3>
    void emit_atomic( const std::string& src, const P1& e1, const P2& e2, const P3& e3 ) const
    {
        std::string tmp((boost::format("r%") % index).str());
        e1.emitCode(Source::code,Source::code.stream());
        e2.emitCode(Source::code,Source::code.stream());
        e3.emitCode(Source::code,Source::code.stream());
        _e1.emitCode(Source::code,Source::code.stream());
        _e2.emitCode(Source::code,Source::code.stream());
        Source::code << boost::format("mov %1%.x___,%2%\nmov r%1%._y__,%3%\n") % tmp % _e1.resultCode() % _e2.resultCode();
        Source::code << boost::format(src) % lds_index % tmp % e1.resultCode() % e2.resultCode() % e3.resultCode();
    }
};


} // detail

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

} // il
} // cal

#endif
