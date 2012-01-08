/*
 * C++ ATI IL program cache
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

#ifndef __CAL_PROGRAM_CACHE_HPP__
#define __CAL_PROGRAM_CACHE_HPP__

#include <cal/cal.hpp>
#include <boost/functional/hash.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp> 
#include <boost/thread.hpp>

namespace cal {
    
class ProgramCache
{
public:
    struct options_t
    {
        std::string directory;
        bool        use_source_file;
        int         hash_length;
    };
    
public:
    options_t opt;
    
protected:    
    boost::filesystem::path get_source_name( const std::string& hash, int idx )
    {
        return boost::filesystem::path(opt.directory) / boost::filesystem::path((boost::format("%s-%i.src") % hash % idx).str());
    }

    boost::filesystem::path get_image_name( const std::string& hash, int idx, const std::vector<Device>& devices )
    {
        std::string name;
        
        name = (boost::format("%s-%i") % hash % idx).str();
        for(unsigned i=0;i<devices.size();i++) {
            name += (boost::format("-%i") % devices[i].getInfo<CAL_DEVICE_TARGET>()).str();
        }
        
        return boost::filesystem::path(opt.directory) / boost::filesystem::path(name+".bin");
    }


    template<class S>
    void load_file( const boost::filesystem::path& name, S& buffer )
    {
        boost::filesystem::ifstream input(name, boost::filesystem::ifstream::in | boost::filesystem::ifstream::binary);
        std::size_t                 size;
        
        input.seekg (0, boost::filesystem::ifstream::end);
        size = input.tellg();
        input.seekg (0, boost::filesystem::ifstream::beg);
                
        buffer.resize(size);
        input.read( (char*)&buffer[0], size );
    }
    
    template<class S>
    void store_file( const boost::filesystem::path& name, S& buffer )
    {
        boost::filesystem::ofstream output(name, boost::filesystem::ofstream::out | boost::filesystem::ofstream::binary | boost::filesystem::ofstream::trunc);
        
        output.write( (char*)&buffer[0], buffer.size() );
    }
        
    std::string c2h( std::size_t v )
    {
        static const char number[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
        std::string  hex(sizeof(std::size_t)/4,'0');
        
        for(int i=0;i<sizeof(std::size_t);i+=4) {
            hex[i/4] = number[ (v>>(sizeof(std::size_t)-4-i))&0xF ];
        }
        
        return hex;
    }
    
    std::string create_hash( const std::string& text, int length )
    {
        std::string::const_iterator itext,iend;
        std::string                 hash;
        int                         b,bs;

        b     = (length + sizeof(std::size_t) - 1)/sizeof(std::size_t);
        bs    = text.length()/b;        
        itext = text.begin();        

        for(;b>0;b--) {
            if( b==1 ) iend = text.end();
            else iend = itext + bs;
            hash += c2h( boost::hash_range(itext, iend) );
            itext += bs;
        }

        return hash;
    }
    
    bool binary_exists( const std::vector<Device>& devices, const std::string& source, const std::string& hash, int& idx, bool lock=false )
    {
        boost::filesystem::path name;
        std::string             _source;
        bool                    r;
            
        if( lock ) lockRead();
        
        try {
            idx=0;
        
            if( opt.use_source_file ) {
                for(int i=0;;i++) {
                    idx = i;
                    name = get_source_name(hash,idx);
                    if( boost::filesystem::exists(name) ) {
                        load_file( name, _source );
                        if( _source==source ) break;                        
                    } else break;
                }
            }
        
            name = get_image_name(hash,idx,devices);
            r = boost::filesystem::exists(name);
        }
        catch(...) {
            if( lock ) unlockRead();
            throw;
        }
        
        if( lock ) unlockRead();
        
        return r;
    }
    
    void load_binary( std::vector<detail::byte_type>& image, const std::vector<Device>& devices, const std::string& source, const std::string& hash, int idx )
    {
        boost::filesystem::path name;
        
        name = get_image_name(hash,idx,devices);
        load_file(name,image);
    }
    
    void store_binary( std::vector<detail::byte_type>& image, const std::vector<Device>& devices, const std::string& source, const std::string& hash, int idx )
    {
        boost::filesystem::path name;

        if( opt.use_source_file ) {
            name = get_source_name(hash,idx);
            store_file(name,source);
        }
        
        name = get_image_name(hash,idx,devices);
        store_file(name,image);        
    }
    
    bool load_program( ::cal::Program& program, const Context& context, const std::vector<Device>& devices, const std::string& source, const std::string& hash, int& idx, bool lock )
    {
        std::vector<detail::byte_type>  image;
        
        if( binary_exists(devices, source, hash, idx, lock) ) {
            load_binary(image, devices, source, hash, idx);                
                            
            program = ::cal::Program(context, &image[0], image.size());
            program.build(devices);
            
            return true;
        }        
        
        return false;
    }
    
protected:
    virtual void lockRead() {}    
    virtual void lockWrite() {}
    virtual void unlockRead() {}
    virtual void unlockWrite() {}
        
public:
    ProgramCache() 
    {
        opt.directory       = "gpu_cache";
        opt.use_source_file = true;
        opt.hash_length     = 256;
    }    
    virtual ~ProgramCache() {}
    
    ::cal::Program createProgram( const Context& context, const std::vector<Device>& devices, const std::string& source )
    {        
        ::cal::Program                  program;
        std::string                     hash;        
        int                             idx;
        
        hash = create_hash(source,opt.hash_length);

        if( load_program(program, context, devices, source, hash, idx, true) ) 
            return program;
                
        lockWrite();
        try {
            if( load_program(program, context, devices, source, hash, idx, false) ) {
                unlockWrite();
                return program;
            }
        
            std::vector<detail::byte_type>  image;
        
            program = ::cal::Program(context, source.c_str(), source.length());
            program.build(devices);
        
            image = program.getInfo<CAL_PROGRAM_BINARY>();
            store_binary(image, devices, source, hash, idx);                        
        } catch(...) {
            unlockWrite();
            throw;
        }
        unlockWrite();
        
        return program;
    }
    
    ::cal::Program createProgram( const Context& context, const Device& device, const std::string& source )
    {
        std::vector<Device> devices;
        devices.push_back(device);
        return createProgram(context, devices, source);
    }
};

class ThreadSafeProgramCache : public ProgramCache
{
protected:
    boost::shared_mutex access_mutex;
    
protected:    
    virtual void lockRead()
    {
        access_mutex.lock_shared();
    }
    
    virtual void lockWrite() 
    {
        access_mutex.lock();
    }
    virtual void unlockRead() 
    {
        access_mutex.unlock_shared();
    }
    virtual void unlockWrite()
    {
        access_mutex.unlock();
    }

public:
    ThreadSafeProgramCache() {}
    virtual ~ThreadSafeProgramCache() {}
};

} // cal

#endif
