/*
 * C++ to IL compiler/generator double4 class
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

#ifndef __CAL_IL_DOUBLE4_H
#define __CAL_IL_DOUBLE4_H

#include <cal/il/cal_il.hpp>

namespace cal {
namespace il {

class double4
{
protected:
    double2 v0,v1;

public:
    double4() {}

    explicit double4( double _v ) : v0(_v), v1(_v) {}
    explicit double4( double _v0, double _v1, double _v2, double _v3 ) : v0(_v0,_v1), v1(_v2,_v3) {}

    template<class E1,class E2>
    explicit double4( const detail::expression<E1>& e1, const detail::expression<E2>& e2 ) : v0(e1()), v1(e2()) {}

    template<class E1,class E2,class E3,class E4>
    explicit double4( const detail::expression<E1>& e1, const detail::expression<E2>& e2, const detail::expression<E3>& e3, const detail::expression<E4>& e4 ) 
    : v0(e1(),e2()), v1(e3(),e4()) 
    {
    }

    ~double4() {}

    double2& xy() { return v0; }
    double2& zw() { return v1; }
    const double2& xy() const { return v0; }
    const double2& zw() const { return v1; }

    detail::swizzle<double2,1,0,0,0> x() const { return v0.x(); }
    detail::swizzle<double2,2,0,0,0> y() const { return v0.y(); }
    detail::swizzle<double2,1,0,0,0> z() const { return v1.x(); }
    detail::swizzle<double2,2,0,0,0> w() const { return v1.y(); }
};

} // il
} // cal

#endif
