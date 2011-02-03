/*
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

/* 
 * This is version of nbody using double variables for computations
 * Point data variables ( p.x,p.y,p.z,p.m ) are splitted over 2 lines. (p.x,p.y) has position (x,y) and (p.z,p.m) has position (x,y+1)
 * Velocity data start at the half of the input buffer. Velocity is also splited over 2 lines in the same way.
 * This method of storing data is used so the reads can be coalesced and there is only 1 buffer ( compatibility with 4xxx gpus )
 *
 * Results:
 * 5850 - 664 GFLOPs ( almost exactly 1/4 of float kernel performance using the same parameters (workitem size, unroll size) )
 *
 */

#ifdef _MSC_VER
  #pragma warning( disable: 4522 )
#endif

#include <cal/cal.hpp>
#include <cal/cal_il.hpp>
#include <cal/il/math/cal_il_rsqrt.hpp>
#include "cal_il_double4.hpp"

using namespace boost;
using namespace cal::il;

void compute_interaction( const double4& a, const double4& b, double4& acc, double eps2, bool use_native )
{
    double1 distSqr,invDist,invDistCube,s;
    double4 r;

    r.x() = a.x() - b.x();
    r.y() = a.y() - b.y();
    r.z() = a.z() - b.z();

    distSqr     = mad( r.x(), r.x(), mad( r.y(), r.y(), mad( r.z(), r.z(), eps2 ) ) );
    invDist     = use_native?native_rsqrt( distSqr ):rsqrt( distSqr );
    invDistCube = invDist*invDist*invDist;
    s           = b.w() * invDistCube;

    acc.x() = mad( s, r.x(), acc.x() );
    acc.y() = mad( s, r.y(), acc.y() );
    acc.z() = mad( s, r.z(), acc.z() );
}

void compute_body_acceleration( const input2d<double2>& input_data, double4* pos, double4* acc,
                                uint1 tile_count, float1 _buffer_width, 
                                int workitem_size, int tile_size, int read_count, int unroll_count, double eps2,
                                bool native_rsqrt )
{
    double4 B[read_count];
    float1  px[read_count],rlimit,v,_py;
    uint1   t,c;
    float2  p;
    int     i,j,k;

    for(i=0;i<workitem_size;i++) acc[i] = double4(0);

    p = 0;
    il_while(tile_count)
    {
        rlimit = p.x() + (tile_size-1);
        px[0] = convert_float1( get_local_id(0) & (tile_size-1) ) + p.x();
        for(i=1;i<read_count;i++) px[i] = select( px[i-1]<rlimit, px[i-1]+1, p.x() );
        _py = p.y() + 1;

        rlimit = p.x() + (tile_size-read_count);
        c = tile_size/(read_count*unroll_count) + 1;
        il_whileloop
        {
            c = c - 1;
            il_breakc(!c);

            for(i=0;i<unroll_count;i++) {
                for(j=0;j<read_count;j++) B[j].xy()  = input_data(px[j],p.y());
                for(j=0;j<read_count;j++) B[j].zw()  = input_data(px[j],_py);

                for(j=0;j<workitem_size;j++) {
                    for(k=0;k<read_count;k++) compute_interaction(pos[j],B[k],acc[j],eps2,native_rsqrt);
                }

                for(j=0;j<read_count;j++) {
                    v = px[j] + read_count;
                    px[j] = select( px[j]<rlimit, v, v - tile_size );
                }
            }
        }
        il_endloop

        p.x()       = p.x() + tile_size;
        t           = p.x()<_buffer_width;
        p.x()       = select( t, p.x(), 0 );
        p.y()       = select( t, p.y(), p.y()+2 );
        tile_count -= 1;
    }
    il_endloop
}

void compute_body_position( double4* pos, double4* vel, double4* acc, double4* npos, double1& dT, int workitem_size )
{
    for(int i=0;i<workitem_size;i++) {
        npos[i].x() = pos[i].x() + (vel[i].x() + double1(0.5)*acc[i].x()*dT)*dT;
        npos[i].y() = pos[i].y() + (vel[i].y() + double1(0.5)*acc[i].y()*dT)*dT;
        npos[i].z() = pos[i].z() + (vel[i].z() + double1(0.5)*acc[i].z()*dT)*dT;
        npos[i].w() = pos[i].w();
    } 
}

