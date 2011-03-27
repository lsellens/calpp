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

variable<float4> functionA( const variable<uint1>& gid )
{
    variable<float4> r;
    
    il_func( r, gid ) 
    {
        r = float4( convert_float1(gid), convert_float1(gid), convert_float1(gid), convert_float1(gid) );
    } 
    il_endfunc
    
    return r;
}

void kernel()
{
    uint1           gid = get_global_id<uint1>();
    global<float4>  out;
    
    out[gid] = functionA(gid)+functionA(gid);
}

std::string create_kernel()
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
Kernel          _kernel;
CommandQueue    _queue;

Image1D         _output;


void print_data( Image1D& _data, int elem_size=1, int elem_group=1 )
{
    float       *data;
    CALuint     pitch;
    int         size = _data.getWidth()*elem_size;

    data = (float*)_queue.mapMemObject(_data,pitch);

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
    source  = create_kernel();
    std::cout << source;
    program = Program( _context, source.c_str(), source.length() );
    program.build(devices);
    _kernel = Kernel(program,"main");
    _kernel.setArgBind(0,"g[]");

    // create queue
    _queue = CommandQueue(_context,devices[dev]);
        
    // create output buffer
    _output = Image1D(_context, WORKGROUP_SIZE*WORKGROUP_COUNT, CAL_FORMAT_UINT_4, CAL_RESALLOC_GLOBAL_BUFFER );
}

void run()
{
    NDRange     global,local;
    Event       event;

    local  = NDRange(WORKGROUP_SIZE);
    global = NDRange(WORKGROUP_SIZE*WORKGROUP_COUNT);

    _kernel.setArg(0,_output);
    _queue.enqueueNDRangeKernel( _kernel, global, local, &event );
    _queue.flush();

    _queue.waitForEvent(event);
}

void print_result()
{
    std::cout << "RESULT\n";
    print_data(_output,4,4);
}

void release_gpu_resources()
{
    _queue     = CommandQueue();
    _kernel    = Kernel();
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
