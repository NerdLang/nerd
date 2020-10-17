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

var OPTIONS = 
{
	"mega": { preset: "-DF_CPU=16000000UL -mmcu=atmega2560", variant: "mega"},
	"mega2560": { preset: "-DF_CPU=16000000UL -mmcu=atmega2560", variant: "mega"},
	"mega1280": { preset: "-DF_CPU=16000000UL -mmcu=atmega1280", variant: "mega"},
	"uno": { preset: "-DF_CPU=16000000UL -mmcu=atmega328p", variant: "standard"},
	"nano": { preset: "-DF_CPU=16000000UL -mmcu=atmega328p", variant: "standard"},
	"nano2": { preset: "-DF_CPU=16000000UL -mmcu=atmega168", variant: "standard"},
	"nano3": { preset: "-DF_CPU=16000000UL -mmcu=atmega328p", variant: "standard"}
}

function getOptions()
{
	var OPT = 
	{
		elf: false,
		cli: false,
	};

	if(CLI.cli["--option"] && CLI.cli["--option"].argument)
	{
		var _args = CLI.cli["--option"].argument.split(",");
		for(var i = 0; i < _args.length; i++)
		{
			OPT[_args[i]] = true;
		}
	}
	return OPT;
}

var ARDUINO =
{
  name: "arduino",
  main: "arduino.cpp",
  cli: function(compiler, preset, out, _in, option, target, spec)
  {
	  var OPT = getOptions();		
	  
	  if(!target || !OPTIONS[target])
	  {
		  console.log("[!] No target selected, switching to 'uno'");
		  target = "uno";
	  }
	  var _cli = `${compiler} ${OPTIONS[target].preset} -DARDUINO_ARCH_AVR -w -Os -fno-exceptions -fno-rtti -fno-stack-protector -fomit-frame-pointer -ffunction-sections -fdata-sections -Wl,--gc-sections \
	  -I ${extern}/avr -I ${extern}/arduino/avr/variants/${OPTIONS[target].variant}/ -I ${extern}/arduino/avr/cores/arduino  -I ${extern}/avr/include -I ${extern}/stlarduino ${extern}/stlarduino/ios.cpp  ${extern}/arduino/avr/cores/arduino/abi.cpp -fno-threadsafe-statics -lm ${COMPILER.LIBS} -o ${out} ${_in}`;
	  
 	  if(!OPT.elf) _cli += `&& avr-objcopy -O ihex -R .eeprom ${out}`;
	if(OPT.cli) console.log("[*]" + _cli);
	return _cli;
  },
  compiler: "avr-g++ -std=c++17",
  stdlib:[],
  out: function(_name)
  {
	var OPT = getOptions();
	if(OPT.elf) _name += ".elf";
	else _name += ".hex";
	return _name;
  },
  check: {
		"env": {
		"es6": true
		},
		"extends": "eslint:recommended",
		"rules": {
			"global-require": "error",
			"no-console": "error",
			"indent": "off",
			"linebreak-style": "off",
			"no-unused-vars": ["warn", { "vars": "all", "args": "after-used", "varsIgnorePattern": "setup|loop", "ignoreRestSiblings": false }],
			"no-redeclare": ["error", { "builtinGlobals": false }],
			"no-const-assign": "error",
		},
		"globals":
		{
			"undefined": false,
			"eval": false,
			"__njs_typeof": false,
			"require": false,
			"module": false,
			"__NJS_Object_Keys": false,
            "__NJS_Call_Function": false,
		}
	}
}

module.exports = ARDUINO;
