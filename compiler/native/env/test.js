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
  main: "test.cpp",
  compiler: "g++",
  stdlib: [],
  cli: function(compiler, preset, out, _in, option)
  {
	  if(preset == "none")
	  {
		  return `${compiler} ${_in} ${option} -I ${extern}/lib/ -fpermissive -w -s ${COMPILER.LIBS} -o ${out}`;
	  }
	  else if(preset == "size")
	  {
		  return `${compiler} ${_in} ${option} -I ${extern}/lib/ -fno-exceptions -fno-rtti -fno-stack-protector -fomit-frame-pointer -fpermissive -w -s ${COMPILER.LIBS}  -o ${out}`;
	  }
	  else return `${compiler} ${_in} -I ${extern}/lib/ ${option} -fpermissive -w -s ${COMPILER.LIBS} -o ${out}`;
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
        "module": false,
        "require": false,
        "__NJS_Log_Console": false,
        "__NJS_ARGS": false,
    }
}
}

module.exports = STD;
