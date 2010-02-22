/*
 * C++ to IL compiler/generator flattening 2d workspace support
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

#ifndef __CAL_IL_FLAT2D_H
#define __CAL_IL_FLAT2D_H

#include <cal/il/cal_il_source.hpp>
#include <cal/il/cal_il_types.hpp>
#include <cal/il/cal_il_misc.hpp>

#ifdef __CAL_HPP
  #include <boost/array.hpp>
#endif

namespace cal {
namespace il {
namespace flat2d {

inline uint4 get_local_size()
{
    return named_variable<uint4>("cb0[0].xy00");
}

inline uint1 get_local_size( int i )
{
    assert( i>=0 && i<2 );
    if( i==0 ) return named_variable<uint1>("cb0[0].x");
    return named_variable<uint1>("cb0[0].y");    
}

inline uint4 get_global_size()
{
    return named_variable<uint4>("cb0[0].zw00");
}

inline uint1 get_global_size( int i )
{
    assert( i>=0 && i<2 );
    if( i==0 ) return named_variable<uint1>("cb0[0].z");
    return named_variable<uint1>("cb0[0].w");
}

inline uint4 get_local_id()
{
    return uint4( named_variable<uint1>("vTidInGrpFlat.x") % named_variable<uint1>("cb0[0].x"),
                  named_variable<uint1>("vTidInGrpFlat.x") / named_variable<uint1>("cb0[0].x"),
                  uint1(0), uint1(0) );
}

inline uint1 get_local_id( int i )
{
    assert( i>=0 && i<2 );
    if( i==0 ) return named_variable<uint1>("vTidInGrpFlat.x") % named_variable<uint1>("cb0[0].x");
    return named_variable<uint1>("vTidInGrpFlat.x") / named_variable<uint1>("cb0[0].x");
}

inline uint4 get_global_id()
{
    return uint4( named_variable<uint1>("vAbsTidFlat.x") % named_variable<uint1>("cb0[0].z"),
                  named_variable<uint1>("vAbsTidFlat.x") / named_variable<uint1>("cb0[0].z"),
                  uint1(0), uint1(0) );
}

inline uint1 get_global_id( int i )
{
    assert( i>=0 && i<2 );
    if( i==0 ) return named_variable<uint1>("vAbsTidFlat.x") % named_variable<uint1>("cb0[0].z");
    return named_variable<uint1>("vAbsTidFlat.x") / named_variable<uint1>("cb0[0].z");
}


inline uint4 get_num_groups()
{
    return uint4( named_variable<uint1>("cb0[0].z") / named_variable<uint1>("cb0[0].x"),
                  named_variable<uint1>("cb0[0].w") / named_variable<uint1>("cb0[0].y"),
                  uint1(0), uint1(0) );
}

inline uint1 get_num_groups( int i )
{
    assert( i>=0 && i<2 );
    if( i==0 ) return named_variable<uint1>("cb0[0].z") / named_variable<uint1>("cb0[0].x");
    return named_variable<uint1>("cb0[0].w") / named_variable<uint1>("cb0[0].y");
}

inline uint4 get_group_id()
{
    return uint4( named_variable<uint1>("vThreadGrpIdFlat.x") % get_num_groups(0),
                  named_variable<uint1>("vThreadGrpIdFlat.x") / get_num_groups(1),
                  uint1(0), uint1(0) );
}

inline uint1 get_group_id( int i )
{
    assert( i>=0 && i<2 );
    if( i==0 ) return named_variable<uint1>("vThreadGrpIdFlat.x") % get_num_groups(0);
    return named_variable<uint1>("vThreadGrpIdFlat.x") / get_num_groups(1);
}

#ifdef __CAL_HPP

inline void make_flat( ::cal::NDRange& global, ::cal::NDRange& local, const ::cal::NDRange& _global, const ::cal::NDRange& _local )
{
    global.width  = _local.width*((_global.width+_local.width-1)/_local.width);
    global.height = _local.height*((_global.height+_local.height-1)/_local.height);

    global.width  = global.width*global.height;
    global.height = 1;
    global.depth  = 1;

    local.width   = _local.width*_local.height;
    local.height  = 1;
    local.depth   = 1;
}

inline ::cal::NDRange make_flat_global( const ::cal::NDRange& _global, const ::cal::NDRange& _local )
{
    ::cal::NDRange  global;
    
    global.width  = _local.width*((_global.width+_local.width-1)/_local.width);
    global.height = _local.height*((_global.height+_local.height-1)/_local.height);

    global.width  = global.width*global.height;
    global.height = 1;
    global.depth  = 1;

    return global;
}

inline ::cal::NDRange make_flat_local( const ::cal::NDRange& _local )
{
    ::cal::NDRange  local;
    
    local.width  = _local.width*_local.height;
    local.height = 1;
    local.depth  = 1;
    
    return local;
}

inline boost::array<uint32_t,4> make_flat_cb0( const ::cal::NDRange& global, const ::cal::NDRange& local )
{
    boost::array<uint32_t,4>    result;

    result[0] = local.width;
    result[1] = local.height;
    result[2] = local.width*((global.width+local.width-1)/local.width);
    result[3] = local.height*((global.height+local.height-1)/local.height);

    return result;
}

#endif

} // flat2d
} // il
} // cal

#endif
