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
#include <float.h>
#include <cal/cal.hpp>
#include <cal/cal_il.hpp>

using namespace boost;
using namespace cal;
using namespace cal::il;

// in ATI's nomenclature warp is wavefront ( but warp is shorter :) )
#define WARPSIZE        64
#define LX              (1*WARPSIZE)
#define LY              8
#define THREADS_PER_GRP (LX*LY)

float1 find_nearest_for_vector( const input2d<float4>& A, const input2d<float4>& B,
                                float1 Ax, uint1 px, float1 ax, float1 ay, float1  by, uint1 tid )
{    
    lds<float4>     sdata(0);
    float4          acc,t4;
    float1          x;

    acc = float4(0);
    x   = ax;
    il_while(x<Ax) {
        t4  = A(x,ay)-B(x,by);
        acc = mad(t4,t4,acc);

        x += float1(LX);
    }
    il_endloop

    sdata(tid, 0) = acc;

    for(int s=LX/2;s>0;s>>=1) {
        if( LX>WARPSIZE ) barrier(CAL_LOCAL_MEM_FENCE);
        il_if( px < uint1(s) ) {
            acc += sdata(tid+uint1(s),0);
            if( s>1 ) sdata(tid,0) = acc;
        } il_endif
    }

    return select( px==uint1(0), acc.x() + acc.y() + acc.z() + acc.w(), 0 );
}

void kernel_findnearest( const input2d<float4>& A, const input2d<float4>& B, global<float4>& error_vector,
                         float1 Ax, float1 Ay, float1 By )
{
    uint1   px  = flat2d::get_global_id(0);
    uint1   py  = flat2d::get_global_id(1);
    uint1   tid = get_local_id<uint1>();
    float1  ax,ay,by,r,max_err,idx;
        
    max_err = float1(FLT_MAX);
    idx     = float1(0);

    ax = cast_type<float1>(px);
    ay = cast_type<float1>(py);
    
    il_if( ay<Ay ) {
        by = float1(0);
        il_while(by<By) {
            r = find_nearest_for_vector(A,B,Ax,px,ax,ay,by,tid);

            uint1 t = r<max_err;
            max_err = select( t, r, max_err );
            idx     = select( t, by, idx );

            by += float1(1);
        }
        il_endloop

        il_if( px==uint1(0) ) {
            error_vector[py].xy() = float2(idx,max_err);
        }
        il_endif
    }
    il_endif
}

std::string create_kernel_findnearest()
{
    std::stringstream   code;

    code << "il_cs_2_0\n";
    code << "dcl_cb cb0[2]\n";
    code << format("dcl_num_thread_per_group %i\n") % THREADS_PER_GRP;
    code << format("dcl_struct_lds_id(0) 16,%i\n") % THREADS_PER_GRP;
    
    Source::begin();
    
    input2d<float4>    A(0),B(1);
    global<float4>     error_vector;
          
    kernel_findnearest( A,B,error_vector,
                        named_variable<float1>("cb0[1].x"), named_variable<float1>("cb0[1].y"),
                        named_variable<float1>("cb0[1].z") );

    Source::end();
    
    Source::emitHeader(code);
    Source::emitCode(code);

    code << "end\n";

    return code.str();
}

#define RM_LX   (2*WARPSIZE)
#define RM_LY   2

void reducematrix_innerloop( const input2d<float4>& A, const indexed_register<float4>& gidx,
                             float4& acc, float1& n, float1& y, uint1& idx,
                             const float1& ax, const float1& ry, int count )
{
    float2      _gidx[count];
    float4      v;

    for(int i=0;i<count;i++) _gidx[i] = gidx[idx+i].xz();
    for(int i=0;i<count;i++) {
        il_if( ry==_gidx[i].x() ) {
            if( i>0 ) v = A(ax,y+float1(i));
            else v = A(ax,y);
            acc = mad( float4(_gidx[i].y(),_gidx[i].y(),_gidx[i].y(),_gidx[i].y()), v, acc );
            n   += _gidx[i].y();
        }
        il_endif
    }

    idx += uint1(count);
    y   += float1(count);
}

