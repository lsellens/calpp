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
#include <cal/il/cal_il.hpp>

using namespace boost;
using namespace cal;
using namespace cal::il;

#define WARPSIZE        64
#define WARPCOUNT       1
#define THREADS_PER_GRP (WARPCOUNT*WARPSIZE)
#define NR_ITERATIONS   10000
#define NR_READS_Y      64
#define NR_READS_X      16
#define LINEWIDTH       8128

void kernel_coalescing( input2d<float4>& A, global<float4>& result, int step)
{
    float4      v;
    float2      p,p0;
    uint2       _p;
    uint1       i;

    _p = uint2( get_group_id<uint1>()*(NR_READS_X*THREADS_PER_GRP/step) + get_local_id<uint1>()%(THREADS_PER_GRP/step)
    , get_local_id<uint1>()/(THREADS_PER_GRP/step) );
    p0 = cast_type<float2>(_p);
    v  = 0;

    i = NR_ITERATIONS;

    il_while(i) {
        p.y() = p0.y();
        for(int k=0;k<NR_READS_Y;k++) {
            p.x() = p0.x();
            for(int l=0;l<NR_READS_X;l++) {
                v = v + A[p];
                p.x() = p.x() + (THREADS_PER_GRP/step);
            }            
            p.y() = p.y() + step;
        }

        i = i - 1;
    }
    il_endloop

    result[get_global_id<uint1>()] = v;
}

std::string create_kernel_coalescing( int step )
{
    std::stringstream   code;

    code << "il_cs_2_0\n";
    code << format("dcl_num_thread_per_group %i\n") % (int)THREADS_PER_GRP;

    Source::begin();

    input2d<float4>    A(0);
    global<float4>     result;
    kernel_coalescing(A,result,step);

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

Image2D         _input;
Image2D         _output;
int             _nr_groups;
int             _exec_time;

void fillMatrix( Image2D& m, float v )
{
    CALuint     pitch;
    float       *ptr,*line;
    int         width,height;

    width  = 4*m.getWidth();
    height = m.getHeight();

    line = (float*)_queue.mapMemObject(m,pitch);

    for(int i=0;i<height;i++) {
        ptr = line;
        for(int j=0;j<width;j++) {            
            *ptr++ = i*width+j;
        }
        line += 4*pitch;
    }

    _queue.unmapMemObject(m);
}

void printMatrix( Image2D& m )
{
    CALuint pitch;
    float   *line,*ptr;
    int     width,height;

    width  = 4*m.getWidth();
    height = m.getHeight();

    line = (float*)_queue.mapMemObject(m,pitch);

    for(int i=0;i<height;i++) {
        ptr = line;
        for(int j=0;j<width;j++) {
            if( j>0 && (j%4)==0 ) std::cout << "  ";
            std::cout << boost::format("%.1f,") % *ptr++;
        }
        std::cout << "\n";
        line += 4*pitch;
    }

    _queue.unmapMemObject(m);
}

int init()
{
   _context = Context(CAL_DEVICE_TYPE_GPU);
    return _context.getInfo<CAL_CONTEXT_DEVICES>().size();
}

void clear()
{
    _input = Image2D();
    _output = Image2D();
    _queue = CommandQueue();
    _kernel = Kernel();
    _program = cal::Program();
}

void setup( int dev, int step )
{
    std::vector<Device> devices = _context.getInfo<CAL_CONTEXT_DEVICES>();
    
    _nr_groups = devices[dev].getInfo<CAL_DEVICE_NUMBEROFSIMD>();
    
    // create program
    std::string source = create_kernel_coalescing(step);
    //std::cout << source; // Uncomment to emit IL code
    _program = Program( _context, source.c_str(), source.length() );
    _program.build(devices);
    //_program.disassemble(std::cout); // Uncomment to emit ISA code

    // create kernel
    _kernel = Kernel(_program,"main");
    _kernel.setArgBind(0,"g[]");
    _kernel.setArgBind(1,"i0");

    // create command queue
    _queue = CommandQueue(_context,devices[dev]);

    // create output buffer    
    _input  = Image2D(_context, NR_READS_X*THREADS_PER_GRP*_nr_groups/step, NR_READS_Y*step, CAL_FORMAT_FLOAT_4, CAL_RESALLOC_GLOBAL_BUFFER );
    _output = Image2D(_context, THREADS_PER_GRP*_nr_groups, 1, CAL_FORMAT_FLOAT_4, CAL_RESALLOC_GLOBAL_BUFFER );

    //fillMatrix(_input,1);
}

void run()
{
    NDRange     global,local;
    Event       event;
    
    local  = NDRange(THREADS_PER_GRP);
    global = NDRange(_nr_groups*THREADS_PER_GRP);

    posix_time::ptime t1 = posix_time::microsec_clock::local_time();

    _kernel.setArg(0,_output);
    _kernel.setArg(1,_input);
    _queue.enqueueNDRangeKernel( _kernel, global, local, &event );
    _queue.flush();
    _queue.waitForEvent(event);

    posix_time::ptime t2 = posix_time::microsec_clock::local_time();

    _exec_time = posix_time::time_period(t1,t2).length().total_microseconds();
}

void show_result( int dev, int step )
{
    double tms    = (double)_exec_time/1000.;
    int64_t bytes = (int64_t)THREADS_PER_GRP*(int64_t)_nr_groups*(int64_t)NR_READS_X*(int64_t)NR_READS_Y*(int64_t)NR_ITERATIONS*(int64_t)4;
    double kbytes = (double)bytes/tms;
    double gbytes = kbytes/1000000.;

    //printMatrix(_output);

    std::cout << format("Device %i: sequential read width %i: execution time %.2f ms, achieved %.2f gbytes/s\n") % dev % (THREADS_PER_GRP/step) % tms % gbytes;
}

void release_gpu_resources()
{
    _queue   = CommandQueue();
    _kernel  = Kernel();
    _context = Context();
    _program = Program();
}

int main( int argc, char* argv[] )
{
    int dev_count;
    
    cal::Init();

    dev_count = init();
        
    if( argc<=1 ) {
        std::cout << "Invalid usage: coalescingtest step\n";
        return 2;
    }
    
    int step = atoi( argv[1] );

    if( step<0 || step>8 ) {
        std::cout << "Invalid step value ( should be in range 0-8 )\n";
        return 2;
    }

    step = 1<<step;

    setup(0,step);
    run();
    show_result(0,step);
    

    /*
    for(int i=0;i<dev_count;i++) {
        int     step=1;
        
        for(int j=0;j<4;j++) {
            clear();
            setup(i,step);
            _queue.flush();
            sleep(10);
            run();
            show_result(i,step);
            step<<=1;
        }
    }
    */
    

    release_gpu_resources();
    cal::Shutdown();

    return 0;
}
