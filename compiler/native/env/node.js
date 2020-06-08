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
			"semi": [
				"warn",
				"always"
			],
			"no-unused-vars": ["warn", { "vars": "all", "args": "after-used", "ignoreRestSiblings": false }],
			"no-use-before-define": ["error"],
			"no-undef": "error",
			"no-redeclare": ["error", { "builtinGlobals": false }],
		},
		"globals":
		{
			"__njs_typeof": false,
			"console": false,
			"module": false,
			"require": false,
			"__NJS_Log_Console": false,
			"__NJS_Object_Keys": false,
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

		if(preset == "none") return `${compiler} ${_stack} ${_in} /std:c++14 /D CL_WINDOWS=1 /I "${CONFIG.win_inc_ucrt}" "${CONFIG.win_lib_um}\\Uuid.Lib" "${CONFIG.win_lib_um}\\kernel32.Lib" "${CONFIG.win_lib_ucrt}\\libucrt.lib" /EHsc  ${COMPILER.LIBS} /o  ${out}`;
		else if(preset == "size") return `${compiler} ${_stack} ${_in} /std:c++14 /D CL_WINDOWS=1 /O1 /I "${CONFIG.win_inc_ucrt}" "${CONFIG.win_lib_um}\\Uuid.Lib" "${CONFIG.win_lib_um}\\kernel32.Lib" "${CONFIG.win_lib_ucrt}\\libucrt.lib" /EHsc ${COMPILER.LIBS} /o  ${out}`;
		else if(preset == "speed") return `${compiler} ${_stack} ${_in} /std:c++14 /D CL_WINDOWS=1 /Ox /I "${CONFIG.win_inc_ucrt}" "${CONFIG.win_lib_um}\\Uuid.Lib" "${CONFIG.win_lib_um}\\kernel32.Lib" "${CONFIG.win_lib_ucrt}\\libucrt.lib" /EHsc ${COMPILER.LIBS} /o  ${out}`;
	}

	var _uvParam = "";
	if(os.platform() == "win32") _uvParam = `-D_WIN32_WINNT=0x0600 -Wno-narrowing  -D_GNU_SOURCE -I${extern}/libuv/include/ -Iextern/libuv/src/ -D_CRT_SECURE_NO_DEPRECATE -D_CRT_NONSTDC_NO_DEPRECATE ${extern}/libuv/include/uv-win.h ${extern}/libuv/src/win/async.c ${extern}/libuv/src/win/atomicops-inl.h ${extern}/libuv/src/win/core.c  ${extern}/libuv/src/win/dl.c ${extern}/libuv/src/win/error.c  ${extern}/libuv/src/win/fs.c ${extern}/libuv/src/win/fs-event.c  ${extern}/libuv/src/win/getaddrinfo.c  ${extern}/libuv/src/win/getnameinfo.c  ${extern}/libuv/src/win/handle.c ${extern}/libuv/src/win/handle-inl.h ${extern}/libuv/src/win/internal.h ${extern}/libuv/src/win/loop-watcher.c ${extern}/libuv/src/win/pipe.c ${extern}/libuv/src/win/thread.c ${extern}/libuv/src/win/poll.c ${extern}/libuv/src/win/process.c ${extern}/libuv/src/win/process-stdio.c ${extern}/libuv/src/win/req.c ${extern}/libuv/src/win/req-inl.h ${extern}/libuv/src/win/signal.c ${extern}/libuv/src/win/snprintf.c ${extern}/libuv/src/win/stream.c ${extern}/libuv/src/win/stream-inl.h ${extern}/libuv/src/win/tcp.c ${extern}/libuv/src/win/tty.c ${extern}/libuv/src/win/timer.c ${extern}/libuv/src/win/udp.c ${extern}/libuv/src/win/util.c ${extern}/libuv/src/win/winapi.c ${extern}/libuv/src/win/winapi.h ${extern}/libuv/src/win/winsock.c ${extern}/libuv/src/win/winsock.h ${extern}/libuv/src/*.h ${extern}/libuv/src/*.c`;
	
	var _uvLib = "";
	if(os.platform() == "win32") _uvLib = "-lm  -ladvapi32 -liphlpapi -lpsapi -lshell32 -luser32  -luserenv -lwsock32 -lws2_32";
	
	if(_stack) _stack = "-Wl,--stack," + _stack;
    else _stack = "";

	  if(preset == "none")
	  {
		  return `${compiler} ${_stack} -std=c++11 ${_uvParam} ${_in} -O1 -fpermissive -w -s ${COMPILER.LIBS} ${_uvLib} && mv a.exe ${out}`;
	  }
	  else if(preset == "size")
	  {
		  return `${compiler} ${_stack} -std=c++11 ${_uvParam} ${_in} -Os -fno-exceptions -fno-rtti -fno-stack-protector -fomit-frame-pointer -fpermissive -w -s ${COMPILER.LIBS}  ${_uvLib} && mv a.exe ${out}`;
	  }
	  else
	  {
		var _opt = "-O";
            if(os.platform() == "darwin" || compiler.indexOf("clang") > -1) _opt += "3";
            else _opt += "fast";

            return `${compiler} ${_stack} -std=c++11 ${_uvParam} ${_in} ${_opt} -fpermissive -w -s ${COMPILER.LIBS}  ${_uvLib} && mv a.exe ${out}`;
	  }
  }
}

module.exports = NODE;
