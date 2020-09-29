/*** HELPERS ***/
#define __NJS_GET_String(_var) _var.get().s->value
#define __NJS_VAR NJS::VAR
#define var NJS::VAR
#define let NJS::VAR
#define __NJS_Create_Boolean(_value) NJS::VAR(new NJS::Class::Boolean(_value))
#define __NJS_Create_Number(_value) NJS::VAR(_value)
#define __NJS_Create_Function(_value) NJS::VAR(NJS::Enum::Type::Function, _value)
#define __NJS_Create_Undefined() NJS::VAR()
#define __NJS_DECL_Function std::function
#define __NJS_RETURN_Undefined \
	var __undef = NJS::VAR(); \
	return __undef;
#define __NJS_Create_String(_value) NJS::VAR(_value)
#define __NJS_Create_Infinity() NJS::VAR(NJS::Enum::Type::ISINFINITY, 0)
#define __NJS_Create_Null() NJS::VAR(NJS::Enum::Type::ISNULL, 0)
#define __NJS_Create_Lambda(name) std::function<NJS::VAR (var, NJS::Type::vector_t)>* name = new std::function<NJS::VAR (var, NJS::Type::vector_t)>([](var __NJS_THIS, NJS::Type::vector_t _NJS_VARARGS)
#define __NJS_Create_Ptr_Scoped_Anon(__CONTENT__) new std::function<NJS::VAR (var, NJS::Type::vector_t)>([&](var __NJS_THIS, NJS::Type::vector_t __NJS_VARARGS){ __CONTENT__ })
#define __NJS_Create_Ptr_Unscoped_Anon(__CONTENT__) new std::function<NJS::VAR (var, NJS::Type::vector_t)>([](var __NJS_THIS, NJS::Type::vector_t __NJS_VARARGS){ __CONTENT__ })
#define __NJS_Create_Var_Scoped_Anon(__CONTENT__) NJS::VAR(NJS::Enum::Type::Function, __NJS_Create_Ptr_Scoped_Anon(__CONTENT__))
#define __NJS_Create_Var_Unscoped_Anon(__CONTENT__) NJS::VAR(NJS::Enum::Type::Function, __NJS_Create_Ptr_Unscoped_Anon(__CONTENT__))
#define __NJS_EXCEPTION_PARAMETER NJS::VAR &e
#define finally ;
#define __NJS_Boolean_TRUE __NJS_Create_Boolean(true)
#define __NJS_Boolean_FALSE __NJS_Create_Boolean(false)
#define __NJS_FAST_INT constexpr int
#define __NJS_CreateMethodToClass(_name, _fn) __NJS_Object_Set(_name, __NJS_Create_Var_Scoped_Anon( return _fn(__NJS_VARARGS); ), &object);
#define __NJS_NEW(_fn) ((NJS::Class::Function*)_fn._ptr)->New
/* END HELPERS */
