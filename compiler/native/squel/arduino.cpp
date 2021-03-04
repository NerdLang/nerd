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

 #include <time.h>
 #include <vector>
 
 #include <nonstd-function.h>

 #define __Nectar_ENV_ARDUINO
 #define __Nectar_NO_EXCEPT

 #include "nectar.cpp"

 using namespace NectarCore::Global;
 using namespace NectarCore::Functions;
 #define __NJS_Create_Object() new NectarCore::Class::Object()
 #define __NJS_Create_Array(_arr) new NectarCore::Class::Array(_arr)
 #define __NJS_InitVar() NectarCore::VAR()
 
 var __NJS_ENV = "arduino";
 var __NJS_PLATFORM = "{{__PLATFORM__}}";
 
 
 
 // Declared weak in Arduino.h to allow user redefinitions.
int atexit(void (* /*func*/ )()) { return 0; }
// Weak empty variant initialization function.
// May be redefined by variant files.
void initVariant() __attribute__((weak));
void initVariant() { }

void setupUSB() __attribute__((weak));
void setupUSB() { }


 {INCLUDE}
 
 {DECL}

int main(int argc, char* argv[])
{
	init();
	initVariant();

	#if defined(USBCON)
	USBDevice.attach();
	#endif

	{INIT}
	
	{
		{CODE}
	}
	
	setup();
	
	while(true)
	{
		loop();
		delay(1);
	}
	
	return 0;
}
