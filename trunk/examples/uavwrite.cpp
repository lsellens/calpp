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

#ifdef _MSC_VER
  #pragma warning( disable : 4522 )
#endif

#include <iostream>
#include <boost/format.hpp>
#include <cal/cal.hpp>
#include <cal/cal_il.hpp>

using namespace boost;
using namespace cal;
using namespace cal::il;

#define WORKGROUP_SIZE      128
#define WORKGROUP_COUNT     8

void kernel_A()
{
    uav_raw<uint1> uav(0);
    uint1          gid = get_global_id<uint1>();

    // raw uav is addressed in bytes, so we need to multiply gid by sizeof(uint)
    uav[4*gid] = gid;
}

void kernel_B()
{
    uav_struct<uint1> uav(0,16);
    uint1             gid = get_global_id<uint1>();

    uav(gid,0)  = gid;
    uav(gid,4)  = 0;
    uav(gid,8)  = 1;
    uav(gid,12) = 2;
}

void kernel_C()
{
    uav<uint1> uav(0,"1d");
    uint1      gid = get_global_id<uint1>();

    uav(gid) = gid;
}

void kernel_C1()
{
    uav<uint2> uav(0,"1d");
    uint1      gid = get_global_id<uint1>();

    uav(gid) = uint2(gid,0);
}

void kernel_D()
{
    uav<uint1> uav(0,"2d");
    uint1      gid = get_global_id<uint1>();
    uint1      x,y;

    x = gid/WORKGROUP_SIZE;
    y = gid%WORKGROUP_SIZE;

    uav(y,x) = gid;
}

void kernel_D1()
{
    uav<float4> uav(0,"2d"); // float used to show it's possible
    uint1       gid = get_global_id<uint1>();
    uint1       x,y;

    x = gid/WORKGROUP_SIZE;
    y = gid%WORKGROUP_SIZE;

    uav(y,x) = as_float4( uint4(gid,0,1,2) );
}

std::string create_kernel( void (*kernel)() )
{
    std::stringstream   code;

    code << "il_cs\n";
    code << format("dcl_num_thread_per_group %i\n") % WORKGROUP_SIZE;

    Source::begin();
    kernel();
    Source::end();

    Source::emitHeader(code);
    Source::emitCode(code);

    code << "end\n";

    return code.str();
}

//
// 
//

Context         _context;
Kernel          _kernel_A,_kernel_B,_kernel_C,_kernel_C1,_kernel_D,_kernel_D1;
CommandQueue    _queue;

Image1D         _output_A;
//Image2D       _output_A;
Image1D         _output_B;
Image1D         _output_C;
Image1D         _output_C1;
Image2D         _output_D;
Image2D         _output_D1;


void print_data_uint( Image1D& _data, int elem_size=1, int elem_group=1 )
{
    boost::uint32_t  *data;
    CALuint          pitch;
    int              size = _data.getWidth()*elem_size;

    data = (boost::uint32_t*)_queue.mapMemObject(_data,pitch);

    for(int i=0;i<size;i+=elem_group) {
        if( i>0 && ((i/elem_group)%WORKGROUP_SIZE)==0 ) std::cout << "\n";
        std::cout << "(";
        for(int j=0;j<elem_group;j++,data++) {
            if(j>0) std::cout << ",";
            std::cout << (*data);
        }
        std::cout << "),";
    }

    _queue.unmapMemObject(_data);
}

void print_data_uint( Image2D& _data, int elem_size=1, int elem_group=1 )
{
    boost::uint32_t  *data;
    CALuint          pitch;
    int              size = _data.getWidth()*_data.getHeight()*elem_size;

    data = (boost::uint32_t*)_queue.mapMemObject(_data,pitch);

    for(int i=0;i<size;i+=elem_group) {
        if( i>0 && ((i/elem_group)%WORKGROUP_SIZE)==0 ) std::cout << "\n";
        std::cout << "(";
        for(int j=0;j<elem_group;j++,data++) {
            if(j>0) std::cout << ",";
            std::cout << (*data);
        }
        std::cout << "),";
    }

    _queue.unmapMemObject(_data);
}


void init()
{
   _context = Context(CAL_DEVICE_TYPE_GPU);
}

