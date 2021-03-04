 #include "mbed.h"
 #include "nectar.cpp"
 
 using namespace NectarCore::Global;
 using namespace NectarCore::Functions;
 
 var __NJS_ENV = "stm32";
 var __NJS_PLATFORM = "{{__PLATFORM__}}";
 
 #define __NJS_Create_Object() new NectarCore::Class::Object()
 #define __NJS_Create_Array(_arr) new NectarCore::Class::Array(_arr)
 #define __NJS_InitVar() NectarCore::VAR()
 {INCLUDE}
 
 {DECL}

int main()
{
  {INIT}

	{
		{CODE}
	}
	return 0;
}
