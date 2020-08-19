/*
 * This file is part of NectarJS
 * Copyright (c) 2017-2020 Adrien THIERRY
 * http://nectarjs.com - https://www.linkedin.com/in/adrien-thierry-fr/
 *
 * sources : https://github.com/nectarjs/nectarjs/
 *
 * this program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * You can be released from the requirements of the license by purchasing
 * a commercial license. Buying such a license is mandatory as soon as you
 * develop commercial activities involving the NectarJS software without
 * disclosing the source code of your own applications. Visit http://seraum.com/
 * and feel free to contact us.
 *
 */
 #include <avr/io.h>
 #include <wiring_digital.c>
 #include <Arduino.h>
 #include <wiring.c>
 #include <hooks.c>
 #include <util/delay.h>
 #include <string.h>
 #include <WString.h>
 #include <WString.cpp>
 #include <new.h>
 #include <new.cpp>
 #include <time.h>
 #include <vector>
 
 #include <nonstd-function.h>

 using namespace std;

 #define __NJS_ARDUINO 1

 #include "njs.h"
 using namespace NECTAR;
 
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
	
	{CODE}
	
	setup();
	
	while(true)
	{
		loop();
		delay(1);
	}
	
	return 0;
}
