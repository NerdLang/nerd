__NJS_DECL_FUNCTION<__NJS_VAR (vector<var> __NJS_VARARGS)>* __NJS_FN_NATIVE_LOG_CONSOLE = new __NJS_DECL_FUNCTION<__NJS_VAR (vector<var> __NJS_VARARGS)>([]( vector<var> __NJS_VARARGS ) -> __NJS_VAR 
{
	if(__NJS_VARARGS.size() == 0) __NJS_Log_Console("");
	else __NJS_Log_Console(__NJS_VARARGS[0]);
	return var();
});

var __NJS_NATIVE_LOG_CONSOLE = __NJS_Create_Function(__NJS_FN_NATIVE_LOG_CONSOLE);
