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

#include <boost/format.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cal/cal.hpp>
#include <cal/cal_il.hpp>

using namespace boost;
using namespace cal;
using namespace cal::il;

#define MAX_THREADS         16
#define NR_ITERATIONS       0x100000
#define NR_MAD_INST         209

void kernel_peekperf()
{
    global<float4>      result;
    float4              a,b;
    uint1               i;

    a = 42;
    b = 42;
    i = NR_ITERATIONS;

    il_while(i) {
        for(int k=0;k<(NR_MAD_INST/2);k++) {
            a = mad(a,a,a);
            b = mad(b,b,b);
        }
        a = mad(a,a,a);

        i -= 1;
    }
    il_endloop

    result[get_global_id<uint1>()] = a+b;
}

std::string create_kernel_peekperf( int workgroup_size )
{
    std::stringstream   code;

    code << "il_cs\n";
    code << format("dcl_num_thread_per_group %i\n") % workgroup_size;

    Source::begin();
    kernel_peekperf();
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
Program         _program;
Kernel          _kernel;
CommandQueue    _queue;
int             _dev_count;

Image2D         _output;
int             _nr_groups;
int             _exec_time;

int init()
{
   _context = Context(CAL_DEVICE_TYPE_GPU);

    std::vector<Device> devices = _context.getInfo<CAL_CONTEXT_DEVICES>();
    _dev_count =  devices.size();

    return _dev_count;
}

void setup( int dev, int workgroup_size )
{
    std::vector<Device> devices = _context.getInfo<CAL_CONTEXT_DEVICES>();

    // create program
    std::string source = create_kernel_peekperf(workgroup_size);
    //std::cout << source; // Uncomment to emit IL code
    _program = Program( _context, source.c_str(), source.length() );
    _program.build(devices);
    //_program.disassemble(std::cout); // Uncomment to emit ISA code

    // create kernel
    _kernel = Kernel(_program,"main");
    _kernel.setArgBind(0,"g[]");

    _nr_groups = devices[dev].getInfo<CAL_DEVICE_NUMBEROFSIMD>();

    _queue = CommandQueue(_context,devices[dev]);

    // create output buffer
    int width = 64*((workgroup_size + 63)/64);
    _output = Image2D(_context, width, _nr_groups, CAL_FORMAT_FLOAT_4, CAL_RESALLOC_GLOBAL_BUFFER );
}

void run( int workgroup_size )
{
    NDRange     global,local;
    Event       event;

    local  = NDRange(workgroup_size);
    global = NDRange(_nr_groups*workgroup_size);

    posix_time::ptime t1 = posix_time::microsec_clock::local_time();

    _kernel.setArg(0,_output);
    _queue.enqueueNDRangeKernel( _kernel, global, local, &event );
    _queue.flush();

    _queue.waitForEvent(event);

    posix_time::ptime t2 = posix_time::microsec_clock::local_time();

    _exec_time = posix_time::time_period(t1,t2).length().total_microseconds();
}

void show_device_info( int dev )
{
    std::vector<Device> devices = _context.getInfo<CAL_CONTEXT_DEVICES>();

    std::cout << format("Device              %i\n"
                        "target              %u\n"
                        "localRAM            %u MB\n"
                        "uncachedRemoteRAM   %u MB\n"
                        "cachedRemoteRAM     %u MB\n"
                        "engineClock         %u MHz\n"
                        "memoryClock         %u MHz\n"
                        "wavefrontSize       %u\n"
                        "numberOfSIMD        %u\n"
                        "doublePrecision     %u\n"
                        "localDataShare      %u\n"
                        "globalDataShare     %u\n"
                        "globalGPR           %u\n"
                        "computeShader       %u\n"
                        "memExport           %u\n"
                        "pitch_alignment     %u\n"
                        "surface_alignment   %u\n"
                        "maxResource1DWidth  %u\n"
                        "maxResource2DWidth  %u\n"
                        "maxResource2DHeight %u\n")
    % dev
    % devices[dev].getInfo<CAL_DEVICE_TARGET>()
    % devices[dev].getInfo<CAL_DEVICE_LOCALRAM>()
    % devices[dev].getInfo<CAL_DEVICE_UNCACHEDREMOTERAM>()
    % devices[dev].getInfo<CAL_DEVICE_CACHEDREMOTERAM>()
    % devices[dev].getInfo<CAL_DEVICE_ENGINECLOCK>()
    % devices[dev].getInfo<CAL_DEVICE_MEMORYCLOCK>()
    % devices[dev].getInfo<CAL_DEVICE_WAVEFRONTSIZE>()
    % devices[dev].getInfo<CAL_DEVICE_NUMBEROFSIMD>()
    % devices[dev].getInfo<CAL_DEVICE_DOUBLEPRECISION>()
    % devices[dev].getInfo<CAL_DEVICE_LOCALDATASHARE>()
    % devices[dev].getInfo<CAL_DEVICE_GLOBALDATASHARE>()
    % devices[dev].getInfo<CAL_DEVICE_GLOBALGPR>()
    % devices[dev].getInfo<CAL_DEVICE_COMPUTESHADER>()
    % devices[dev].getInfo<CAL_DEVICE_MEMEXPORT>()
    % devices[dev].getInfo<CAL_DEVICE_PITCHALIGNMENT>()
    % devices[dev].getInfo<CAL_DEVICE_SURFACEALIGNMENT>()
    % devices[dev].getInfo<CAL_DEVICE_MAXRESOURCE1DWIDTH>()
    % devices[dev].getInfo<CAL_DEVICE_MAXRESOURCE2DWIDTH>()
    % devices[dev].getInfo<CAL_DEVICE_MAXRESOURCE2DHEIGHT>();
}

void show_result( int dev, int workgroup_size, int wavefront_size )
{
    double tms      = (double)_exec_time/1000.;
    uint64_t mflops = ((uint64_t)8*(uint64_t)NR_MAD_INST*(uint64_t)NR_ITERATIONS*(uint64_t)workgroup_size*(uint64_t)_nr_groups)/(uint64_t)_exec_time;
    double gflops   = (double)mflops/1000.;

    std::cout << format("Device %i: workgroup size %i (%i hardware thread(s) per SIMD) execution time %.2f ms, achieved %.2f gflops\n") 
                 % dev % workgroup_size % ((workgroup_size+wavefront_size-1)/wavefront_size) % tms % gflops;
}

void release_gpu_resources()
{
    _queue   = CommandQueue();
    _kernel  = Kernel();
    _program = Program();
    _context = Context();
}

int main( int argc, char* argv[] )
{
    std::vector<Device> devices;
    int wavefront_size;

    cal::Init();
    init();

    devices = _context.getInfo<CAL_CONTEXT_DEVICES>();

    for(int i=0;i<_dev_count;i++) {
        show_device_info(i);

        wavefront_size = devices[i].getInfo<CAL_DEVICE_WAVEFRONTSIZE>();

        for(int workgroup_size=wavefront_size/2;workgroup_size<=(MAX_THREADS*wavefront_size);workgroup_size+=wavefront_size/2) {
            setup(i,workgroup_size);
            run(workgroup_size);
            show_result(i,workgroup_size,wavefront_size);
        }
    }

    release_gpu_resources();
    cal::Shutdown();

    return 0;
}
