/*
 * C++ to IL compiler/generator il code flow control
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

#ifndef _CAL_IL_FLOWCONTROL_H
#define _CAL_IL_FLOWCONTROL_H

#include <cal/il/cal_il_flowcontrol_cmp.hpp>

namespace cal {
namespace il {

namespace detail {

template<int N>
struct if_code
{
    static const char* nz;
    static const char* z;

    static const char* logicalnz;
    static const char* logicalz;

    static const char* relop_lt;
    static const char* relop_le;
    static const char* relop_ne;
    static const char* relop_eq;
    static const char* relop_ge;
    static const char* relop_gt;    
};

template<int N> const char* if_code<N>::nz="ifnz %s\n";
template<int N> const char* if_code<N>::z="ifc_relop(eq) %s,l0.x\n";
    
template<int N> const char* if_code<N>::logicalnz="if_logicalnz %s\n";
template<int N> const char* if_code<N>::logicalz="if_logicalz %s\n";

template<int N> const char* if_code<N>::relop_lt="ifc_relop(lt) %s,%s\n";
template<int N> const char* if_code<N>::relop_le="ifc_relop(le) %s,%s\n";
template<int N> const char* if_code<N>::relop_ne="ifc_relop(ne) %s,%s\n";
template<int N> const char* if_code<N>::relop_eq="ifc_relop(eq) %s,%s\n";
template<int N> const char* if_code<N>::relop_ge="ifc_relop(ge) %s,%s\n";
template<int N> const char* if_code<N>::relop_gt="ifc_relop(gt) %s,%s\n";

template<int N> 
struct break_code
{
    static const char* nz;
    static const char* z;
    
    static const char* logicalnz;
    static const char* logicalz;

    static const char* relop_lt;
    static const char* relop_le;
    static const char* relop_ne;
    static const char* relop_eq;
    static const char* relop_ge;
    static const char* relop_gt;
};

template<int N> const char* break_code<N>::nz="breakc_relop(ne) %s,l0.x\n";
template<int N> const char* break_code<N>::z="breakc_relop(eq) %s,l0.x\n";
    
template<int N> const char* break_code<N>::logicalnz="break_logicalnz %s\n";
template<int N> const char* break_code<N>::logicalz="break_logicalz %s\n";

template<int N> const char* break_code<N>::relop_lt="breakc_relop(lt) %s,%s\n";
template<int N> const char* break_code<N>::relop_le="breakc_relop(le) %s,%s\n";
template<int N> const char* break_code<N>::relop_ne="breakc_relop(ne) %s,%s\n";
template<int N> const char* break_code<N>::relop_eq="breakc_relop(eq) %s,%s\n";
template<int N> const char* break_code<N>::relop_ge="breakc_relop(ge) %s,%s\n";
template<int N> const char* break_code<N>::relop_gt="breakc_relop(gt) %s,%s\n";


template<int N>
struct continue_code
{
    static const char* nz;
    static const char* z;
    
    static const char* logicalnz;
    static const char* logicalz;

    static const char* relop_lt;
    static const char* relop_le;
    static const char* relop_ne;
    static const char* relop_eq;
    static const char* relop_ge;
    static const char* relop_gt;
};

template<int N> const char* continue_code<N>::nz="continuec_relop(ne) %s,l0.x\n";
template<int N> const char* continue_code<N>::z="continuec_relop(eq) %s,l0.x\n";
    
template<int N> const char* continue_code<N>::logicalnz="continue_logicalnz %s\n";
template<int N> const char* continue_code<N>::logicalz="continue_logicalz %s\n";

template<int N> const char* continue_code<N>::relop_lt="continuec_relop(lt) %s,%s\n";
template<int N> const char* continue_code<N>::relop_le="continuec_relop(le) %s,%s\n";
template<int N> const char* continue_code<N>::relop_ne="continuec_relop(ne) %s,%s\n";
template<int N> const char* continue_code<N>::relop_eq="continuec_relop(eq) %s,%s\n";
template<int N> const char* continue_code<N>::relop_ge="continuec_relop(ge) %s,%s\n";
template<int N> const char* continue_code<N>::relop_gt="continuec_relop(gt) %s,%s\n";

template<class E>
void emit_if( const detail::expression<E>& e )
{
    emit_cmp( if_code<0>(), e() );
}

inline void emit_else()
{
    Source::code << "else\n";
}

inline void emit_endif()
{
    Source::code << "endif\n";
}

template<class E>
void emit_break( const detail::expression<E>& e )
{
    emit_cmp( break_code<0>(), e() );
}

inline void emit_break()
{
    Source::code << "break\n";
}

template<class E>
void emit_continue( const detail::expression<E>& e )
{
    emit_cmp( continue_code<0>(), e() );
}

inline void emit_continue()
{
    Source::code << "continue\n";
}

template<class E>
void emit_while( const detail::expression<E>& e )
{
    Source::code << "whileloop\n";
    emit_cmp( break_code<0>(), e(), true );
}

inline void emit_whileloop()
{
    Source::code << "whileloop\n";
}

inline void emit_endloop()
{
    Source::code << "endloop\n";
}

} // detail

#define il_if(V) ::cal::il::detail::emit_if(V);
#define il_else  ::cal::il::detail::emit_else();
#define il_endif ::cal::il::detail::emit_endif();

#define il_break ::cal::il::detail::emit_break()
#define il_breakc(V) ::cal::il::detail::emit_break(V)

#define il_continue ::cal::il::detail::emit_continue()
#define il_continuec(V) ::cal::il::detail::emit_continue(V)

#define il_whileloop ::cal::il::detail::emit_whileloop();
#define il_while(V) ::cal::il::detail::emit_while(V);
#define il_endloop ::cal::il::detail::emit_endloop();

} // il
} // cal

#endif