void kernel_reducematrix( const input2d<float4>& A, const indexed_register<float4>& gidx, global<float4>& R,
                          uint1 Ax, uint1 Ay, uint1 Rx, uint1 Ry )
{
    uint1       px = flat2d::get_global_id(0);
    uint1       py = flat2d::get_global_id(1);
    float1      ax,ry,y;
    uint1       idx,t;
    uint32_t    loop_step=8; // must be power of 2
        
    ax = cast_type<float1>(px);
    ry = cast_type<float1>(py);

    il_if( (px<Ax) & (py<Ry) ) {
        float4 acc = float4(0);
        float1 n   = float1(0);

        y   = float1(0);
        idx = uint1(0);
        
        uint1 _Ay = Ay & uint1(~(loop_step-1));
        il_while(idx<_Ay) {
            reducematrix_innerloop(A,gidx,acc,n,y,idx,ax,ry,loop_step);
        }
        il_endloop
        for(int i=loop_step/2;i>0;i>>=1) {
            il_if( Ay&uint1(i) ) {
                reducematrix_innerloop(A,gidx,acc,n,y,idx,ax,ry,i);
            }
            il_endif
        }
        
        uint1   t  = n>float1(0);
        float1  n1 = float1(1)/n;
        R[ mad(py,Rx,px) ] = select( t, float4(n1,n1,n1,n1)*acc, 0 );
    }
    il_endif
}

std::string create_kernel_reducematrix()
{
    std::stringstream   code;

    code << "il_cs_2_0\n";
    code << "dcl_cb cb0[2]\n";
    code << "dcl_cb cb1[4096]\n";
    code << format("dcl_num_thread_per_group %i\n") % (RM_LX*RM_LY);

    cal::il::Program::begin();

    input2d<float4>             A(0);
    global<float4>              R;
    indexed_register<float4>    gidx("cb1");

    kernel_reducematrix( A,gidx,R,
                         named_variable<uint1>("cb0[1].x"), named_variable<uint1>("cb0[1].y"),
                         named_variable<uint1>("cb0[1].z"), named_variable<uint1>("cb0[1].w") );

    cal::il::Program::end();

    cal::il::Program::emitHeader(code);
    cal::il::Program::emitCode(code);

    code << "end\n";

    return code.str();
}

//
//
//

#include "matrix_cal.h"

#define WIDTH           1024
#define HEIGHT          1024
#define REDUCED         128

math::cal::Context          _context;
math::cal::matrix<float>    _A(_context),_R(_context);
cal::Image1D                _gidx;
cal::Kernel                 _kernel_findnearest;
cal::Kernel                 _kernel_reducematrix;

struct gidx_t
{
    float   idx;
    float   err_max;
    float   weight;
    float   empty;
};

