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
https://api.github.com/repos/ARMmbed/mbed-os/zipball/mbed-os-6.1.0
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

	  return `${compiler} compile -t ${COMPILER.TARGET} --toolchain GCC_ARM --profile profile/stm32.json > res.txt && mv ./BUILD/${COMPILER.TARGET}/GCC_ARM/${COMPILER.TARGET}.bin  ${out}`;
  },
  prepare: function(_folder)
    {
        copyDirSync(path.join(NECTAR_PATH, "extern", "stm32"), _folder, true);
    },
  compiler: "mbed",
  stdlib:["stm32"],
  check: {
      "env": {
          "node": true
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
            "no-undef": "error",
            "no-redeclare": ["error", { "builtinGlobals": false }],
      },
      "globals":
      {
        "__njs_typeof":false,
        "stm32": false,
        "module": false,
        "__NJS_Object_Keys": false,
        "__NJS_Call_Function": false,
      }
  }
}

module.exports = STM32;
