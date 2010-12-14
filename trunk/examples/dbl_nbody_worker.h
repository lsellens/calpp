#ifndef __NBODY_WORKER_H
#define __NBODY_WORKER_H

#include <vector>
#include <cal/cal.hpp>

class DNBodyWorker
{
public:
    struct body_t {
        double x,y,z;
        double m;
    };

    struct velocity_t {
        double x,y,z;
    };

    struct options_t {
        int device;
        int num_bodies;
        int num_threads;
        int workitem_size;
        int tile_size;
        int read_count;
        int unroll_count;
        double dT;
        double eps2;
    };

protected:
    cal::Context      _context;
    cal::Device       _device;
    cal::Program      _program;
    cal::Kernel       _kernel;
    cal::CommandQueue _queue;
    cal::Image2D      _data[2];
    int               _active_buffer;
    int64_t           _exec_time;

public:
    options_t               opt;
    std::vector<body_t>     position;
    std::vector<velocity_t> velocity;

public:
    DNBodyWorker();
    ~DNBodyWorker();

    void init();

    void runKernel();
    void sendDataToGPU();
    void receiveDataFromGPU();

    void showFLOPS();
};

#endif
