/*
 * This file is part of NectarJS
 * Copyright (c) 2019 Adrien THIERRY
 * http://nectarjs.com - https://nectrium.com
 *
 * sources : https://github.com/nectarjs/nectarjs
 *
 * NectarJS
 * Copyright (C) 2019 Adrien THIERRY - Necrium
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

var ARDUINO =
{
  name: "arduino",
  base: "arduino.cpp",
  cli: "__COMPILER__ -Os -fno-exceptions -fno-rtti -fno-stack-protector -fomit-frame-pointer -ffunction-sections -fdata-sections -Wl,--gc-sections \
   -I extern/avr/ -I extern/arduino/avr/cores/arduino -I extern/avrlib/variants/__SPEC__/ extern/arduino/avr/cores/arduino/abi.cpp -lm -o __OUT__ __IN__ __OPTION__ && avr-objcopy -O ihex -R .eeprom __OUT__",
  compiler: "/opt/tools/avr/bin/avr-g++ -DF_CPU=16000000UL -mmcu=atmega2560",
  stdlib:["arduino"],
  check: "arduino.json",
}

module.exports = ARDUINO;
