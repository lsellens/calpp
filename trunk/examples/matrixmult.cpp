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
#include <cal/il/cal_il.hpp>

using namespace boost;
using namespace cal;
using namespace cal::il;

#define BX  8
#define BY  8
#define BX4 (BX/4)
#define BY4 (BY/4)

void kernel_matrixmul( input2d<float4>& A0, input2d<float4>& A1,
                       input2d<float4>& B0, input2d<float4>& B1, global<float4>& C, float1 xsize, float1 ysize )
{
    float4  R[BY][BX4],ta[2][BY4],tb[2][BX4],k;
    float2  p;
    int     i,j;

    assert( BX==8 && BY==8 );

    p = (named_variable<float2>("vWinCoord0.xy")-float2(0.5))*float2(BX4,BY);

    for(i=0;i<BY;i++) {
        for(j=0;j<BX4;j++) R[i][j]=float4(0);
    }

    k  = float4( p.y(), p.x(), float1(-2), float1(-1) );

    il_whileloop {
        k += float4(0,0,2,2);
        il_breakc( k.z()>=ysize );

        ta[0][0] = A0[k.xz()];
        ta[0][1] = A1[k.xz()];
        tb[0][0] = B0[k.yz()];
        tb[0][1] = B1[k.yz()];

        ta[1][0] = A0[k.xw()];
        ta[1][1] = A1[k.xw()];
        tb[1][0] = B0[k.yw()];
        tb[1][1] = B1[k.yw()];

        for(i=0;i<BY4;i++) {
            for(j=0;j<BX4;j++) {
                R[4*i+0][j].x() = mad( ta[i][0].x(),tb[j][0].x() , mad( ta[i][1].x(),tb[j][1].x(), R[4*i+0][j].x() ) );
                R[4*i+0][j].y() = mad( ta[i][0].x(),tb[j][0].y() , mad( ta[i][1].x(),tb[j][1].y(), R[4*i+0][j].y() ) );
                R[4*i+0][j].z() = mad( ta[i][0].x(),tb[j][0].z() , mad( ta[i][1].x(),tb[j][1].z(), R[4*i+0][j].z() ) );
                R[4*i+0][j].w() = mad( ta[i][0].x(),tb[j][0].w() , mad( ta[i][1].x(),tb[j][1].w(), R[4*i+0][j].w() ) );

                R[4*i+1][j].x() = mad( ta[i][0].y(),tb[j][0].x() , mad( ta[i][1].y(),tb[j][1].x(), R[4*i+1][j].x() ) );
                R[4*i+1][j].y() = mad( ta[i][0].y(),tb[j][0].y() , mad( ta[i][1].y(),tb[j][1].y(), R[4*i+1][j].y() ) );
                R[4*i+1][j].z() = mad( ta[i][0].y(),tb[j][0].z() , mad( ta[i][1].y(),tb[j][1].z(), R[4*i+1][j].z() ) );
                R[4*i+1][j].w() = mad( ta[i][0].y(),tb[j][0].w() , mad( ta[i][1].y(),tb[j][1].w(), R[4*i+1][j].w() ) );

                R[4*i+2][j].x() = mad( ta[i][0].z(),tb[j][0].x() , mad( ta[i][1].z(),tb[j][1].x(), R[4*i+2][j].x() ) );
                R[4*i+2][j].y() = mad( ta[i][0].z(),tb[j][0].y() , mad( ta[i][1].z(),tb[j][1].y(), R[4*i+2][j].y() ) );
                R[4*i+2][j].z() = mad( ta[i][0].z(),tb[j][0].z() , mad( ta[i][1].z(),tb[j][1].z(), R[4*i+2][j].z() ) );
                R[4*i+2][j].w() = mad( ta[i][0].z(),tb[j][0].w() , mad( ta[i][1].z(),tb[j][1].w(), R[4*i+2][j].w() ) );

                R[4*i+3][j].x() = mad( ta[i][0].w(),tb[j][0].x() , mad( ta[i][1].w(),tb[j][1].x(), R[4*i+3][j].x() ) );
                R[4*i+3][j].y() = mad( ta[i][0].w(),tb[j][0].y() , mad( ta[i][1].w(),tb[j][1].y(), R[4*i+3][j].y() ) );
                R[4*i+3][j].z() = mad( ta[i][0].w(),tb[j][0].z() , mad( ta[i][1].w(),tb[j][1].z(), R[4*i+3][j].z() ) );
                R[4*i+3][j].w() = mad( ta[i][0].w(),tb[j][0].w() , mad( ta[i][1].w(),tb[j][1].w(), R[4*i+3][j].w() ) );
            }
            il_breakc( xsize<float1(0) ); // hack to reduce register usage
        }
    }
    il_endloop

    uint1 s,step;

    s    = cast_type<uint1>(p.y()*xsize + p.x());
    step = cast_type<uint1>(xsize);

    for(i=0;i<BY;i++) {
        for(j=0;j<BX4;j++) {
            C[s+j] = R[i][j];
        }
        s += step;
    }
}

