/*
 * C++ to IL compiler/generator operation functors
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

#ifndef __CAL_IL_FUNCTORS_H
#define __CAL_IL_FUNCTORS_H

#include <boost/format.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>
#include <cal/il/cal_il_functors_bitop.hpp>
#include <cal/il/cal_il_functors_cast.hpp>
#include <cal/il/cal_il_functors_relop.hpp>
#include <cal/il/cal_il_functors_mathop.hpp>
#include <cal/il/cal_il_functors_multimedia.hpp>

namespace cal {
namespace il {
namespace detail {

//
// cmov_logical
//

template<class S1, class S2, class S3>
struct cal_ternary_cmov_logical {
    typedef S2 value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, const std::string& s2, int t0 )
    {
        typedef boost::is_same<S2,S3> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );
        BOOST_STATIC_ASSERT( S1::type_size==1 || S1::type_size==S2::type_size );

        return (boost::format("cmov_logical %1%,%2%,%3%,%4%\n") % r % s0 % s1 % s2).str();
    }
};

//
// cmov_logical for select
//

template<class S1, class S2, class S3>
struct cal_ternary_select {
    typedef S2 value_type;
    static const int temp_reg_count=0;

    static std::string emitCode( const std::string& r, const std::string& s0, const std::string& s1, const std::string& s2, int t0 )
    {
        typedef boost::is_same<S2,S3> assert_value;
        BOOST_STATIC_ASSERT( assert_value::value );
        BOOST_STATIC_ASSERT( S1::component_size==1 );
        BOOST_STATIC_ASSERT( S1::component_count==1 || S1::component_count==S2::component_count );

        if( S1::component_count==2 && S2::component_size==2 ) {
            return (boost::format("cmov_logical %1%,%2%,%3%,%4%\n") % r % make_swizzle(s0,1,1,2,2) % s1 % s2).str();
        }

        return (boost::format("cmov_logical %1%,%2%,%3%,%4%\n") % mask_output(r) % s0 % s1 % s2).str();
    }
};

} // detail
} // cal
} // il

#endif
