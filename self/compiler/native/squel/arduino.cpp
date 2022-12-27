 #define _USE_MATH_DEFINES
 #include <string>
 #include <avr/io.h>
 #include <wiring_digital.c>
 #include <Arduino.h>
 #include <wiring.c>
 #include <hooks.c>
 #include <util/delay.h>
 #include <string.h>
 #include <WString.h>
 #include <WString.cpp>
 #include <new>
 #include <string_view>

 #include <time.h>
 #include <vector>
 
 #include <nonstd-function.h>

 #define __NERD_ENV_ARDUINO
 #define __NERD_NO_EXCEPT

 #include "nerdcore/src/nerd.cpp"

 using namespace NerdCore::Global;
 using namespace NerdCore::Functions;
 #define __NERD_Create_Object() new NerdCore::Class::Object()
 #define __NERD_Create_Array(_arr) new NerdCore::Class::Array(_arr)
 #define __NERD_InitVar() NerdCore::VAR()
 
 var __NERD_ENV = "arduino";
 var __NERD_PLATFORM = "{{__PLATFORM__}}";
 

 
 
 // Declared weak in Arduino.h to allow user redefinitions.
int atexit(void (* /*func*/ )()) { return 0; }
// Weak empty variant initialization function.
// May be redefined by variant files.
void initVariant() __attribute__((weak));
void initVariant() { }

void setupUSB() __attribute__((weak));
void setupUSB() { }


 {INCLUDE}

int main(int argc, char* argv[])
{
	
	{DECL}
	
	init();
	initVariant();

	#if defined(USBCON)
	USBDevice.attach();
	#endif

	{INIT}
	
	{
		{CODE}
	}
	
	return 0;
}
