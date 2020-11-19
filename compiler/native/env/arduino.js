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

const TARGETS = {
	"mega": { args: "-DF_CPU=16000000UL -mmcu=atmega2560", variant: "mega" },
	"mega2560": { args: "-DF_CPU=16000000UL -mmcu=atmega2560", variant: "mega" },
	"mega1280": { args: "-DF_CPU=16000000UL -mmcu=atmega1280", variant: "mega" },
	"mega328p": { args: "-DF_CPU=16000000UL -mmcu=atmega328p", variant: "standard" },
	"uno": { args: "-DF_CPU=16000000UL -mmcu=atmega328p", variant: "standard" },
	"nano": { args: "-DF_CPU=16000000UL -mmcu=atmega328p", variant: "standard" },
	"nano2": { args: "-DF_CPU=16000000UL -mmcu=atmega168", variant: "standard" },
	"nano3": { args: "-DF_CPU=16000000UL -mmcu=atmega328p", variant: "standard" }
}

function getOptions (args) {
	const opts = { elf: false, cli: false };
	if (args["--option"] && args["--option"].argument) {
		for (const opt of args["--option"].argument.split(",")) {
			opts[opt] = true;
		}
	}
	return opts;
}

module.exports = {
	name: "arduino",
	main: "arduino.cpp",
	compiler: "avr-g++ -std=c++17",
	stdlib: [],
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
			"no-unused-vars": ["warn", {
				"vars": "all",
				"args": "after-used",
				"varsIgnorePattern": "setup|loop",
				"ignoreRestSiblings": false
			}],
			"no-const-assign": "error",
		},
		"globals": {
			"undefined": false,
			"eval": false,
			"__njs_typeof": false,
			"require": false,
			"module": false,
			"__NJS_Object_Keys": false,
			"__NJS_Call_Function": false,
		}
	},
	cli: function (compiler, preset, output, input, option, target, spec) {
		const { elf, cli } = getOptions(CLI.cli)
		const optionArg = CLI.cli["--option"] ? CLI.cli["--option"].argument : "";

		if (!TARGETS[target]) {
			console.log("[!] No target selected, switching to 'uno'");
			target = "uno";
		}
		const { args, variant } = TARGETS[target];

		let _cli = `${compiler} ${args} -DARDUINO_ARCH_AVR -w \
		-Os -fno-exceptions -fno-rtti -fno-stack-protector -fomit-frame-pointer \
		-ffunction-sections -fdata-sections -Wl,--gc-sections -I ${extern}/avr \
		-I ${extern}/arduino/avr/variants/${variant}/ \
		-I ${extern}/arduino/avr/cores/arduino \
		-I ${extern}/avr/include -I ${extern}/stlarduino \
		${extern}/stlarduino/ios.cpp ${extern}/arduino/avr/cores/arduino/abi.cpp \
		-fno-threadsafe-statics -lm ${COMPILER.LIBS} -o ${output} ${input} ${optionArg}`;

		if (!elf) _cli += `&& avr-objcopy -O ihex -R .eeprom ${output}`;
		if (cli) console.log("[*]" + _cli);
		return _cli;
	},
	out: name => `${name}.${getOptions().elf ? "elf" : "hex"}`
};
