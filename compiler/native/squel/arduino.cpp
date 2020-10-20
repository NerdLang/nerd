/*
 * This file is part of NectarJS
 * Copyright (c) 2017 - 2020 Adrien THIERRY
 * http://nectarjs.com - https://seraum.com/
 *
 * sources : https://github.com/nectarjs/nectarjs
 * 
 * NectarJS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * NectarJS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with NectarJS.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
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

 #define __NJS_ENV_ARDUINO
 #define __NJS_NO_EXCEPT

 #include "njs.h"

 
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
