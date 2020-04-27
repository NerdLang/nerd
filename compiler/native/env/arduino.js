/*
 * This file is part of NectarJS
 * Copyright (c) 2020 Adrien THIERRY
 * http://nectarjs.com - https://nectrium.com
 *
 * sources : https://github.com/nectarjs/nectarjs
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

var OPTIONS = 
{
	"mega2560": { preset: "-DF_CPU=16000000UL -mmcu=atmega2560", variant: "mega"},
	"mega1280": { preset: "-DF_CPU=16000000UL -mmcu=atmega1280", variant: "mega"},
	"uno": { preset: "-DF_CPU=16000000UL -mmcu=atmega328p", variant: "standard"},
}

var ARDUINO =
{
  name: "arduino",
  main: "arduino.cpp",
  cli: function(compiler, preset, out, _in, option, target, spec)
  {
	  if(!target || !OPTIONS[target])
	  {
		  console.log("[!] No target selected, switching to 'uno'");
		  target = "uno";
	  }
	  var _cli = `${compiler} ${OPTIONS[target].preset} -w -fpermissive -Os -fno-exceptions -fno-rtti -fno-stack-protector -fomit-frame-pointer -ffunction-sections -fdata-sections -Wl,--gc-sections \
   -I ${extern}/avr -I ${extern}/arduino/avr/variants/${OPTIONS[target].variant}/ -I ${extern}/arduino/avr/cores/arduino  -I ${extern}/avr/include -I ${extern}/stlarduino  ${extern}/arduino/avr/cores/arduino/abi.cpp -fno-threadsafe-statics -lm -o ${out} ${_in} && avr-objcopy -O ihex -R .eeprom ${out}`;

	return _cli;
  },
  compiler: "avr-c++ -std=c++14",
  stdlib:[],
  check: "arduino.json",
}

module.exports = ARDUINO;