void init()
{
    Program         program;
    std::string     source;

    math::cal::Context::init();
    _context = math::cal::Context(0);

    // create program
    source = create_kernel_findnearest();
    std::cout << source;
    program = Program( _context.getCALContext(), source.c_str(), source.length() );
    program.build(_context.getCALContext().getInfo<CAL_CONTEXT_DEVICES>());
    program.disassemble(std::cout);

    // create kernel
    _kernel_findnearest = Kernel(program,"main");    
    _kernel_findnearest.setArgBind(0,"i0"); // A
    _kernel_findnearest.setArgBind(1,"i1"); // R
    _kernel_findnearest.setArgBind(2,"g[]"); // gidx
    _kernel_findnearest.setArgBind(3,"cb0",0,16); // flat2d data
    _kernel_findnearest.setArgBind(4,"cb0",16,4); // Ax
    _kernel_findnearest.setArgBind(5,"cb0",16+4,4); // Ay
    _kernel_findnearest.setArgBind(6,"cb0",16+8,4); // Ry
    
    // create program
    source = create_kernel_reducematrix();
    std::cout << source;
    program = cal::Program( _context.getCALContext(), source.c_str(), source.length() );
    program.build(_context.getCALContext().getInfo<CAL_CONTEXT_DEVICES>());
    program.disassemble(std::cout);

    // create kernel
    _kernel_reducematrix = Kernel(program,"main");
    _kernel_reducematrix.setArgBind(0,"i0"); // A
    _kernel_reducematrix.setArgBind(1,"cb1"); // gidx
    _kernel_reducematrix.setArgBind(2,"g[]"); // R
    _kernel_reducematrix.setArgBind(3,"cb0",0,16); // flat2d data
    _kernel_reducematrix.setArgBind(4,"cb0",16,4); // Ax
    _kernel_reducematrix.setArgBind(5,"cb0",16+4,4); // Ay
    _kernel_reducematrix.setArgBind(6,"cb0",16+8,4); // Rx
    _kernel_reducematrix.setArgBind(7,"cb0",16+12,4); // Ry

    // allocate data
    _A.resize(HEIGHT,WIDTH);
    _R.resize(REDUCED,WIDTH);
    _gidx = Image1D( _context.getCALContext(), 4096, CAL_FORMAT_FLOAT_4, CAL_RESALLOC_GLOBAL_BUFFER );
}

void run_findnearest( math::cal::matrix<float>& A, math::cal::matrix<float>& R, cal::Image1D& gidx )
{
    NDRange     local,global;

    global = NDRange(LX,A.size1());
    local  = NDRange(LX,LY);

    _kernel_findnearest.setArg(0,A.data());
    _kernel_findnearest.setArg(1,R.data());
    _kernel_findnearest.setArg(2,gidx);
    _kernel_findnearest.setArg(3,flat2d::make_flat_cb0(global,local));
    _kernel_findnearest.setArg(4,(float)((uint32_t)(A.size2()+3)/4));
    _kernel_findnearest.setArg(5,(float)A.size1());
    _kernel_findnearest.setArg(6,(float)R.size1());

    _context.enqueueKernel( _kernel_findnearest,
                            flat2d::make_flat_global(global, local),
                            flat2d::make_flat_local(local) );
}

void run_reducematrix( math::cal::matrix<float>& A, math::cal::matrix<float>& R, cal::Image1D& gidx )
{
    NDRange     local,global;

    global = NDRange(A.data_ld(),R.size1());
    local  = NDRange(RM_LX,RM_LY);

    _kernel_reducematrix.setArg(0,A.data());
    _kernel_reducematrix.setArg(1,gidx);
    _kernel_reducematrix.setArg(2,R.data());
    _kernel_reducematrix.setArg(3,flat2d::make_flat_cb0(global,local));
    _kernel_reducematrix.setArg(4,(uint32_t)(A.size2()+3)/4);
    _kernel_reducematrix.setArg(5,(uint32_t)A.size1());
    _kernel_reducematrix.setArg(6,(uint32_t)R.data_ld());
    _kernel_reducematrix.setArg(7,(uint32_t)R.size1());

    _context.enqueueKernel( _kernel_reducematrix,
                            flat2d::make_flat_global(global, local),
                            flat2d::make_flat_local(local) );
}

void fill_matrix( math::cal::matrix<float>& A )
{
    A.map();
    
    for(int i=0;i<(int)A.size1();i++) {
        for(int j=0;j<(int)A.size2();j++) {
            A(i,j) = 10000*i + j;
        }
        for(int j=A.size2();j<(int)A.data_ld();j++) A(i,j)=0;
    }

    A.unmap();
}

