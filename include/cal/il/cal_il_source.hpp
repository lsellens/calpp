/*
 * C++ to IL compiler/generator source generation
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

#ifndef __CAL_IL_SOURCE_H
#define __CAL_IL_SOURCE_H

#include <map>
#include <vector>
#include <sstream>
#include <cstring>
#include <boost/cstdint.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/array.hpp>
#include <boost/format.hpp>
#include <boost/function.hpp>

namespace cal {
namespace il {

template<int N>
class SourceGenerator
{
public:
    struct func_info
    {
        static const int ARG_INOUT=0;
        static const int ARG_IN   =1;
        static const int ARG_OUT  =2;

        struct arg_info
        {
            int type;
            int id;            
        
            arg_info( int _type, int _id ) : type(_type), id(_id) {}
        };
        
        std::string                             source;
        std::vector<arg_info>                   arg;
        std::vector<boost::function<void ()> >  change_var;
        std::vector<boost::function<void ()> >  undo_var;
        int                                     fid;
    
        template<class T>
        std::string pre_call( int idx, const T& v )
        {
            if( arg[idx].type==ARG_INOUT || arg[idx].type==ARG_IN ) {
                return (boost::format("mov r%i,%s\n") % arg[idx].id % v.resultCode()).str();
            }
        
            return "";
        }
    
        template<class T>
        std::string post_call( int idx, const T& v )
        {
            if( arg[idx].type==ARG_INOUT || arg[idx].type==ARG_OUT ) {
                return (boost::format("mov %s,r%i\n") % v.resultCode() % arg[idx].id).str();
            }
        
            return "";
        }
        
        void add_source( const std::string& _source )
        {
            if( !undo_var.empty() ) source += _source;
        }
    
        void make_changes()
        {
            for(unsigned i=0;i<change_var.size();i++) 
                change_var[i]();
            change_var.clear();      
        }
        
        void undo_changes()
        {
            for(unsigned i=0;i<undo_var.size();i++) 
                undo_var[i]();
            undo_var.clear();
        }
    };
    
    struct state_info
    {
        int  emit_ieee;
        int  available;        

#if defined(__CAL_HPP__) || defined(__CAL_H__)        
        CALtarget  target;
        CALuint    maxResource1DWidth;
        CALuint    maxResource2DWidth;
        CALuint    maxResource2DHeight;

        CALuint    localRAM;            /**< Amount of local GPU RAM in megabytes */
        CALuint    uncachedRemoteRAM;   /**< Amount of uncached remote GPU memory in megabytes */
        CALuint    cachedRemoteRAM;     /**< Amount of cached remote GPU memory in megabytes */
        CALuint    engineClock;         /**< GPU device clock rate in megahertz */
        CALuint    memoryClock;         /**< GPU memory clock rate in megahertz */
        CALuint    wavefrontSize;       /**< Wavefront size */
        CALuint    numberOfSIMD;        /**< Number of SIMDs */
        CALboolean doublePrecision;     /**< double precision supported */
        CALboolean localDataShare;      /**< local data share supported */
        CALboolean globalDataShare;     /**< global data share supported */
        CALboolean globalGPR;           /**< global GPR supported */
        CALboolean computeShader;       /**< compute shader supported */
        CALboolean memExport;           /**< memexport supported */
        CALuint    pitch_alignment;     /**< Required alignment for calCreateRes allocations (in data elements) */
        CALuint    surface_alignment;   /**< Required start address alignment for calCreateRes allocations (in bytes) */
        CALuint    numberOfUAVs;        /**< Number of UAVs */
        CALboolean bUAVMemExport;       /**< Hw only supports mem export to simulate 1 UAV */
        CALboolean b3dProgramGrid;      /**< CALprogramGrid for have height and depth bigger than 1*/
        CALuint    numberOfShaderEngines;/**< Number of shader engines */
        CALuint    targetRevision;      /**< Asic family revision */

        CALuint   availLocalRAM;          /**< Amount of available local GPU RAM in megabytes */
        CALuint   availUncachedRemoteRAM; /**< Amount of available uncached remote GPU memory in megabytes */
        CALuint   availCachedRemoteRAM;   /**< Amount of available cached remote GPU memory in megabytes */
#endif        
    };

protected:
    typedef std::map<std::string,func_info>                 func_map;
    
protected:
    unsigned                                                next_instruction_index;
    int                                                     next_literal_index;
    int                                                     next_func_index;
    std::map<std::string,boost::function<std::string ()> >  dcl_data;
    std::map<boost::array<boost::uint32_t,4>,int>           literal_data;
    func_map                                                func_data;
    std::vector<typename func_map::iterator>                func_stack;
    std::string                                             source;

public:
    static SourceGenerator<N>       code;
    static state_info               info;

protected:
    void iemitHeader( std::ostream& _out )
    {
        std::map<std::string,boost::function<std::string ()> >::iterator  idcl;
        for(idcl=dcl_data.begin();idcl!=dcl_data.end();++idcl) {
            _out << idcl->second() << "\n";
        }

        std::map<boost::array<boost::uint32_t,4>,int>::iterator    iliteral;
        for(iliteral=literal_data.begin();iliteral!=literal_data.end();++iliteral) {
            _out << boost::format("dcl_literal l%i, 0x%x, 0x%x, 0x%x, 0x%x\n") % iliteral->second % iliteral->first[0] % iliteral->first[1] % iliteral->first[2] % iliteral->first[3];
        }
    }

    void iemitCode( std::ostream& _out )
    {
        typename func_map::iterator  ifunc;
        
        _out << source;
        
        for(ifunc=func_data.begin();ifunc!=func_data.end();++ifunc) {
            _out << boost::format("func %i\n") % ifunc->second.fid;
            _out << ifunc->second.source;
            _out << "ret\nendfunc\n";
        }
        
        _out << "end\n";        
    }
    
    void iEnd()
    {
        assert( next_func_index>=1 ); // calling without Source::begin
        if( !func_data.empty() ) source += "endmain\n";
        next_func_index=-1;        
    }

