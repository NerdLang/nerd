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
 
module.exports = getTips;

function getTips(target, file)
{
  switch(target)
  {
    case "wasm":
      return "";
      break;
    case "asm-js":
      return "[*] Tips : run this file with node : 'node " + file + "', or embed it in a .html page with <script src=\"" + file + "\"></script>"
      break;
    case "wast":
      return "";
      break;
    case "win-x86-32":
    case "win-x86-64":
      return "[*] Tips : on Linux, you can run this .exe with Wine : 'wine " + file + "'"
      break;
    case "linux-x86-32":
    case "linux-x86-64":
    case "linux-arm32v7":
      return "[*] Tips : on Linux, don't forget to : 'chmod +x " + file + "'."
      break;
    case "arduino-uno":
      return "[*] Tips : avrdude -p ATMEGA328P -c arduino -P [COMPORT] -b 19200 -F -U flash:w:" + file;
      break;
    case "arduino-mega1280":
      return "[*] Tips : avrdude -p m1280 -c arduino -P [COMPORT] -b 57600 -F -U flash:w:" + file;
      break;
    case "arduino-mega2560":
      return "[*] Tips : avrdude -p m2560 -c wiring -P [COMPORT] -b 115200 -F -U flash:w:" + file;
      break;
    case "nucleo-l152re":
    case "nucleo-l432kc":
      return "[*] Connect your nucleo on your computer, and symple copy/paste " + file + " on the nucleo drive"
    default:
      return "";
      break;
  }
}
