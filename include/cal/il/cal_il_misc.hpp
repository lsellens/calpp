/*
 * C++ to IL compiler/generator misc functions
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

#include <boost/format.hpp>
#include <boost/bind.hpp>
#include <string>
#include <cal/il/math/cal_il_floor.hpp>

#ifndef __CAL_IL_MISC_H
#define __CAL_IL_MISC_H


namespace cal {
namespace il {

enum CALILBarrierTypeEnum
{
    CAL_THREADS_FENCE    = 1,
    CAL_LOCAL_MEM_FENCE  = 2,
    CAL_GLOBAL_MEM_FENCE = 4,
    CAL_SR_FENCE         = 8
};

inline void cal_fence( int type )
{
    std::string txt = "fence";
    if( type&CAL_THREADS_FENCE    ) txt += "_threads";
    if( type&CAL_LOCAL_MEM_FENCE  ) txt += "_lds";
    if( type&CAL_GLOBAL_MEM_FENCE ) txt += "_memory";
    if( type&CAL_SR_FENCE         ) txt += "_sr";
    Source::code() << txt << "\n";
}

inline void barrier( int type )
{
    cal_fence(type|(int)CAL_THREADS_FENCE);
}

inline void mem_fence( int type )
{
    type &= (CAL_LOCAL_MEM_FENCE | CAL_GLOBAL_MEM_FENCE);
    cal_fence(type);
}

inline void read_mem_fence( int type )
{
    std::string txt = "fence";
    if( type&CAL_LOCAL_MEM_FENCE ) txt += "_lds";
    if( type&CAL_GLOBAL_MEM_FENCE ) txt += "_mem_read_only";
    Source::code() << txt << "\n";
}

inline void write_mem_fence( int type )
{
    std::string txt = "fence";
    if( type&CAL_LOCAL_MEM_FENCE ) txt += "_lds";
    if( type&CAL_GLOBAL_MEM_FENCE ) txt += "_mem_write_only";
    Source::code() << txt << "\n";
}

template<class T> named_variable<T> get_global_id();

template<>
inline named_variable<uint1> get_global_id()
{
    return named_variable<uint1>("vAbsTidFlat");
}

template<>
inline named_variable<uint4> get_global_id()
{
    return named_variable<uint4>("vAbsTid.xyzx");
}

inline named_variable<uint1> get_global_id( int idx )
{
    assert( idx>=0 && idx<3 );
    if( idx==0 ) return named_variable<uint1>("vAbsTid.x");
    else if( idx==1 ) return named_variable<uint1>("vAbsTid.y");
    return named_variable<uint1>("vAbsTid.z");
}

template<class T> named_variable<T> get_local_id();

template<>
inline named_variable<uint1> get_local_id()
{
    return named_variable<uint1>("vTidInGrpFlat");
}

template<>
inline named_variable<uint4> get_local_id()
{
    return named_variable<uint4>("vTidInGrp.xyzx");
}

inline named_variable<uint1> get_local_id( int idx )
{
    assert( idx>=0 && idx<3 );
    if( idx==0 ) return named_variable<uint1>("vTidInGrp.x");
    else if( idx==1 ) return named_variable<uint1>("vTidInGrp.y");
    return named_variable<uint1>("vTidInGrp.z");
}

template<class T> named_variable<T> get_group_id();

template<>
inline named_variable<uint1> get_group_id()
{
    return named_variable<uint1>("vThreadGrpIdFlat");
}

template<>
inline named_variable<uint4> get_group_id()
{
    return named_variable<uint4>("vThreadGrpId.xyzx");
}

inline named_variable<uint1> get_group_id( int idx )
{
    assert( idx>=0 && idx<3 );
    if( idx==0 ) return named_variable<uint1>("vThreadGrpId.x");
    else if( idx==1 ) return named_variable<uint1>("vThreadGrpId.y");
    return named_variable<uint1>("vThreadGrpId.z");
}

inline void emit_comment( const std::string& comment )
{
    Source::code() << ";" << comment << "\n";
}

namespace ps {

namespace detail {

    template<int N>
    struct dcl_helper
    {
        static std::string emit_dcl() { return "dcl_input_position_interp(linear_noperspective) vWinCoord0.xy__"; }
    };

} // detail

template<class T> T get_global_id();

template<>
inline float2 get_global_id()
{
    Source::code().registerDCL( "ps:vWinCoord0", boost::bind(&detail::dcl_helper<0>::emit_dcl) );
    return floor(named_variable<float2>("vWinCoord0.xy"));
}

template<>
inline uint2 get_global_id()
{
    Source::code().registerDCL( "ps:vWinCoord0", boost::bind(&detail::dcl_helper<0>::emit_dcl) );
    return cast_type<uint2>(named_variable<float2>("vWinCoord0.xy"));
}

template<class T> T get_global_id( int idx );

template<>
inline float1 get_global_id( int idx )
{
    Source::code().registerDCL( "ps:vWinCoord0", boost::bind(&detail::dcl_helper<0>::emit_dcl) );

    if( idx==0 ) return floor(named_variable<float1>("vWinCoord0.x"));
    return floor(named_variable<float1>("vWinCoord0.y"));
}

template<>
inline uint1 get_global_id( int idx )
{
    Source::code().registerDCL( "ps:vWinCoord0", boost::bind(&detail::dcl_helper<0>::emit_dcl) );

    if( idx==0 ) return cast_type<uint1>(named_variable<float1>("vWinCoord0.x"));
    return cast_type<uint1>(named_variable<float1>("vWinCoord0.y"));
}

} // ps

} // il
} // cal

#endif

