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

var getExt = function(target)
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
module.exports = getExt;