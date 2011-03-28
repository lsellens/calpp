/*
 * C++ to IL compiler/generator il function support
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

#ifndef _CAL_IL_FUNC_H
#define _CAL_IL_FUNC_H

#include <boost/type_traits.hpp>
#include <boost/bind.hpp>

namespace cal {
namespace il {
 

namespace detail {

template<class T>
class func_in_wrapper
{
public:
    const variable<T>& var;    
public:    
    func_in_wrapper( const variable<T>& _var ) : var(_var) {}
    func_in_wrapper( const func_in_wrapper<T>& f ) : var(f.var) {}
    
    std::string resultCode() const { return var.resultCode(); }
};

template<class T>
class func_out_wrapper
{
public:
    variable<T>& var;    
public:    
    func_out_wrapper( variable<T>& _var ) : var(_var) {}
    func_out_wrapper( const func_out_wrapper<T>& f ) : var(f.var) {}
    
    std::string resultCode() const { return var.resultCode(); }
};

template<class T>
class func_inout_wrapper
{
public:
    variable<T>& var;    
public:        
    func_inout_wrapper( variable<T>& _var ) : var(_var) {}    
    func_inout_wrapper( const func_inout_wrapper<T>& f ) : var(f.var) {}
    
    std::string resultCode() const { return var.resultCode(); }
};

template<typename T>
void func_change_variable( variable<T>& v, int id )
{
    v.setNewID(id);
}
    
template<typename T>
void func_add_arg( Source::func_info& func, variable<T>& v )
{
    int id = Source::code.getNewID(1);
    func.arg.push_back(Source::func_info::arg_info(Source::func_info::ARG_INOUT,id));
    func.change_var.push_back( boost::bind(func_change_variable<T>,boost::ref(v),id) );
    func.undo_var.push_back( boost::bind(func_change_variable<T>,boost::ref(v),v.getID()) );
}

template<typename T>
void func_add_arg( Source::func_info& func, const variable<T>& v )
{
    int id = Source::code.getNewID(1);
    func.arg.push_back(Source::func_info::arg_info(Source::func_info::ARG_IN,id));
    func.change_var.push_back( boost::bind(&func_change_variable<T>,boost::ref(const_cast<variable<T>&>(v)),id) ); 
    func.undo_var.push_back( boost::bind(&func_change_variable<T>,boost::ref(const_cast<variable<T>&>(v)),v.getID()) );    
}

template<typename T>
void func_add_arg( Source::func_info& func, const func_in_wrapper<T>& v )
{
    func_add_arg(func,v.var);    
}

template<typename T>
void func_add_arg( Source::func_info& func, const func_out_wrapper<T>& v )
{
    int id = Source::code.getNewID(1);
    func.arg.push_back(Source::func_info::arg_info(Source::func_info::ARG_OUT,id));
    func.change_var.push_back( boost::bind(func_change_variable<T>,boost::ref(v.var),id) );
    func.undo_var.push_back( boost::bind(func_change_variable<T>,boost::ref(v.var),v.var.getID()) );
}

template<typename T>
void func_add_arg( Source::func_info& func, const func_inout_wrapper<T>& v )
{
    func_add_arg(func,v.var);
}

template<typename T0>
void func_create(const std::string& name, T0& v0)
{
    if( Source::code.isFuncAvailable(name) ) return;

    Source::func_info& func(Source::code.getFunc(name));
    func_add_arg(func,v0);
}

template<typename T0, typename T1>
void func_create(const std::string& name, T0& v0, T1& v1 )
{
    if( Source::code.isFuncAvailable(name) ) return;

    Source::func_info& func(Source::code.getFunc(name));
    func_add_arg(func,v0);
    func_add_arg(func,v1);
}

template<typename T0, typename T1, typename T2>
void func_create(const std::string& name, T0& v0, T1& v1, T2& v2 )
{
    if( Source::code.isFuncAvailable(name) ) return;

    Source::func_info& func(Source::code.getFunc(name));
    func_add_arg(func,v0);
    func_add_arg(func,v1);
    func_add_arg(func,v2);
}

template<typename T0, typename T1, typename T2, typename T3>
void func_create(const std::string& name, T0& v0, T1& v1, T2& v2, T3& v3 )
{
    if( Source::code.isFuncAvailable(name) ) return;

    Source::func_info& func(Source::code.getFunc(name));
    func_add_arg(func,v0);
    func_add_arg(func,v1);
    func_add_arg(func,v2);
    func_add_arg(func,v3);
}

template<typename T0, typename T1, typename T2, typename T3, typename T4>
void func_create(const std::string& name, T0& v0, T1& v1, T2& v2, T3& v3, T4& v4 )
{
    if( Source::code.isFuncAvailable(name) ) return;

    Source::func_info& func(Source::code.getFunc(name));
    func_add_arg(func,v0);
    func_add_arg(func,v1);
    func_add_arg(func,v2);
    func_add_arg(func,v3);
    func_add_arg(func,v4);
}

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
void func_create(const std::string& name, T0& v0, T1& v1, T2& v2, T3& v3, T4& v4, T5& v5 )
{
    if( Source::code.isFuncAvailable(name) ) return;

    Source::func_info& func(Source::code.getFunc(name));
    func_add_arg(func,v0);
    func_add_arg(func,v1);
    func_add_arg(func,v2);
    func_add_arg(func,v3);
    func_add_arg(func,v4);
    func_add_arg(func,v5);
}

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
void func_create(const std::string& name, T0& v0, T1& v1, T2& v2, T3& v3, T4& v4, T5& v5, T6& v6 )
{
    if( Source::code.isFuncAvailable(name) ) return;

    Source::func_info& func(Source::code.getFunc(name));
    func_add_arg(func,v0);
    func_add_arg(func,v1);
    func_add_arg(func,v2);
    func_add_arg(func,v3);
    func_add_arg(func,v4);
    func_add_arg(func,v5);
    func_add_arg(func,v6);
}

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
void func_create(const std::string& name, T0& v0, T1& v1, T2& v2, T3& v3, T4& v4, T5& v5, T6& v6, T7& v7 )
{
    if( Source::code.isFuncAvailable(name) ) return;

    Source::func_info& func(Source::code.getFunc(name));
    func_add_arg(func,v0);
    func_add_arg(func,v1);
    func_add_arg(func,v2);
    func_add_arg(func,v3);
    func_add_arg(func,v4);
    func_add_arg(func,v5);
    func_add_arg(func,v6);
    func_add_arg(func,v7);
}

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
void func_create(const std::string& name, T0& v0, T1& v1, T2& v2, T3& v3, T4& v4, T5& v5, T6& v6, T7& v7, T8& v8 )
{
    if( Source::code.isFuncAvailable(name) ) return;

    Source::func_info& func(Source::code.getFunc(name));
    func_add_arg(func,v0);
    func_add_arg(func,v1);
    func_add_arg(func,v2);
    func_add_arg(func,v3);
    func_add_arg(func,v4);
    func_add_arg(func,v5);
    func_add_arg(func,v6);
    func_add_arg(func,v7);
    func_add_arg(func,v8);
}

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
void func_create(const std::string& name, T0& v0, T1& v1, T2& v2, T3& v3, T4& v4, T5& v5, T6& v6, T7& v7, T8& v8, T9& v9 )
{
    if( Source::code.isFuncAvailable(name) ) return;

    Source::func_info& func(Source::code.getFunc(name));
    func_add_arg(func,v0);
    func_add_arg(func,v1);
    func_add_arg(func,v2);
    func_add_arg(func,v3);
    func_add_arg(func,v4);
    func_add_arg(func,v5);
    func_add_arg(func,v6);
    func_add_arg(func,v7);
    func_add_arg(func,v8);
    func_add_arg(func,v9);
}

template<typename T0>
void func_emit_call( const std::string& name, T0& v0 )
{
    Source::func_info& func(Source::code.getFunc(name));
    
    Source::code << func.pre_call(0,v0);
    Source::code << boost::format("call %i\n") % func.fid;
    Source::code << func.post_call(0,v0);    
}

template<typename T0, typename T1>
void func_emit_call( const std::string& name, T0& v0, T1& v1 )
{
    Source::func_info& func(Source::code.getFunc(name));
    
    Source::code << func.pre_call(0,v0);
    Source::code << func.pre_call(1,v1);
    Source::code << boost::format("call %i\n") % func.fid;
    Source::code << func.post_call(0,v0);
    Source::code << func.post_call(1,v1);
}

template<typename T0, typename T1, typename T2>
void func_emit_call( const std::string& name, T0& v0, T1& v1, T2& v2 )
{
    Source::func_info& func(Source::code.getFunc(name));
    
    Source::code << func.pre_call(0,v0);
    Source::code << func.pre_call(1,v1);
    Source::code << func.pre_call(2,v2);
    Source::code << boost::format("call %i\n") % func.fid;
    Source::code << func.post_call(0,v0);
    Source::code << func.post_call(1,v1);
    Source::code << func.post_call(2,v2);
}

template<typename T0, typename T1, typename T2, typename T3>
void func_emit_call( const std::string& name, T0& v0, T1& v1, T2& v2, T3& v3 )
{
    Source::func_info& func(Source::code.getFunc(name));
    
    Source::code << func.pre_call(0,v0);
    Source::code << func.pre_call(1,v1);
    Source::code << func.pre_call(2,v2);
    Source::code << func.pre_call(3,v3);
    Source::code << boost::format("call %i\n") % func.fid;
    Source::code << func.post_call(0,v0);
    Source::code << func.post_call(1,v1);
    Source::code << func.post_call(2,v2);
    Source::code << func.post_call(3,v3);
}

template<typename T0, typename T1, typename T2, typename T3, typename T4>
void func_emit_call( const std::string& name, T0& v0, T1& v1, T2& v2, T3& v3, T4& v4 )
{
    Source::func_info& func(Source::code.getFunc(name));
    
    Source::code << func.pre_call(0,v0);
    Source::code << func.pre_call(1,v1);
    Source::code << func.pre_call(2,v2);
    Source::code << func.pre_call(3,v3);
    Source::code << func.pre_call(4,v4);
    Source::code << boost::format("call %i\n") % func.fid;
    Source::code << func.post_call(0,v0);
    Source::code << func.post_call(1,v1);
    Source::code << func.post_call(2,v2);
    Source::code << func.post_call(3,v3);
    Source::code << func.post_call(4,v4);
}

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
void func_emit_call( const std::string& name, T0& v0, T1& v1, T2& v2, T3& v3, T4& v4, T5& v5 )
{
    Source::func_info& func(Source::code.getFunc(name));
    
    Source::code << func.pre_call(0,v0);
    Source::code << func.pre_call(1,v1);
    Source::code << func.pre_call(2,v2);
    Source::code << func.pre_call(3,v3);
    Source::code << func.pre_call(4,v4);
    Source::code << func.pre_call(5,v5);
    Source::code << boost::format("call %i\n") % func.fid;
    Source::code << func.post_call(0,v0);
    Source::code << func.post_call(1,v1);
    Source::code << func.post_call(2,v2);
    Source::code << func.post_call(3,v3);
    Source::code << func.post_call(4,v4);
    Source::code << func.post_call(5,v5);
}

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
void func_emit_call( const std::string& name, T0& v0, T1& v1, T2& v2, T3& v3, T4& v4, T5& v5, T6& v6 )
{
    Source::func_info& func(Source::code.getFunc(name));
    
    Source::code << func.pre_call(0,v0);
    Source::code << func.pre_call(1,v1);
    Source::code << func.pre_call(2,v2);
    Source::code << func.pre_call(3,v3);
    Source::code << func.pre_call(4,v4);
    Source::code << func.pre_call(5,v5);
    Source::code << func.pre_call(6,v6);
    Source::code << boost::format("call %i\n") % func.fid;
    Source::code << func.post_call(0,v0);
    Source::code << func.post_call(1,v1);
    Source::code << func.post_call(2,v2);
    Source::code << func.post_call(3,v3);
    Source::code << func.post_call(4,v4);
    Source::code << func.post_call(5,v5);
    Source::code << func.post_call(6,v6);
}

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
void func_emit_call( const std::string& name, T0& v0, T1& v1, T2& v2, T3& v3, T4& v4, T5& v5, T6& v6, T7& v7 )
{
    Source::func_info& func(Source::code.getFunc(name));
    
    Source::code << func.pre_call(0,v0);
    Source::code << func.pre_call(1,v1);
    Source::code << func.pre_call(2,v2);
    Source::code << func.pre_call(3,v3);
    Source::code << func.pre_call(4,v4);
    Source::code << func.pre_call(5,v5);
    Source::code << func.pre_call(6,v6);
    Source::code << func.pre_call(7,v7);
    Source::code << boost::format("call %i\n") % func.fid;
    Source::code << func.post_call(0,v0);
    Source::code << func.post_call(1,v1);
    Source::code << func.post_call(2,v2);
    Source::code << func.post_call(3,v3);
    Source::code << func.post_call(4,v4);
    Source::code << func.post_call(5,v5);
    Source::code << func.post_call(6,v6);
    Source::code << func.post_call(7,v7);
}

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
void func_emit_call( const std::string& name, T0& v0, T1& v1, T2& v2, T3& v3, T4& v4, T5& v5, T6& v6, T7& v7, T8& v8 )
{
    Source::func_info& func(Source::code.getFunc(name));
    
    Source::code << func.pre_call(0,v0);
    Source::code << func.pre_call(1,v1);
    Source::code << func.pre_call(2,v2);
    Source::code << func.pre_call(3,v3);
    Source::code << func.pre_call(4,v4);
    Source::code << func.pre_call(5,v5);
    Source::code << func.pre_call(6,v6);
    Source::code << func.pre_call(7,v7);
    Source::code << func.pre_call(8,v8);
    Source::code << boost::format("call %i\n") % func.fid;
    Source::code << func.post_call(0,v0);
    Source::code << func.post_call(1,v1);
    Source::code << func.post_call(2,v2);
    Source::code << func.post_call(3,v3);
    Source::code << func.post_call(4,v4);
    Source::code << func.post_call(5,v5);
    Source::code << func.post_call(6,v6);
    Source::code << func.post_call(7,v7);
    Source::code << func.post_call(8,v8);
}

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
void func_emit_call( const std::string& name, T0& v0, T1& v1, T2& v2, T3& v3, T4& v4, T5& v5, T6& v6, T7& v7, T8& v8, T9& v9 )
{
    Source::func_info& func(Source::code.getFunc(name));
    
    Source::code << func.pre_call(0,v0);
    Source::code << func.pre_call(1,v1);
    Source::code << func.pre_call(2,v2);
    Source::code << func.pre_call(3,v3);
    Source::code << func.pre_call(4,v4);
    Source::code << func.pre_call(5,v5);
    Source::code << func.pre_call(6,v6);
    Source::code << func.pre_call(7,v7);
    Source::code << func.pre_call(8,v8);
    Source::code << func.pre_call(9,v9);    
    Source::code << boost::format("call %i\n") % func.fid;
    Source::code << func.post_call(0,v0);
    Source::code << func.post_call(1,v1);
    Source::code << func.post_call(2,v2);
    Source::code << func.post_call(3,v3);
    Source::code << func.post_call(4,v4);
    Source::code << func.post_call(5,v5);
    Source::code << func.post_call(6,v6);
    Source::code << func.post_call(7,v7);
    Source::code << func.post_call(8,v8);
    Source::code << func.post_call(9,v9);
}

inline std::string func_name( const std::string& file, int line, int id )
{
    return (boost::format("func:%s:%i:%i") % file % line % id).str();
}

template<typename T0>
void func_begin( const std::string& name, T0& v0 )
{
    func_create(name,v0);
    func_emit_call(name,v0);
    Source::code.makeFuncActive(name);
}

template<typename T0, typename T1>
void func_begin( const std::string& name, T0& v0, T1& v1 )
{
    func_create(name,v0,v1);
    func_emit_call(name,v0,v1);
    Source::code.makeFuncActive(name);
}

template<typename T0, typename T1, typename T2>
void func_begin( const std::string& name, T0& v0, T1& v1, T2& v2 )
{
    func_create(name,v0,v1,v2);
    func_emit_call(name,v0,v1,v2);
    Source::code.makeFuncActive(name);
}

template<typename T0, typename T1, typename T2, typename T3>
void func_begin( const std::string& name, T0& v0, T1& v1, T2& v2, T3& v3 )
{
    func_create(name,v0,v1,v2,v3);
    func_emit_call(name,v0,v1,v2,v3);
    Source::code.makeFuncActive(name);
}

template<typename T0, typename T1, typename T2, typename T3, typename T4>
void func_begin( const std::string& name, T0& v0, T1& v1, T2& v2, T3& v3, T4& v4 )
{
    func_create(name,v0,v1,v2,v3,v4);
    func_emit_call(name,v0,v1,v2,v3,v4);
    Source::code.makeFuncActive(name);
}

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
void func_begin( const std::string& name, T0& v0, T1& v1, T2& v2, T3& v3, T4& v4, T5& v5 )
{
    func_create(name,v0,v1,v2,v3,v4,v5);
    func_emit_call(name,v0,v1,v2,v3,v4,v5);
    Source::code.makeFuncActive(name);
}

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
void func_begin( const std::string& name, T0& v0, T1& v1, T2& v2, T3& v3, T4& v4, T5& v5, T6& v6 )
{
    func_create(name,v0,v1,v2,v3,v4,v5,v6);
    func_emit_call(name,v0,v1,v2,v3,v4,v5,v6);
    Source::code.makeFuncActive(name);
}

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
void func_begin( const std::string& name, T0& v0, T1& v1, T2& v2, T3& v3, T4& v4, T5& v5, T6& v6, T7& v7 )
{
    func_create(name,v0,v1,v2,v3,v4,v5,v6,v7);
    func_emit_call(name,v0,v1,v2,v3,v4,v5,v6,v7);
    Source::code.makeFuncActive(name);
}

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
void func_begin( const std::string& name, T0& v0, T1& v1, T2& v2, T3& v3, T4& v4, T5& v5, T6& v6, T7& v7, T8& v8 )
{    
    func_create(name,v0,v1,v2,v3,v4,v5,v6,v7,v8);
    func_emit_call(name,v0,v1,v2,v3,v4,v5,v6,v7,v8);
    Source::code.makeFuncActive(name);
}

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
void func_begin( const std::string& name, T0& v0, T1& v1, T2& v2, T3& v3, T4& v4, T5& v5, T6& v6, T7& v7, T8& v8, T9& v9 )
{
    func_create(name,v0,v1,v2,v3,v4,v5,v6,v7,v8,v9);
    func_emit_call(name,v0,v1,v2,v3,v4,v5,v6,v7,v8,v9);
    Source::code.makeFuncActive(name);
}

inline void func_end()
{
    Source::code.endFunc();
}

template<int N>
class func_name_helper
{
protected:    
    static int counter;

protected:    
    int id;
    
public:    
    func_name_helper() : id(counter++) {}
    int operator()() const { return id; }
};

template<int N>
int func_name_helper<N>::counter=0;

} // detail
    
#define il_func(...) { static ::cal::il::detail::func_name_helper<0> __id; ::cal::il::detail::func_begin(::cal::il::detail::func_name(__FILE__, __LINE__, __id()), __VA_ARGS__); }
#define il_endfunc { ::cal::il::detail::func_end(); }

template<typename T>
const detail::func_in_wrapper<T> _in( const variable<T>& v )
{
    return detail::func_in_wrapper<T>(v);
}

template<typename T>
const detail::func_out_wrapper<T> _out( variable<T>& v )
{
    return detail::func_out_wrapper<T>(v);
}

template<typename T>
const detail::func_inout_wrapper<T> _inout( variable<T>& v )
{
    return detail::func_inout_wrapper<T>(v);
}

}
}

#endif
