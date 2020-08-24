/*** HELPERS ***/
#define __NJS_GET_STRING(_var) _var.get().s->__NJS_VALUE
#define var __NJS_VAR
#define let __NJS_VAR
#define __NJS_Create_Boolean(_value) __NJS_VAR(__NJS_BOOLEAN, _value)
#define __NJS_Create_Number(_value) __NJS_VAR(_value)
#define __NJS_Create_Function(_value) __NJS_VAR(__NJS_FUNCTION, _value)
#define __NJS_Create_Undefined() __NJS_VAR()
#define __NJS_DECL_FUNCTION function
#define __NJS_RETURN_UNDEFINED \
	var __undef = __NJS_VAR(); \
	return __undef;
#define __NJS_Create_String(_value) __NJS_VAR(_value)
#define __NJS_Create_Infinity() __NJS_VAR(__NJS_INFINITY, 0)
#define Infinity __NJS_Create_Infinity()
#define __NJS_Create_Null() __NJS_VAR(__NJS_NULL, 0)
#define __NJS_Create_Lambda(name) function<__NJS_VAR (vector<var>)>* name = new function<__NJS_VAR (vector<var>)>([](vector<var> __NJS_VARARGS)
#define __NJS_Create_Ptr_Scoped_Anon(__CONTENT__) new function<__NJS_VAR (vector<var>)>([&](vector<var> __NJS_VARARGS){ __CONTENT__ })
#define __NJS_Create_Ptr_Unscoped_Anon(__CONTENT__) new function<__NJS_VAR (vector<var>)>([](vector<var> __NJS_VARARGS){ __CONTENT__ })
#define __NJS_Create_Var_Scoped_Anon(__CONTENT__) __NJS_VAR(__NJS_FUNCTION, __NJS_Create_Ptr_Scoped_Anon(__CONTENT__))
#define __NJS_Create_Var_Unscoped_Anon(__CONTENT__) __NJS_VAR(__NJS_FUNCTION, __NJS_Create_Ptr_Unscoped_Anon(__CONTENT__))
#define __NJS_EXCEPTION_PARAMETER __NJS_VAR &e
#define finally ;
#define __NJS_BOOLEAN_TRUE __NJS_Create_Boolean(true)
#define __NJS_BOOLEAN_FALSE __NJS_Create_Boolean(false)
#define __NJS_FAST_INT constexpr int
/*** END HELPERS ***/