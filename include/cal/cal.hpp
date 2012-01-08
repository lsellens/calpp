/*
 * C++ wrapper for ATI CAL
 * 
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

#ifndef __CAL_HPP__
#define __CAL_HPP__

#include <cal/cal.h>
#include <cal/calcl.h>
#include <cal/cal_ext.h>
#include <cassert>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cstddef>
#include <stdexcept>
#include <ostream>
#include <string>
#include <vector>
#include <set>
#include <map>

#ifndef _MSC_VER
  #include <stdint.h>
#endif

#define __CAL_DONT_USE_TYPE_TRAITS  1
//#define __CAL_USE_BLOCKING_WAIT 1
#define __CAL_KERNEL_USE_PINNED_MEMORY 1

#ifndef __CAL_DONT_USE_TYPE_TRAITS
  #include <type_traits>
#endif


enum CALInfoEnum {
    CAL_CONTEXT_DEVICES,             /**  Context devices */
    CAL_DEVICE_TARGET,               /**< Device Kernel ISA  */ 
    CAL_DEVICE_MAXRESOURCE1DWIDTH,   /**< Maximum resource 1D width */
    CAL_DEVICE_MAXRESOURCE2DWIDTH,   /**< Maximum resource 2D width */
    CAL_DEVICE_MAXRESOURCE2DHEIGHT,  /**< Maximum resource 2D height */
    CAL_DEVICE_ASIC_TARGET,          /**< Asic identifier */
    CAL_DEVICE_LOCALRAM,             /**< Amount of local GPU RAM in megabytes */
    CAL_DEVICE_UNCACHEDREMOTERAM,    /**< Amount of uncached remote GPU memory in megabytes */
    CAL_DEVICE_CACHEDREMOTERAM,      /**< Amount of cached remote GPU memory in megabytes */
    CAL_DEVICE_ENGINECLOCK,          /**< GPU device clock rate in megahertz */
    CAL_DEVICE_MEMORYCLOCK,          /**< GPU memory clock rate in megahertz */
    CAL_DEVICE_WAVEFRONTSIZE,        /**< Wavefront size */
    CAL_DEVICE_NUMBEROFSIMD,         /**< Number of SIMDs */
    CAL_DEVICE_DOUBLEPRECISION,      /**< double precision supported */
    CAL_DEVICE_LOCALDATASHARE,       /**< local data share supported */
    CAL_DEVICE_GLOBALDATASHARE,      /**< global data share supported */
    CAL_DEVICE_GLOBALGPR,            /**< global GPR supported */
    CAL_DEVICE_COMPUTESHADER,        /**< compute shader supported */
    CAL_DEVICE_MEMEXPORT,            /**< memexport supported */
    CAL_DEVICE_PITCHALIGNMENT,       /**< Required alignment for calCreateRes allocations (in data elements) */
    CAL_DEVICE_SURFACEALIGNMENT,     /**< Required start address alignment for calCreateRes allocations (in bytes) */
    CAL_DEVICE_NUMBEROFUAVS,         /**< Number of UAVs */
    CAL_DEVICE_BUAVMEMEXPORT,        /**< Hw only supports mem export to simulate 1 UAV */
    CAL_DEVICE_B3DPROGRAMGRID,       /**< CALprogramGrid for have height and depth bigger than 1*/
    CAL_DEVICE_NUMBEROFSHADERENGINES,/**< Number of shader engines */
    CAL_DEVICE_TARGETREVISION,       /**< Asic family revision */
    CAL_DEVICE_AVAILLOCALRAM,          /**< Amount of available local GPU RAM in megabytes */
    CAL_DEVICE_AVAILUNCACHEDREMOTERAM, /**< Amount of available uncached remote GPU memory in megabytes */
    CAL_DEVICE_AVAILCACHEDREMOTERAM,   /**< Amount of available cached remote GPU memory in megabytes */
    CAL_DEVICE_INDEX,                  /**  Device index */
    CAL_DEVICE_NAME,                   /**  Device name */
    CAL_KERNEL_MAXSCRATCHREGSNEEDED,   /**< Maximum number of scratch regs needed */ 
    CAL_KERNEL_NUMSHAREDGPRUSER,       /**< Number of shared GPRs */
    CAL_KERNEL_NUMSHAREDGPRTOTAL,      /**< Number of shared GPRs including ones used by SC */
    CAL_KERNEL_ECSSETUPMODE,           /**< Slow mode */
    CAL_KERNEL_NUMTHREADPERGROUP,      /**< Flattend umber of threads per group */
    CAL_KERNEL_NUMTHREADPERGROUPX,     /**< x dimension of numThreadPerGroup */
    CAL_KERNEL_NUMTHREADPERGROUPY,     /**< y dimension of numThreadPerGroup */
    CAL_KERNEL_NUMTHREADPERGROUPZ,     /**< z dimension of numThreadPerGroup */
    CAL_KERNEL_TOTALNUMTHREADGROUP,    /**< Total number of thread groups */
    CAL_KERNEL_NUMWAVEFRONTPERSIMD,    /**< Number of wavefronts per SIMD */
    CAL_KERNEL_ISMAXNUMWAVEPERSIMD,    /**< Is this the max num active wavefronts per SIMD */
    CAL_KERNEL_SETBUFFERFORNUMGROUP,   /**< Need to set up buffer for info on number of thread groups? */
    CAL_PROGRAM_BINARY,                /**  Return program binary */
    CAL_PROGRAM_BINARY_SIZE            /** Size of program binary */
};

enum CALTargetTypeEnum {
    CAL_DEVICE_TYPE_GPU
};

enum CALresallocflagsextensionEnum {
    CAL_RESALLOC_REMOTE = 128
};

