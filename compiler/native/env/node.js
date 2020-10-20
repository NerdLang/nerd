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

var NODE =
{
  name: "node",
  main: "node.cpp",
  compiler: "g++",
  stdlib: ["console", "Object", "Math", "JSON"],
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
			"__njs_typeof": false,
			"console": false,
			"module": false,
			"require": false,
			"__NJS_Log_Console": false,
			"__NJS_Object_Keys": false,
			"__NJS_PLATFORM": false,
			"__NJS_ENV": false,			
            "__NJS_Call_Function": false,
			"__NJS_ARGS": false,
			"JSON": false,
			"Object": false,
		}
	},
  cli: function(compiler, preset, out, _in, option)
  {
	var _stack = 0;

	if(CLI.cli["--stack"])
	{
		try 
		{
			_stack = parseInt(CLI.cli["--stack"].argument);
		}
		catch(e)
		{
			console.log("[!] Error: --stack flags required a number, received -> " + CLI.cli["--stack"].argument);
			process.exit(1);
		}
	}
	if(compiler == "cl" || compiler.indexOf("cl ") == 0)
	{
		if(_stack) _stack = "/F " + _stack;
        else _stack = "";

		if(preset == "none") return `${compiler} ${_stack} ${_in} /D __NJS_REGISTER_SIZE=${COMPILER.REGISTER} /std:c++14 /D CL_WINDOWS=1 /I "${CONFIG.win_inc_ucrt}" "${CONFIG.win_lib_um}\\Uuid.Lib" "${CONFIG.win_lib_um}\\kernel32.Lib" "${CONFIG.win_lib_ucrt}\\libucrt.lib" /EHsc  ${COMPILER.LIBS} /o  ${out}`;
		else if(preset == "size") return `${compiler} ${_stack} ${_in} /D __NJS_REGISTER_SIZE=${COMPILER.REGISTER} /std:c++14 /D CL_WINDOWS=1 /O1 /I "${CONFIG.win_inc_ucrt}" "${CONFIG.win_lib_um}\\Uuid.Lib" "${CONFIG.win_lib_um}\\kernel32.Lib" "${CONFIG.win_lib_ucrt}\\libucrt.lib" /EHsc ${COMPILER.LIBS} /o  ${out}`;
		else if(preset == "speed") return `${compiler} ${_stack} ${_in} /D __NJS_REGISTER_SIZE=${COMPILER.REGISTER} /std:c++14 /D CL_WINDOWS=1 /Ox /I "${CONFIG.win_inc_ucrt}" "${CONFIG.win_lib_um}\\Uuid.Lib" "${CONFIG.win_lib_um}\\kernel32.Lib" "${CONFIG.win_lib_ucrt}\\libucrt.lib" /EHsc ${COMPILER.LIBS} /o  ${out}`;
	}
	
	var _hashmap = "-D__NJS__OBJECT_HASHMAP";
	if(CLI.cli['--no-object-hashmap']) _hashmap = "";
	
	var _uvParam = "";
	if(os.platform() == "win32") _uvParam = `-D_WIN32_WINNT=0x0600 -Wno-narrowing  -D_GNU_SOURCE -I${extern}/libuv/include/ -I${extern}/libuv/src/ -D_CRT_SECURE_NO_DEPRECATE -D_CRT_NONSTDC_NO_DEPRECATE ${extern}/libuv/src/*.h ${extern}/libuv/src/*.c ${extern}/libuv/src/win/*.h ${extern}/libuv/src/win/*.c`;
	
	var _uvLib = "-luv ";
	if(os.platform() == "win32") _uvLib = "-lm  -ladvapi32 -liphlpapi -lpsapi -lshell32 -luser32  -luserenv -lwsock32 -lws2_32";
	if(os.platform() == "sunos") _uvLib += "-lkstat -lsendfile -lsocket -lnsl";
	
	if(_stack) _stack = "-Wl,--stack," + _stack;
    else _stack = "";

	  if(preset == "none")
	  {
		  return `${compiler} ${_hashmap} -D__NJS_REGISTER_SIZE=${COMPILER.REGISTER} ${_stack} -std=c++17 ${_uvParam} ${_in} -O1 -s ${COMPILER.LIBS} ${_uvLib} -o a.exe && mv a.exe ${out}`;
	  }
	  else if(preset == "size")
	  {
		  return `${compiler} ${_hashmap} -D__NJS_REGISTER_SIZE=${COMPILER.REGISTER} ${_stack} -std=c++17 ${_uvParam} ${_in} -Os -fno-rtti -fno-stack-protector -fomit-frame-pointer -s ${COMPILER.LIBS}  ${_uvLib} -o a.exe && mv a.exe ${out}`;
	  }
	  else
	  {
		var _opt = "-O";
            if(os.platform() == "darwin" || compiler.indexOf("clang") > -1) _opt += "3";
            else _opt += "fast";

            return `${compiler} ${_hashmap} -D__NJS_REGISTER_SIZE=${COMPILER.REGISTER} ${_stack} -std=c++17 ${_uvParam} ${_in} ${_opt} -s ${COMPILER.LIBS}  ${_uvLib} -o a.exe && mv a.exe ${out}`;
	  }
  }
}

module.exports = NODE;
