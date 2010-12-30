/*
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

/* After lookin at the n-body example in ATI SDK and posting optimization tips 
 * I've had a feeling that it should be possible to squeeze all the juice out of ATI card.
 * My first step was to run some numbers.
 *
 * - 5870 can do 850M*1600 ops,
 *
 * - computing interaction between bodies takes 13 ops.
 *
 * - we need to transfer 16B for 1 interaction
 *
 * So 5870 can compute 104G interactions per sec and need to transfer 1673GB/s.
 *
 * As we see our problem is memory transfer. It's over 10x higher than what's available ( ~150GB/s ).
 * We notice that for n-body problem if we group k particles, than we can read data for that group once. This reduces transfer k times.
 *
 * L1 cache can be used for decreasing transfer from global memory. We will load data for whole work group once. 
 * After setting work group size to 256 transfer from global memory is limited to ~0.5GB/s.
 *
 * But this doesn't solve our problem. L1 cache has agregate transfer of ~1TB/s - this is still not enough.
 * 
 * Most developers forget that there is one important difference between Nvidia and ATI cards. 
 * ATI cards have much bigger register file. And these registers can be used as ultimate cache !!!
 *
 * So next step is to group particles in registers. Register file is much smaller than cache so we can have only 8(remark 1) particles grouped in one work item. 
 * This reduce transfer requirement on L1 cache from 1.6TB/s to 210GB/s. Finally we are at home and we can start coding 
 * 
 * Results:
 * Using classical flops count for force calculation (38 flops) 4770 is doing 1250 GFlops/s - this gives 90% peek ops efficiency. 
 * 4% goes for necessary memory index calculations. This gives total 94% used only for computations. 
 * 
 * Performance for other cards
 * 5850 - 2800 GFLOPs ( 2950 GFLOPs with workitem size 10 )
 *
 * Here are estimated values for other cards.
 * 4870 - 1580 GFLOPs (vs 1TFLOP for best know solution at the moment of writing)
 * 5870 - 3580 GFLOPs
 *
 * Remark 1
 * It's possible to use larger workitem size (10). This gives kernel with maximum number of register used for 4 threads.
 * Unfortunatelly on 4xxx cards this leads to some unstable behaviour - results are ranging from 88% to 92% peek ops depending on the run.
 * On 5xxx cards results are much more stable and workitem size = 10 gives best performance.
 */

#ifdef _MSC_VER
  #pragma warning( disable: 4522 )
#endif

#include <cal/cal.hpp>
#include <cal/il/cal_il.hpp>
#include <cal/il/math/cal_il_rsqrt.hpp>

using namespace boost;
using namespace cal::il;

void compute_interaction( const float4& a, const float4& b, float4& acc, float eps2 )
{
    float1 distSqr,invDist,invDistCube,s;
    float4 r;

    r.x() = a.x() - b.x();
    r.y() = a.y() - b.y();
    r.z() = a.z() - b.z();

    distSqr     = mad( r.x(), r.x(), mad( r.y(), r.y(), mad( r.z(), r.z(), eps2 ) ) );
    invDist     = rsqrt( distSqr );
    invDistCube = invDist*invDist*invDist;
    s           = b.w() * invDistCube;

    acc.x() = mad( s, r.x(), acc.x() );
    acc.y() = mad( s, r.y(), acc.y() );
    acc.z() = mad( s, r.z(), acc.z() );
}

