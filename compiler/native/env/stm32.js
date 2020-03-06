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

var STM32 =
{
  name: "stm32",
  base: "stm32.cpp",
  cli: "cp -r $(pwd)/extern/mbos/mbed-os $(dirname __IN__)/mbed-os\ && cp $(pwd)/extern/mbos/mbed-os.lib $(dirname __IN__)/mbed-os.lib && \
      cp $(pwd)/extern/mbos/mbed_settings.py $(dirname __IN__)/mbed_settings.py && \
      cp $(pwd)/profile/stm32.json $(dirname __IN__)/stm32.json  \
      && cd $(dirname __IN__) && __COMPILER__ compile --target __TARGET__ --toolchain GCC_ARM --profile stm32.json > res.txt && mv $(dirname __IN__)/BUILD/__TARGET__/GCC_ARM/$(basename $(dirname __IN__)).bin  __OUT__",
  compiler: "mbed",
  stdlib:["stm32"],
  check: "mbed.json",
}

module.exports = STM32;