namespace cal {

class Device;

namespace detail {

#ifndef _MSC_VER
  typedef uint8_t byte_type;
#else
  typedef unsigned __int8 byte_type;
#endif

enum CALTypeInfoEnum {
    CAL_TYPE_CALDEVICE,
    CAL_TYPE_CALCONTEXT,
    CAL_TYPE_CALRESOURCE,
    CAL_TYPE_CALMEM,
    CAL_TYPE_CALMODULE,
    CAL_TYPE_CALOBJECT,
    CAL_TYPE_CALIMAGE,
};

template<int HN, typename info_type>
struct info_traits {};

template<>
struct info_traits<CAL_TYPE_CALDEVICE,CALdeviceinfo>
{
    static CALresult getInfo( CALdeviceinfo& info, CALdevice dev, CALuint ordinal )
    {
        return calDeviceGetInfo(&info,ordinal);
    }
};

template<>
struct info_traits<CAL_TYPE_CALDEVICE,CALdeviceattribs>
{
    static CALresult getInfo( CALdeviceattribs& info, CALdevice dev, CALuint ordinal )
    {
        info.struct_size = sizeof(CALdeviceattribs);
        return calDeviceGetAttribs(&info,ordinal);
    }
};

template<>
struct info_traits<CAL_TYPE_CALDEVICE,CALdevicestatus>
{
    static CALresult getInfo(CALdevicestatus& info, CALdevice dev, CALuint ordinal )
    {
        info.struct_size = sizeof(CALdevicestatus);
        return calDeviceGetStatus(&info,dev);
    }
};

struct CALDeviceInfoHelper
{
    CALuint index;
};


template<>
struct info_traits<CAL_TYPE_CALDEVICE,CALDeviceInfoHelper>
{
    static CALresult getInfo(CALDeviceInfoHelper& info, CALdevice dev, CALuint ordinal )
    {
        info.index = ordinal;
        return CAL_RESULT_OK;
    }
};

struct CALDeviceNameHelper
{
    std::string name;
};

template<>
struct info_traits<CAL_TYPE_CALDEVICE,CALDeviceNameHelper>
{
    static CALresult getInfo(CALDeviceNameHelper& info, CALdevice dev, CALuint ordinal )
    {
        static const char* device_name[18] = { "ATI RV600",     "ATI RV610",     "ATI RV630",
                                               "ATI RV670",     "ATI RV7XX",     "ATI RV770",
                                               "ATI RV710",     "ATI RV730",     "ATI CYPRESS",
                                               "ATI JUNIPER",   "AMD REDWOOD",   "AMD CEDAR",
                                               "AMD RESERVED0", "AMD RESERVED1", "AMD WRESTLER",
                                               "AMD CAYMAN",    "AMD RESERVED2", "AMD BARTS" };
        CALdeviceinfo _info;
        CALresult     r;
        r = calDeviceGetInfo(&_info,ordinal);
        if( r!=CAL_RESULT_OK ) return r;

        if( _info.target<18 ) info.name = device_name[_info.target];
        else info.name="AMD GPU DEVICE";

        return CAL_RESULT_OK;
    }
};

template <int handle_name, int param_name>
struct param_traits {};

#define __PARAM_NAME_INFO1(F) \
    F(CAL_TYPE_CALDEVICE,CAL_DEVICE_INDEX,CALuint,CALDeviceInfoHelper,index)                         /**< Device index */ \
    F(CAL_TYPE_CALDEVICE,CAL_DEVICE_NAME,std::string,CALDeviceNameHelper,name)                       /**< Device target name */ \
    F(CAL_TYPE_CALDEVICE,CAL_DEVICE_TARGET,CALtarget,CALdeviceinfo,target)                           /**< Device Kernel ISA  */ \
    F(CAL_TYPE_CALDEVICE,CAL_DEVICE_MAXRESOURCE1DWIDTH,CALuint,CALdeviceinfo,maxResource1DWidth)     /**< Maximum resource 1D width */ \
    F(CAL_TYPE_CALDEVICE,CAL_DEVICE_MAXRESOURCE2DWIDTH,CALuint,CALdeviceinfo,maxResource2DWidth)     /**< Maximum resource 2D width */ \
    F(CAL_TYPE_CALDEVICE,CAL_DEVICE_MAXRESOURCE2DHEIGHT,CALuint,CALdeviceinfo,maxResource2DHeight)   /**< Maximum resource 2D height */ \
    F(CAL_TYPE_CALDEVICE,CAL_DEVICE_ASIC_TARGET,CALtarget,CALdeviceattribs,target)                   /**< Asic identifier */ \
    F(CAL_TYPE_CALDEVICE,CAL_DEVICE_LOCALRAM,CALuint,CALdeviceattribs,localRAM)                      /**< Amount of local GPU RAM in megabytes */ \
    F(CAL_TYPE_CALDEVICE,CAL_DEVICE_UNCACHEDREMOTERAM,CALuint,CALdeviceattribs,uncachedRemoteRAM)    /**< Amount of uncached remote GPU memory in megabytes */ \
    F(CAL_TYPE_CALDEVICE,CAL_DEVICE_CACHEDREMOTERAM,CALuint,CALdeviceattribs,cachedRemoteRAM)        /**< Amount of cached remote GPU memory in megabytes */ \
    F(CAL_TYPE_CALDEVICE,CAL_DEVICE_ENGINECLOCK,CALuint,CALdeviceattribs,engineClock)                /**< GPU device clock rate in megahertz */ \
    F(CAL_TYPE_CALDEVICE,CAL_DEVICE_MEMORYCLOCK,CALuint,CALdeviceattribs,memoryClock)                /**< GPU memory clock rate in megahertz */ \
    F(CAL_TYPE_CALDEVICE,CAL_DEVICE_WAVEFRONTSIZE,CALuint,CALdeviceattribs,wavefrontSize)            /**< Wavefront size */ \
    F(CAL_TYPE_CALDEVICE,CAL_DEVICE_NUMBEROFSIMD,CALuint,CALdeviceattribs,numberOfSIMD)              /**< Number of SIMDs */ \
    F(CAL_TYPE_CALDEVICE,CAL_DEVICE_DOUBLEPRECISION,CALboolean,CALdeviceattribs,doublePrecision)     /**< double precision supported */ \
    F(CAL_TYPE_CALDEVICE,CAL_DEVICE_LOCALDATASHARE,CALboolean,CALdeviceattribs,localDataShare)       /**< local data share supported */ \
    F(CAL_TYPE_CALDEVICE,CAL_DEVICE_GLOBALDATASHARE,CALboolean,CALdeviceattribs,globalDataShare)     /**< global data share supported */ \
    F(CAL_TYPE_CALDEVICE,CAL_DEVICE_GLOBALGPR,CALboolean,CALdeviceattribs,globalGPR)                 /**< global GPR supported */ \
    F(CAL_TYPE_CALDEVICE,CAL_DEVICE_COMPUTESHADER,CALboolean,CALdeviceattribs,computeShader)         /**< compute shader supported */ \
    F(CAL_TYPE_CALDEVICE,CAL_DEVICE_MEMEXPORT,CALboolean,CALdeviceattribs,memExport)                 /**< memexport supported */ \
    F(CAL_TYPE_CALDEVICE,CAL_DEVICE_PITCHALIGNMENT,CALuint,CALdeviceattribs,pitch_alignment)         /**< Required alignment for calCreateRes allocations (in data elements) */ \
    F(CAL_TYPE_CALDEVICE,CAL_DEVICE_SURFACEALIGNMENT,CALuint,CALdeviceattribs,surface_alignment)     /**< Required start address alignment for calCreateRes allocations (in bytes) */ \
    F(CAL_TYPE_CALDEVICE,CAL_DEVICE_NUMBEROFUAVS,CALuint,CALdeviceattribs,numberOfUAVs)              /**< Number of UAVs */ \
    F(CAL_TYPE_CALDEVICE,CAL_DEVICE_BUAVMEMEXPORT,CALboolean,CALdeviceattribs,bUAVMemExport)         /**< Hw only supports mem export to simulate 1 UAV */ \
    F(CAL_TYPE_CALDEVICE,CAL_DEVICE_B3DPROGRAMGRID,CALboolean,CALdeviceattribs,b3dProgramGrid)       /**< CALprogramGrid for have height and depth bigger than 1*/ \
    F(CAL_TYPE_CALDEVICE,CAL_DEVICE_NUMBEROFSHADERENGINES,CALuint,CALdeviceattribs,numberOfShaderEngines)  /**< Number of shader engines */ \
    F(CAL_TYPE_CALDEVICE,CAL_DEVICE_TARGETREVISION,CALuint,CALdeviceattribs,targetRevision)                /**< Asic family revision */ \
    F(CAL_TYPE_CALDEVICE,CAL_DEVICE_AVAILLOCALRAM,CALuint,CALdevicestatus,availLocalRAM)                   /**< Amount of available local GPU RAM in megabytes */ \
    F(CAL_TYPE_CALDEVICE,CAL_DEVICE_AVAILUNCACHEDREMOTERAM,CALuint,CALdevicestatus,availUncachedRemoteRAM) /**< Amount of available uncached remote GPU memory in megabytes */ \
    F(CAL_TYPE_CALDEVICE,CAL_DEVICE_AVAILCACHEDREMOTERAM,CALuint,CALdevicestatus,availCachedRemoteRAM)     /**< Amount of available cached remote GPU memory in megabytes */

#define __PARAM_NAME_INFO2(F) \
    F(CAL_TYPE_CALMODULE,CAL_KERNEL_MAXSCRATCHREGSNEEDED,CALuint,CALfuncInfo,maxScratchRegsNeeded) /**< Maximum number of scratch regs needed */ \
    F(CAL_TYPE_CALMODULE,CAL_KERNEL_NUMSHAREDGPRUSER,CALuint,CALfuncInfo,numSharedGPRUser)         /**< Number of shared GPRs */ \
    F(CAL_TYPE_CALMODULE,CAL_KERNEL_NUMSHAREDGPRTOTAL,CALuint,CALfuncInfo,numSharedGPRTotal)       /**< Number of shared GPRs including ones used by SC */ \
    F(CAL_TYPE_CALMODULE,CAL_KERNEL_ECSSETUPMODE,CALboolean,CALfuncInfo,eCsSetupMode)              /**< Slow mode */ \
    F(CAL_TYPE_CALMODULE,CAL_KERNEL_NUMTHREADPERGROUP,CALuint,CALfuncInfo,numThreadPerGroup)       /**< Flattend umber of threads per group */ \
    F(CAL_TYPE_CALMODULE,CAL_KERNEL_NUMTHREADPERGROUPX,CALuint,CALfuncInfo,numThreadPerGroupX)     /**< x dimension of numThreadPerGroup */ \
    F(CAL_TYPE_CALMODULE,CAL_KERNEL_NUMTHREADPERGROUPY,CALuint,CALfuncInfo,numThreadPerGroupY)     /**< y dimension of numThreadPerGroup */ \
    F(CAL_TYPE_CALMODULE,CAL_KERNEL_NUMTHREADPERGROUPZ,CALuint,CALfuncInfo,numThreadPerGroupZ)     /**< z dimension of numThreadPerGroup */ \
    F(CAL_TYPE_CALMODULE,CAL_KERNEL_TOTALNUMTHREADGROUP,CALuint,CALfuncInfo,totalNumThreadGroup)   /**< Total number of thread groups */ \
    F(CAL_TYPE_CALMODULE,CAL_KERNEL_NUMWAVEFRONTPERSIMD,CALuint,CALfuncInfo,numWavefrontPerSIMD)   /**< Number of wavefronts per SIMD */ \
    F(CAL_TYPE_CALMODULE,CAL_KERNEL_ISMAXNUMWAVEPERSIMD,CALboolean,CALfuncInfo,isMaxNumWavePerSIMD)/**< Is this the max num active wavefronts per SIMD */ \
    F(CAL_TYPE_CALMODULE,CAL_KERNEL_SETBUFFERFORNUMGROUP,CALboolean,CALfuncInfo,setBufferForNumGroup) /**< Need to set up buffer for info on number of thread groups? */


#define __DECLARE_PARAM_TRAITS1(HN, param_name, T, IT, FIELD )           \
template<>                                                              \
struct param_traits<HN,param_name>                                      \
{                                                                       \
    typedef T  param_type;                                              \
    typedef IT info_type;                                               \
                                                                        \
    static CALresult getInfo( param_type& res, CALdevice dev, CALuint ordinal ) { \
        CALresult   r;                                                  \
        info_type   info;                                               \
        r = info_traits<HN,info_type>::getInfo(info,dev,ordinal);       \
        if( r!=CAL_RESULT_OK ) return r;                                \
        res = info.FIELD;                                               \
        return r;                                                       \
    }                                                                   \
};

__PARAM_NAME_INFO1(__DECLARE_PARAM_TRAITS1);



#define __DECLARE_PARAM_TRAITS2(HN, param_name, T, IT, FIELD )           \
template<>                                                              \
struct param_traits<HN,param_name>                                      \
{                                                                       \
    typedef T  param_type;                                              \
    typedef IT info_type;                                               \
                                                                        \
    static void getInfo( param_type& res, CALfuncInfo& info ) {         \
        res = info.FIELD;                                               \
    }                                                                   \
};

__PARAM_NAME_INFO2(__DECLARE_PARAM_TRAITS2);

#undef __DECLARE_PARAM_TRAITS1
#undef __DECLARE_PARAM_TRAITS2


template<>
struct param_traits<CAL_TYPE_CALCONTEXT,CAL_CONTEXT_DEVICES>
{
    typedef const std::vector<Device>& param_type;
};

template<>
struct param_traits<CAL_TYPE_CALIMAGE,CAL_PROGRAM_BINARY_SIZE>
{
    typedef CALuint param_type;

    static CALresult getInfo( CALimage handle, param_type& size )            
    {        
        return calclImageGetSize(&size, handle);
    }
};

template<>
struct param_traits<CAL_TYPE_CALIMAGE,CAL_PROGRAM_BINARY>
{
    typedef std::vector<byte_type> param_type;

