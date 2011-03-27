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
#include <cal/cal_il_atomics.hpp>

using namespace boost;
using namespace cal;
using namespace cal::il;

#define WORKGROUP_SIZE      128
#define WORKGROUP_COUNT     16

void kernel_A()
{
    uav_raw<uint1> uav(0);
    uint1          gid = get_group_id<uint1>();

    // function with underscore doesn't read previous value
    _atom_add( uav[4*gid], 1 );
}

void kernel_B()
{
    uav_struct<uint1> uav(0,4);
    uint1             gid = get_group_id<uint1>();
    uint1             prev;

    prev = atom_add( uav(gid,0), 1 );
}

void kernel_C()
{
    uav<uint1> uav(0,"1d");
    uint1      gid = get_group_id<uint1>();
    uint1      prev;

    prev = atom_inc( uav(gid) );
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

    return code.str();
}

//
// 
//

Context         _context;
Kernel          _kernel_A,_kernel_B,_kernel_C;
CommandQueue    _queue;

Image1D         _output_A;
Image1D         _output_B;
Image1D         _output_C;

void set_data( Image1D& _data )
{
    boost::uint32_t  *data;
    CALuint          pitch;
    int              size = _data.getWidth();

    data = (boost::uint32_t*)_queue.mapMemObject(_data,pitch);

    for(int i=0;i<size;i++,data++) {
        *data = 0;
    }

    _queue.unmapMemObject(_data);
}

void print_data( Image1D& _data )
{
    boost::uint32_t  *data;
    CALuint          pitch;
    int              size = _data.getWidth();

    data = (boost::uint32_t*)_queue.mapMemObject(_data,pitch);

    for(int i=0;i<size;i++,data++) {
        std::cout << *data << ",";
    }
    std::cout << "\n";

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

    // create queue
    _queue = CommandQueue(_context,devices[dev]);

    // create output buffers
    _output_A = Image1D(_context, WORKGROUP_COUNT, CAL_FORMAT_UINT_1, 0 );
    _output_B = Image1D(_context, WORKGROUP_COUNT, CAL_FORMAT_UINT_1, 0 );
    _output_C = Image1D(_context, WORKGROUP_COUNT, CAL_FORMAT_UINT_1, 0 );

    set_data(_output_A);
    set_data(_output_B);
    set_data(_output_C);
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

    _queue.waitForEvent(event);
}

void print_result()
{
    std::cout << "RESULT A\n";
    print_data(_output_A);

    std::cout << "\n\n\nRESULT B\n";
    print_data(_output_B);

    std::cout << "\n\n\nRESULT C\n";
    print_data(_output_C);
}

void release_gpu_resources()
{
    _queue     = CommandQueue();
    _kernel_A  = Kernel();
    _kernel_B  = Kernel();
    _kernel_C  = Kernel();
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
