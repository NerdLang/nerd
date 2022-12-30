 #define __NERD_ENV_WASM
 #include "nerdcore/src/nerd.hpp"
 
 using namespace NerdCore::Global;
 using namespace NerdCore::Functions;
 
 var __NERD_ENV = "wasm";
 var __NERD_PLATFORM = "{{__PLATFORM__}}";
 NerdCore::Global::var __NERD_ARGS = new NerdCore::Class::Array();

 {INCLUDE}

int main(int __NERD_VARLENGTH, char* __Nerd_Argv[])
{
	{DECL}
	
	NerdCore::VAR __NERD_VARARGS[__NERD_VARLENGTH];
	for( int i = 0; i < __NERD_VARLENGTH; i++)
	{
		__NERD_ARGS[i] = __Nerd_Argv[i];
		__NERD_VARARGS[i] = __Nerd_Argv[i];
	}

	try 
	{

		{INIT}
		
		#ifdef __NERD_INIT_RAND_SEED
		srand (time(NULL));
		#endif
		
		{
			{CODE}
		}
		
	}
	catch(NerdCore::VAR __NERD_Global_Exception)
	{
		__NERD_Log_Console(__NERD_Global_Exception);
		exit(1);
	}
	return 0;
}