    static CALresult getInfo( CALimage handle, param_type& image )
    {
        CALuint    size;
        CALresult  r;
        
        r = calclImageGetSize(&size, handle);
        if( r!=CAL_RESULT_OK ) return r;
        
        image.resize(size);        
        r = calclImageWrite((CALvoid*)&image[0], size, handle);
        
        return r;
    }
};

template<class D>
class shared_data
{
protected:
    class shared_counter : public D
    {
    public:
        typedef shared_counter* ptr;

    protected:
        int     count_;

    public:
        shared_counter() : D(), count_(1) {}
        ~shared_counter() {}

        void retain() { count_++; }
        bool release() { count_--; if( count_>0 ) return false; delete this; return true; }
    };

protected:
    typename shared_counter::ptr data_;

    void createInstance()
    {
        if( !data_ ) data_ = new shared_counter();
    }

public:
    shared_data( int make_valid=0 ) : data_(NULL)
    {
        if( make_valid ) data_ = new shared_counter();
    }
    shared_data( const shared_data<D>& rhs ) : data_(rhs.data_)
    {
        retain();
    }
    ~shared_data() { release(); }

    shared_data<D>& operator=(const shared_data<D>& rhs)
    {
        release();
        data_ = rhs.data_;
        retain();

        return *this;
    }


    const D& data() const
    {
        assert( isValid() );        
        return *data_;
    }

    D& data()
    {
        assert( isValid() );        
        return *data_;
    }

    bool isValid() const
    {
        return data_!=NULL;
    }

protected:
    void retain() { if( data_ ) data_->retain(); }
    void release() { if( data_ ) data_->release(); }
};

struct CALcontext_helper
{

    typedef std::pointer_to_binary_function<void*,CALcontext,void>          callback_functor;
    typedef std::map<void*,callback_functor>                                ptrcall_container;
    typedef std::map<CALcontext,ptrcall_container>                          callback_container;

    typedef CALcontext handle_type;    

    template<int N>
    struct release_callback
    {
        static callback_container data;
    };

    static void release(CALcontext context)
    {
        callback_container::iterator    imap;
        ptrcall_container::iterator     icall;

        imap = release_callback<0>::data.find(context);
        if( imap==release_callback<0>::data.end() ) return;

        for(icall=imap->second.begin();icall!=imap->second.end();++icall) {
            icall->second(icall->first,context);
        }
     
        release_callback<0>::data.erase(imap);
    }

    static void registerCallback( CALcontext context, void* ptr, const callback_functor& func )
    {
        release_callback<0>::data[context].insert(std::make_pair(ptr,func));
    }

    static void unregisterCallback( CALcontext context, void* ptr )
    {
        release_callback<0>::data[context].erase(ptr);
    }
};

template<int N>
CALcontext_helper::callback_container   CALcontext_helper::release_callback<N>::data;


template<int N>
struct cal_extension_table
{
    typedef CALresult (CALAPIENTRYP PFNCALCTXWAITFOREVENTS)(CALcontext ctx, CALevent *event, CALuint num, CALuint flags);

    PFNCALCTXWAITFOREVENTS calCtxWaitForEvents;
    PFNCALRESCREATE1D      calResCreate1D;
    PFNCALRESCREATE2D      calResCreate2D;

    static cal_extension_table data;

    cal_extension_table() : calCtxWaitForEvents(NULL), calResCreate1D(NULL), calResCreate2D(NULL) {}

    void init()
    {
        if (calExtSupported((CALextid)0x8009) == CAL_RESULT_OK) {
            calExtGetProc((CALextproc*)&calCtxWaitForEvents, (CALextid)0x8009, "calCtxWaitForEvents");
        }

        if (calExtSupported(CAL_EXT_RES_CREATE) == CAL_RESULT_OK) {
            calExtGetProc((CALextproc*)&calResCreate1D, CAL_EXT_RES_CREATE, "calResCreate1D");
            calExtGetProc((CALextproc*)&calResCreate2D, CAL_EXT_RES_CREATE, "calResCreate2D");
        }
    }
};

template<int N> cal_extension_table<N> cal_extension_table<N>::data;

} // namespace detail

class Error : public std::exception
{
private:
    template<int N>
    struct error_text
    {
        static const char* data[CAL_RESULT_WARNING+1];
    };

private:
    CALresult           err_;

public:
    Error(CALresult err ) : err_(err)
    {}

    ~Error() throw() {}

    virtual const char *what() const throw ()
    {
        if( err_<0 || err_>CAL_RESULT_WARNING ) return "Unknown";
        return error_text<0>::data[err_];
    }

    const CALresult err() const { return err_; }
};

template<int N>
const char* Error::error_text<N>::data[CAL_RESULT_WARNING+1] = {
        "No error",        
        "Operational error",        
        "Parameter passed in is invalid",
        "Function used properly but currently not supported",
        "Stateful operation requested has already been performed",
        "CAL function was called without CAL being initialized",
        "A handle parameter is invalid",
        "A name parameter is invalid",
        "An asynchronous operation is still pending",
        "The resource in question is still in use",
        "Compiler generated a warning" };

namespace detail {
class DeviceData
{
public:
    CALdevice   handle_;
    CALuint     ordinal_;

public:
    DeviceData() : handle_(0), ordinal_(0) {}    
    ~DeviceData() { if( handle_ ) calDeviceClose(handle_); }
};

class KernelData;

} // detail

class Device : public detail::shared_data<detail::DeviceData>
{
public:
    Device() : detail::shared_data<detail::DeviceData>()
    {
    }

    Device( const Device& rhs ) : detail::shared_data<detail::DeviceData>(rhs)
    {
    }

    Device( CALuint ordinal ) : detail::shared_data<detail::DeviceData>(1)
    {        
        CALdevice   dev;
        CALresult   res;
        
        res = calDeviceOpen(&dev,ordinal);
        if( res!=CAL_RESULT_OK ) throw Error(res);

        data().ordinal_ = ordinal;
        data().handle_  = dev;
    }

    template <int Name>
    typename detail::param_traits<detail::CAL_TYPE_CALDEVICE,Name>::param_type getInfo() const
    {
        typename detail::param_traits<detail::CAL_TYPE_CALDEVICE,Name>::param_type   v;
        CALresult   r;
                
        r = detail::param_traits<detail::CAL_TYPE_CALDEVICE,Name>::getInfo(v,data().handle_,data().ordinal_);
        if( r!=CAL_RESULT_OK ) throw Error(r);

        return v;
    }

    template<typename T>
    void getInfo( T& param ) const
    {
        CALresult   r;

        r = detail::info_traits<detail::CAL_TYPE_CALDEVICE,T>::getInfo(param,data().handle_,data().ordinal_);
        if( r!=CAL_RESULT_OK ) throw Error(r);
    }

    CALdevice operator()() const { return data().handle_; }
};

namespace detail {
class ContextData
{
public:
    std::vector<Device>     devices_;

public:
    ContextData() {}
    ~ContextData() {}
};
} // detail

class Context : public detail::shared_data<detail::ContextData>
{
public:
    Context() : detail::shared_data<detail::ContextData>(0)
    {
    }

    Context( int type ) : detail::shared_data<detail::ContextData>(1)
    {
        CALresult  r;
        CALuint    c;

        r = calDeviceGetCount(&c);
        if( r!=CAL_RESULT_OK ) throw Error(r);

        for(CALuint i=0;i<c;++i) data().devices_.push_back(Device(i));
    }

    Context( const Context& rhs ) : detail::shared_data<detail::ContextData>(rhs)
    {
    }

    Context( const Device& dev ) : detail::shared_data<detail::ContextData>(1)
    {
        data().devices_.push_back(dev);
    }

    Context( const std::vector<Device>& devices ) : detail::shared_data<detail::ContextData>(1)
    {
        data().devices_ = devices;
    }

    template<int Name>
    typename detail::param_traits<detail::CAL_TYPE_CALCONTEXT,Name>::param_type getInfo() const
    {
        return data().devices_;
    }

    friend class Image1D;
    friend class Image2D;
};

class Event 
{
public:
    typedef CALevent    element_type;

protected:
    CALevent            event_;

public:
    Event() : event_() {}
    Event( CALevent event ) : event_(event) {}

    const CALevent& operator()() const { return event_; }
    CALevent& operator()() { return event_; }    
};

namespace detail {
class MemoryData
{
public: 
    struct map_info
    {
        void*   ptr;
        int     counter;
        CALuint pitch;

        map_info( void* _ptr, int _counter, CALuint _pitch ) : ptr(_ptr), counter(_counter), pitch(_pitch) {}
    };
public:
    std::map<CALdevice,CALresource> handle_;
    std::map<CALcontext,CALmem>     mem_;
    std::vector<Device>             device_;
    int                             width_,height_;
    std::map<CALdevice,map_info>    map_;
    bool                            remote_;

protected:
    void registerContext( CALcontext context ) const
    {        
        detail::CALcontext_helper::registerCallback(context,(void*)this,std::ptr_fun(&callback));
    }

    void unregisterContext() const
    {
        std::map<CALcontext,CALmem>::const_iterator   imem;

        for(imem=mem_.begin();imem!=mem_.end();++imem) {
            detail::CALcontext_helper::unregisterCallback(imem->first,(void*)this);
        }
    }

    void releaseContext( CALcontext context )
    {
        std::map<CALcontext,CALmem>::iterator   imem;

        imem = mem_.find(context);
        if( imem==mem_.end() ) return;

        calCtxReleaseMem(imem->first,imem->second);
        mem_.erase(imem);
    }

    static void callback( void* pMemory, CALcontext context )
    {
        static_cast<MemoryData*>(pMemory)->releaseContext(context);
    }

public:
    MemoryData() : width_(0), height_(0), remote_(false) {}
    ~MemoryData()
    {
        unregisterContext();

        std::map<CALcontext,CALmem>::iterator   imem;
        for(imem=mem_.begin();imem!=mem_.end();++imem) calCtxReleaseMem(imem->first,imem->second);

        std::map<CALdevice,CALresource>::iterator ihandle;
        for(ihandle=handle_.begin();ihandle!=handle_.end();++ihandle) calResFree(ihandle->second);
    }

