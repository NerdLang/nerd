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
  name: "wasm",
  main: "std.cpp",
  compiler: "em++",
  stdlib: ["console", "Math"],
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
			"__NJS_ARGS": false,
		}
	},
	out: function(_name)
  {
		if(CLI.cli["--target"])
		{
			if(CLI.cli["--target"].argument == "js")  return _name + ".asm.js";
			else if(CLI.cli["--target"].argument == "wasm") return _name + ".wasm";
			else 
			{
				console.log("[!] Invalid target, expected js or wasm");
				process.exit(1);
			}
		}
	    return _name + ".wasm";
  },
  cli: function(compiler, preset, out, _in, option)
  {
		var _prefix = "./";
		var _source = "source ";
		var _script = path.join(NECTAR_PATH, "tools", "emsdk", "emsdk_env");

		if(os.platform() == "win32")
		{
			_prefix = "";
			_source = "";
			_script += ".bat";
		}
		else _script += ".sh";
		
		if(!fs.existsSync(_script))
		{
			console.log("[!] Please install EMSDK and compile again: nectar --installEMSDK");
			process.exit();
		}

		if(preset == "none")
		{
			return `${_source} ${_script} && ${compiler} ${_in} -O1 -fpermissive -w -s TOTAL_MEMORY=33554432 ${COMPILER.LIBS} -o ${out}`;
		}
		else if(preset == "size")
		{
			return `${_source} ${_script} && ${compiler} ${_in} -Os -fno-exceptions -fno-rtti -fno-stack-protector -fomit-frame-pointer -fpermissive -w -s TOTAL_MEMORY=33554432 ${COMPILER.LIBS} -o ${out}`;
		}
		else
		{
			return `${_source} ${_script} && ${compiler} ${_in} -O3 -fpermissive -w -s TOTAL_MEMORY=33554432 ${COMPILER.LIBS} -o ${out}`;
		}
  }
}

module.exports = NODE;