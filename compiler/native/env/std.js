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
  stdlib: ["console", "Math"],
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
        //"no-undef": "error",
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
}
}

module.exports = STD;
