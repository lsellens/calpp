/*
 * C++ to IL compiler/generator source generation
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

#ifndef __CAL_IL_SOURCE_H
#define __CAL_IL_SOURCE_H

#include <map>
#include <sstream>
#include <boost/cstdint.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/array.hpp>
#include <boost/format.hpp>

namespace cal {
namespace il {

class Source
{
protected:
    unsigned next_instruction_index;
    
protected:
    int                                     next_literal_index;
    std::map<int,std::pair<int,int> >       input_data;
    std::map<boost::array<boost::uint32_t,4>,int>  literal_data;
    std::stringstream                       code_stream;
        
public:
    static  Source                         code;
        
protected:
    void iemitHeader( std::ostream& _out )
    {
        std::map<int,std::pair<int,int> >::iterator     iinput;

        for(iinput=input_data.begin();iinput!=input_data.end();++iinput) {
            _out << boost::format("dcl_resource_id(%i)_type(%id,unnorm)_fmtx(float)_fmty(float)_fmtz(float)_fmtw(float)\n") % iinput->first % iinput->second.first;
        }

        std::map<boost::array<boost::uint32_t,4>,int>::iterator    iliteral;

        for(iliteral=literal_data.begin();iliteral!=literal_data.end();++iliteral) {
            _out << boost::format("dcl_literal l%i, 0x%x, 0x%x, 0x%x, 0x%x\n") % iliteral->second % iliteral->first[0] % iliteral->first[1] % iliteral->first[2] % iliteral->first[3];
        }        
    }

    void iemitCode( std::ostream& _out )
    {                
        _out << code.code_stream.str();
    }
        
public:
    Source()
    {
        next_instruction_index=0;
        next_literal_index = 0; 
    }
    ~Source()
    {
    }

    void clear()
    {
        next_instruction_index=0;
        next_literal_index=0;
        
        input_data.clear();
        literal_data.clear();

        code_stream.str(std::string());
        
        boost::array<boost::uint32_t,4>    data;
        data.assign(0);
        literal_data[data]=next_literal_index++;        
        data.assign(0xFFFFFFFF);
        literal_data[data]=next_literal_index++;        
    }

    unsigned getNewID( unsigned count )
    {
        unsigned v = next_instruction_index;
        next_instruction_index+=count;        
        return v;
    }

    void registerInput( int input_index, int dim, int size )
    {
        input_data[input_index] = std::make_pair(dim,size);
    }

    int getLiteral( const boost::array<boost::uint32_t,4>& data )
    {
        std::map<boost::array<boost::uint32_t,4>,int>::iterator    idata;

        idata = literal_data.find(data);
        if( idata!=literal_data.end() ) return idata->second;

        literal_data[data] = next_literal_index;
        return next_literal_index++;
    }

    template<class T>
    std::ostream& operator<<( const T& r )
    {
        return code_stream << r;
    }

    std::ostream& stream()
    {
        return code_stream;
    }

    static void begin()
    {
        code.clear();
    }

    static void end()
    {
    }

    static void emitHeader( std::ostream& _out )
    {
        code.iemitHeader(_out);
    }

    static void emitCode( std::ostream& _out )
    {
        code.iemitCode(_out);
    }
};

Source Source::code;

namespace detail {

template<class E>
class expression 
{
public:
    typedef E expression_type;

protected:
    int index;

public:
    expression() { index = Source::code.getNewID(E::temp_reg_count+1); }
    expression( const expression<E>& rhs ) : index(rhs.index) {}
    ~expression() {}

    const expression_type& operator()() const {
        return *static_cast<const expression_type *>( this );
    }

    expression_type& operator()() {
        return *static_cast<expression_type *>( this );
    }
};

} // detail

} // il
} // cal

#endif