void setup( int dev )
{
    std::vector<Device> devices = _context.getInfo<CAL_CONTEXT_DEVICES>();
    std::string source;
    Program     program;

    // create kernel A
    source  = create_kernel(kernel_A);
    //std::cout << source; // uncomment to output il source 
    program = Program( _context, source.c_str(), source.length() );
    program.build(devices);
    _kernel_A = Kernel(program,"main");
    _kernel_A.setArgBind(0,"uav0");

    // create kernel B
    source  = create_kernel(kernel_B);
    //std::cout << source; // uncomment to output il source 
    program = Program( _context, source.c_str(), source.length() );
    program.build(devices);
    _kernel_B = Kernel(program,"main");
    _kernel_B.setArgBind(0,"uav0");

    // create kernel C
    source  = create_kernel(kernel_C);
    //std::cout << source; // uncomment to output il source 
    program = Program( _context, source.c_str(), source.length() );
    program.build(devices);
    _kernel_C = Kernel(program,"main");
    _kernel_C.setArgBind(0,"uav0");

    // create kernel C1
    source  = create_kernel(kernel_C1);
    //std::cout << source; // uncomment to output il source 
    program = Program( _context, source.c_str(), source.length() );
    program.build(devices);
    _kernel_C1 = Kernel(program,"main");
    _kernel_C1.setArgBind(0,"uav0");

    // create kernel D
    source  = create_kernel(kernel_D);
    //std::cout << source; // uncomment to output il source 
    program = Program( _context, source.c_str(), source.length() );
    program.build(devices);
    _kernel_D = Kernel(program,"main");
    _kernel_D.setArgBind(0,"uav0");

    // create kernel D1
    source  = create_kernel(kernel_D1);
    //std::cout << source; // uncomment to output il source 
    program = Program( _context, source.c_str(), source.length() );
    program.build(devices);
    _kernel_D1 = Kernel(program,"main");
    _kernel_D1.setArgBind(0,"uav0");

    // create queue
    _queue = CommandQueue(_context,devices[dev]);

    // create output buffers

    // raw uav - buffer must be 1D, possible buffer types are UINT_1, INT_1, FLOAT_1
    _output_A = Image1D(_context, WORKGROUP_SIZE*WORKGROUP_COUNT, CAL_FORMAT_UINT_1, 0 );
    // this one isn't working ( probably due to bug in CAL ) even though it is example from CAL Manual
    //_output_A = Image2D(_context, WORKGROUP_SIZE, WORKGROUP_COUNT, CAL_FORMAT_UINT_1, CAL_RESALLOC_GLOBAL_BUFFER );

    // struct uav - buffer must be 1D, possible buffer types are UINT_1, INT_1, FLOAT_1
    _output_B = Image1D(_context, 4*WORKGROUP_SIZE*WORKGROUP_COUNT, CAL_FORMAT_UINT_1, 0 );

    // typed uav 1D
    _output_C = Image1D(_context, WORKGROUP_SIZE*WORKGROUP_COUNT, CAL_FORMAT_UINT_1, 0 );

    // typed uav 1D
    _output_C1 = Image1D(_context, WORKGROUP_SIZE*WORKGROUP_COUNT, CAL_FORMAT_UINT_2, 0 );

    // typed uav 2D
    _output_D = Image2D(_context, WORKGROUP_SIZE, WORKGROUP_COUNT, CAL_FORMAT_UINT_1, 0 );

    // typed uav 2D
    _output_D1 = Image2D(_context, WORKGROUP_SIZE, WORKGROUP_COUNT, CAL_FORMAT_FLOAT_4, 0 );
    // this one also doesn't work ( probably bug in CAL )
    //_output_D1 = Image2D(_context, WORKGROUP_SIZE, WORKGROUP_COUNT, CAL_FORMAT_FLOAT_4, CAL_RESALLOC_GLOBAL_BUFFER );
}

void run()
{
    NDRange     global,local;
    Event       event;

    local  = NDRange(WORKGROUP_SIZE);
    global = NDRange(WORKGROUP_SIZE*WORKGROUP_COUNT);

    // run kernel A
    _kernel_A.setArg(0,_output_A);
    _queue.enqueueNDRangeKernel( _kernel_A, global, local, &event );
    _queue.flush();

    // run kernel B
    _kernel_B.setArg(0,_output_B);
    _queue.enqueueNDRangeKernel( _kernel_B, global, local, &event );
    _queue.flush();

    // run kernel C
    _kernel_C.setArg(0,_output_C);
    _queue.enqueueNDRangeKernel( _kernel_C, global, local, &event );
    _queue.flush();

    // run kernel C1
    _kernel_C1.setArg(0,_output_C1);
    _queue.enqueueNDRangeKernel( _kernel_C1, global, local, &event );
    _queue.flush();

    // run kernel D
    _kernel_D.setArg(0,_output_D);
    _queue.enqueueNDRangeKernel( _kernel_D, global, local, &event );
    _queue.flush();

    // run kernel D1
    _kernel_D1.setArg(0,_output_D1);
    _queue.enqueueNDRangeKernel( _kernel_D1, global, local, &event );
    _queue.flush();

    _queue.waitForEvent(event);
}

void print_result()
{
    std::cout << "RESULT A\n";
    print_data_uint(_output_A,1,1);

    std::cout << "\n\n\nRESULT B\n";
    print_data_uint(_output_B,1,4);

    std::cout << "\n\n\nRESULT C\n";
    print_data_uint(_output_C,1,1);

    std::cout << "\n\n\nRESULT C1\n";
    print_data_uint(_output_C1,2,2);

    std::cout << "\n\n\nRESULT D\n";
    print_data_uint(_output_D,1,1);

    std::cout << "\n\n\nRESULT D1\n";
    print_data_uint(_output_D1,4,4);
}

void release_gpu_resources()
{
    _queue     = CommandQueue();
    _kernel_A  = Kernel();
    _kernel_B  = Kernel();
    _kernel_C  = Kernel();
    _kernel_C1 = Kernel();
    _kernel_D  = Kernel();
    _kernel_D1 = Kernel();
    _context   = Context();
}

int main( int argc, char* argv[] )
{
    cal::Init();
    init();

    setup(0);
    run();
    print_result();

    release_gpu_resources();
    cal::Shutdown();

    return 0;
}
