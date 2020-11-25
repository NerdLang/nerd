#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#define __Nectar_ENV_ESP32
#define __Nectar_NO_EXCEPT

#include "nectar.cpp"
using namespace NectarCore::Global;
using namespace NectarCore::Functions;

var __NJS_ENV = "esp32";
var __NJS_PLATFORM = "{{__PLATFORM__}}";
#define __NJS_Create_Object() new NectarCore::Class::Object()
#define __NJS_Create_Array(_arr) new NectarCore::Class::Array(_arr)
#define __NJS_InitVar() NectarCore::VAR()
 
 {INCLUDE}
 
 {DECL}
 
 
 namespace NJS
 {
	void __NJS_MAIN()
	{
		 {INIT}
		{
			{CODE}
		}
	}
 }
 
extern "C" void app_main(void)
{
	NJS::__NJS_MAIN();
}