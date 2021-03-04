 #define _USE_MATH_DEFINES

 #include "nectar.hpp"
 using namespace NectarCore::Global;
 using namespace NectarCore::Functions;
 
 var __NJS_ENV = "test";
 var __NJS_PLATFORM = "{{__PLATFORM__}}";
 
/*** $ERROR ***/
NectarCore::VAR __NJS_DOLLAR_ERROR = __Nectar_Create_Var_Unscoped_Anon( __Nectar_Log_Console(__Nectar_VARARGS[0]); exit(1); return NectarCore::VAR(); );
/* end $ERROR */
 #define __NJS_Create_Object() new NectarCore::Class::Object()
 #define __NJS_Create_Array(_arr) new NectarCore::Class::Array(_arr)
 #define __NJS_InitVar() NectarCore::VAR()
 {INCLUDE}
 
 {DECL}

int main(int argc, char* argv[])
{
	var __NJS_ARGS = __NJS_Create_Array();
	for( int i = 0; i < argc; i++)
	{
		__NJS_ARGS[i] = NectarCore::VAR(argv[i]);
	}
	
	try 
	{
		{INIT}
		{
			{CODE}
		}
	}
	catch(NectarCore::VAR __NJS_Global_Exception)
	{
		__Nectar_Log_Console(__NJS_Global_Exception);
		exit(1);
	}
	return 0;
}