    void attach( CALcontext context, CALdevice device )
    {
        if( isAttached(context) ) return;

        std::map<CALdevice,CALresource>::iterator ihandle;
        CALmem      mem;
        CALresult   r;

        ihandle = remote_?handle_.find(0):handle_.find(device);
        if( ihandle==handle_.end() ) throw Error(CAL_RESULT_ERROR);

        r = calCtxGetMem(&mem,context,ihandle->second);
        if( r!=CAL_RESULT_OK ) throw Error(r);

        mem_.insert( std::make_pair(context,mem) );
        registerContext(context);
    }

    bool isAttached( CALcontext context ) const
    {
        return mem_.find(context)!=mem_.end();
    }

    CALmem getMem( CALcontext context ) const
    {
        std::map<CALcontext,CALmem>::const_iterator imem;

        imem = mem_.find(context);
        if( imem==mem_.end() ) throw Error(CAL_RESULT_NOT_INITIALIZED);

        return imem->second;
    }

    CALvoid* map2( CALuint& pitch, CALdevice device )
    {
        std::map<CALdevice,map_info>::iterator imap;

        if( remote_ ) device=0;

        imap = map_.find(device);
        if( imap==map_.end() ) throw Error(CAL_RESULT_NOT_INITIALIZED);

        if( imap->second.ptr ) {
            imap->second.counter++;
            pitch = imap->second.pitch;
            return imap->second.ptr;
        }

        std::map<CALdevice,CALresource>::iterator ihandle;
        CALresult   r;
        CALvoid*    ptr;

        ihandle = handle_.find(device);
        if( ihandle==handle_.end() ) throw Error(CAL_RESULT_ERROR);

        r = calResMap(&ptr,&imap->second.pitch,ihandle->second,0);
        if( r!=CAL_RESULT_OK ) throw Error(r);

        imap->second.ptr     = ptr;
        imap->second.counter = 1;
        pitch                = imap->second.pitch;

        return ptr;
    }

    void unmap2( CALdevice device )
    {
        std::map<CALdevice,map_info>::iterator imap;

        if( remote_ ) device=0;

        imap = map_.find(device);
        if( imap==map_.end() ) throw Error(CAL_RESULT_NOT_INITIALIZED);

        if( imap->second.ptr==NULL ) return;
        if( --imap->second.counter>0 ) return;

        std::map<CALdevice,CALresource>::iterator ihandle;
        CALresult   r;

        ihandle = handle_.find(device);
        if( ihandle==handle_.end() ) throw Error(CAL_RESULT_ERROR);

        r = calResUnmap(ihandle->second);
        if( r!=CAL_RESULT_OK ) throw Error(r);

        imap->second.ptr = NULL;
    }

    /*
    CALvoid* map( CALuint& pitch, int idx=0 )
    {
        return map2( pitch, device_[idx]() );
    }
    
    void unmap( int idx=0 )
    {
        return unmap2( device_[idx]() );
    }
    */

    void addDevices( const std::vector<Device>& device )
    {
        device_ = device;
        if( !remote_ ) {
            for(unsigned i=0;i<device.size();i++) {
                map_.insert( std::make_pair(device[i](),map_info(NULL,0,0)) );
            }
        } else map_.insert( std::make_pair((CALdevice)0,map_info(NULL,0,0)) );
    }

    void addDevices( const std::vector<CALdevice>& device )
    {
        if( !remote_ ) {
            for(unsigned i=0;i<device.size();i++) {
                map_.insert( std::make_pair(device[i],map_info(NULL,0,0)) );
            }
        } else map_.insert( std::make_pair((CALdevice)0,map_info(NULL,0,0)) );
    }

    /*
    CALresource getHandle( int idx ) const
    {
        std::map<CALdevice,CALresource>::const_iterator ihandle;
        CALdevice device;
        
        assert( idx>=0 && idx<device_.size() );

        device = remote_?0:device_[idx]();

        return getHandle2(device);
    }
    */
    
    CALresource getHandle2( CALdevice device ) const
    {
        std::map<CALdevice,CALresource>::const_iterator ihandle;

        ihandle = handle_.find(device);
        if( ihandle==handle_.end() ) throw Error(CAL_RESULT_ERROR);

        return ihandle->second;        
    }
};
} // detail

class Memory : public detail::shared_data<detail::MemoryData>
{
protected:
    void attach( CALcontext context, CALdevice device ) { data().attach(context,device); }
    bool isAttached( CALcontext context ) const { return data().isAttached(context); }
    CALvoid* map2( CALuint& pitch, CALdevice device ) { return data().map2(pitch,device); }
    void unmap2( CALdevice device ) { data().unmap2(device); }

public:
    Memory() : detail::shared_data<detail::MemoryData>()
    {
    }

    Memory( const Memory& rhs ) : detail::shared_data<detail::MemoryData>(rhs)
    {
    }

    ~Memory()
    {
    }

    /*
    CALvoid* map( CALuint& pitch, int idx=0 )
    {
        #pragma message("Memory::map is obsolete. Use CommandQueue::mapMemObject instead")
        return data().map(pitch,idx);
    }

    void unmap( int idx=0 )
    {
        #pragma message("Memory::unmap is obsolete. Use CommandQueue::unmapMemObject instead")
        data().unmap(idx);
    }
    */

    CALresource operator()( const Device& device ) const { return data().getHandle2(device()); }
    CALresource operator()( CALdevice device ) const { return data().getHandle2(device); }

    CALmem getMem( CALcontext context ) const { return data().getMem(context); }

    friend class detail::KernelData;
    friend class CommandQueue;
};

class Image : public Memory
{
public:
    Image() : Memory() {}
    Image( const Image& rhs ) : Memory(rhs) {}
};

class Image1D : public Image
{
protected:
    Image1D( CALdevice device, CALuint width, CALformat format, CALuint flags, CALvoid* host_ptr, int size ) : Image()
    {
        std::vector<CALdevice>   devices;
        CALresource              res;
        CALresult                r;

        devices.push_back(device);
        
        createInstance();

        if( !detail::cal_extension_table<0>::data.calResCreate1D ) throw Error(CAL_RESULT_NOT_SUPPORTED);        

        r = detail::cal_extension_table<0>::data.calResCreate1D(&res,device,host_ptr,width,format,size,flags);
        if( r!=CAL_RESULT_OK ) throw Error(r);
          
        data().handle_.insert( std::make_pair(device, res) );

        data().remote_ = false;                
        data().addDevices(devices);
        data().width_  = width;
    }
    
public:
    Image1D() : Image()
    {
    }

    Image1D( const Image1D& rhs ) : Image(rhs)
    {
    }

    Image1D( const Context& context, CALuint width, CALformat format, CALuint flags ) : Image()
    {
        CALresult  r;
        bool       remote;

        createInstance();

        remote = flags&(CALuint)CAL_RESALLOC_REMOTE;
        flags  &= ~(CALuint)CAL_RESALLOC_REMOTE;

        if( !remote ) {
            CALresource              res;
            std::vector<CALresource> _res;

            for(unsigned i=0;i<context.data().devices_.size();i++) {
               r = calResAllocLocal1D(&res,context.data().devices_[i](),width,format,flags);
               if( r!=CAL_RESULT_OK ) {
                   for(unsigned j=0;j<_res.size();j++) calResFree(_res[i]);
                   throw Error(r);
               }
               _res.push_back(res);
            }

            for(unsigned i=0;i<_res.size();i++) 
                data().handle_.insert( std::make_pair(context.data().devices_[i](), _res[i]) );
        } else {
            std::vector<CALdevice>  devices;
            CALresource             res;

            for(unsigned i=0;i<context.data().devices_.size();i++) devices.push_back(context.data().devices_[i]());
            r = calResAllocRemote1D(&res,&devices[0],devices.size(),width,format,flags);
            if( r!=CAL_RESULT_OK ) throw Error(r);

            data().handle_.insert( std::make_pair((CALdevice)0,res) );
        }
        data().remote_ = remote;
        data().addDevices(context.data().devices_);
        data().width_  = width;
    }

    // Create pinned memory image
    // there must be one item in host_ptr for each device in context
    // addresses in host_ptr must be aligned to 256 byte boundary ( 4096 on Vista )
    // there is limit on total amount of pinned memory ( depends on system - 32MB to 64MB )
    Image1D( const Context& context, CALuint width, CALformat format, CALuint flags, std::vector<CALvoid*> host_ptr, int size ) : Image()
    {
        CALresource              res;
        std::vector<CALresource> _res;
        CALresult                r;

        createInstance();

        if( !detail::cal_extension_table<0>::data.calResCreate1D ) throw Error(CAL_RESULT_NOT_SUPPORTED);
        if( host_ptr.size()!=context.data().devices_.size() ) throw Error(CAL_RESULT_INVALID_PARAMETER);

        for(unsigned i=0;i<context.data().devices_.size();i++) {
           r = detail::cal_extension_table<0>::data.calResCreate1D(&res,context.data().devices_[i](),host_ptr[i],width,format,size,flags);
           if( r!=CAL_RESULT_OK ) {
               for(unsigned j=0;j<_res.size();j++) calResFree(_res[i]);
               throw Error(r);
           }
           _res.push_back(res);
        }

        for(unsigned i=0;i<_res.size();i++) 
            data().handle_.insert( std::make_pair(context.data().devices_[i](), _res[i]) );

        data().remote_ = false;
        data().addDevices(context.data().devices_);
        data().width_  = width;
    }

    int getWidth() const { return data().width_; }
    