void print_matrix( math::cal::matrix<float>& A )
{
    A.map();

    std::cout << "************** matrix\n";
    for(int i=0;i<(int)A.size1();i++) {
        std::cout << format("line %i - ") % i;
        for(int j=0;j<(int)A.size2();j++) {
            if( j>0 && (j%4)==0 ) std::cout << " ";
            std::cout << format("%.2f,") % A(i,j);
        }
        std::cout << "\n";
    }

    A.unmap();
}

void print_gidx( Image1D& gidx, int width )
{
    CALuint     pitch;
    gidx_t      *_gidx,*p;
    int         i;

    _gidx = (gidx_t*)gidx.map(pitch);    

    std::cout << "********* gidx\n";
    for(i=0,p=_gidx;i<width;i++,p++) {
        std::cout << format("%i (%.1f,%.5f,%.5f)\n") % i % p->idx % p->err_max % p->weight;
    }
    
    gidx.unmap();        
}

double get_error( Image1D& gidx, int width )
{
    CALuint     pitch;
    gidx_t      *_gidx,*p;
    double      err;
    int         i;

    _gidx = (gidx_t*)gidx.map(pitch);    

    err = 0;
    for(i=0,p=_gidx;i<width;i++,p++) {
        err += p->err_max*p->weight;
    }
    
    gidx.unmap();

    return err;
}

void generate_gidx( math::cal::matrix<float>& A, math::cal::matrix<float>& R, cal::Image1D& gidx )
{
    CALuint     pitch;
    gidx_t      *_gidx,*p;
    float       smax,s,v;
    int         i,j;

    _gidx = (gidx_t*)gidx.map(pitch);

    // init gidx
    smax=0;
    for(i=0,p=_gidx;i<(int)A.size1();i++,p++) {
        p->idx     = -1;
        p->err_max = 0;
        p->weight  = 1;
        p->empty   = 0;
                
        smax += p->weight;
    }
    
    // select random rows to R
    for(i=0;i<(int)R.size1();i++) {
        v = ((rand() % 100000)/100000.)*smax;
        s = 0;
        for(j=0,p=_gidx;j<(int)A.size1();j++,p++) {
            if( p->idx>=0 ) continue;
            
            if( v<=(s+p->weight) ) {
                p->idx=(float)i;
                smax-=p->weight;
                break;           
            }

            s += p->weight;
        }        
    }

    gidx.unmap();    
}

void vector_quantization()
{    
    fill_matrix(_A);

    posix_time::ptime t1 = posix_time::microsec_clock::local_time();
    
    generate_gidx(_A,_R,_gidx);
    run_reducematrix(_A,_R,_gidx);

    /*
    print_gidx(_gidx,HEIGHT);
    print_matrix(_A);
    run_reducematrix(_A,_R,_gidx);
    _context.finish();
    //print_matrix(_R);

    run_findnearest(_A,_R,_gidx);
    _context.finish();
    //print_gidx(_gidx,HEIGHT);
    */    
    
    for(int i=0;i<100;i++) {
        run_findnearest(_A,_R,_gidx);
        //_context.finish();
        //std::cout << format("i=%i err=%.5f\n") % i % get_error(_gidx,HEIGHT);
        //print_gidx(_gidx,HEIGHT);
        run_reducematrix(_A,_R,_gidx);
    }

    _context.finish();    

    posix_time::ptime t2 = posix_time::microsec_clock::local_time();

    std::cout << format("err=%.5f\n") % get_error(_gidx,HEIGHT);

    double t = posix_time::time_period(t1,t2).length().total_microseconds()/1000000.;

    std::cout << format("vector quantization time %.2f\n") % t;
}


void release_gpu_resources()
{
    _queue   = CommandQueue();
    _kernel_findnearest  = Kernel();
    _kernel_reducematrix = Kernel();
    _context = Context();
    _program = Program();
}

int main( int argc, char* argv[] )
{
    cal::Init();    
    init();

    vector_quantization();

    release_gpu_resources();
    cal::Shutdown();

    return 0;
}
