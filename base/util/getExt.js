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
 
module.exports = getExt;

function getExt(target)
{
  switch(target)
  {
    case "wasm":
      return ".wasm";
      break;
    case "asm-js":
      return ".asm.js";
      break;
    case "wast":
      return ".wast";
      break;
    case "win-x86-32":
    case "win-x86-64":
      return "-" + target + ".exe";
      break;
    case "nucleo-l432kc":
    case "nucleo-l152re":
    case "mac-osx":
    case "linux-x86-32":
    case "linux-x86-64":
    case "linux-arm32v7":
      return "-" + target + ".bin";
      break;
    case "arduino-uno":
      return "-" + target + ".hex";
      break;
    case "arduino-mega1280":
      return "-" + target + ".hex";
      break;
    case "arduino-mega2560":
      return "-" + target + ".hex";
      break;
    default:
      return ".bin";
      break;
  }
}
