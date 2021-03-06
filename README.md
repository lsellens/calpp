Fork of haseman's CAL++ http://calpp.sourceforge.net

This is CAL++, library for efficient use of ATI CAL with C++.
The library consist of 2 main parts. First is C++ wrapper for CAL
and second is implementation of OpenCL like language for efficient coding of CAL kernels.

CAL++ library depends on boost library ( www.boost.org ). To generate build files cmake is used ( http://www.cmake.org/ ).


INSTALLATION ( Windows + Visual C++ )

    Install AMDAPP SDK ( http://developer.amd.com/tools-and-sdks/opencl-zone/amd-accelerated-parallel-processing-app-sdk/ )
    Install cmake ( http://www.cmake.org/ )
    Install boost ( http://www.boostpro.com/download ) ( CALPP examples require data_time component )

    Ensure that enviroment variable AMDAPPSDKROOT points to ATI APP SDK directory. 
    Sometimes there is problem if directory in AMDAPPSDKROOT doesn't end with '\'

    Start cmake-gui. Choose CAL++ directory as source code path and build the binaries path.
    Press Configure ( select Visual Studio as generator ).
    Press Generate

    Start Visual C++ and open CALPP project file.  Compile examples using build command.

INSTALLATION ( Linux )
    Install AMDAPP SDK ( http://developer.amd.com/tools-and-sdks/opencl-zone/amd-accelerated-parallel-processing-app-sdk/ )
    Install cmake and boost.

    Ensure that enviroment variable AMDAPPSDKROOT points to ATI APP SDK directory.
    Sometimes there is problem if directory in AMDAPPSDKROOT doesn't end with '/'

    Go to CAL++ directory 
    From command line enter commands

    cmake .
    make
    ( optional ) make install

OPTIONAL INSTALLATION
    Just copy content of include directory to appropriate destination ( on Unix /usr/local/include/ ).

1. C++ wrapper for CAL ( file include/cal/cal.hpp )

This wrapper closely reassembles OpenCL C++ bindings. There are some minor changes to better match CAL library.
All classes reside in cal namespace.

- at the moment only error reporting by exceptions is supported.
- function Init() must be called before any CAL function is used.
- function Shutdown() must be called at the end of program execution.
- CommandQueue::enqueueMap* is changed to CommandQueue::mapMemoryObject, also there is map, unmap method in Memory object
- CommandQueue::enqueueUnmap* is changed to CommandQueue::unmapMemoryObject 
- CommandQueue::enqueueReadBuffer, CommandQueue::enqueueWriteBuffer are removed ( doesn't make sense to use them with CAL, but if required could be emulated with use of Map/Unamp and memcpy )
- CommandQueue::enqueueCopyBuffer is asynchronous to the kernel execution 
- CommandQueue::enqueueNDRangeKernel( Kernel& kernel, const NDRange& global, const NDRange& local, Event* event = NULL) is used to execute compute shaders.
- CommandQueue::enqueueNDRangeKernel( Kernel& kernel, const NDRange& global, Event* event = NULL) is used to execute pixel shaders.
- CommandQueue::enqueueTask,enqueueNativeKernel,enqueueMarker,enqueueBarrier are removed ( no support with CAL )
- CommandQueue::enqueueWaitForEvents renamed to waitForEvents ( due to change in functionality - enqueue waits for events after previous tasks in queue are done, waitForEvents starts waiting without any delays )
- CommandQueue::waitForEvent added ( waiting for one event )
- no Platform class ( doesn't make sense with only ATI CAL ), new Context class is simply created with 'Context(CAL_DEVICE_TYPE_GPU)'
- Program::disassemble( std::ostream& out ) added ( for emiting ISA code )
- kernel name argument in the class Kernel constructor must be "main" ( CAL doesn't support different name ).
- class Kernel handles allocation and initialization of constant buffers ( based on data from setArgBind functions )

IL kernel doesn't have explicit list of kernel parameters ( opposed to OpenCL ). This is why we need to do explicit bindings.
To do this class Kernel has following methods.

- void setArgBind( int index, const std::string& name )
    binds argument 'index' to IL register 'name'
- void setArgBind( int index, const std::string& name, int cb_offset, int cb_size=0 )
    binds argument 'index' to constant buffer register. 
    Name must be 'cbX' ( X=0..14 ), offset is position in bytes from start of cbX buffer, size is argument size in bytes

The binding must be done only once after kernel creation.

Example:
    _kernel = Kernel(_program,"main");
    _kernel.setArgBind(0,"g[]");     // binds argument 0 to global buffer
    _kernel.setArgBind(1,"i0");      // binds argument 1 to input register 0
    _kernel.setArgBind(2,"i1");      // binds argument 2 to input register 1
    _kernel.setArgBind(3,"i2");      // binds argument 3 to input register 2
    _kernel.setArgBind(4,"i3");      // binds argument 4 to input register 3
    _kernel.setArgBind(5,"cb0",0,4); // binds argument 5 to IL constant buffer 0 ( position 0B, size 4B )
    _kernel.setArgBind(6,"cb0",4,4); // binds argument 6 to IL constant buffer 0 ( position 4B, size 4B )

after this kernel arguments can be initialized the same way as in OpenCL

    // _C,_A0,_A1,_B0,_B1 are Image2D classes 
    _kernel.setArg(0,_C);
    _kernel.setArg(1,_A0);
    _kernel.setArg(2,_A1);
    _kernel.setArg(3,_B0);
    _kernel.setArg(4,_B1);
    _kernel.setArg(5,(float)_C.getWidth());
    _kernel.setArg(6,(float)_C.getHeight());

2. C++ to IL compiler/generator

This is set of templates which allow to convert C++ code directly to CAL IL.

- Basic types
    Any operations on basic types will be converted into coresponding IL code.

    type list:
    uint1,uint2,uint4    -  vector types with 1 to 4 components, each component is 32 bit unsigned int.
    int1,int2,int4       -  vector types with 1 to 4 components, each component is 32 bit signed int.
    float1,float2,float4 -  vector types with 1 to 4 components, each component is float.
    double1,double2	 -  vector types with 1 to 2 components, each component is double.

- basic types swizzle
  Component selection can be done by using swizzles. Difference beetwen CAL++ and OpenCL is that swizzle must be ended with ().
  
  Examples
    float4	v;
    float1	a;
    float2	b;
    
    v.x() = a;
    a     = v.z();
    
    v.xy() = b;
    v.zw() = b;
    
    b = v.yw();
    
    v = v.yzwx();
    

- Invalid type detection
  Any operations with invalid type are detected at compilation time. This is done by using BOOST_ASSERT macro.
  If C++ compiler shows error in cal_il_* header and the line contains BOOST_ASSERT then probably you have made some error in your CAL++ kernel.
  
  Examples:
  float2	a;
  float4	b;

  a = b; <- this will cause compilation error;

- Advanced types
    variable<basic type> 	- template friendly IL variable
    value<basic type> 		- class which represents IL literal ( example: value<float2>(1.,2.), value<uint1>(1) )
    named_variable<basic type>  - allow to use special IL registers ( example: named_variable<float2>("vWinCoord0.xy") )
    input1d<basic type> 	- maps to input register. Constructor takes id of input register (0 for "i0", 1 for "i1").
				  Assumes that input register is binded to CAL 1D image. Image value can be accessed by 
				  [] or () operators. 
	Example:
	    input1d<float4>	input(0);
	    float4		v;
	    float1		position;
	    
	    ...
	    
	    // all following instructions do the same
	    v = input[position];
	    v = input(position);

    input2d<basic type> 	- maps to input register. Constructor takes id of input register (0 for "i0", 1 for "i1").
				  Assumes that input register is binded to CAL 2D image. Image values can be accessed by 
				  [] or () operators.
	Example:
	    input1d<float4>	input(0);
	    float4		v;
	    float2		position;
	    float1		px,py;
	    
	    ...
	    
	    position = float2(px,py);
	    
	    // all following instructions do the same
	    v = input[position];
	    v = input(position);
	    v = input(px,py)
	    v = input(position);

    indexed_register<basic type> - maps to special IL register with ability to index ( the name of register is given as argument in constructor ).
				   Indexing can be done by [] or () operators.
				   
	Example:
	    indexed_register<uint4>	temp_array("x0");
	    uint4	v;
	    int1	p;
	    int		offset; ( normal C int )
	    
	    ...
	    
	    // following code do the same
	    temp_array[p] = v;
	    temp_array(p) = v;
	    
	    // offseting by some const value
	    temp_array[p+3] = v;
	    temp_array(p+3) = v;
	    
	    // reading 
	    v = temp_array[p];
	    v = temp_array(p+10);
	    
	    // using C int to offset
	    v = temp_array[p+offset];
	    v = temp_array(p+offset);

    global<basic type>	- this is indexed_register<basic type> mapped to global buffer ( g[] )
    lds<basic_type> - class which allows accessing LDS. Constructor takes LDS id as argument. Operator () and [] allow accesing LDS data.

- Compare operations
    Any variables of the same basic type can be compared ( <,>,<=,>=,!=,== ). The comparison result is of uintX type.
    In C++ comparison result type is bool. But quite often result of vector comparison is used as the mask to bit ops. This is why uintX has been chosen as output type.

- Bit operations.
    Bit operations |,&,<<,>>,~ are available. Type returned by operators is the type of first argument. The second argument should be of uintX type.
    Bit operations for floatX and doubleX are supported ( this is not the case in OpenCL ).

- basic types casting
    Functions convert_typeX are available. Also template friendly version cast_type<result type>(...) is available.

- bits casting
    Functions as_typeX are available. Also template friendly version cast_bits<result type>(...) is available.

- logical operations
    Logical !,||,&& are available.
    ! converts 0 to all bits 1, and any non 0 value to all bits 0.
    || and && are implemented using coresponding bit ops.

- IL flow control
    To control execution flow in IL kernel there are special statments available.

    - IL if statement
    il_if( uint1 or float1 type ) {
      ...
    } il_else {
      ...
    }
    il_endif
    
    - This is while loop ( loop continues as long condition is not zero )
    il_while( uint1 or float1 type ) {
    }
    il_endloop

    - Second version of while loop
    il_whileloop {
    ...
        il_breakc(break condition, must be uint1 of float1 type);
    ...
    }
    il_endloop

    Also inside any loop we can use il_continuec( condition ) - this emits IL continuec statement.

- using C++ flow control
  Any flow control instructions from C can be used. But they are not converted to IL.
  for(;;) usually is used for loop unroling at compilation time. if() can be used for conditional compilation.

- special functions available
    <cal/cal_il.hpp>
    mad   - multiply add
    barrier( int type )
    mem_fence( int type )
    read_mem_fence( int type )
    write_mem_fence( int type )
    get_global_id<uint1>() - flattened global id
    get_global_id<uint4>()
    get_global_id( int idx )
    get_local_id<uint1>() - flattened local id
    get_local_id<uint4>()
    get_local_id( int idx )
    get_group_id<uint1>() - flattened group id
    get_group_id<uint4>()
    get_group_id( int idx )
    bitalign
    bytealign

    <cal/cal_il_math.hpp> ( all functions support both floatX and doubleX )
    ldexp
    frexp
    fract
    round
    exp
    log
    floor
    tanh
    atanh
    rsqrt
    sqrt
    reciprocal

    <cal/cal_il_atomics.hpp> ( uav and lds atomics )
    atom_add
    atom_sub
    atom_inc
    atom_dec
    atom_min
    atom_max
    atom_and
    atom_or
    atom_xor
    atom_xchg
    for each function there is available version with underscore ( _atom_xxx ) which doesn't return value


3. CAL++ examples

- peekflops
    Kernel executes huge numbers of mads to estimate peek FLOPS for card.
    In the kernel 'C for' is used for loop unroling.

- matrixmul
    This is implementation of prunedtree's matrixmul algorithm ( http://forum.beyond3d.com/showthread.php?t=54842 ). 
    I think this is good example of power of CAL++. The CAL++ code is much easier to write ( and read ) and yet it gives almost exactly the same ISA as the handwritten IL.

- matrixmul2
    Modified version with sample offset and without matrix split

- coalescingtest
    This is test kernel to verify coalescing behaviour of ATI cards.

- nbody ( + double version - dbl_nbody )
    Optimal (fastest possible) implementation of brute-force n-body algorithm on ATI GPU.
    Achives 90% of peek operation count ( including required index computations gives 94% ).
    It's 10-20x faster than OpenCL implementation in ATI SDK.

- vectorquantization
    Implementations of vector quantization. It shows a little bit more advanced kernels and use of LDS.
    It cannot be compiled at the time as it depends on some CAL Vector/Matrix classes which aren't available for public use.

- uavwrite
    Shows how to use various types of UAV.

- uavatomics
    Shows how to use uav atomics.