    friend class detail::KernelData;
};

class Image2D : public Image
{
public:
    Image2D() : Image() {}
    Image2D( const Image2D& rhs ) : Image(rhs) {}
    Image2D( const Context& context, CALuint width, CALuint height, CALformat format, CALuint flags ) : Image()
    {
        CALresult   r;
        bool        remote;

        createInstance();

        remote = flags&(CALuint)CAL_RESALLOC_REMOTE;
        flags  &= ~(CALuint)CAL_RESALLOC_REMOTE;

        if( !remote ) {
            CALresource              res;
            std::vector<CALresource> _res;

            for(unsigned i=0;i<context.data().devices_.size();i++) {
               r = calResAllocLocal2D(&res,context.data().devices_[i](),width,height,format,flags);
               if( r!=CAL_RESULT_OK ) {
                   for(unsigned j=0;j<_res.size();j++) calResFree(_res[i]);
                   throw Error(r);
               }
               _res.push_back(res);
            }

            for(unsigned i=0;i<_res.size();i++) 
                data().handle_.insert( std::make_pair(context.data().devices_[i](), _res[i]) );
        } else {
            std::vector<CALdevice>  devices;
            CALresource             res;

            for(unsigned i=0;i<context.data().devices_.size();i++) devices.push_back(context.data().devices_[i]());
            r = calResAllocRemote2D(&res,&devices[0],devices.size(),width,height,format,flags);
            if( r!=CAL_RESULT_OK ) throw Error(r);

            data().handle_.insert( std::make_pair((CALdevice)0,res) );
        }

        data().remote_ = remote;
        data().addDevices(context.data().devices_);
        data().width_  = width;
        data().height_ = height;
    }

    // Create pinned memory image
    // there must be one item in host_ptr for each device in context
    // addresses in host_ptr must be aligned to 256 byte boundary ( 4096 on Vista )
    // there is limit on total amount of pinned memory ( depends on system - 32MB to 64MB )
    Image2D( const Context& context, CALuint width, CALuint height, CALformat format, CALuint flags, std::vector<CALvoid*> host_ptr, int size ) : Image()
    {
        CALresource              res;
        std::vector<CALresource> _res;
        CALresult                r;

        createInstance();

        if( !detail::cal_extension_table<0>::data.calResCreate2D ) throw Error(CAL_RESULT_NOT_SUPPORTED);
        if( host_ptr.size()!=context.data().devices_.size() ) throw Error(CAL_RESULT_INVALID_PARAMETER);

        for(unsigned i=0;i<context.data().devices_.size();i++) {
           r = detail::cal_extension_table<0>::data.calResCreate2D(&res,context.data().devices_[i](),host_ptr[i],width,height,format,size,flags);
           if( r!=CAL_RESULT_OK ) {
               for(unsigned j=0;j<_res.size();j++) calResFree(_res[i]);
               throw Error(r);
           }
           _res.push_back(res);
        }

        for(unsigned i=0;i<_res.size();i++) 
            data().handle_.insert( std::make_pair(context.data().devices_[i](), _res[i]) );

        data().remote_ = false;
        data().addDevices(context.data().devices_);
        data().width_  = width;
    }

    int getWidth() const { return data().width_; }
    int getHeight() const { return data().height_; }
};

class NDRange : public CALdomain3D
{
public:
    NDRange()
    {
        width = height = depth = 1;    
    }

    //! Create a 1D range
    NDRange(CALuint size0) 
    {
        width = size0;
        height = depth = 1;
    }

    //! Create a 2D range
    NDRange(CALuint size0, CALuint size1)

    {
        width  = size0;
        height = size1;
        depth  = 1;
    }

    //! Create a 3D range
    NDRange(CALuint size0, CALuint size1, CALuint size2)
    {
        width  = size0;
        height = size1;
        depth  = size2;
    }
};

namespace detail {
class ProgramData
{
public:
    CALimage                handle_;
    Context                 context_;
    std::vector<byte_type>  buffer_;
    int                     type_;

public:
    ProgramData() : handle_(0), context_(), buffer_(), type_(-1) {}
    ~ProgramData()
    {
        if( handle_ ) calImageFree(handle_);
    }

    void buildFromSource( const std::vector<Device>& devices )
    {
        std::vector<CALobject>  object;
        std::set<CALtarget>     target;
        CALimage                image;
        CALresult               r;

        for(unsigned i=0;i<devices.size();++i)
            target.insert( devices[i].getInfo<CAL_DEVICE_TARGET>() );

        try {
            for(std::set<CALtarget>::iterator itarget=target.begin();itarget!=target.end();++itarget) {
                CALobject   obj;

                r = calclCompile(&obj,(CALlanguage)type_,(CALchar*)&buffer_[0], *itarget );
                if( r!=CAL_RESULT_OK ) throw Error(r);
                object.push_back(obj);
            }
        } catch(...) {
            for(unsigned i=0;i<object.size();++i)
                calclFreeObject(object[i]);
            throw;
        }

        r = calclLink(&image,&object[0],object.size());
        for(unsigned i=0;i<object.size();++i)
            calclFreeObject(object[i]);
        if( r!=CAL_RESULT_OK ) throw Error(r);

        handle_ = image;
    }

    void buildFromBinary( const std::vector<Device>& devices )
    {
        CALimage                image;
        CALresult               r;

        r = calImageRead(&image,(CALvoid*)&buffer_[0],buffer_.size());
        if( r!=CAL_RESULT_OK ) throw Error(r);        

        handle_ = image;
    }
};
} // detail

class Program : public detail::shared_data<detail::ProgramData>
{
private:
    template<int N>
    struct log_stream {
        static std::ostream*   ptr_;
    };

    static void outputToStream( const char* txt )
    {
        if( log_stream<0>::ptr_ ) (*log_stream<0>::ptr_) << txt;
    }

public:
    Program() : detail::shared_data<detail::ProgramData>()
    {
    }

    Program( const Program& rhs ) : detail::shared_data<detail::ProgramData>(rhs)
    {
    }

    Program( const Context& context, const CALchar* source, CALuint size, CALlanguage language=CAL_LANGUAGE_IL ) : detail::shared_data<detail::ProgramData>(1)
    {
        assert( source && size>0 );

        data().context_ = context;
        data().type_    = language;
        data().buffer_.resize(size+1);
        std::memcpy(&data().buffer_[0], source, size);
        data().buffer_[size]=0;
    }

    Program( const Context& context, const CALvoid* binary, CALuint size ) : detail::shared_data<detail::ProgramData>(1)
    {
        assert( binary && size>0 );

        data().context_ = context;
        data().type_    = 0;
        data().buffer_.resize(size);
        std::memcpy(&data().buffer_[0], binary, size);
    }

    void build( const std::vector<Device>& devices )
    {
        assert( devices.size()>0 );

        if( data().type_>0 ) data().buildFromSource(devices);
        else if( data().type_==0 ) data().buildFromBinary(devices);
        else throw Error(CAL_RESULT_ERROR);
    }

    void build( const Device& device )
    {
        std::vector<Device> devices(1,device);
        build(devices);
    }

    CALimage operator()() const { return data().handle_; }

    void disassemble( std::ostream& out ) const
    {
        log_stream<0>::ptr_ = &out;
        calclDisassembleImage(data().handle_, &outputToStream);        
    }
    
    template<int Name>
    typename detail::param_traits<detail::CAL_TYPE_CALIMAGE,Name>::param_type getInfo() const
    {
        typename detail::param_traits<detail::CAL_TYPE_CALIMAGE,Name>::param_type result;
        CALresult r;
                
        r = detail::param_traits<detail::CAL_TYPE_CALIMAGE,Name>::getInfo(data().handle_,result);
        if( r!=CAL_RESULT_OK ) throw Error(r);
        
        return result;
    }

    friend class Kernel;
};

template<int N>
std::ostream* Program::log_stream<N>::ptr_=NULL;

class KernelFunctor;
class CommandQueue;

namespace detail {
class KernelData
{
public:
    struct argument_data
    {
        // binding info
        std::string     name;
        int             cb_index;
        int             cb_offset;
        int             cb_size;

        // data
        Memory          mem;
        byte_type       data[16];
        byte_type       *ptr;

        argument_data() : name(), cb_index(-1), cb_offset(0), cb_size(0), ptr(NULL) {}
        argument_data( const std::string& _name ) : name(_name), cb_index(-1), cb_offset(0), cb_size(0), ptr(NULL) {}
        argument_data( const std::string& _name, int _cbi, int _cbo, int _cbs ) : name(_name), cb_index(_cbi), cb_offset(_cbo), cb_size(_cbs), ptr(NULL) {}
    };

    struct arg_state    
    {
        CALresource     resource;
        CALname         name;
        byte_type       data[16];
        bool            update;
        
        arg_state() : resource(0), name(0), update(true) {}
    };
    
    struct cb_state
    {
        Image1D     data;
        int         size;        
#ifdef __CAL_KERNEL_USE_PINNED_MEMORY
        void*       host_ptr;
#endif
        byte_type*  ptr;
        bool        update;

#ifdef __CAL_KERNEL_USE_PINNED_MEMORY        
        cb_state() : size(0), host_ptr(NULL), ptr(NULL), update(true) {}
        ~cb_state() { if( host_ptr ) std::free(host_ptr); }
#else
        cb_state() : size(0), ptr(NULL), update(true) {}
#endif
    };
    
    struct state_data
    {
        std::map<int,cb_state> cb;
        std::vector<arg_state> arg;
        
        CALcontext             ctx;
        CALdevice              device;
        CALmodule              module;
        CALfunc                func;
        
        state_data() : ctx(0), module(0), func(0) {}
        ~state_data() { if( ctx && module ) calModuleUnload(ctx,module); }
    };
    

public:
    Program                             program_;
    std::string                         name_;
    std::vector<argument_data>          arg_;
    std::map<CALcontext,state_data>     state_;

protected:
    void registerContext( CALcontext context ) const
    {
        detail::CALcontext_helper::registerCallback(context,(void*)this,std::ptr_fun(&callback));
    }

