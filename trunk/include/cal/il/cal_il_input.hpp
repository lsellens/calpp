/*
 * C++ to IL compiler/generator input support
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

#ifndef __CAL_IL_INPUT_H
#define __CAL_IL_INPUT_H

#include <boost/format.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>
#include <boost/array.hpp>
#include <cmath>

namespace cal {
namespace il {

namespace detail {

template<class T,class E,int DIM>
class input_expression : public detail::swizzable_expression<T,input_expression<T,E,DIM> >
{
protected:
    typedef input_expression<T,E,DIM>                                   self_type;
    typedef detail::swizzable_expression<T,input_expression<T,E,DIM> >  base_type;
    typedef const E                                                     expression_type;
    typedef typename E::const_closure_type                              expression_closure_type;

    typedef union conv_float_union { boost::array<float,4> base; boost::array<boost::uint32_t,4> hex; } conv_float;
    typedef union conv_int_union   { boost::array<boost::int32_t,4> base; boost::array<boost::uint32_t,4> hex; } conv_int;

public:
    typedef T                                                           value_type;
    typedef const self_type                                             const_closure_type;
    typedef self_type                                                   closure_type;
    static const int                                                    temp_reg_count=1;
    static const bool                                                   swizzle_has_assign=false;

protected:
    int                     input_index;
    float                   xoffset,yoffset;
    int                     sampler;
    expression_closure_type _e;
    using base_type::index;

public:
    using base_type::resultCode;

    void iemitCode( Source& prg, std::ostream& _out, int s, float_type ) const
    {
        if( xoffset<-8 || xoffset>7.5 ) {
            conv_float conv;
            int        idx;
            conv.base[0] = xoffset; conv.base[1] = yoffset; conv.base[2] = 0; conv.base[3] = 0;
            idx = prg.getLiteral( conv.hex );
            _out << boost::format("add r%1%,%2%000,l%3%.x000\n") % (index+1) % make_swizzle(_e.resultCode(),1,0,0,0) % idx;
            _out << boost::format("sample_resource(%1%)_sampler(%2%) %3%,r%4%\n") % input_index % s % resultCode() % (index+1);
            return;
        }

        if( xoffset!=0 || yoffset!=0 ) _out << boost::format("sample_resource(%1%)_sampler(%2%)_aoffimmi(%3%,%4%,0) %5%,%6%000\n") % input_index % s % xoffset % yoffset % resultCode() % make_swizzle(_e.resultCode(),1,0,0,0);
        else _out << boost::format("sample_resource(%1%)_sampler(%2%) %3%,%4%000\n") % input_index % s % resultCode() % make_swizzle(_e.resultCode(),1,0,0,0);
    }

    void iemitCode( Source& prg, std::ostream& _out, int s, float2_type ) const
    {
        if( xoffset<-8 || xoffset>7.5 || yoffset<-8 || yoffset>7.5 ) {
            conv_float conv;
            int        idx;
            conv.base[0] = xoffset; conv.base[1] = yoffset; conv.base[2] = 0; conv.base[3] = 0;
            idx = prg.getLiteral( conv.hex );
            _out << boost::format("add r%1%,%2%00,l%3%.xy00\n") % (index+1) % make_swizzle(_e.resultCode(),1,2,0,0) % idx;
            _out << boost::format("sample_resource(%1%)_sampler(%2%) %3%,r%4%\n") % input_index % s % resultCode() % (index+1);
            return;
        }

        if( xoffset!=0 || yoffset!=0 ) _out << boost::format("sample_resource(%1%)_sampler(%2%)_aoffimmi(%3%,%4%,0) %5%,%6%00\n") % input_index % s % xoffset % yoffset % resultCode() % make_swizzle(_e.resultCode(),1,2,0,0);
        else _out << boost::format("sample_resource(%1%)_sampler(%2%) %3%,%4%00\n") % input_index % s % resultCode() % make_swizzle(_e.resultCode(),1,2,0,0);
    }

    void iemitCode( Source& prg, std::ostream& _out, int s, int_type ) const
    {
        if( xoffset<-8 || xoffset>7.5 ) {
            conv_int   conv;
            int        idx;
            conv.base[0] = xoffset; conv.base[1] = yoffset; conv.base[2] = 0; conv.base[3] = 0;
            idx = prg.getLiteral( conv.hex );
            _out << boost::format("iadd r%1%,%2%000,l%3%.x000\n") % (index+1) % make_swizzle(_e.resultCode(),1,0,0,0) % idx;
            _out << boost::format("load_resource(%1%) %2%,r%3%\n") % input_index % resultCode() % (index+1);
            return;
        }

        if( xoffset!=0 || yoffset!=0 ) _out << boost::format("load_resource(%1%)_aoffimmi(%2%,%3%,0) %4%,%5%000\n") % input_index % xoffset % yoffset % resultCode() % make_swizzle(_e.resultCode(),1,0,0,0);
        else _out << boost::format("load_resource(%1%) %2%,%3%000\n") % input_index % resultCode() % make_swizzle(_e.resultCode(),1,0,0,0);
    }

    void iemitCode( Source& prg, std::ostream& _out, int s, int2_type ) const
    {
        if( xoffset<-8 || xoffset>7.5 || yoffset<-8 || yoffset>7.5 ) {
            conv_int   conv;
            int        idx;
            conv.base[0] = xoffset; conv.base[1] = yoffset; conv.base[2] = 0; conv.base[3] = 0;
            idx = prg.getLiteral( conv.hex );
            _out << boost::format("iadd r%1%,%2%00,l%3%.xy00\n") % (index+1) % make_swizzle(_e.resultCode(),1,2,0,0) % idx;
            _out << boost::format("load_resource(%1%) %2%,r%3%\n") % input_index % resultCode() % (index+1);
            return;
        }

        if( xoffset!=0 || yoffset!=0 ) _out << boost::format("load_resource(%1%)_aoffimmi(%2%,%3%,0) %4%,%5%00\n") % input_index % xoffset % yoffset % resultCode() % make_swizzle(_e.resultCode(),1,2,0,0);
        else _out << boost::format("load_resource(%1%) %2%,%3%00\n") % input_index % resultCode() % make_swizzle(_e.resultCode(),1,2,0,0);
    }

    void iemitCode( Source& prg, std::ostream& _out, int s, uint_type ) const
    {
        if( xoffset<-8 || xoffset>7.5 ) {
            conv_int   conv;
            int        idx;
            conv.base[0] = xoffset; conv.base[1] = yoffset; conv.base[2] = 0; conv.base[3] = 0;
            idx = prg.getLiteral( conv.hex );
            _out << boost::format("iadd r%1%,%2%000,l%3%.x000\n") % (index+1) % make_swizzle(_e.resultCode(),1,0,0,0) % idx;
            _out << boost::format("load_resource(%1%) %2%,r%3%\n") % input_index % resultCode() % (index+1);
            return;
        }

        if( xoffset!=0 || yoffset!=0 ) _out << boost::format("load_resource(%1%)_aoffimmi(%2%,%3%,0) %4%,%5%000\n") % input_index % xoffset % yoffset % resultCode() % make_swizzle(_e.resultCode(),1,0,0,0);
        else _out << boost::format("load_resource(%1%) %2%,%3%000\n") % input_index % resultCode() % make_swizzle(_e.resultCode(),1,0,0,0);
    }

    void iemitCode( Source& prg, std::ostream& _out, int s, uint2_type ) const
    {
        if( xoffset<-8 || xoffset>7.5 || yoffset<-8 || yoffset>7.5 ) {
            conv_int   conv;
            int        idx;
            conv.base[0] = xoffset; conv.base[1] = yoffset; conv.base[2] = 0; conv.base[3] = 0;
            idx = prg.getLiteral( conv.hex );
            _out << boost::format("iadd r%1%,%2%00,l%3%.xy00\n") % (index+1) % make_swizzle(_e.resultCode(),1,2,0,0) % idx;
            _out << boost::format("load_resource(%1%) %2%,r%3%\n") % input_index % resultCode() % (index+1);
            return;
        }

        if( xoffset!=0 || yoffset!=0 ) _out << boost::format("load_resource(%1%)_aoffimmi(%2%,%3%,0) %4%,%5%00\n") % input_index % xoffset % yoffset % resultCode() % make_swizzle(_e.resultCode(),1,2,0,0);
        else _out << boost::format("load_resource(%1%) %2%,%3%00\n") % input_index % resultCode() % make_swizzle(_e.resultCode(),1,2,0,0);
    }

public:
    input_expression( int idx, const E& e, float x=0, float y=0, int s=-1 ) : base_type(), input_index(idx), xoffset(std::floor(2.f*x+.5f)/2.f), yoffset(std::floor(2.f*y+.5f)/2.f), sampler(s), _e(e)
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
        iemitCode(prg,_out,s,typename E::value_type());
    }
};

} // detail


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
        typedef boost::is_same<typename E::value_type,float_type> assert_v1;
        typedef boost::is_same<typename E::value_type,int_type>   assert_v2;
        typedef boost::is_same<typename E::value_type,uint_type>   assert_v3;
        BOOST_STATIC_ASSERT( assert_v1::value || assert_v2::value || assert_v3::value );

        return detail::input_expression<value_type,E,1>(input_index,e(),0,0,input_sampler);
    }

    input1d<T> operator()( int s ) const
    {
        return input1d<T>(input_index,s);
    }

    template<class E>
    detail::input_expression<value_type,E,1> operator()( const detail::binary<E,detail::value<E>,detail::cal_binary_add<typename E::value_type,typename E::value_type> >& e ) const
    {
        typedef boost::is_same<typename E::value_type,float_type> assert_v1;
        typedef boost::is_same<typename E::value_type,int_type>   assert_v2;
        typedef boost::is_same<typename E::value_type,uint_type>   assert_v3;
        BOOST_STATIC_ASSERT( assert_v1::value || assert_v2::value || assert_v3::value );

        return detail::input_expression<value_type,E,1>(input_index,e._e1,e._e2.getValue(),0,input_sampler);
    }

    template<class E>
    detail::input_expression<value_type,E,1> operator()( const detail::expression<E>& e ) const
    {
        typedef boost::is_same<typename E::value_type,float_type> assert_v1;
        typedef boost::is_same<typename E::value_type,int_type>   assert_v2;
        typedef boost::is_same<typename E::value_type,uint_type>   assert_v3;
        BOOST_STATIC_ASSERT( assert_v1::value || assert_v2::value || assert_v3::value );

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
        typedef boost::is_same<typename E::value_type,float2_type> assert_v1;
        typedef boost::is_same<typename E::value_type,int2_type>   assert_v2;
        typedef boost::is_same<typename E::value_type,uint2_type>  assert_v3;
        BOOST_STATIC_ASSERT( assert_v1::value || assert_v2::value || assert_v3::value );
        

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

        typedef boost::is_same<typename detail::cal_binary_cast<typename E1::value_type,typename E2::value_type>::value_type,float2_type> assert_v1;
        typedef boost::is_same<typename detail::cal_binary_cast<typename E1::value_type,typename E2::value_type>::value_type,int2_type> assert_v2;
        typedef boost::is_same<typename detail::cal_binary_cast<typename E1::value_type,typename E2::value_type>::value_type,uint2_type> assert_v3;
        BOOST_STATIC_ASSERT( assert_v1::value || assert_v2::value || assert_v3::value );

        return expression_type(input_index,merge_types(x(),y()),0,0,input_sampler);
    }

    template<class E>
    detail::input_expression<value_type,E,1> operator()( const detail::binary<E,detail::value<E>,detail::cal_binary_add<typename E::value_type,typename E::value_type> >& e ) const
    {
        typedef boost::is_same<typename E::value_type,float_type> assert_v1;
        typedef boost::is_same<typename E::value_type,int_type>   assert_v2;
        typedef boost::is_same<typename E::value_type,uint_type>   assert_v3;
        BOOST_STATIC_ASSERT( assert_v1::value || assert_v2::value || assert_v3::value );

        return detail::input_expression<value_type,E,1>(input_index,e._e1,e._e2.getValue(),0,input_sampler);
    }

    template<class E1,class E2>
    detail::input_expression<value_type, detail::binary<typename E1::closure_type,typename E2::closure_type, detail::cal_binary_cast<typename E1::value_type,typename E2::value_type> >, 2>
    operator()( const detail::binary<E1,detail::value<E1>,detail::cal_binary_add<typename E1::value_type,typename E1::value_type> >& x,
                const detail::binary<E2,detail::value<E2>,detail::cal_binary_add<typename E2::value_type,typename E2::value_type> >& y ) const
    {
        typedef detail::input_expression<value_type, detail::binary<typename E1::closure_type,typename E2::closure_type, detail::cal_binary_cast<typename E1::value_type,typename E2::value_type> >, 2> expression_type;

        typedef boost::is_same<typename detail::cal_binary_cast<typename E1::value_type,typename E2::value_type>::value_type,float2_type> assert_v1;
        typedef boost::is_same<typename detail::cal_binary_cast<typename E1::value_type,typename E2::value_type>::value_type,int2_type> assert_v2;
        typedef boost::is_same<typename detail::cal_binary_cast<typename E1::value_type,typename E2::value_type>::value_type,uint2_type> assert_v3;
        BOOST_STATIC_ASSERT( assert_v1::value || assert_v2::value || assert_v3::value );

        return expression_type(input_index,merge_types(x._e1,y._e1),x._e2.getValue(),y._e2.getValue(),input_sampler);
    }

    template<class E1,class E2>
    detail::input_expression<value_type, detail::binary<E1,typename E2::closure_type, detail::cal_binary_cast<typename E1::value_type,typename E2::value_type> >, 2> 
    operator()( const detail::expression<E1>& x,
                const detail::binary<E2,detail::value<E2>,detail::cal_binary_add<typename E2::value_type,typename E2::value_type> >& y ) const
    {
        typedef detail::input_expression<value_type, detail::binary<E1,typename E2::closure_type, detail::cal_binary_cast<typename E1::value_type,typename E2::value_type> >, 2> expression_type;

        typedef boost::is_same<typename detail::cal_binary_cast<typename E1::value_type,typename E2::value_type>::value_type,float2_type> assert_v1;
        typedef boost::is_same<typename detail::cal_binary_cast<typename E1::value_type,typename E2::value_type>::value_type,int2_type> assert_v2;
        typedef boost::is_same<typename detail::cal_binary_cast<typename E1::value_type,typename E2::value_type>::value_type,uint2_type> assert_v3;
        BOOST_STATIC_ASSERT( assert_v1::value || assert_v2::value || assert_v3::value );

        return expression_type(input_index,merge_types(x(),y._e1),0,y._e2.getValue(),input_sampler);
    }

    template<class E1,class E2>
    detail::input_expression<value_type, detail::binary<typename E1::closure_type, E2, detail::cal_binary_cast<typename E1::value_type,typename E2::value_type> >, 2> 
    operator()( const detail::binary<E1,detail::value<E1>,detail::cal_binary_add<typename E1::value_type,typename E1::value_type> >& x,
                const detail::expression<E2>& y ) const
    {
        typedef detail::input_expression<value_type, detail::binary<typename E1::closure_type, E2, detail::cal_binary_cast<typename E1::value_type,typename E2::value_type> >, 2> expression_type;

        typedef boost::is_same<typename detail::cal_binary_cast<typename E1::value_type,typename E2::value_type>::value_type,float2_type> assert_v1;
        typedef boost::is_same<typename detail::cal_binary_cast<typename E1::value_type,typename E2::value_type>::value_type,int2_type> assert_v2;
        typedef boost::is_same<typename detail::cal_binary_cast<typename E1::value_type,typename E2::value_type>::value_type,uint2_type> assert_v3;
        BOOST_STATIC_ASSERT( assert_v1::value || assert_v2::value || assert_v3::value );

        return expression_type(input_index,merge_types(x._e1,y()),x._e2.getValue(),0,input_sampler);
    }
};

} // il
} // cal

#endif
