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

#include <boost/format.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cal/cal.hpp>
#include "nbody_worker.h"

std::string create_nbody_kernel( cal::Device& device, int num_threads, int workitem_size, int tile_size, int read_count, int unroll_count, float eps2 );

using namespace boost;
using namespace cal;

NBodyWorker::NBodyWorker()
{
    opt.device        = 0;
    opt.num_bodies    = 1000;
    opt.num_threads   = 4;
    opt.workitem_size = 8;
    opt.tile_size     = 1*64;
    opt.read_count    = 4;
    opt.unroll_count  = 8;
    opt.eps2          = 50;
    opt.dT            = 0.005;

    _active_buffer    = 0;
    _exec_time        = 0;
}

NBodyWorker::~NBodyWorker()
{
}

void NBodyWorker::init()
{
    std::vector<Device> devices;

    // create context
    _context = Context(CAL_DEVICE_TYPE_GPU);
    devices  = _context.getInfo<CAL_CONTEXT_DEVICES>();

    _device  = devices[opt.device];
    _context = Context(_device);
    devices  = _context.getInfo<CAL_CONTEXT_DEVICES>();

    // create program
    std::string source = create_nbody_kernel(_device,opt.num_threads,opt.workitem_size,opt.tile_size,opt.read_count,opt.unroll_count,opt.eps2);
    //std::cout << source; // Uncomment to emit IL code
    _program = Program( _context, source.c_str(), source.length() );
    _program.build(devices);
    //_program.disassemble(std::cout); // Uncomment to emit ISA code

    // create kernel
    _kernel = Kernel(_program,"main");
    _kernel.setArgBind(0,"i0");
    _kernel.setArgBind(1,"g[]");
    _kernel.setArgBind(2,"cb0",0,4);
    _kernel.setArgBind(3,"cb0",4,4);
    _kernel.setArgBind(4,"cb0",8,4);
    _kernel.setArgBind(5,"cb0",16,4);
    _kernel.setArgBind(6,"cb0",20,4);
    _kernel.setArgBind(7,"cb0",24,4);

    // round num_bodies to optimal size for gpu
    int optimal_step = opt.num_threads*_device.getInfo<CAL_DEVICE_WAVEFRONTSIZE>()*_device.getInfo<CAL_DEVICE_NUMBEROFSIMD>()*opt.workitem_size;
    opt.num_bodies = optimal_step*((opt.num_bodies + optimal_step - 1)/optimal_step);
    /*
    opt.num_bodies = opt.tile_size*((opt.num_bodies + opt.tile_size-1)/opt.tile_size);
    */

    assert( (opt.num_bodies%opt.tile_size)==0 );

    // allocate buffers
    int min_width,max_height,width,height,width_step;

    width_step = std::max( 64, opt.tile_size )*opt.workitem_size;

    max_height = _device.getInfo<CAL_DEVICE_MAXRESOURCE2DHEIGHT>()/2;
    min_width  = (opt.num_bodies + max_height - 1)/max_height;
    width      = width_step*((min_width + width_step - 1)/width_step);
    height     = (opt.num_bodies + width - 1)/width;

    _data[0]   = Image2D( _context, width, 2*height, CAL_FORMAT_FLOAT_4, CAL_RESALLOC_GLOBAL_BUFFER );
    _data[1]   = Image2D( _context, width, 2*height, CAL_FORMAT_FLOAT_4, CAL_RESALLOC_GLOBAL_BUFFER );

    // create command queue
    _queue = CommandQueue(_context, _device);
}

void NBodyWorker::runKernel()
{
    NDRange global,local;
    Event   event;

    posix_time::ptime t1 = posix_time::microsec_clock::local_time();

    local  = NDRange( opt.num_threads*_device.getInfo<CAL_DEVICE_WAVEFRONTSIZE>() );
    global = NDRange( local.width*_device.getInfo<CAL_DEVICE_NUMBEROFSIMD>() );

    _kernel.setArg(0, _data[_active_buffer]);
    _kernel.setArg(1, _data[1-_active_buffer]);
    _kernel.setArg(2, (uint32_t)opt.num_bodies);
    _kernel.setArg(3, (uint32_t)(opt.num_bodies/opt.tile_size));
    _kernel.setArg(4, (uint32_t)_data[0].getWidth());
    _kernel.setArg(5, (float)_data[0].getWidth());
    _kernel.setArg(6, (float)(_data[0].getHeight()/2));
    _kernel.setArg(7, opt.dT);

    _queue.enqueueNDRangeKernel( _kernel, global, local, &event );
    _queue.waitForEvent(event);

    posix_time::ptime t2 = posix_time::microsec_clock::local_time();

    _exec_time = posix_time::time_period(t1,t2).length().total_microseconds();

    _active_buffer = 1-_active_buffer;
}

void NBodyWorker::sendDataToGPU()
{
    float*  data,*p;
    int     i,width,height;
    CALuint pitch;

    assert( position.size()>=opt.num_bodies );
    assert( velocity.size()>=opt.num_bodies );

    width  = _data[_active_buffer].getWidth();
    height = _data[_active_buffer].getHeight();
    data = (float*)_queue.mapMemObject(_data[_active_buffer],pitch);

    p = data;
    for(i=0;i<opt.num_bodies;i++,p+=4) {
        *(p + 0) = position[i].x;
        *(p + 1) = position[i].y;
        *(p + 2) = position[i].z;
        *(p + 3) = position[i].m;
    }

    p = data + height*width*2;
    for(i=0;i<opt.num_bodies;i++,p+=4) {
        *(p + 0) = velocity[i].x;
        *(p + 1) = velocity[i].y;
        *(p + 2) = velocity[i].z;
        *(p + 3) = 0;
    }

    _queue.unmapMemObject(_data[_active_buffer]);
}

void NBodyWorker::receiveDataFromGPU()
{
    float*  data,*p;
    int     i,width,height;
    CALuint pitch;

    position.resize(opt.num_bodies);
    velocity.resize(opt.num_bodies);

    width  = _data[_active_buffer].getWidth();
    height = _data[_active_buffer].getHeight();
    data = (float*)_queue.mapMemObject(_data[_active_buffer],pitch);

    p = data;
    for(i=0;i<opt.num_bodies;i++,p+=4) {
        position[i].x = *(p+0);
        position[i].y = *(p+1);
        position[i].z = *(p+2);
        position[i].m = *(p+3);
    }

    p = data + height*width*2;
    for(i=0;i<opt.num_bodies;i++,p+=4) {
        velocity[i].x = *(p+0);
        velocity[i].y = *(p+1);
        velocity[i].z = *(p+2);
    }

    _queue.unmapMemObject(_data[_active_buffer]);
}

void NBodyWorker::showFLOPS()
{
    double tms = (double)_exec_time/1000.;
    double classic_kflops = (double)((uint64_t)opt.num_bodies * (uint64_t)opt.num_bodies * (uint64_t)38)/tms;
    double modern_kflops  = (double)((uint64_t)opt.num_bodies * (uint64_t)opt.num_bodies * (uint64_t)20)/tms;

    std::cout << format("execution time %.2f ms, classic GFLOPS %.2f, modern GFLOPS %.2f\n")
                 % tms
                 % (classic_kflops/1000000.)
                 % (modern_kflops/1000000.);
}