void compute_body_acceleration( const input2d<float4>& input_data, float4* pos, float4* acc,
                                uint1 tile_count, float1 _buffer_width, 
                                int workitem_size, int tile_size, int read_count, int unroll_count, float eps2 )
{
    float4 B[read_count];
    float1 px[read_count],rlimit,v;
    uint1  t,c;
    float2 p;
    int    i,j,k;

    for(i=0;i<workitem_size;i++) acc[i] = 0;

    p = 0;
    il_while(tile_count)
    {
        rlimit = p.x() + (tile_size-1);
        px[0] = convert_float1( get_local_id(0) & (tile_size-1) ) + p.x();
        for(i=1;i<read_count;i++) px[i] = select( px[i-1]<rlimit, px[i-1]+1, p.x() );

        rlimit = p.x() + (tile_size-read_count);
        c = tile_size/(read_count*unroll_count) + 1;
        il_whileloop
        {
            c = c - 1;
            il_breakc(!c);

            for(i=0;i<unroll_count;i++) {
                for(j=0;j<read_count;j++) B[j]  = input_data(px[j],p.y());

                for(j=0;j<workitem_size;j++) {
                    for(k=0;k<read_count;k++) compute_interaction(pos[j],B[k],acc[j],eps2);
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
        p.x()       = select( t, p.x(), float1(0) );
        p.y()       = select( t, p.y(), p.y()+1 );
        tile_count -= 1;
    }
    il_endloop
}

void compute_body_position( float4* pos, float4* vel, float4* acc, float4* npos, float1& dT, int workitem_size )
{
    for(int i=0;i<workitem_size;i++) {
        npos[i].x() = pos[i].x() + (vel[i].x() + float1(0.5)*acc[i].x()*dT)*dT;
        npos[i].y() = pos[i].y() + (vel[i].y() + float1(0.5)*acc[i].y()*dT)*dT;
        npos[i].z() = pos[i].z() + (vel[i].z() + float1(0.5)*acc[i].z()*dT)*dT;
        npos[i].w() = pos[i].w();
    } 
}

void compute_body_velocity( float4* pos, float4* vel, float4* acc, float4* nvel, float1& dT, int workitem_size )
{
    for(int i=0;i<workitem_size;i++) {
        nvel[i].x() = vel[i].x() + acc[i].x()*dT;
        nvel[i].y() = vel[i].y() + acc[i].y()*dT;
        nvel[i].z() = vel[i].z() + acc[i].z()*dT;
        nvel[i].w() = float1(0);
    }
}

void nbody_kernel( const input2d<float4>& input_data, global<float4>& output_data,
                   uint1 data_size, uint1 tile_count,
                   uint1 buffer_width, float1 _buffer_width, float1 _buffer_height2,
                   float1 dT, float eps2, 
                   int workforce_size, int workitem_size, int tile_size, int read_count, int unroll_count )
{
    float4 pos[workitem_size],vel[workitem_size],acc[workitem_size];
    float4 npos[workitem_size],nvel[workitem_size];
    float1 px[workitem_size],py,py2;
    uint1  idx,off;
    int    i;

    idx = get_global_id(0)*workitem_size;

    il_while(idx<data_size)
    {
        py    = convert_float1(idx/buffer_width);
        px[0] = convert_float1(idx%buffer_width);
        for(i=1;i<workitem_size;i++) px[i] = px[0] + i;
        for(i=0;i<workitem_size;i++) pos[i] = input_data(px[i],py);

        compute_body_acceleration( input_data, pos, acc, tile_count, _buffer_width, workitem_size, tile_size, read_count, unroll_count, eps2 );

        py2 = py + _buffer_height2;
        for(i=0;i<workitem_size;i++) vel[i] = input_data(px[i],py2);

        compute_body_position( pos, vel, acc, npos, dT, workitem_size );
        off = convert_uint1( py*_buffer_width + px[0] );
        for(i=0;i<workitem_size;i++) output_data[off+i] = npos[i];

        compute_body_velocity( pos, vel, acc, nvel, dT, workitem_size );
        off = convert_uint1( py2*_buffer_width + px[0] );
        for(i=0;i<workitem_size;i++) output_data[off+i] = nvel[i];

        idx += workforce_size*workitem_size;
    }
    il_endloop
}

std::string create_nbody_kernel( cal::Device& device, int num_threads, int workitem_size, int tile_size, int read_count, int unroll_count, float eps2 )
{
    std::stringstream code;
    int               workforce_size,workgroup_size;

    workgroup_size = num_threads * device.getInfo<CAL_DEVICE_WAVEFRONTSIZE>();
    workforce_size = workgroup_size * device.getInfo<CAL_DEVICE_NUMBEROFSIMD>();

    code << "il_cs\n";
    code << format("dcl_num_thread_per_group %i\n") % workgroup_size;
    code << "dcl_cb cb0[2]\n";

    Source::begin(device);

    input2d<float4>        input_data(0);
    global<float4>         output_data;
    named_variable<uint1>  data_size("cb0[0].x"),tile_count("cb0[0].y"), buffer_width("cb0[0].z");
    named_variable<float1> _buffer_width("cb0[1].x"),_buffer_height2("cb0[1].y"),dT("cb0[1].z");

    nbody_kernel( input_data, output_data,
                  data_size, tile_count, buffer_width, 
                  _buffer_width, _buffer_height2, 
                  dT, eps2,
                  workforce_size, workitem_size, tile_size, read_count, unroll_count );

    Source::end();

    Source::emitHeader(code);
    Source::emitCode(code);

    code << "end\n";

    return code.str();
}
