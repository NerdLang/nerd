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
  main: "std.cpp",
  compiler: "g++",
  stdlib: ["console"],
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
			"quotes": [
				"error",
				"double"
			],
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
		"__njs_typeof":false,
		"require":false,
		"module": false,
		"console": false,
		}
	},
  cli: function(compiler, preset, out, _in, option)
  {
	  if(preset == "none")
	  {
		  return `${compiler} ${_in} -O1 ${option} -fpermissive -w -s  -o ${out}`;
	  }
	  else if(preset == "size")
	  {
		  return `${compiler} ${_in} -Os -fno-exceptions -fno-rtti -fno-stack-protector -fomit-frame-pointer ${option} -fpermissive -w -s  -o ${out}`;
	  }
	  else return `${compiler} ${_in} -Ofast ${option} -fpermissive -w -s  -o ${out}`;
  }
}

module.exports = NODE;