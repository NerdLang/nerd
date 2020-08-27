/*** HELPERS ***/

#define __NJS_GET_STRING(_var) _var.get().s->value
#define __NJS_VAR NJS::VAR
#define var NJS::VAR
#define let NJS::VAR
#define __NJS_Create_Boolean(_value) NJS::VAR(NJS::Enum::Type::BOOLEAN, _value)
#define __NJS_Create_Number(_value) NJS::VAR(_value)
#define __NJS_Create_Function(_value) NJS::VAR(NJS::Enum::Type::FUNCTION, _value)
#define __NJS_Create_Undefined() NJS::VAR()
#define __NJS_DECL_FUNCTION function
#define __NJS_RETURN_UNDEFINED \
	var __undef = NJS::VAR(); \
	return __undef;
#define __NJS_Create_String(_value) NJS::VAR(_value)
#define __NJS_Create_Infinity() NJS::VAR(NJS::Enum::Type::ISINFINITY, 0)
#define __NJS_Create_Null() NJS::VAR(NJS::Enum::Type::ISNULL, 0)
#define __NJS_Create_Lambda(name) function<NJS::VAR (vector<var>)>* name = new function<NJS::VAR (vector<var>)>([](vector<var> _NJS_VARARGS)
#define __NJS_Create_Ptr_Scoped_Anon(__CONTENT__) new function<NJS::VAR (vector<var>)>([&](vector<var> _NJS_VARARGS){ __CONTENT__ })
#define __NJS_Create_Ptr_Unscoped_Anon(__CONTENT__) new function<NJS::VAR (vector<var>)>([](vector<var> _NJS_VARARGS){ __CONTENT__ })
#define __NJS_Create_Var_Scoped_Anon(__CONTENT__) NJS::VAR(NJS::Enum::Type::FUNCTION, __NJS_Create_Ptr_Scoped_Anon(__CONTENT__))
#define __NJS_Create_Var_Unscoped_Anon(__CONTENT__) NJS::VAR(NJS::Enum::Type::FUNCTION, __NJS_Create_Ptr_Unscoped_Anon(__CONTENT__))
#define __NJS_EXCEPTION_PARAMETER NJS::VAR &e
#define finally ;
#define __NJS_BOOLEAN_TRUE __NJS_Create_Boolean(true)
#define __NJS_BOOLEAN_FALSE __NJS_Create_Boolean(false)
#define __NJS_FAST_INT constexpr int
#define __NJS_CreateMethodToClass(name, fn) __NJS_Object_Set(name, __NJS_Create_Var_Scoped_Anon( return fn(_NJS_VARARGS); ), &this->object);

/*** END HELPERS ***/