std::string create_kernel_matrixmul()
{
    std::stringstream   code;

    code << "il_ps_2_0\n";
    code << "dcl_cb cb0[1]\n";
    code << "dcl_input_position_interp(linear_noperspective) vWinCoord0.xy__\n";

    Source::begin();

    input2d<float4>    A0(0),A1(1),B0(2),B1(3);
    global<float4>     C;

    kernel_matrixmul(A0,A1,B0,B1,C,named_variable<float1>("cb0[0].x"),named_variable<float1>("cb0[0].y") );

    Source::end();

    Source::emitHeader(code);
    Source::emitCode(code);

    code << "end\n";

    return code.str();
}

//
//
//

#define ITER_COUNT      100
#define WIDTH           2048
#define HEIGHT          2048

Context         _context;
Program         _program;
Kernel          _kernel;
CommandQueue    _queue;

Image2D         _A0,_A1,_B0,_B1,_C;
int             _exec_time;

void fillMatrix( Image2D& m, float v )
{
    CALuint     pitch;
    float       *ptr,*line;
    int         width,height;

    width  = 4*m.getWidth();
    height = m.getHeight();

    line = (float*)m.map(pitch);

    for(int i=0;i<height;i++) {
        ptr = line;
        for(int j=0;j<width;j++) *ptr++ = v;
        line += 4*pitch;
    }

    m.unmap();
}

void printMatrix( Image2D& m )
{
    CALuint pitch;
    float   *line,*ptr;
    int     width,height;

    width  = 4*m.getWidth();
    height = m.getHeight();

    line = (float*)m.map(pitch);

    for(int i=0;i<height;i++) {
        ptr = line;
        for(int j=0;j<width;j++) {
            std::cout << boost::format("%.2f,") % *ptr++;
        }
        std::cout << "\n";
        line += 4*pitch;
    }

    m.unmap();
}

int init()
{
   _context = Context(CAL_DEVICE_TYPE_GPU);

    std::vector<Device> devices = _context.getInfo<CAL_CONTEXT_DEVICES>();

    // create program
    std::string source = create_kernel_matrixmul();
    //std::cout << source; // Uncomment to emit IL code
    _program = Program( _context, source.c_str(), source.length() );
    _program.build(devices);
    //_program.disassemble(std::cout); // Uncomment to emit ISA code

    // create kernel
    _kernel = Kernel(_program,"main");
    _kernel.setArgBind(0,"g[]");
    _kernel.setArgBind(1,"i0");
    _kernel.setArgBind(2,"i1");
    _kernel.setArgBind(3,"i2");
    _kernel.setArgBind(4,"i3");
    _kernel.setArgBind(5,"cb0",0,4);
    _kernel.setArgBind(6,"cb0",4,4);

    // allocate buffers
    _A0 = Image2D( _context, WIDTH/8, HEIGHT, CAL_FORMAT_FLOAT_4, 0 );
    _A1 = Image2D( _context, WIDTH/8, HEIGHT, CAL_FORMAT_FLOAT_4, 0 );

    _B0 = Image2D( _context, WIDTH/8, HEIGHT, CAL_FORMAT_FLOAT_4, 0 );
    _B1 = Image2D( _context, WIDTH/8, HEIGHT, CAL_FORMAT_FLOAT_4, 0 );

    _C  = Image2D( _context, WIDTH/4, HEIGHT, CAL_FORMAT_FLOAT_4, CAL_RESALLOC_GLOBAL_BUFFER );    

    fillMatrix(_A0,2);
    fillMatrix(_A1,2);
    fillMatrix(_B0,4);
    fillMatrix(_B1,4);

    return devices.size();
}

void setup( int dev )
{
    std::vector<Device> devices = _context.getInfo<CAL_CONTEXT_DEVICES>();
    _queue = CommandQueue(_context,devices[dev]);
}

void run()
{
    NDRange     rect;
    Event       event;

    rect = NDRange(_C.getWidth()/2,_C.getHeight()/8);

    posix_time::ptime t1 = posix_time::microsec_clock::local_time();

    _kernel.setArg(0,_C);
    _kernel.setArg(1,_A0);
    _kernel.setArg(2,_A1);
    _kernel.setArg(3,_B0);
    _kernel.setArg(4,_B1);
    _kernel.setArg(5,(float)_C.getWidth());
    _kernel.setArg(6,(float)_C.getHeight());

    for(int i=0;i<ITER_COUNT;i++) {
        _queue.enqueueNDRangeKernel( _kernel, rect, &event );
        _queue.flush();
        _queue.waitForEvent(event);
    }

    posix_time::ptime t2 = posix_time::microsec_clock::local_time();

    _exec_time = posix_time::time_period(t1,t2).length().total_microseconds();
}

void show_result( int dev )
{
    double tms    = (double)_exec_time/1000.;
    double kflops = (double)((int64_t)2*(int64_t)ITER_COUNT*(int64_t)WIDTH*(int64_t)HEIGHT*(int64_t)WIDTH)/tms;
    double gflops = kflops/1000000.;

    //printMatrix(_C);

    std::cout << format("Device %i: execution time %.2f ms, achieved %.2f gflops\n") % dev % tms % gflops;
}

int main( int argc, char* argv[] )
{
    int dev_count;

    cal::Init();

    dev_count = init();

    for(int i=0;i<dev_count;i++) {
        setup(i);
        run();
        show_result(i);
    }

    cal::Shutdown();

    return 0;
}
