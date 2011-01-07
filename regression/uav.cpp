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

    uav[4*gid] = gid;
}

void kernel_D()
{
    uav<uint4>  uav(0,"2d");
    uint1       gid = get_global_id<uint1>();
    uint1       x,y;

    x = gid/WORKGROUP_SIZE;
    y = gid%WORKGROUP_SIZE;

    uav(y,x) = uint4(gid,0,1,2);
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
Kernel          _kernel_A,_kernel_D;
CommandQueue    _queue;

Image2D         _output_A;
Image2D         _output_D;

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
    //program.disassemble(std::cout); // uncomment to output ISA
    _kernel_A = Kernel(program,"main");
    _kernel_A.setArgBind(0,"uav0");

    // create kernel D
    source  = create_kernel(kernel_D);
    //std::cout << source; // uncomment to output il source 
    program = Program( _context, source.c_str(), source.length() );
    program.build(devices);
    //program.disassemble(std::cout); // uncomment to output ISA
    _kernel_D = Kernel(program,"main");
    _kernel_D.setArgBind(0,"uav0");

    // create queue
    _queue = CommandQueue(_context,devices[dev]);

    // create output buffers
    _output_A = Image2D(_context, WORKGROUP_SIZE, WORKGROUP_COUNT, CAL_FORMAT_UINT_1, CAL_RESALLOC_GLOBAL_BUFFER );
    _output_D = Image2D(_context, WORKGROUP_SIZE, WORKGROUP_COUNT, CAL_FORMAT_UINT_4, CAL_RESALLOC_GLOBAL_BUFFER );
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

    // run kernel D1
    _kernel_D.setArg(0,_output_D);
    _queue.enqueueNDRangeKernel( _kernel_D, global, local, &event );
    _queue.flush();

    _queue.waitForEvent(event);
}

void print_result()
{
    std::cout << "RESULT A\n";
    print_data_uint(_output_A,1,1);

    std::cout << "\n\n\nRESULT D\n";
    print_data_uint(_output_D,4,4);
}

void release_gpu_resources()
{
    _queue     = CommandQueue();
    _kernel_A  = Kernel();
    _kernel_D  = Kernel();
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
