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
#include <cal/il/math/cal_il_rsqrt.hpp>

using namespace boost;
using namespace cal;
using namespace cal::il;

void kernel()
{
    named_variable<double2> output("o0");
    input2d<double2>        input(0);
    float2                  input_coord;
    uint1                   input_offset;
    uint4                   vector_size;
    uint2                   output_mask,v;
    double2                 x,w,w2;

    input_coord  = ps::get_global_id<float2>();
    v            = convert_uint2(input_coord);
    input_offset = ((v.y() << 8) + v.x()) << 1;

    vector_size  = named_variable<uint4>("cb0[0]");
    output_mask  = (uint2(input_offset,input_offset) + uint2(0,1))<vector_size.xy();

    w      = input[input_coord];
    w2     = -ldexp(w,-1);
    x      = native_rsqrt(w);
    x      = x*mad( x*x, w2, 1.5 );

    //*** select one of the following lines to have working/not working kernel
    x      = x*mad( x*x, w2, 1.5 ); // gives different value on o0.xy and o0.zw
    // x   = mad( x*x, w2, 1.5 );   // gives different value on o0.xy and o0.zw
    // x   = mad( x, w2, 1.5 );     // gives the same value on o0.xy and o0.zw
    //***

    output = select(output_mask,x,double2(0));
}

std::string create_kernel( Device& device )
{
    std::stringstream   code;

    code << "il_ps_2_0\n";
    code << "dcl_cb cb0[1]\n";
    code << "dcl_output_generic o0\n";

    Source::begin(device);
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
Kernel          _kernel;
CommandQueue    _queue;

Image2D         _input;
Image2D         _output;

void fill_data( Image2D& _data )
{
    double*  data;
    CALuint  pitch;
    unsigned size;

    data = (double*)_queue.mapMemObject(_data,pitch);
    size = 2*_data.getWidth()*_data.getHeight();

    for(unsigned i=0;i<size;i+=2) {
        *(data + 0) = i+1;
        *(data + 1) = i+1;

        data+=2;
    }

    _queue.unmapMemObject(_data);
}

void print_data( Image2D& _data )
{
    double*  data;
    CALuint  pitch;
    unsigned size;

    data = (double*)_queue.mapMemObject(_data,pitch);
    size = 2*_data.getWidth()*_data.getHeight();

    for(unsigned i=0;i<size;i+=2) {
        std::cout << boost::format("(%.3f,%.3f)") % *data % *(data+1);
        if( *data == *(data+1) ) std::cout << " OK\n";
        else std::cout << " INVALID RESULT\n";

        data+=2;
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
    source  = create_kernel(devices[dev]);
    std::cout << source; // uncomment to output il source 
    program = Program( _context, source.c_str(), source.length() );
    program.build(devices);
    program.disassemble(std::cout); // uncomment to emit ISA
    _kernel = Kernel(program,"main");
    _kernel.setArgBind(0,"cb0",0,16);
    _kernel.setArgBind(1,"i0");
    _kernel.setArgBind(2,"o0");

    // create queue
    _queue = CommandQueue(_context,devices[dev]);

    // create buffers
    _input  = Image2D( _context, 256, 64, CAL_FORMAT_UINT_4, 0 );
    _output = Image2D( _context, 256, 64, CAL_FORMAT_UINT_4, 0 );

    fill_data(_input);
}

void run()
{
    NDRange                         global;
    Event                           event;
    boost::array<boost::uint32_t,4> size;

    size.assign(2*256*64);
    global = NDRange(256,64);

    // run kernel A
    _kernel.setArg(0,size);
    _kernel.setArg(1,_input);
    _kernel.setArg(2,_output);
    _queue.enqueueNDRangeKernel( _kernel, global, &event );
    _queue.flush();

    _queue.waitForEvent(event);
}

void print_result()
{
    print_data(_output);
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
