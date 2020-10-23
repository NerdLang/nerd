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

var STM32 =
{
  name: "stm32",
  main: "stm32.cpp",
  cli: function(compiler, preset, out, _in, option)
  {
    if(!COMPILER.TARGET) 
    {
      console.log("[!] Error: please specify a target with --target");
      process.exit(1);
    }
    
    var _mbosSrc = path.join(extern, "stm32", "mbed-os", "nectar");
    copyDirSync(COMPILER.TMP_FOLDER, _mbosSrc, true);

    var _profile = "SIZE";
    if(COMPILER.preset == "speed") _profile = "SPEED";

	  return `cd ${path.join(extern, "stm32")} && ${compiler} compile -m ${COMPILER.TARGET} --profile ${path.join(extern, "stm32", "profile", _profile + ".json")} -t GCC_ARM > stm32_debug_res.txt && mv ${path.join(extern, "stm32", "BUILD", COMPILER.TARGET, "GCC_ARM-" + _profile)}/stm32.bin ${out}`;
  },
  clean: function()
  {
    var _mbosSrc = path.join(extern, "stm32", "mbed-os", "nectar");
    rmdir(_mbosSrc);
  },
  compiler: "mbed",
  stdlib:[{bind: "Nectar", module: "stm32"}],
  check: {
      "env": {
          "node": true
      },
      "extends": "eslint:recommended",
      "rules": {
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
        "__njs_typeof":false,
        "Nectar": false,
        "module": false,
        "__NJS_Object_Keys": false,
        "__NJS_Call_Function": false,
        "__NJS_Log_Console": false,
      }
  }
}

module.exports = STM32;
