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
#include <sstream>
#include <cstring>
#include <boost/cstdint.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/array.hpp>
#include <boost/format.hpp>

namespace cal {
namespace il {

template<int N>
class SourceGenerator
{
public:
#if defined(__CAL_HPP__) || defined(__CAL_H__)
    struct device_info
    {
        int available;

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
    };
#endif

    struct uav_data_t
    {
        int         uav_type;
        int         struct_stride;
        std::string typed_type;
        std::string typed_format;

        uav_data_t() : uav_type(-1), struct_stride(0), typed_type(), typed_format() {}
        uav_data_t( int type, int stride, const std::string& ttype, const std::string& tformat ) : uav_type(type), struct_stride(stride), typed_type(ttype), typed_format(tformat) {}
    };

protected:
    unsigned next_instruction_index;

protected:
    int                                            next_literal_index;
    std::map<int,std::pair<int,int> >              input_data;
    std::map<int,uav_data_t>                       uav_data;
    std::map<boost::array<boost::uint32_t,4>,int>  literal_data;
    std::stringstream                              code_stream;

public:
    static SourceGenerator<N>              code;
#if defined(__CAL_HPP__) || defined(__CAL_H__)
    static device_info                     info;
#endif

protected:
    void iemitHeader( std::ostream& _out )
    {
        std::map<int,std::pair<int,int> >::iterator     iinput;

        for(iinput=input_data.begin();iinput!=input_data.end();++iinput) {
            _out << boost::format("dcl_resource_id(%i)_type(%id,unnorm)_fmtx(unknown)_fmty(unknown)_fmtz(unknown)_fmtw(unknown)\n") % iinput->first % iinput->second.first;
        }

        typename std::map<int,uav_data_t>::iterator iuav;

        for(iuav=uav_data.begin();iuav!=uav_data.end();++iuav) {
            switch( iuav->second.uav_type ) {
            case 0:
                _out << boost::format("dcl_uav_id(%i)_type(%s)_fmtx(%s)\n") % iuav->first % iuav->second.typed_type % iuav->second.typed_format;
                break;
            case 1:
                _out << boost::format("dcl_struct_uav_id(%i) %i\n") % iuav->first % iuav->second.struct_stride;
                break;
            case 2:
                _out << boost::format("dcl_raw_uav_id(%i)\n") % iuav->first;
                break;
            case 3:
                _out << boost::format("dcl_arena_uav_id(%i)\n") % iuav->first;
                break;
            }
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
    SourceGenerator()
    {
        next_instruction_index=0;
        next_literal_index = 0; 
    }
    ~SourceGenerator()
    {
    }

    void clear()
    {
        next_instruction_index=0;
        next_literal_index=0;

        input_data.clear();
        uav_data.clear();
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

    void registerUAV( int uav_index, int uav_type, int struct_stride, const std::string& typed_type, const std::string& typed_format )
    {
        uav_data[uav_index] = uav_data_t( uav_type, struct_stride, typed_type, typed_format );
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
#if defined(__CAL_HPP__) || defined(__CAL_H__)
        std::memset( &info, 0, sizeof(info) );
#endif
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
template<int N> typename SourceGenerator<N>::device_info SourceGenerator<N>::info;

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
