/*
 * C++ to IL compiler/generator uav support
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

#ifndef __CAL_IL_UAV_H
#define __CAL_IL_UAV_H

#include <boost/format.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>
#include <boost/bind.hpp>

namespace cal {
namespace il {

enum CALuavcacheflags {
    UAV_AUTO_CACHE,
    UAV_UNCACHED,
    UAV_CACHED    
};

namespace detail {

template<class T,class E,class C>
class uav_expression_base : public detail::swizzable_expression<T,C>
{
protected:
    typedef uav_expression_base<T,E,C>         self_type;
    typedef detail::swizzable_expression<T,C > base_type;
    typedef const E                            expression_type;
    typedef typename E::const_closure_type     expression_closure_type;

protected:
    int                     uav_index;
    int                     uav_caching;

    expression_closure_type _e;
    using base_type::index;

public:
    using base_type::resultCode;
    using base_type::operator=;

public:
    uav_expression_base( int idx, int caching, const E& e ) : base_type(), uav_index(idx), uav_caching(caching), _e(e) {}
    uav_expression_base( const uav_expression_base<T,E,C>& rhs ) : base_type(rhs), uav_index(rhs.uav_index), uav_caching(rhs.uav_caching), _e(rhs._e) {}
    ~uav_expression_base() {}

    template<class E1>
    void emit_atomic( const std::string& src, const E1& e1 ) const
    {
        e1.emitCode();
        _e.emitCode();
        Source::code() << boost::format(src) % uav_index % _e.resultCode() % e1.resultCode();
    }

    template<class E1,class E2>
    void emit_atomic( const std::string& src, const E1& e1, const E2& e2 ) const
    {
        e1.emitCode();
        e2.emitCode();
        _e.emitCode();
        Source::code() << boost::format(src) % uav_index % _e.resultCode() % e1.resultCode() % e2.resultCode();
    }

    template<class E1,class E2,class E3>
    void emit_atomic( const std::string& src, const E1& e1, const E2& e2, const E3& e3 ) const
    {
        e1.emitCode();
        e2.emitCode();
        e3.emitCode();
        _e.emitCode();
        Source::code() << boost::format(src) % uav_index % _e.resultCode() % e1.resultCode() % e2.resultCode() % e3.resultCode();
    }
};

template<class T,class E>
class uav_expression : public uav_expression_base<T,E,uav_expression<T,E> >
{
protected:
    typedef uav_expression<T,E>                           self_type;
    typedef uav_expression_base<T,E,uav_expression<T,E> > base_type;
    typedef const E                                       expression_type;
    typedef typename E::const_closure_type                expression_closure_type;

public:
    typedef T                                             value_type;
    typedef const self_type                               const_closure_type;
    typedef self_type                                     closure_type;
    static const int                                      temp_reg_count=1;
    static const bool                                     swizzle_has_assign=false;

protected:
    std::string             uav_load;
    std::string             uav_store;

    using base_type::uav_index;
    using base_type::uav_caching;
    using base_type::_e;
    using base_type::index;

public:
    using base_type::resultCode;
    using base_type::operator=;

protected:
    template<class E1>
    void iEmitCode( const E1& e ) const
    {
        e.emitCode();
        _e.emitCode();

        switch( T::type_size ) {
        case 1:
            Source::code() << boost::format("%4%(%1%) mem.x,%2%,%3%\n") %  uav_index % _e.resultCode() % e.resultCode() % uav_store;
            break;
        case 2:
            Source::code() << boost::format("%4%(%1%) mem.xy,%2%,%3%\n") %  uav_index % _e.resultCode() % e.resultCode() % uav_store;
            break;
        case 3:
            Source::code() << boost::format("%4%(%1%) mem.xyz,%2%,%3%\n") %  uav_index % _e.resultCode() % e.resultCode() % uav_store;
            break;
        default:
            Source::code() << boost::format("%4%(%1%) mem.xyzw,%2%,%3%\n") %  uav_index % _e.resultCode() % e.resultCode() % uav_store;
        }
    }

public:
    uav_expression( int idx, int caching, const std::string& load, const std::string& store, const E& e ) : base_type(idx,caching,e), uav_load(load), uav_store(store)
    {
    }
    uav_expression( const uav_expression<T,E>& rhs ) : base_type(rhs), uav_load(rhs.uav_load), uav_store(rhs.uav_store)
    {
    }
    ~uav_expression()
    {
    }

    void emitCode() const
    {
        std::string rout = (boost::format("r%i") % index).str();
        std::string caching;
        
        if( uav_caching==UAV_CACHED   ) caching = "_cached";
        if( uav_caching==UAV_UNCACHED ) caching = "_uncached";

        _e.emitCode();

        switch( T::type_size ) {
        case 1:
            Source::code() << boost::format("%6%(%1%)%7% r%4%.x___,%3%\n"
                                           "mov %2%,%5%\n") % uav_index % detail::mask_output(resultCode()) % _e.resultCode() % index % detail::match_input_to_output(resultCode(),rout+".x") % uav_load % caching;
            break;
        case 2:
            Source::code() << boost::format("%6%(%1%)%7% r%4%.xy__,%3%\n"
                                           "mov %2%,%5%\n") % uav_index % detail::mask_output(resultCode()) % _e.resultCode() % index % detail::match_input_to_output(resultCode(),rout+".xy") % uav_load % caching;
            break;
        case 3:
            Source::code() << boost::format("%6%(%1%)%7% r%4%.xyz_,%3%\n"
                                           "mov %2%,%5%\n") % uav_index % detail::mask_output(resultCode()) % _e.resultCode() % index % detail::match_input_to_output(resultCode(),rout+".xyz") % uav_load % caching;
            break;
        default:
            Source::code() << boost::format("%6%(%1%)%7% r%4%.xyzw,%3%\n"
                                           "mov %2%,%5%\n") % uav_index % detail::mask_output(resultCode()) % _e.resultCode() % index % detail::match_input_to_output(resultCode(),rout+".xyzw") % uav_load % caching;
            break;
        }
    }

    uav_expression<T,E>& operator=( const uav_expression<T,E>& v )
    {
        iEmitCode(v);
        return *this;
    }

    const uav_expression<T,E>& operator=( const uav_expression<T,E>& v ) const
    {
        iEmitCode(v);
        return *this;
    }

    template<class E1>
    uav_expression<T,E>& operator=( const detail::expression<E1>& e )
    {
        typedef boost::is_same<typename E1::value_type,value_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );
        iEmitCode(e());
        return *this;
    }

    template<class E1>
    const uav_expression<T,E>& operator=( const detail::expression<E1>& e ) const
    {
        typedef boost::is_same<typename E1::value_type,value_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );
        iEmitCode(e());
        return *this;
    }
};

template<class T,class E>
class uav_typed_expression : public uav_expression_base<T,E,uav_typed_expression<T,E> >
{
protected:
    typedef uav_typed_expression<T,E>                           self_type;
    typedef uav_expression_base<T,E,uav_typed_expression<T,E> > base_type;
    typedef const E                                             expression_type;
    typedef typename E::const_closure_type                      expression_closure_type;

public:
    typedef T                                                   value_type;
    typedef const self_type                                     const_closure_type;
    typedef self_type                                           closure_type;
    static const int                                            temp_reg_count=1;
    static const bool                                           swizzle_has_assign=false;

protected:
    using base_type::uav_index;
    using base_type::uav_caching;
    using base_type::_e;
    using base_type::index;

public:
    using base_type::resultCode;
    using base_type::operator=;

protected:
    template<class E1>
    void iEmitCode( const E1& e ) const
    {
        e.emitCode();
        _e.emitCode();

        switch( T::type_size ) {
        case 1:
            Source::code() << boost::format("uav_store_id(%1%) %2%,%3%\n") %  uav_index % _e.resultCode() % e.resultCode();
            break;
        case 2:
            Source::code() << boost::format("uav_store_id(%1%) %2%,%3%\n") %  uav_index % _e.resultCode() % e.resultCode();
            break;
        case 3:
            Source::code() << boost::format("uav_store_id(%1%) %2%,%3%\n") %  uav_index % _e.resultCode() % e.resultCode();
            break;
        default:
            Source::code() << boost::format("uav_store_id(%1%) %2%,%3%\n") %  uav_index % _e.resultCode() % e.resultCode();
        }
    }

public:
    uav_typed_expression( int idx, int caching, const E& e ) : base_type(idx,caching,e)
    {
    }
    uav_typed_expression( const uav_typed_expression<T,E>& rhs ) : base_type(rhs)
    {
    }
    ~uav_typed_expression()
    {
    }

    void emitCode() const
    {
        std::string rout = (boost::format("r%i") % index).str();
        std::string caching;
        
        if( uav_caching==UAV_CACHED   ) caching = "_cached";
        if( uav_caching==UAV_UNCACHED ) caching = "_uncached";

        _e.emitCode();

        switch( T::type_size ) {
        case 1:
            Source::code() << boost::format("uav_load_id(%1%)%6% r%4%,%3%\n"
                                            "mov %2%,%5%\n") % uav_index % detail::mask_output(resultCode()) % _e.resultCode() % index % detail::match_input_to_output(resultCode(),rout+".x") % caching;
            break;
        case 2:
            Source::code() << boost::format("uav_load_id(%1%)%6% r%4%,%3%\n"
                                            "mov %2%,%5%\n") % uav_index % detail::mask_output(resultCode()) % _e.resultCode() % index % detail::match_input_to_output(resultCode(),rout+".xy") % caching;
            break;
        case 3:
            Source::code() << boost::format("uav_load_id(%1%)%6% r%4%,%3%\n"
                                            "mov %2%,%5%\n") % uav_index % detail::mask_output(resultCode()) % _e.resultCode() % index % detail::match_input_to_output(resultCode(),rout+".xyz") % caching;
            break;
        default:
            Source::code() << boost::format("uav_load_id(%1%)%6% r%4%,%3%\n"
                                            "mov %2%,%5%\n") % uav_index % detail::mask_output(resultCode()) % _e.resultCode() % index % detail::match_input_to_output(resultCode(),rout+".xyzw") % caching;
            break;
        }
    }

    uav_typed_expression<T,E>& operator=( const uav_typed_expression<T,E>& v )
    {
        iEmitCode(v);
        return *this;
    }

    const uav_typed_expression<T,E>& operator=( const uav_typed_expression<T,E>& v ) const
    {
        iEmitCode(v);
        return *this;
    }

    template<class E1>
    uav_typed_expression<T,E>& operator=( const detail::expression<E1>& e )
    {
        typedef boost::is_same<typename E1::value_type,value_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );
        iEmitCode(e());
        return *this;
    }

    template<class E1>
    const uav_typed_expression<T,E>& operator=( const detail::expression<E1>& e ) const
    {
        typedef boost::is_same<typename E1::value_type,value_type> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );
        iEmitCode(e());
        return *this;
    }
};

} // detail


template<class T>
class uav_raw
{
public:
    typedef typename detail::base_cal_type<T>::value    value_type;

protected:
    int         uav_index;
    int         uav_caching;

protected:
    static std::string emit_dcl( int id )
    {
        return (boost::format("dcl_raw_uav_id(%i)") % id).str();
    }

public:
    uav_raw( int idx, CALuavcacheflags caching=UAV_AUTO_CACHE  )
    {
        assert( idx>=0 );
        uav_index   = idx;
        uav_caching = caching;
        Source::code().registerDCL( (boost::format("uav:%i") % idx).str(),
                                    boost::bind(&uav_raw<T>::emit_dcl,idx) );
    }

    void cached( bool enable=true )
    {
        uav_caching = enable?UAV_CACHED:UAV_AUTO_CACHE;
    }
    
    void uncached( bool enable=true )
    {
        uav_caching = enable?UAV_UNCACHED:UAV_AUTO_CACHE;
    }

    template<class E>
    detail::uav_expression<value_type,E> operator[]( const detail::expression<E>& e ) const
    {
        typedef boost::is_same<typename E::value_type,uint_type>    assert_v1;
        typedef boost::is_same<typename E::value_type,int_type>     assert_v2;

        BOOST_STATIC_ASSERT( assert_v1::value || assert_v2::value );

        return detail::uav_expression<value_type,E>(uav_index,uav_caching,"uav_raw_load_id","uav_raw_store_id",e());
    }

    template<class E>
    detail::uav_expression<value_type,E> operator()( const detail::expression<E>& e ) const
    {
        typedef boost::is_same<typename E::value_type,uint_type>    assert_v1;
        typedef boost::is_same<typename E::value_type,int_type>     assert_v2;

        BOOST_STATIC_ASSERT( assert_v1::value || assert_v2::value );

        return detail::uav_expression<value_type,E>(uav_index,uav_caching,"uav_raw_load_id","uav_raw_store_id",e());
    }
};

template<class T>
class uav_struct
{
public:
    typedef typename detail::base_cal_type<T>::value    value_type;

protected:
    int         uav_index;
    int         uav_caching;

protected:
    static std::string emit_dcl( int id, int stride )
    {
        return (boost::format("dcl_struct_uav_id(%i) %i") % id % stride).str();
    }

public:
    uav_struct( int idx, int stride, CALuavcacheflags caching=UAV_AUTO_CACHE )
    {
        assert( idx>=0 && stride>0 && (stride%4)==0 );
        uav_index   = idx;
        uav_caching = caching;
        Source::code().registerDCL( (boost::format("uav:%i") % idx).str(), 
                                    boost::bind(&uav_struct<T>::emit_dcl,idx,stride) );
    }

    void cached( bool enable=true )
    {
        uav_caching = enable?UAV_CACHED:UAV_AUTO_CACHE;
    }
    
    void uncached( bool enable=true )
    {
        uav_caching = enable?UAV_UNCACHED:UAV_AUTO_CACHE;
    }

    template<class E>
    detail::uav_expression<value_type,E> operator[]( const detail::expression<E>& e ) const
    {
        typedef boost::is_same<typename E::value_type,uint2_type>   assert_v1;
        typedef boost::is_same<typename E::value_type,int2_type>    assert_v2;

        BOOST_STATIC_ASSERT( assert_v1::value || assert_v2::value );

        return detail::uav_expression<value_type,E>(uav_index,uav_caching,"uav_struct_load_id","uav_struct_store_id",e());
    }

    template<class E>        
    detail::uav_expression<value_type,E> operator()( const detail::expression<E>& e ) const
    {
        typedef boost::is_same<typename E::value_type,uint2_type>   assert_v1;
        typedef boost::is_same<typename E::value_type,int2_type>    assert_v2;

        BOOST_STATIC_ASSERT( assert_v1::value || assert_v2::value );

        return detail::uav_expression<value_type,E>(uav_index,uav_caching,"uav_struct_load_id","uav_struct_store_id",e());
    }

    template<class E1,class E2>
    detail::uav_expression<value_type,detail::binary<E1,E2,detail::cal_binary_cast<typename E1::value_type,typename E2::value_type> > > operator()( const detail::expression<E1>& idx, const detail::expression<E2>& offset ) const
    {
        typedef detail::uav_expression<value_type,detail::binary<E1,E2,detail::cal_binary_cast<typename E1::value_type,typename E2::value_type> > > expression_type;
        typedef boost::is_same<typename E1::value_type,uint_type>    assert_v1;
        typedef boost::is_same<typename E1::value_type,int_type>     assert_v2;
        typedef boost::is_same<typename E2::value_type,uint_type>    assert_v3;
        typedef boost::is_same<typename E2::value_type,int_type>     assert_v4;

        BOOST_STATIC_ASSERT( (assert_v1::value && assert_v3::value) || (assert_v2::value && assert_v4::value) );

        return expression_type(uav_index,uav_caching,"uav_struct_load_id","uav_struct_store_id",merge_types(idx(),offset()));
    }

    template<class E1>
    detail::uav_expression<value_type,detail::binary<E1,value<typename E1::value_type>,detail::cal_binary_cast<typename E1::value_type,typename E1::value_type> > > operator()( const detail::expression<E1>& idx, int offset ) const
    {
        typedef detail::uav_expression<value_type,detail::binary<E1,value<typename E1::value_type>,detail::cal_binary_cast<typename E1::value_type,typename E1::value_type> > > expression_type;
        typedef boost::is_same<typename E1::value_type,uint_type>   assert_v1;
        typedef boost::is_same<typename E1::value_type,int_type>    assert_v2;

        BOOST_STATIC_ASSERT( assert_v1::value || assert_v2::value );

        return expression_type(uav_index,uav_caching,"uav_struct_load_id","uav_struct_store_id",merge_types(idx(),value<typename E1::value_type>(offset)));
    }
};

template<class T>
class uav
{
public:
    typedef typename detail::base_cal_type<T>::value    value_type;

protected:
    int         uav_index;
    int         uav_caching;

protected:
    std::string getFormatName( const int_type& ) { return "sint"; }
    std::string getFormatName( const int2_type& ) { return "sint"; }
    std::string getFormatName( const int4_type& ) { return "sint"; }
    std::string getFormatName( const uint_type& ) { return "uint"; }
    std::string getFormatName( const uint2_type& ) { return "uint"; }
    std::string getFormatName( const uint4_type& ) { return "uint"; }
    std::string getFormatName( const float_type& ) { return "float"; }
    std::string getFormatName( const float2_type& ) { return "float"; }
    std::string getFormatName( const float4_type& ) { return "float"; }
    std::string getFormatName( const double_type& ) { return "unknown"; }
    std::string getFormatName( const double2_type& ) { return "unknown"; }

    static std::string emit_dcl( int id, const std::string& type, const std::string& format )
    {
        return (boost::format("dcl_uav_id(%i)_type(%s)_fmtx(%s)") % id % type % format).str();
    }

public:
    uav( int idx, const std::string& type, CALuavcacheflags caching=UAV_AUTO_CACHE )
    {
        assert( idx>=0 );
        uav_index   = idx;
        uav_caching = caching;

        std::string format = getFormatName(typename detail::base_cal_type<T>::value());
        Source::code().registerDCL( (boost::format("uav:%i") % idx).str(), 
                                    boost::bind(&uav<T>::emit_dcl,idx,type,format) );
    }

    uav( int idx, const std::string& type, const std::string& format, CALuavcacheflags caching=UAV_AUTO_CACHE )
    {
        assert( idx>=0 );
        uav_index   = idx;
        uav_caching = caching;
        Source::code().registerDCL( (boost::format("uav:%i") % idx).str(),
                                    boost::bind(&uav<T>::emit_dcl,idx,type,format) );
    }

    void cached( bool enable=true )
    {
        uav_caching = enable?UAV_CACHED:UAV_AUTO_CACHE;
    }
    
    void uncached( bool enable=true )
    {
        uav_caching = enable?UAV_UNCACHED:UAV_AUTO_CACHE;
    }

    template<class E>
    detail::uav_typed_expression<value_type,E> operator[]( const detail::expression<E>& e ) const
    {
        typedef boost::is_same<typename E::value_type,uint_type>    assert_v1;
        typedef boost::is_same<typename E::value_type,int_type>     assert_v2;
        typedef boost::is_same<typename E::value_type,uint2_type>   assert_v3;
        typedef boost::is_same<typename E::value_type,int2_type>    assert_v4;

        BOOST_STATIC_ASSERT( assert_v1::value || assert_v2::value || assert_v3::value || assert_v4::value );

        return detail::uav_typed_expression<value_type,E>(uav_index,uav_caching,e());
    }

    template<class E>        
    detail::uav_typed_expression<value_type,E> operator()( const detail::expression<E>& e ) const
    {
        typedef boost::is_same<typename E::value_type,uint_type>    assert_v1;
        typedef boost::is_same<typename E::value_type,int_type>     assert_v2;
        typedef boost::is_same<typename E::value_type,uint2_type>   assert_v3;
        typedef boost::is_same<typename E::value_type,int2_type>    assert_v4;

        BOOST_STATIC_ASSERT( assert_v1::value || assert_v2::value || assert_v3::value || assert_v4::value );

        return detail::uav_typed_expression<value_type,E>(uav_index,uav_caching,e());
    }

    template<class E1,class E2>
    detail::uav_typed_expression<value_type,detail::binary<E1,E2,detail::cal_binary_cast<typename E1::value_type,typename E2::value_type> > > operator()( const detail::expression<E1>& idx, const detail::expression<E2>& offset ) const
    {
        typedef detail::uav_typed_expression<value_type,detail::binary<E1,E2,detail::cal_binary_cast<typename E1::value_type,typename E2::value_type> > > expression_type;
        typedef boost::is_same<typename E1::value_type,uint_type>    assert_v1;
        typedef boost::is_same<typename E1::value_type,int_type>     assert_v2;
        typedef boost::is_same<typename E2::value_type,uint_type>    assert_v3;
        typedef boost::is_same<typename E2::value_type,int_type>     assert_v4;

        BOOST_STATIC_ASSERT( (assert_v1::value || assert_v2::value) && (assert_v3::value || assert_v4::value) );

        return expression_type(uav_index,uav_caching,merge_types(idx(),offset()));
    }
};



} // il
} // cal

#endif
