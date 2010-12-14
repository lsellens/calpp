/*
 * C++ to IL compiler/generator register swizzle helper functions
 * 
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

#ifndef __CAL_IL_SWIZZLE_H
#define __CAL_IL_SWIZZLE_H

#include <boost/format.hpp>
#include <boost/static_assert.hpp>

namespace cal {
namespace il {
namespace detail {

inline std::string::size_type swizzle_find_dot( const std::string& r )
{
    std::string::size_type  p,k;
    static std::string      valid_chars("xyzw_01");
    
    if( r.length()<=0 ) return std::string::npos;
    
    p = r.length();
    while( p>0 ) {
        p--;

        if( r[p]=='.' ) return p;

        k = valid_chars.find(r[p]);
        if( k==std::string::npos ) return std::string::npos;
    }
    
    return std::string::npos;
}

inline int swizzle_letter_position( char v )
{
    if( v=='x' ) return 0;
    if( v=='y' ) return 1;
    if( v=='z' ) return 2;
    return 3;
}

inline bool check_output_register_swizzle( const std::string& dst )
{
    std::string::size_type  i,p;
    int                     prev,v;

    p = swizzle_find_dot(dst);
    if( p==std::string::npos ) return true;

    prev=-1;
    for(i=p+1;i<dst.length();i++) {
        char c = dst[i];
        if( c!='_' && c!='x' && c!='y' && c!='z' && c!='w'  ) return false;
        v = swizzle_letter_position(c); if( v<=prev ) return false;
        prev = v;
    }

    return true;
}

inline std::string output_swizzle_mask( const std::string& r )
{
    std::string             mask="____";
    std::string::size_type  p,i;

    if( !check_output_register_swizzle(r) ) throw std::runtime_error("invalid register swizzle mask");

    p = swizzle_find_dot(r);
    if( p==std::string::npos ) return "xyzw";

    for(i=p+1;i<r.length();i++) {
        char c = r[i];

        if( c=='_' ) continue;
        mask[swizzle_letter_position(c)] = c;
    }

    return mask;
}

inline std::string mask_output( const std::string& r )
{
    std::string::size_type  p;

    p = swizzle_find_dot(r);
    if( p==std::string::npos ) return r+".xyzw";

    return r.substr(0,p+1) + output_swizzle_mask(r);
}

inline std::string match_input_to_output( const std::string& dst, const std::string& src )
{
    std::string::size_type  i,p1,p2,s1,s2;
    std::string             res,mask;
    
    if( !check_output_register_swizzle(dst) ) throw std::runtime_error("invalid output register swizzle");

    p1 = swizzle_find_dot(dst);
    if( p1==std::string::npos ) return src;
    s1 = dst.length()-p1-1;

    p2 = swizzle_find_dot(src);
    if( p2==std::string::npos ) {
        assert( s1==4 );
        return src;
    }
    s2 = src.length()-p2-1;

    assert( s1==s2 );

    mask = "0000";

    for(i=0;i<s1;i++) {
        char c = dst[p1+1+i];
        if( c=='_' ) continue;

        mask[swizzle_letter_position(c)] = src[p2+1+i];
    }

    return src.substr(0,p2+1)+mask;
}

inline std::string make_swizzle( const std::string& r, int a, int b, int c, int d )
{
    std::string::size_type  p;
    std::string             res;    

    assert( a>0 && b>=0 && c>=0 && d>=0 );
    assert( a<=4 && b<=4 && c<=4 && d<=4 );

    p = swizzle_find_dot(r);
    if( p!=std::string::npos ) {
        std::string res = r.substr(0,p+1);
        int         size = r.length()-p-1;
        
        assert( p>0 && size>=1 );

        if( a>size ) throw std::runtime_error("invalid swizzle");        
        res += r[p + a];

        if( b==0 ) return res;
        if( b>size ) throw std::runtime_error("invalid swizzle");
        res += r[p + b];

        if( c==0 ) return res;
        if( c>size ) throw std::runtime_error("invalid swizzle");
        res += r[p + c];
        
        if( d==0 ) return res;
        if( d>size ) throw std::runtime_error("invalid swizzle");
        res += r[p + d];

        return res;
    }
        
    static const char* table[5]={"","x","y","z","w"};

    if( a==1 && b==2 && c==3 && d==4 ) return r;

    res = r + ".";

    res += table[a];
    res += table[b];
    res += table[c];
    res += table[d];

    return res;
}

inline std::string make_swizzle( const std::string& r, int size )
{
    assert( size>0 && size<5 );
    
    switch( size ) {
    case 1 : return make_swizzle(r,1,0,0,0);
    case 2 : return make_swizzle(r,1,2,0,0);
    case 3 : return make_swizzle(r,1,2,3,0);    
    }

    return make_swizzle(r,1,2,3,4);
}

} // detail
} // il
} // cal

#endif