    void unregisterContext() const
    {
        std::map<CALcontext,state_data>::const_iterator   istate;        

        for(istate=state_.begin();istate!=state_.end();++istate) {
            detail::CALcontext_helper::unregisterCallback(istate->first,(void*)this);
        }
    }

    void releaseContext( CALcontext context )
    {
        std::map<CALcontext,state_data>::iterator   istate;

        istate = state_.find(context);
        if( istate==state_.end() ) return;

        state_.erase(istate);
    }

    static void callback( void* pKernel, CALcontext context )
    {
        static_cast<KernelData*>(pKernel)->releaseContext(context);
    }
    
public:
    KernelData() {}
    ~KernelData()
    {
        unregisterContext();
    }

    void clearState()
    {
        unregisterContext();
        state_.clear();
    }

    void allocCB( state_data& state )
    {
        for(unsigned int i=0;i<arg_.size();i++) {
            if( arg_[i].cb_index<0 ) continue;            
            state.cb[arg_[i].cb_index].size = std::max( state.cb[arg_[i].cb_index].size,
                                                        (arg_[i].cb_offset+(arg_[i].cb_size==0?16:arg_[i].cb_size)+15)/16 );
        }

        std::map<int,cb_state>::iterator icb;

        for(icb=state.cb.begin();icb!=state.cb.end();++icb) {
#ifdef __CAL_KERNEL_USE_PINNED_MEMORY
            icb->second.host_ptr = std::malloc( 16*icb->second.size + 4096 );
            icb->second.ptr      = (byte_type*)(((ptrdiff_t)icb->second.host_ptr + (ptrdiff_t)4095) & (~(ptrdiff_t)0xFFF));
            icb->second.data     = Image1D(state.device, icb->second.size, CAL_FORMAT_UNSIGNED_INT32_4, 0, icb->second.ptr, 16*icb->second.size );
#else       
            icb->second.data = Image1D(program_.data().context_, icb->second.size, CAL_FORMAT_UNSIGNED_INT32_4, 0);
#endif            
        }
    }

    void attachCB( state_data& state )
    {
        std::map<int,cb_state>::iterator    icb;
        CALresult                           r;
        CALname                             name;
        char                                cname[64];

        for(icb=state.cb.begin();icb!=state.cb.end();++icb) {
            icb->second.data.attach(state.ctx,state.device);
            
            std::sprintf(cname,"cb%i",icb->first);
            r = calModuleGetName(&name,state.ctx,state.module,cname);
            if( r!=CAL_RESULT_OK ) throw Error(r);
            
            r = calCtxSetMem(state.ctx,name,icb->second.data.getMem(state.ctx));
            if( r!=CAL_RESULT_OK ) throw Error(r);
        }        
    }
    
    void argName( state_data& state )
    {
        CALresult r;
        
        for(unsigned i=0;i<arg_.size();i++) {
            if( arg_[i].cb_index>=0 ) continue;
                        
            r = calModuleGetName(&state.arg[i].name,state.ctx,state.module,arg_[i].name.c_str());
            if( r!=CAL_RESULT_OK ) throw Error(r);            
        }        
    }

    state_data& loadState( CALcontext context, CALdevice device )
    {
        std::map<CALcontext,state_data>::iterator istate;
        CALresult r;
        
        istate = state_.find(context);
        if( istate!=state_.end() ) {
            assert( istate->second.device==device );
            return istate->second;
        }
        
        istate = state_.insert( std::make_pair(context,state_data()) ).first;
        
        registerContext(context);
        
        istate->second.ctx    = context;
        istate->second.device = device;
        istate->second.arg.resize(arg_.size());

        r = calModuleLoad(&istate->second.module,istate->second.ctx,program_());
        if( r!=CAL_RESULT_OK ) throw Error(r);

        r = calModuleGetEntry(&istate->second.func,istate->second.ctx,istate->second.module,name_.c_str());
        if( r!=CAL_RESULT_OK ) throw Error(r);
                
        allocCB(istate->second);
        attachCB(istate->second);
        argName(istate->second);
        
        return istate->second;
    }

    void mapCB( state_data& state )
    {
#ifndef __CAL_KERNEL_USE_PINNED_MEMORY
        CALuint                 pitch;

        std::map<int,cb_state>::iterator icb;

        for(icb=state.cb.begin();icb!=state.cb.end();++icb) {
            if( icb->second.update ) {
                icb->second.ptr = (byte_type*)icb->second.data.map2(pitch,state.device);
                icb->second.update = false;
            }
        }        
#endif        
    }

    void unmapCB( state_data& state )
    {
#ifndef __CAL_KERNEL_USE_PINNED_MEMORY        
        std::map<int,cb_state>::iterator icb;

        for(icb=state.cb.begin();icb!=state.cb.end();++icb) {
            if( icb->second.ptr ) {
                icb->second.data.unmap2(state.device);
                icb->second.ptr = NULL;
            }
        }
#endif
    }

    void checkUpdates( state_data& state )
    {
        for(unsigned i=0;i<arg_.size();i++) {
            if( arg_[i].cb_index>=0 ) {
                if( !arg_[i].ptr ) {
                    if( std::memcmp( state.arg[i].data, arg_[i].data, arg_[i].cb_size ) ) {
                        state.arg[i].update = true;
                    }
                } else state.arg[i].update = true;
            
                if( state.arg[i].update ) state.cb[arg_[i].cb_index].update = true;
            } else {
                if( arg_[i].mem(state.device)!=state.arg[i].resource ) state.arg[i].update = true;
            }
        }        
    }

    void copyData( state_data& state )
    {        
        for(unsigned i=0;i<arg_.size();i++) {
            if( arg_[i].cb_index<0 || !state.arg[i].update ) continue;

            if( !arg_[i].ptr ) {
                std::memcpy( state.cb[arg_[i].cb_index].ptr+arg_[i].cb_offset, arg_[i].data, arg_[i].cb_size );
                std::memcpy( state.arg[i].data, arg_[i].data, arg_[i].cb_size );
            } else {
                std::memcpy( state.cb[arg_[i].cb_index].ptr+arg_[i].cb_offset, arg_[i].ptr, arg_[i].cb_size );
            }
            state.arg[i].update = false;
        }
    }

    void attachMem( state_data& state )
    {
        CALname     name;
        CALresult   r;
        
        for(unsigned i=0;i<arg_.size();i++) {
            if( arg_[i].cb_index>=0 || !state.arg[i].update ) continue;
            
            arg_[i].mem.attach(state.ctx,state.device);
            
            state.arg[i].resource = arg_[i].mem(state.device);
            
            r = calCtxSetMem(state.ctx,state.arg[i].name,arg_[i].mem.getMem(state.ctx));
            if( r!=CAL_RESULT_OK ) throw Error(r);
            
            state.arg[i].update = false;
        }        
    }

    void prepareKernel( CALcontext context, CALdevice device )
    {
        state_data& state(loadState(context,device));                

        checkUpdates(state);
        
        mapCB(state);
        copyData(state);
        unmapCB(state);

        attachMem(state);
    }

    CALfunc getFunc( CALcontext context ) 
    {
        std::map<CALcontext,state_data>::const_iterator istate;
        
        istate = state_.find(context);
        if( istate==state_.end() ) throw Error(CAL_RESULT_ERROR);
        
        return istate->second.func;
    }

    /*
    void printCB()
    {
        CALuint pitch;
        int     s;

        for(int i=0;i<cb_.size();i++) {
            std::cout << boost::format("cb[%i] size=%i\n") % i % cb_[i].getWidth();
            s = cb_[i].getWidth();
            float* ptr = (float*)cb_[i].map(pitch);
            for(int j=0;j<(s*4);j++) std::cout << boost::format("{%u,%f},") % (*((uint32_t*)ptr+j)) % ptr[j];
            std::cout << "\n";
            cb_[i].unmap();
        }
    }
    */
};
}

class Kernel : public detail::shared_data<detail::KernelData>
{
public:
    typedef detail::KernelData::argument_data argument_data;
    typedef argument_data arg;

protected:
    void prepareKernel( CALcontext context, CALdevice device ) { data().prepareKernel(context,device); }
    CALfunc getFunc( CALcontext context ) { return data().getFunc(context); }

#ifndef __CAL_DONT_USE_TYPE_TRAITS
    template<typename T>
    void isetArg( int index, const T& val, const std::false_type& )
    {        
        if( index<0 || index>=(int)data().arg_.size() ) throw Error(CAL_RESULT_INVALID_PARAMETER);
        if( sizeof(val)>16 ) throw Error(CAL_RESULT_INVALID_PARAMETER);
        if( data().arg_[index].cb_index<0 ) throw Error(CAL_RESULT_INVALID_PARAMETER);

        union { T s; detail::byte_type d[16]; } conv;

        conv.s = val;
        std::memcpy( data().arg_[index].data, conv.d, 16 );
        data().arg_[index].cb_size = sizeof(T);
    }

    template<typename T>
    void isetArg( int index, const T& mem, const std::true_type& )
    {        
        if( index<0 || index>=(int)data().arg_.size() ) throw Error(CAL_RESULT_INVALID_PARAMETER);
        if( data().arg_[index].cb_index>=0 ) throw Error(CAL_RESULT_INVALID_PARAMETER);

        data().arg_[index].mem = mem;
    }
#endif
         
public:
    Kernel() : detail::shared_data<detail::KernelData>()
    {
    }

    Kernel( const Kernel& rhs ) : detail::shared_data<detail::KernelData>(rhs)
    {
    }

    Kernel(const Program& program, const char* name="main" ) : detail::shared_data<detail::KernelData>(1)
    {
        assert( std::strcmp(name,"main")==0 );

        data().program_ = program;
        data().name_    = name;
    }

    void setArgBind( int index, const std::string& name )
    {
        data().clearState();
        
        data().arg_.resize(index+1);
        data().arg_[index] = arg(name);
    }

