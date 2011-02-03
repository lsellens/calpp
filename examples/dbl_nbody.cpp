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

#include <boost/format.hpp>
#include <cal/cal.hpp>
#include <iostream>
#include "dbl_nbody_worker.h"

using namespace boost;
using namespace cal;

DNBodyWorker* worker;

double random( double _min, double  _max )
{
    double a = (double)rand()/(double)RAND_MAX;
    return _min + a*(_max-_min);
}

void init_data()
{
    int num_bodies = worker->opt.num_bodies;

    worker->position.resize(num_bodies);
    worker->velocity.resize(num_bodies);

    for(int i=0;i<num_bodies;i++) {
        worker->position[i].x = random(3,50);
        worker->position[i].y = random(3,50);
        worker->position[i].z = random(3,50);
        worker->position[i].m = random(1,1000);

        worker->velocity[i].x = 0;
        worker->velocity[i].y = 0;
        worker->velocity[i].z = 0;
    }

    worker->sendDataToGPU();
}

int main( int argc, char* argv[] )
{
    cal::Init();
    worker = new DNBodyWorker();

    worker->opt.num_bodies    = 500000;
    if( argc==2 ) worker->opt.num_bodies = atoi(argv[1]);
    worker->opt.num_threads   = 4;
    worker->opt.workitem_size = 4; // increasing this value without reducing num_threads will cause register spilling 
    worker->opt.tile_size     = 64;
    worker->opt.read_count    = 4;
    worker->opt.unroll_count  = 4; // too big value here might cause kernel size to be larger than 48kB ( penalty for not fitting in program cache )
    worker->opt.native_rsqrt  = false;

    worker->init();

    std::cout << "Data size: " << worker->opt.num_bodies << "\n";

    init_data();

    worker->runKernel();
    worker->showFLOPS();

    delete worker;
    cal::Shutdown();

    return 0;
}
