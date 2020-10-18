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

var ESP32 =
{
    name: "esp32",
    main: "esp32.cpp",
    compiler: "idf.py",
    stdlib: [],
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
			"no-const-assign": "error",
        },
        "globals":
        {
			"undefined": false,
			"eval": false,
            "__njs_typeof": false,
            "Nectar": false,
            "module": false,
            "require": false,
            "__NJS_Log_Console": false,
            "__NJS_Object_Keys": false,
            "__NJS_ARGS": false,
            "__NJS_Call_Function": false,
            "JSON": false,
            "Object": false,
        },
    },
    cli: function(compiler, preset, out, _in, option)
    {
        return `${compiler} build`;
    },
    out: function(_name)
    {
        return _name + ".bind";
    },
    init: function(_folder)
    {
        copyDirSync(path.join(COMPILER.MAIN_PATH, "platform", "esp32"), _folder, true);
    },
    write: function(_content)
    {
        fs.writeFileSync(path.join(COMPILER.TMP_FOLDER, "esp32.cpp"), _content);
    }

}

module.exports = ESP32;
