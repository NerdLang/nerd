#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#define __NJS_ENV_ESP32
#define __NJS_NO_EXCEPT

#include "njs.h"

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