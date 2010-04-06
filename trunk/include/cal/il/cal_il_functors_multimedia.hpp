/*
 * C++ to IL compiler/generator multimedia functors
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

#ifndef __CAL_IL_FUNCTORS_MULTIMEDIA_H
#define __CAL_IL_FUNCTORS_MULTIMEDIA_H

#include <boost/format.hpp>
#include <boost/static_assert.hpp>
#include <cal/il/cal_il_base_types.hpp>

namespace cal {
namespace il {
namespace detail {

//
// bitalign
//

template<class S1, class S2, class S3>
struct cal_ternary_bitalign {
    typedef S1 value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, const std::string& s2, int t0 )
    {
        typedef boost::is_same<S1,S2> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );
        BOOST_STATIC_ASSERT( S1::type_size==S3::type_size ); 
        BOOST_STATIC_ASSERT( S1::component_count==S3::component_count );

        std::string    res;

        for(int i=1;i<=S1::component_count;i++) {
            res += (boost::format("bitalign %1%,%2%,%3%,%4%\n") % mask_output(make_swizzle(r,i,0,0,0)) 
                                                                % make_swizzle(s0,i,0,0,0) 
                                                                % make_swizzle(s1,i,0,0,0) 
                                                                % make_swizzle(s2,i,0,0,0) ).str();
        }

        return res;
    }
};

//
// bytealign
//

template<class S1, class S2, class S3>
struct cal_ternary_bytealign {
    typedef S1 value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, const std::string& s2, int t0 )
    {
        typedef boost::is_same<S1,S2> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );
        BOOST_STATIC_ASSERT( S1::type_size==S3::type_size ); 
        BOOST_STATIC_ASSERT( S1::component_count==S3::component_count );

        std::string    res;

        for(int i=1;i<=S1::component_count;i++) {
            res += (boost::format("bytealign %1%,%2%,%3%,%4%\n") % mask_output(make_swizzle(r,i,0,0,0)) 
                                                                 % make_swizzle(s0,i,0,0,0) 
                                                                 % make_swizzle(s1,i,0,0,0) 
                                                                 % make_swizzle(s2,i,0,0,0) ).str();
        }

        return res;
    }
};


} // detail
} // cal
} // il

#endif
