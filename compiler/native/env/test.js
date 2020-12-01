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

var os = require("os");

var TEST =
{
  name: "test",
  main: "test.cpp",
  compiler: "g++",
  stdlib: [],
  cli: function(compiler, preset, out, _in, option)
  {
	var _cachePath = path.join(process.cwd(), "..", "cached_" + COMPILER.ENV.name + "_" + os.platform + "_" + VERSION);
	var _precompiled = path.join(_cachePath, "nectar.o");
	if(!fs.existsSync(_precompiled))
	{
		console.log(`[+] Creating Nectar binary lib for ${COMPILER.ENV.name + "_" + os.platform + "_" + VERSION}`);
		try { fs.mkdirSync(_cachePath); } catch(e){};
		execSync(`${compiler} -std=c++17 -c nectar.cpp -Ofast -o "${_precompiled}"`);
		console.log("[+] Compiling with precompiled Nectar lib");
	}
	
    if(compiler == "cl" || compiler.indexOf("cl ") == 0)
    {
        if(preset == "none") return `${compiler} ${_in} /std:c++17 /D CL_WINDOWS=1 /I "${CONFIG.win_inc_ucrt}" "${CONFIG.win_lib_um}\\Uuid.Lib" "${CONFIG.win_lib_um}\\kernel32.Lib" "${CONFIG.win_lib_ucrt}\\libucrt.lib" /EHsc  ${COMPILER.LIBS} /o  ${out}`;
        else if(preset == "size") return `${compiler} ${_in} /std:c++17 /D CL_WINDOWS=1 /O1 /I "${CONFIG.win_inc_ucrt}" "${CONFIG.win_lib_um}\\Uuid.Lib" "${CONFIG.win_lib_um}\\kernel32.Lib" "${CONFIG.win_lib_ucrt}\\libucrt.lib" /EHsc ${COMPILER.LIBS} /o  ${out}`;
        else if(preset == "speed") return `${compiler} ${_in} /std:c++17 /D CL_WINDOWS=1 /Ox /I "${CONFIG.win_inc_ucrt}" "${CONFIG.win_lib_um}\\Uuid.Lib" "${CONFIG.win_lib_um}\\kernel32.Lib" "${CONFIG.win_lib_ucrt}\\libucrt.lib" /EHsc ${COMPILER.LIBS} /o  ${out}`;
    }
	
	var _cliOption = "";
	if(CLI.cli["--option"]) _cliOption = CLI.cli["--option"].argument;
	
	  var _files = `"${_precompiled}" "${_in}"`;
	  if(os.platform == "win32") _files = `"${_in}" "${_precompiled}"`;
	  
	  if(preset == "none")
	  {
		  return `${compiler} -std=c++17 ${_files} ${option} -I ${extern}/lib/ -s ${COMPILER.LIBS} -o ${out} ${_cliOption}`;
	  }
	  else if(preset == "size")
	  {
		  return `${compiler} -std=c++17 ${_files} ${option} -I ${extern}/lib/ -fno-rtti -fno-stack-protector -fomit-frame-pointer -s ${COMPILER.LIBS}  -o ${out} ${_cliOption}`;
	  }
	  else return `${compiler} -std=c++17 ${_files} -I ${extern}/lib/ ${option} -s ${COMPILER.LIBS} -o ${out} ${_cliOption}`;
  },
  check: {
    "env": {
        "es6": true
    },
    "extends": "eslint:recommended",
    "rules": {
        "strict": "global",
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
		"__Nectar_Log_Console": false,
		"__Nectar_InitVar": false,
		"__Nectar_Object_Keys": false,
		"__Nectar_Object_Stringify": false,
		"__Nectar_Call_Function": false,
		"__NJS_ARGS": false,
		"__NJS_ENV": false,
		"__NJS_PLATFORM": false,
		"__Nectar_typeof": false,
		"__Nectar_THIS": false,
		"__Nectar_instanceof": false,
		"__Nectar_delete": false,
		"__Nectar_EQUAL_VALUE_AND_TYPE": false,
			"__Nectar_NOT_EQUAL_VALUE_AND_TYPE": false,
		"JSON": false,
		"Object": false,
		"isNaN": false,
		"Array": false,
		"$ERROR": false,
    }
}
}

module.exports = TEST;