void compute_body_velocity( double4* pos, double4* vel, double4* acc, double4* nvel, double1& dT, int workitem_size )
{
    for(int i=0;i<workitem_size;i++) {
        nvel[i].x() = vel[i].x() + acc[i].x()*dT;
        nvel[i].y() = vel[i].y() + acc[i].y()*dT;
        nvel[i].z() = vel[i].z() + acc[i].z()*dT;
        nvel[i].w() = double1(0);
    }
}

void nbody_kernel( const input2d<double2>& input_data, global<double2>& output_data,
                   uint1 data_size, uint1 tile_count,
                   uint1 buffer_width, float1 _buffer_width, float1 _buffer_height2,
                   double1 dT, double eps2, 
                   int workforce_size, int workitem_size, int tile_size, int read_count, int unroll_count,
                   bool native_rsqrt )
{
    double4 pos[workitem_size],vel[workitem_size],acc[workitem_size];
    double4 npos[workitem_size],nvel[workitem_size];
    float1  px[workitem_size],py,_py,py2;
    uint1   idx,off,_off;
    int     i;

    idx = get_global_id(0)*workitem_size;

    il_while(idx<data_size)
    {
        py    = 2*convert_float1(idx/buffer_width);
        _py   = py + 1;
        px[0] = convert_float1(idx%buffer_width);
        for(i=1;i<workitem_size;i++) px[i] = px[0] + i;
        for(i=0;i<workitem_size;i++) pos[i].xy() = input_data(px[i],py);
        for(i=0;i<workitem_size;i++) pos[i].zw() = input_data(px[i],_py);

        compute_body_acceleration( input_data, pos, acc, tile_count, _buffer_width, workitem_size, tile_size, read_count, unroll_count, eps2, native_rsqrt );

        py2 = py + _buffer_height2;
        _py = py2 + 1;
        for(i=0;i<workitem_size;i++) vel[i].xy() = input_data(px[i],py2);
        for(i=0;i<workitem_size;i++) vel[i].zw() = input_data(px[i],_py);

        compute_body_position( pos, vel, acc, npos, dT, workitem_size );
        off  = convert_uint1( py*_buffer_width + px[0] );
        _off = off + buffer_width;
        for(i=0;i<workitem_size;i++) output_data[off+i]  = npos[i].xy(); 
        for(i=0;i<workitem_size;i++) output_data[_off+i] = npos[i].zw(); 

        compute_body_velocity( pos, vel, acc, nvel, dT, workitem_size );
        off  = convert_uint1( py2*_buffer_width + px[0] );
        _off = off+buffer_width;
        for(i=0;i<workitem_size;i++) output_data[off+i]  = nvel[i].xy();
        for(i=0;i<workitem_size;i++) output_data[_off+i] = nvel[i].zw();

        idx += workforce_size*workitem_size;
    }
    il_endloop
}

std::string create_nbody_kernel( cal::Device& device, int num_threads, int workitem_size, int tile_size, int read_count, int unroll_count, double eps2, bool native_rsqrt )
{
    std::stringstream code;
    int               workforce_size,workgroup_size;

    workgroup_size = num_threads * device.getInfo<CAL_DEVICE_WAVEFRONTSIZE>();
    workforce_size = workgroup_size * device.getInfo<CAL_DEVICE_NUMBEROFSIMD>();

    code << "il_cs\n";
    code << format("dcl_num_thread_per_group %i\n") % workgroup_size;
    code << "dcl_cb cb0[2]\n";

    Source::begin(device);

    input2d<double2>        input_data(0);
    global<double2>         output_data;
    named_variable<uint1>   data_size("cb0[0].x"),tile_count("cb0[0].y"), buffer_width("cb0[0].z");
    named_variable<float1>  _buffer_width("cb0[1].x"),_buffer_height2("cb0[1].y");
    named_variable<double1> dT("cb0[1].zw");

    nbody_kernel( input_data, output_data,
                  data_size, tile_count, buffer_width, 
                  _buffer_width, _buffer_height2, 
                  dT, eps2,
                  workforce_size, workitem_size, tile_size, read_count, unroll_count,
                  native_rsqrt );

    Source::end();

    Source::emitHeader(code);
    Source::emitCode(code);

    code << "end\n";

    return code.str();
}