public:
    SourceGenerator()
    {
        next_instruction_index=0;
        next_literal_index = 0; 
        next_func_index = -1;
    }
    ~SourceGenerator()
    {
    }

    void clear()
    {
        next_instruction_index=0;
        next_literal_index=0;
        next_func_index=1;

        dcl_data.clear();
        literal_data.clear();
        func_data.clear();
        func_stack.clear();

        source.clear();        

        boost::array<boost::uint32_t,4>    data;
        data.assign(0);
        literal_data[data]=next_literal_index++;        
        data.assign(0xFFFFFFFF);
        literal_data[data]=next_literal_index++;        
    }

    unsigned getNewID( unsigned count )
    {
        assert( next_func_index>=1 ); // creating variables before call to Source::begin
        
        unsigned v = next_instruction_index;
        next_instruction_index+=count;        
        return v;
    }

    void registerDCL( const std::string& idx, const boost::function<std::string ()>& dcl )
    {
        dcl_data[idx] = dcl;
    }

    int getLiteral( const boost::array<boost::uint32_t,4>& data )
    {
        std::map<boost::array<boost::uint32_t,4>,int>::iterator    idata;

        idata = literal_data.find(data);
        if( idata!=literal_data.end() ) return idata->second;

        literal_data[data] = next_literal_index;
        return next_literal_index++;
    }
    
    bool isFuncAvailable( const std::string& name ) const
    {
        return func_data.find(name)!=func_data.end();
    }
    
    func_info& getFunc( const std::string& name )
    {
        typename func_map::iterator  ifunc;
        
        ifunc = func_data.find(name);
        if( ifunc==func_data.end() ) {
            func_data[name].fid = next_func_index++;
            ifunc = func_data.find(name);            
        }
        
        assert( ifunc!=func_data.end() );
        return ifunc->second;
    }
    
    void makeFuncActive( const std::string& name )
    {
        typename func_map::iterator  ifunc;
        
        ifunc = func_data.find(name);
        assert( ifunc!=func_data.end() );
                
        ifunc->second.make_changes();
        func_stack.push_back(ifunc);
    }
    
    void endFunc()
    {
        assert( !func_stack.empty() );
        func_stack.back()->second.undo_changes();
        func_stack.pop_back();
    }

    template<class T>
    SourceGenerator<N>& operator<<( const T& r )
    {
        std::stringstream    str;
        str << r;
        
        if( func_stack.empty() ) source += str.str();
        else func_stack.back()->second.add_source(str.str());

        return *this;
    }

    static void begin()
    {
        code.clear();
        std::memset( &info, 0, sizeof(info) );
    }

#if defined(__CAL_H__)
    static void begin( CALuint ordinal )
    {
        CALdeviceinfo    _info;
        CALdeviceattribs _attribs;

        begin();

        _attribs.struct_size = sizeof(CALdeviceattribs);

        if( calDeviceGetInfo(&_info,ordinal)!=CAL_RESULT_OK ) return;
        if( calDeviceGetAttribs(&_attribs,ordinal)!=CAL_RESULT_OK ) return;

        info.available = 1;

        info.target = _info.target;
        info.maxResource1DWidth = _info.maxResource1DWidth;
        info.maxResource2DWidth = _info.maxResource2DWidth;
        info.maxResource2DHeight = _info.maxResource2DHeight;

        info.localRAM = _attribs.localRAM;
        info.uncachedRemoteRAM = _attribs.uncachedRemoteRAM;
        info.cachedRemoteRAM = _attribs.cachedRemoteRAM;
        info.engineClock = _attribs.engineClock;
        info.memoryClock = _attribs.memoryClock;
        info.wavefrontSize = _attribs.wavefrontSize;
        info.numberOfSIMD = _attribs.numberOfSIMD;
        info.doublePrecision = _attribs.doublePrecision;
        info.localDataShare = _attribs.localDataShare;
        info.globalDataShare = _attribs.globalDataShare;
        info.globalGPR = _attribs.globalGPR;
        info.computeShader = _attribs.computeShader;
        info.memExport = _attribs.memExport;
        info.pitch_alignment = _attribs.pitch_alignment;
        info.surface_alignment = _attribs.surface_alignment;
        info.numberOfUAVs = _attribs.numberOfUAVs;
        info.bUAVMemExport = _attribs.bUAVMemExport;
        info.b3dProgramGrid = _attribs.b3dProgramGrid;
        info.numberOfShaderEngines = _attribs.numberOfShaderEngines;
        info.targetRevision = _attribs.targetRevision;
    }
#endif

#if defined(__CAL_HPP__)
    static void begin( const cal::Device& device )
    {
        begin(device.getInfo<CAL_DEVICE_INDEX>());
    }
#endif

    static void end()
    {
        code.iEnd();
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

template<int N> SourceGenerator<N> SourceGenerator<N>::code;
template<int N> typename SourceGenerator<N>::state_info SourceGenerator<N>::info;

typedef SourceGenerator<0> Source;

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
