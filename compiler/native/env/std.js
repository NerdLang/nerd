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

var os = require("os");

var STD =
{
    name: "std",
    main: "std.cpp",
    compiler: "g++",
    stdlib: ["console", "Object", "Math", "JSON"],
    check: 
    {
        "env": 
        {
            "es6": true
        },
        "extends": "eslint:recommended",
        "rules": 
        {
            "strict": "global",
            "no-console": "off",
            "indent": "off",
            "linebreak-style": "off",
            "no-unused-vars": ["warn", { "vars": "all", "args": "after-used", "ignoreRestSiblings": false }],
            "no-redeclare": ["error", { "builtinGlobals": false }],
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
            "__NJS_Object_Stringify": false,
            "__NJS_Call_Function": false,
            "__NJS_ARGS": false,
            "__NJS_ENV": false,
            "__NJS_PLATFORM": false,
            "JSON": false,
            "Object": false,
        },
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

            if(preset == "none") return `${compiler} ${_stack} "${_in}" /std:c++14 /D CL_WINDOWS=1 /I "${CONFIG.win_inc_ucrt}" "${CONFIG.win_lib_um}\\Uuid.Lib" "${CONFIG.win_lib_um}\\kernel32.Lib" "${CONFIG.win_lib_ucrt}\\libucrt.lib" /EHsc  ${COMPILER.LIBS} /o  "${out}"`;
            else if(preset == "size") return `${compiler}  ${_stack} "${_in}" /std:c++14 /D CL_WINDOWS=1 /O1 /I "${CONFIG.win_inc_ucrt}" "${CONFIG.win_lib_um}\\Uuid.Lib" "${CONFIG.win_lib_um}\\kernel32.Lib" "${CONFIG.win_lib_ucrt}\\libucrt.lib" /EHsc ${COMPILER.LIBS} /o  "${out}"`;
            else if(preset == "speed") return `${compiler}  ${_stack} "${_in}" /std:c++14 /D CL_WINDOWS=1 /Ox /I "${CONFIG.win_inc_ucrt}" "${CONFIG.win_lib_um}\\Uuid.Lib" "${CONFIG.win_lib_um}\\kernel32.Lib" "${CONFIG.win_lib_ucrt}\\libucrt.lib" /EHsc ${COMPILER.LIBS} /o  "${out}"`;
        }

        if(_stack) _stack = "-Wl,--stack," + _stack;
        else _stack = "";
        
        var _sysVNetLibs = "";
        if(os.platform() == "sunos") _sysVNetLibs = "-lsocket -lnsl";

        if(preset == "none")
        {
            return `${compiler} ${_stack} -std=c++11 "${_in}" -O1 -fpermissive -w -s ${COMPILER.LIBS} -o "${out}" ${_sysVNetLibs}`;
        }
        else if(preset == "size")
        {
            return `${compiler} ${_stack} -std=c++11 "${_in}" -Os -fno-rtti -fno-stack-protector -fomit-frame-pointer -fpermissive -w -s ${COMPILER.LIBS} -o "${out}" ${_sysVNetLibs}`;
        }
        else
        {   
            var _opt = "-O";
            if(os.platform() == "darwin" || compiler.indexOf("clang") > -1) _opt += "3";
            else _opt += "fast";

            return `${compiler} ${_stack} -std=c++11 "${_in}" ${_opt} -fpermissive -w -s ${COMPILER.LIBS}  -o "${out}" ${_sysVNetLibs}`;
        }
    }

}

module.exports = STD;
