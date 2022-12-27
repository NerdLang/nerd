/*
	Copyright (c) 2021 NerdLang - Adrien THIERRY and contributors

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.

*/

/*** HELPERS ***/
#define __NERD_GET_String(_var) _var.get().s->value
#define __NERD_Create_Boolean(_value) NerdCore::VAR(NerdCore::Enum::Type::Boolean, _value)
#define __NERD_Create_Number(_value) NerdCore::VAR(_value)
#define __NERD_Create_Function(_value) NerdCore::VAR(NerdCore::Enum::Type::Function, _value)
#define __NERD_Create_Undefined() NerdCore::VAR()
#define __NERD_Create_String(_value) NerdCore::VAR(_value)
#define __NERD_Create_Infinity() NerdCore::VAR(std::numeric_limits<double>::infinity)
#define __NERD_Create_Null() NerdCore::VAR(NerdCore::Enum::Type::Null, 0)
#define __NERD_Create_Struct(_value) NerdCore::VAR(new _value(), new NerdCore::Type::clean_struct([](void* _ptr){ delete (_value*)_ptr;}))
#define __NERD_Create_FixedArray(_length) NerdCore::VAR(new NerdCore::Class::FixedArray(_length))
#define __NERD_Create_Lambda(name) NerdCore::Type::function_t* name = new NerdCore::Type::function_t([](NerdCore::VAR& __NERD_THIS, NerdCore::VAR* __NERD_VARARGS, int __NERD_VARLENGTH)

#define __NERD_Create_Ptr_Scoped_Anon(__CONTENT__) new NerdCore::Type::function_t([&](NerdCore::VAR& __NERD_THIS, NerdCore::VAR* __NERD_VARARGS, int __NERD_VARLENGTH) mutable  -> NerdCore::Global::var { __CONTENT__ })
#define __NERD_Create_Ptr_Scoped_Copy_Anon(__CONTENT__) new NerdCore::Type::function_t([=](NerdCore::VAR& __NERD_THIS, NerdCore::VAR* __NERD_VARARGS, int __NERD_VARLENGTH) mutable  -> NerdCore::Global::var { __CONTENT__ })
#define __NERD_Create_Ptr_Scoped_Copy_Anon_With_Ref(__FN__, __CONTENT__) new NerdCore::Type::function_t([=, &__FN__](NerdCore::VAR& __NERD_THIS, NerdCore::VAR* __NERD_VARARGS, int __NERD_VARLENGTH) mutable  -> NerdCore::Global::var { __CONTENT__ })
#define __NERD_Create_Ptr_Unscoped_With_Copy(__FN__, __CONTENT__) new NerdCore::Type::function_t([__FN__](NerdCore::VAR& __NERD_THIS, NerdCore::VAR* __NERD_VARARGS, int __NERD_VARLENGTH) mutable  -> NerdCore::Global::var { __CONTENT__ })
#define __NERD_Create_Ptr_Unscoped_Anon(__CONTENT__) new NerdCore::Type::function_t([](NerdCore::VAR& __NERD_THIS, NerdCore::VAR* __NERD_VARARGS, int __NERD_VARLENGTH) -> NerdCore::Global::var{ __CONTENT__ })

#define __NERD_Create_Var_Scoped_Anon(__CONTENT__) NerdCore::VAR(NerdCore::Enum::Type::Function, __NERD_Create_Ptr_Scoped_Anon(__CONTENT__))
#define __NERD_Create_Var_Unscoped_Anon(__CONTENT__) NerdCore::VAR(NerdCore::Enum::Type::Function, __NERD_Create_Ptr_Unscoped_Anon(__CONTENT__))
#define __NERD_Create_Var_Scoped_Copy_Anon(__CONTENT__) NerdCore::VAR(NerdCore::Enum::Type::Function, __NERD_Create_Ptr_Scoped_Copy_Anon(__CONTENT__))
#define __NERD_Create_Var_Unscoped_With_Copy(__FN__, __CONTENT__) NerdCore::VAR(NerdCore::Enum::Type::Function, __NERD_Create_Ptr_Unscoped_With_Copy(__FN__, __CONTENT__))
#define __NERD_Create_Var_Scoped_Copy_Anon_With_Ref(__FN__, __CONTENT__) NerdCore::VAR(NerdCore::Enum::Type::Function, __NERD_Create_Ptr_Scoped_Copy_Anon_With_Ref(__FN__, __CONTENT__))

#define __NERD_Init_Int(_name, _value) int _name = _value
#define __NERD_Init_Double(_name, _value) double _name = _value
#define __NERD_Init_String(_name, _value) std::string _name = _value
#define __NERD_EXCEPTION_PARAMETER NerdCore::VAR &e
#define finally ;
#define __NERD_Throw_Error(_err) NerdCore::VAR(NerdCore::VAR(_err) + NerdCore::VAR(", line: ") + std::to_string(__LINE__) + NerdCore::VAR(", file: ") + NerdCore::VAR(__FILE__))
#define __NERD_Boolean_TRUE __NERD_Create_Boolean(true)
#define __NERD_Boolean_FALSE __NERD_Create_Boolean(false)
#define __NERD_FAST_INT double
#define __NERD_CreateMethodToClass(_name, _fn) __NERD_Object_Set(_name, __NERD_Create_Var_Scoped_Anon( return _fn(NerdCore::VAR& __NERD_THIS, __NERD_VARARGS, __NERD_VARLENGTH); ), &object);
#define __NERD_NEW(_fn) ((NerdCore::Class::Function*)_fn.data.ptr)->New
#define __NERD_Access_Struct(_exp, _name) (*(_name*)((NerdCore::Class::Struct*)_exp.data.ptr)->value)
#define arguments() new NerdCore::Class::FixedArray(__NERD_VARARGS, __NERD_VARLENGTH);
//#define __NERD_Native_Ptr(_var, _type) ((_type)((NerdCore::Class::NativeTPL<_type>*)_var.data.ptr)->value)
#define __NERD_OBJECT(_var) ((NerdCore::Class::Object*)_var.data.ptr)
#define __NERD_ARRAY(_var) ((NerdCore::Class::Array*)_var.data.ptr)
#define __NERD_FUNCTION(_var) ((NerdCore::Class::Function*)_var.data.ptr)
#define __NERD_BIND(_var, _function, _bind) _var = _function;((NerdCore::Class::Function*)_var.data.ptr)->bind = _bind;
#define Prototype() __NERD_Create_Var_Scoped_Copy_Anon( return __NERD_THIS; )