    //
    // cb_offset in bytes
    // cb_size   in bytes
    void setArgBind( int index, const std::string& name, int cb_offset, int cb_size=0 )
    {
        int     cb_index;
        char*   endptr;

        if( name.size()<3 || name[0]!='c' || name[1]!='b' )  throw Error(CAL_RESULT_INVALID_PARAMETER);
        
        data().clearState();
        
        cb_index = std::strtol(&name[2], &endptr, 10);
        if( endptr!=(&name[0]+name.size()) ) throw Error(CAL_RESULT_INVALID_PARAMETER);
        
        data().arg_.resize(index+1);
        data().arg_[index] = arg(name,cb_index,cb_offset,cb_size);
    }

    Kernel& operator%( const arg& v )
    {
        data().clearState();        
        data().arg_.push_back(v);
        return *this;
    }

#ifndef __CAL_DONT_USE_TYPE_TRAITS
    template<typename T>
    void setArg( int index, const T& val )
    {
        isetArg(index,val,std::is_base_of<Memory,T>());
    }
#else
    void setArg( int index, const Memory& mem )
    {        
        if( index<0 || index>=(int)data().arg_.size() ) throw Error(CAL_RESULT_INVALID_PARAMETER);
        if( data().arg_[index].cb_index>=0 ) throw Error(CAL_RESULT_INVALID_PARAMETER);

        data().arg_[index].mem = mem;
    }
    void setArg( int index, const Image1D& mem )
    {        
        if( index<0 || index>=(int)data().arg_.size() ) throw Error(CAL_RESULT_INVALID_PARAMETER);
        if( data().arg_[index].cb_index>=0 ) throw Error(CAL_RESULT_INVALID_PARAMETER);

        data().arg_[index].mem = mem;
    }
    void setArg( int index, const Image2D& mem )
    {        
        if( index<0 || index>=(int)data().arg_.size() ) throw Error(CAL_RESULT_INVALID_PARAMETER);
        if( data().arg_[index].cb_index>=0 ) throw Error(CAL_RESULT_INVALID_PARAMETER);

        data().arg_[index].mem = mem;
    }

    template<typename T>
    void setArg( int index, const T& val )
    {        
        if( index<0 || index>=(int)data().arg_.size() ) throw Error(CAL_RESULT_INVALID_PARAMETER);
        if( sizeof(val)>16 ) throw Error(CAL_RESULT_INVALID_PARAMETER);
        if( data().arg_[index].cb_index<0 ) throw Error(CAL_RESULT_INVALID_PARAMETER);

        union { T s; detail::byte_type d[16]; } conv;

        conv.s = val;
        std::memcpy( data().arg_[index].data, conv.d, 16 );
        data().arg_[index].cb_size = sizeof(val);
    }
#endif

    template<typename T>
    void setArg( int index, const T* pval, int size=0 )
    {
        if( index<0 || index>=(int)data().arg_.size() ) throw Error(CAL_RESULT_INVALID_PARAMETER);
        if( data().arg_[index].cb_index<0 ) throw Error(CAL_RESULT_INVALID_PARAMETER);        
        
        data().arg_[index].ptr = (detail::byte_type*)pval;
        if( size>0 ) data().arg_[index].cb_size = size;
    }

    KernelFunctor bind( const CommandQueue& queue, const NDRange& global, const NDRange& local );
    KernelFunctor bind( const CommandQueue& queue, const NDRange& global );

    template<int Name>
    typename detail::param_traits<detail::CAL_TYPE_CALMODULE,Name>::param_type getInfo( const CommandQueue& queue );

    friend class CommandQueue;
};

namespace detail {
class CommandQueueData
{
public:
    CALcontext  handle_;
    Device      device_;

public:
    CommandQueueData() : handle_(0) {}
    ~CommandQueueData()
    {
        if( handle_ ) {
            CALcontext_helper::release(handle_);
            calCtxDestroy(handle_);
        }
    }    
};
}

class CommandQueue : public detail::shared_data<detail::CommandQueueData>
{
public:
    CommandQueue() : detail::shared_data<detail::CommandQueueData>()
    {
    }

    CommandQueue( const CommandQueue& rhs ) : detail::shared_data<detail::CommandQueueData>(rhs)
    {
    }

    CommandQueue( Context& context, const Device& device ) : detail::shared_data<detail::CommandQueueData>(1)
    {
        CALresult   r;
        CALcontext  ctx;

        r = calCtxCreate(&ctx,device());
        if( r!=CAL_RESULT_OK ) throw Error(r);

        data().handle_ = ctx;
        data().device_ = device;
    }

    void enqueueNDRangeKernel( Kernel& kernel, const NDRange& global, const NDRange& local, Event* event = NULL)
    {
        CALevent        _event;
        CALresult       r;
        CALprogramGrid  grid;

        assert( local.width>0 && local.height>0 && local.depth>0 );

        kernel.prepareKernel(data().handle_,data().device_());

        grid.func            = kernel.getFunc(data().handle_);
        grid.gridBlock       = local;
        grid.gridSize.width  = (global.width+local.width-1)/local.width;
        grid.gridSize.height = (global.height+local.height-1)/local.height;
        grid.gridSize.depth  = (global.depth+local.depth-1)/local.depth;        
        grid.flags           = 0;

        r = calCtxRunProgramGrid(&_event,data().handle_,&grid);
        if( r!=CAL_RESULT_OK ) throw Error(r);

        if( event ) *event = Event(_event);
    }

    void enqueueNDRangeKernel( Kernel& kernel, const NDRange& global, Event* event = NULL)
    {
        CALevent        _event;
        CALresult       r;
        CALfunc         func;
        CALdomain       rect;

        kernel.prepareKernel(data().handle_,data().device_());

        func        = kernel.getFunc(data().handle_);
        rect.x      = 0;
        rect.y      = 0;
        rect.width  = global.width;
        rect.height = global.height;

        r = calCtxRunProgram(&_event,data().handle_,func,&rect);
        if( r!=CAL_RESULT_OK ) throw Error(r);

        if( event ) *event = Event(_event);
    }


    void enqueueCopyBuffer( const Memory& src, Memory& dst, Event* event )
    {
        CALevent    _event;
        CALresult   r;

        const_cast<Memory&>(src).attach(data().handle_,data().device_());
        dst.attach(data().handle_,data().device_());

        r = calMemCopy(&_event,data().handle_,src.getMem(data().handle_),dst.getMem(data().handle_),0);
        if( r!=CAL_RESULT_OK ) throw Error(r);

        if( event ) *event=Event(_event);
    }

    void* mapMemObject( Memory& mem, CALuint& pitch )
    {
        return mem.map2(pitch,data().device_());
    }

    void unmapMemObject( Memory& mem )
    {
        mem.unmap2(data().device_());
    }

    void waitForEvent( const Event& event )
    {
        CALresult   r;

        if( !event() ) return;

#ifdef __CAL_USE_BLOCKING_WAIT
        if( detail::cal_extension_table<0>::data.calCtxWaitForEvents ) {
            r = detail::cal_extension_table<0>::data.calCtxWaitForEvents(data().handle_,(CALevent*)&event(),1,0);
            if( r!=CAL_RESULT_OK ) throw Error(r);
            return;
        }
#endif

        while( 1 ) {
            r = calCtxIsEventDone(data().handle_,event());
            if( r!=CAL_RESULT_PENDING ) break;
        }

        if( r!=CAL_RESULT_OK ) throw Error(r);
    }

    void waitForEvents( const std::vector<Event>& events )
    {
#ifdef __CAL_USE_BLOCKING_WAIT
        if( detail::cal_extension_table<0>::data.calCtxWaitForEvents ) {
            CALresult r = detail::cal_extension_table<0>::data.calCtxWaitForEvents(data().handle_,(CALevent*)&events[0],events.size(),0);
            if( r!=CAL_RESULT_OK ) throw Error(r);
            return;
        }
#endif

        for(unsigned i=0;i<events.size();i++) {
            CALresult   r;
            r = calCtxIsEventDone(data().handle_,events[i]());
            if( r!=CAL_RESULT_OK && r!=CAL_RESULT_PENDING ) throw Error(r);
            if( r==CAL_RESULT_PENDING ) i--;
        }
    }

    bool isEventDone( const Event& event )
    {
        CALresult   r;

        if( !event() ) return true;

        r = calCtxIsEventDone(data().handle_,event());
        if( r!=CAL_RESULT_PENDING && r!=CAL_RESULT_OK ) throw Error(r);

        return r!=CAL_RESULT_PENDING;
    }

    void flush()
    {
        CALresult   r;
        r = calCtxFlush(data().handle_);
        if( r!=CAL_RESULT_OK ) throw Error(r);
    }

    CALcontext operator()() const { return data().handle_; }
};


class KernelFunctor
{
private:
    Kernel          kernel_;
    CommandQueue    queue_;
    NDRange         global_;
    NDRange         local_;
    bool            local_valid;

protected:
    void run( Event& event )
    {
        if( local_valid ) queue_.enqueueNDRangeKernel(kernel_,  global_, local_, &event);
        else queue_.enqueueNDRangeKernel(kernel_,  global_, &event);
    }

public:
    KernelFunctor(
        const Kernel& kernel,
        const CommandQueue& queue,
        const NDRange& global,
        const NDRange& local) :
            kernel_(kernel),
            queue_(queue),
            global_((NDRange)global),
            local_((NDRange)local),
            local_valid(true)
    {
    }

    KernelFunctor(
        const Kernel& kernel,
        const CommandQueue& queue,
        const NDRange& global ) :
            kernel_(kernel),
            queue_(queue),
            global_((NDRange)global),
            local_(),
            local_valid(false)
    {
    }

    KernelFunctor(const KernelFunctor& rhs) : kernel_(rhs.kernel_), queue_(rhs.queue_), global_(rhs.global_), local_(rhs.local_) {}

