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
 
//TODO for (NaN == NaN) -> false correctness, we need the -fno-finite-math-only flag with -Ofast

var os = require("os");

var STD =
{
    name: "std",
    main: "std.cpp",
    compiler: "g++",
    stdlib: ["console", {bind:"performance", module:"Performance"}, "Error", "RegExp", "Number", "Object", "Math", "JSON", "Array", "Date"],
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
        },
    },
    cli: function(compiler, preset, out, _in, option)
    {
		var _cachePath = path.join(process.cwd(), "..", "cached_" + COMPILER.ENV.name + "_" + os.platform + "_" + VERSION);
		var _precompiled = path.join(_cachePath, "nectar.o");

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
		
		if(!fs.existsSync(_precompiled))
		{
			console.log(`[+] Creating Nectar binary lib for ${COMPILER.ENV.name + "_" + os.platform + "_" + VERSION}`);
			try { fs.mkdirSync(_cachePath); } catch(e){};
			execSync(`${compiler} -std=c++17 -c nectar.cpp -Ofast -o "${_precompiled}"`);
			console.log("[+] Compiling with precompiled Nectar lib");
		}
		
        if(compiler == "cl" || compiler.indexOf("cl ") == 0)
        {
			console.log("[!] cl is not supported, please use g++, clang++, em++ or avr-g++");
			process.exit(1);
        }

		var _hashmap = "-D__Nectar__OBJECT_HASHMAP";
		if(CLI.cli['--no-object-hashmap']) _hashmap = "";
		
        if(_stack) _stack = "-Wl,--stack," + _stack;
        else _stack = "";
        
        var _sysVNetLibs = "";
        if(os.platform() == "sunos") _sysVNetLibs = "-lsocket -lnsl";

		var _cliOption = "";
		if(CLI.cli["--option"]) _cliOption = CLI.cli["--option"].argument;
		
		
		if(CLI.cli["--profile"])
		{
			if(!CLI.cli["--conserve"]) CLI.cli["--conserve"] = true;
			if(CLI.cli["--profile"].argument == "gen")
			{
				_cliOption += " -fprofile-generate";
				console.log("[*] Profiling data will be stored in: " + COMPILER.TMP_FOLDER);
			}
			else if(CLI.cli["--profile"].argument == "use")
			{
				_cliOption += " -fprofile-use";
				console.log("[*] Using profile data from: " + COMPILER.TMP_FOLDER);
			}
			else 
			{
				console.log("[!] Please use --profile with gen or use");
			}
		}
		
		var _files = `"${_precompiled}" "${_in}"`;
		if(os.platform == "win32") _files = `"${_in}" "${_precompiled}"`;
		
        if(preset == "none")
        {
            return `${compiler} ${_stack} -std=c++17 ${_files} -O1 -s ${COMPILER.LIBS} -lpthread -o "${out}" ${_sysVNetLibs} ${_cliOption}`;
        }
        else if(preset == "size")
        {
            return `${compiler} ${_stack} -std=c++17 ${_files} -lpthread -Os -fno-rtti -fno-stack-protector -fomit-frame-pointer -s ${COMPILER.LIBS} -o "${out}" ${_sysVNetLibs} ${_cliOption}`;
        }
        else
        {   
            var _opt = "-O";
            if(os.platform() == "darwin" || compiler.indexOf("clang") > -1) _opt += "3";
            else _opt += "fast";
			
			return `${compiler} ${_stack} -std=c++17 ${_files} ${_opt} -lpthread -s ${COMPILER.LIBS}  -o "${out}" ${_sysVNetLibs} ${_cliOption}`;
        }
    },
	write: function(_content, _in)
    {
		if(CLI.cli["--profile"] && CLI.cli["--profile"].argument == "use")
		{
			return;
		}
		
        fs.writeFileSync(_in, _content);
    }

}

module.exports = STD;
