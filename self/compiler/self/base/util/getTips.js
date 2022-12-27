/*
	Copyright (c) 2021 NerdLang - Adrien THIERRY and contributors

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.

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