    KernelFunctor& operator=(const KernelFunctor& rhs)
    {
        kernel_ = rhs.kernel_;
        queue_  = rhs.queue_;
        global_ = rhs.global_;
        local_  = rhs.local_;
        return *this;
    }

    Event operator()()
    {
        Event event;

        run(event);

        return event;
    }

    template<typename A1>
    Event operator()( const A1& a1 )
    {
        Event event;

        kernel_.setArg(0,a1);

        run(event);        

        return event;
    }

    template<class A1, class A2>
    Event operator()( const A1& a1, const A2& a2 )
    {
        Event event;

        kernel_.setArg(0,a1);
        kernel_.setArg(1,a2);

        run(event);        

        return event;
    }

    template<class A1, class A2, class A3>
    Event operator()( const A1& a1, const A2& a2, const A3& a3 )
    {
        Event event;

        kernel_.setArg(0,a1);
        kernel_.setArg(1,a2);
        kernel_.setArg(2,a3);

        run(event);

        return event;
    }

    template<class A1, class A2, class A3, class A4>
    Event operator()( const A1& a1, const A2& a2, const A3& a3, const A4& a4 )
    {
        Event event;

        kernel_.setArg(0,a1);
        kernel_.setArg(1,a2);
        kernel_.setArg(2,a3);
        kernel_.setArg(3,a4);

        run(event);        

        return event;
    }

    template<class A1, class A2, class A3, class A4, class A5>
    Event operator()( const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5)
    {
        Event event;

        kernel_.setArg(0,a1);
        kernel_.setArg(1,a2);
        kernel_.setArg(2,a3);
        kernel_.setArg(3,a4);
        kernel_.setArg(4,a5);

        run(event);        

        return event;
    }

    template<class A1, class A2, class A3, class A4, class A5, class A6>
    Event operator()( const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6 )
    {
        Event event;

        kernel_.setArg(0,a1);
        kernel_.setArg(1,a2);
        kernel_.setArg(2,a3);
        kernel_.setArg(3,a4);
        kernel_.setArg(4,a5);
        kernel_.setArg(5,a6);

        run(event);        

        return event;
    }

    template<class A1, class A2, class A3, class A4,
             class A5, class A6, class A7>
    Event operator()( const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6,
                             const A7& a7)
    {
        Event event;

        kernel_.setArg(0,a1);
        kernel_.setArg(1,a2);
        kernel_.setArg(2,a3);
        kernel_.setArg(3,a4);
        kernel_.setArg(4,a5);
        kernel_.setArg(5,a6);
        kernel_.setArg(6,a7);

        run(event);        

        return event;
    }

    template<class A1, class A2, class A3, class A4, class A5,
             class A6, class A7, class A8>
    Event operator()( const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6,
                             const A7& a7, const A8& a8 )
    {
        Event event;

        kernel_.setArg(0,a1);
        kernel_.setArg(1,a2);
        kernel_.setArg(2,a3);
        kernel_.setArg(3,a4);
        kernel_.setArg(4,a5);
        kernel_.setArg(5,a6);
        kernel_.setArg(6,a7);
        kernel_.setArg(7,a8);

        run(event);        

        return event;
    }

    template<class A1, class A2, class A3, class A4, class A5,
             class A6, class A7, class A8, class A9>
    Event operator()( const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6,
                             const A7& a7, const A8& a8, const A9& a9 )
    {
        Event event;

        kernel_.setArg(0,a1);
        kernel_.setArg(1,a2);
        kernel_.setArg(2,a3);
        kernel_.setArg(3,a4);
        kernel_.setArg(4,a5);
        kernel_.setArg(5,a6);
        kernel_.setArg(6,a7);
        kernel_.setArg(7,a8);
        kernel_.setArg(8,a9);

        run(event);        

        return event;
    }

    template<class A1, class A2, class A3, class A4, class A5,
             class A6, class A7, class A8, class A9, class A10>
    Event operator()( const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6,
                             const A7& a7, const A8& a8, const A9& a9, const A10& a10 )
    {
        Event event;

        kernel_.setArg(0,a1);
        kernel_.setArg(1,a2);
        kernel_.setArg(2,a3);
        kernel_.setArg(3,a4);
        kernel_.setArg(4,a5);
        kernel_.setArg(5,a6);
        kernel_.setArg(6,a7);
        kernel_.setArg(7,a8);
        kernel_.setArg(8,a9);
        kernel_.setArg(9,a10);

        run(event);        

        return event;
    }

    template<class A1, class A2, class A3, class A4, class A5,
             class A6, class A7, class A8, class A9, class A10,
             class A11>
    Event operator()( const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6,
                             const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11 )
    {
        Event event;

        kernel_.setArg(0,a1);
        kernel_.setArg(1,a2);
        kernel_.setArg(2,a3);
        kernel_.setArg(3,a4);
        kernel_.setArg(4,a5);
        kernel_.setArg(5,a6);
        kernel_.setArg(6,a7);
        kernel_.setArg(7,a8);
        kernel_.setArg(8,a9);
        kernel_.setArg(9,a10);
        kernel_.setArg(10,a11);

        run(event);        

        return event;
    }

    template<class A1, class A2, class A3, class A4, class A5,
             class A6, class A7, class A8, class A9, class A10,
             class A11, class A12>
    Event operator()( const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6,
                             const A7& a7, const A8& a8, const A9& a9, const A10& a10,const A11& a11, const A12& a12 )
    {
        Event event;

        kernel_.setArg(0,a1);
        kernel_.setArg(1,a2);
        kernel_.setArg(2,a3);
        kernel_.setArg(3,a4);
        kernel_.setArg(4,a5);
        kernel_.setArg(5,a6);
        kernel_.setArg(6,a7);
        kernel_.setArg(7,a8);
        kernel_.setArg(8,a9);
        kernel_.setArg(9,a10);
        kernel_.setArg(10,a11);
        kernel_.setArg(11,a12);

        run(event);        

        return event;
    }

    template<class A1, class A2, class A3, class A4, class A5,
             class A6, class A7, class A8, class A9, class A10,
             class A11, class A12, class A13>
    Event operator()( const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6,
                             const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12,
                             const A13& a13)
    {
        Event event;

        kernel_.setArg(0,a1);
        kernel_.setArg(1,a2);
        kernel_.setArg(2,a3);
        kernel_.setArg(3,a4);
        kernel_.setArg(4,a5);
        kernel_.setArg(5,a6);
        kernel_.setArg(6,a7);
        kernel_.setArg(7,a8);
        kernel_.setArg(8,a9);
        kernel_.setArg(9,a10);
        kernel_.setArg(10,a11);
        kernel_.setArg(11,a12);
        kernel_.setArg(12,a13);

        run(event);        

        return event;
    }

    template<class A1, class A2, class A3, class A4, class A5,
             class A6, class A7, class A8, class A9, class A10,
             class A11, class A12, class A13, class A14>
    Event operator()( const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6,
                             const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12,
                             const A13& a13, const A14& a14 )
    {
        Event event;

        kernel_.setArg(0,a1);
        kernel_.setArg(1,a2);
        kernel_.setArg(2,a3);
        kernel_.setArg(3,a4);
        kernel_.setArg(4,a5);
        kernel_.setArg(5,a6);
        kernel_.setArg(6,a7);
        kernel_.setArg(7,a8);
        kernel_.setArg(8,a9);
        kernel_.setArg(9,a10);
        kernel_.setArg(10,a11);
        kernel_.setArg(11,a12);
        kernel_.setArg(12,a13);
        kernel_.setArg(13,a14);

        run(event);        

        return event;
    }

    template<class A1, class A2, class A3, class A4, class A5,
             class A6, class A7, class A8, class A9, class A10,
             class A11, class A12, class A13, class A14, class A15>
    Event operator()( const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6,
                             const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12,
                             const A13& a13, const A14& a14, const A15& a15 )
    {
        Event event;

        kernel_.setArg(0,a1);
        kernel_.setArg(1,a2);
        kernel_.setArg(2,a3);
        kernel_.setArg(3,a4);
        kernel_.setArg(4,a5);
        kernel_.setArg(5,a6);
        kernel_.setArg(6,a7);
        kernel_.setArg(7,a8);
        kernel_.setArg(8,a9);
        kernel_.setArg(9,a10);
        kernel_.setArg(10,a11);
        kernel_.setArg(11,a12);
        kernel_.setArg(12,a13);
        kernel_.setArg(13,a14);
        kernel_.setArg(14,a15);

        run(event);        

        return event;
    }
};

inline KernelFunctor Kernel::bind( const CommandQueue& queue, const NDRange& global, const NDRange& local )
{
    return KernelFunctor(*this,queue,global,local);
}

inline KernelFunctor Kernel::bind( const CommandQueue& queue, const NDRange& global )
{
    return KernelFunctor(*this,queue,global);
}

template<int Name>
typename detail::param_traits<detail::CAL_TYPE_CALMODULE,Name>::param_type Kernel::getInfo( const CommandQueue& queue )
{
    typename detail::param_traits<detail::CAL_TYPE_CALMODULE,Name>::param_type value;

    detail::KernelData::state_data& state(data().loadState(queue(),queue.data().device_()));
    CALfuncInfo             info;
    CALresult               r;

    r = calModuleGetFuncInfo(&info,state.ctx,state.module,state.func);
    if( r!=CAL_RESULT_OK ) throw Error(r);

    detail::param_traits<detail::CAL_TYPE_CALMODULE,Name>::getInfo(value,info);

    return value;
}

inline void Init()
{
    CALresult   r;

    r = calInit();
    if( r!=CAL_RESULT_OK ) throw Error(r);

    detail::cal_extension_table<0>::data.init();
}

inline void Shutdown()
{
    CALresult   r;

    r = calShutdown();
    if( r!=CAL_RESULT_OK ) throw Error(r);
}

} // namespace cal

#endif
