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
  name: "std",
  main: "test.cpp",
  compiler: "g++",
  stdlib: [],
  cli: function(compiler, preset, out, _in, option)
  {
    if(compiler == "cl" || compiler.indexOf("cl ") == 0)
    {
        if(preset == "none") return `${compiler} ${_in} /std:c++17 /D CL_WINDOWS=1 /I "${CONFIG.win_inc_ucrt}" "${CONFIG.win_lib_um}\\Uuid.Lib" "${CONFIG.win_lib_um}\\kernel32.Lib" "${CONFIG.win_lib_ucrt}\\libucrt.lib" /EHsc  ${COMPILER.LIBS} /o  ${out}`;
        else if(preset == "size") return `${compiler} ${_in} /std:c++17 /D CL_WINDOWS=1 /O1 /I "${CONFIG.win_inc_ucrt}" "${CONFIG.win_lib_um}\\Uuid.Lib" "${CONFIG.win_lib_um}\\kernel32.Lib" "${CONFIG.win_lib_ucrt}\\libucrt.lib" /EHsc ${COMPILER.LIBS} /o  ${out}`;
        else if(preset == "speed") return `${compiler} ${_in} /std:c++17 /D CL_WINDOWS=1 /Ox /I "${CONFIG.win_inc_ucrt}" "${CONFIG.win_lib_um}\\Uuid.Lib" "${CONFIG.win_lib_um}\\kernel32.Lib" "${CONFIG.win_lib_ucrt}\\libucrt.lib" /EHsc ${COMPILER.LIBS} /o  ${out}`;
    }
	  if(preset == "none")
	  {
		  return `${compiler} -std=c++17 "${_in}" ${option} -I ${extern}/lib/ -s ${COMPILER.LIBS} -o ${out}`;
	  }
	  else if(preset == "size")
	  {
		  return `${compiler} -std=c++17 "${_in}" ${option} -I ${extern}/lib/ -fno-rtti -fno-stack-protector -fomit-frame-pointer -s ${COMPILER.LIBS}  -o ${out}`;
	  }
	  else return `${compiler} -std=c++17 "${_in}" -I ${extern}/lib/ ${option} -s ${COMPILER.LIBS} -o ${out}`;
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
        "module": false,
        "require": false,
        "__NJS_Log_Console": false,
        "__NJS_Object_Keys": false,
        "__NJS_ARGS": false,
        "__NJS_Call_Function": false,
		"$ERROR": false,
    }
}
}

module.exports = TEST;
