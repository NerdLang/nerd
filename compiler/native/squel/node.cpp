 #define __NJS_ENV_NODE
 #include "uv.h"
 #include "nectar.hpp"
 
 using namespace NectarCore::Global;
 using namespace NectarCore::Functions;
 
 var __NJS_ENV = "node";
 var __NJS_PLATFORM = "{{__PLATFORM__}}"; 
 #define __NJS_Create_Object() new NectarCore::Class::Object()
 #define __NJS_Create_Array(_arr) new NectarCore::Class::Array(_arr)
 #define __NJS_InitVar() NectarCore::VAR()
 
 uv_loop_t *__NJS_UV_DEFAULT_LOOP = (uv_loop_t *)malloc(sizeof(uv_loop_t));
 
 {INCLUDE}
 
 {DECL}

int main(int argc, char* argv[])
{
	uv_loop_init(__NJS_UV_DEFAULT_LOOP);
	var __NJS_ARGS = __NJS_Create_Array();
	for( int i = 0; i < argc; i++)
	{
		__NJS_ARGS[i] = argv[i];
	}

	{INIT}

	{
		{CODE};
	}
	
    uv_run(__NJS_UV_DEFAULT_LOOP, UV_RUN_DEFAULT);

    uv_loop_close(__NJS_UV_DEFAULT_LOOP);
    free(__NJS_UV_DEFAULT_LOOP);
    return 0;
	
	return 0;
}
