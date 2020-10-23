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

var WASM =
{
  name: "wasm",
  main: "std.cpp",
  compiler: "em++",
  stdlib: [{bind: "Nectar", module: "WASM"},"console", "Math", "JSON"],
  check: {
		"env": {
			"node": true,
			"es6": true
		},
		"extends": "eslint:recommended",
		"rules": {
			"no-console": "off",
			"indent": "off",
			"linebreak-style": "off",
			"no-unused-vars": ["warn", { "vars": "all", "args": "after-used", "ignoreRestSiblings": false }],
			"no-const-assign": "error",
		},
		"globals":
		{
			"undefined": false,
			"eval": false,
			"Nectar": false,
			"__njs_typeof": false,
			"console": false,
			"module": false,
			"require": false,
			"__NJS_Log_Console": false,
			"__NJS_Object_Keys": false,
			"__NJS_ARGS": false,
            "__NJS_Call_Function": false,
			"JSON": false,
		}
	},
	out: function(_name)
  {
		if(CLI.cli["--target"])
		{
			if(CLI.cli["--target"].argument == "js")  return _name + ".asm.js";
			else if(CLI.cli["--target"].argument == "wasm") return _name + ".wasm";
			else if(CLI.cli["--target"].argument == "html") return _name + ".html";
			else 
			{
				console.log("[!] Invalid target, expected js, wasm, html");
				process.exit(1);
			}
		}
	    return _name + ".wasm";
  },
  cli: function(compiler, preset, out, _in, option)
  {
		if(preset == "none")
		{
			return `${compiler} -D__NJS_REGISTER_SIZE=${COMPILER.REGISTER} ${_in} -O1 -w -s TOTAL_MEMORY=33554432 ${COMPILER.LIBS} -o ${out}`;
		}
		else if(preset == "size")
		{
			return `${compiler} -D__NJS_REGISTER_SIZE=${COMPILER.REGISTER} ${_in} -Os -fno-exceptions -fno-rtti -fno-stack-protector -fomit-frame-pointer -w -s TOTAL_MEMORY=33554432 ${COMPILER.LIBS} -o ${out}`;
		}
		else
		{
			return `${compiler} -D__NJS_REGISTER_SIZE=${COMPILER.REGISTER} ${_in} -O3 -w -s TOTAL_MEMORY=33554432 ${COMPILER.LIBS} -o ${out}`;
		}
  }
}

module.exports = WASM;
