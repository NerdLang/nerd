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
 
module.exports = Flash;
var fs = require("fs");
var path = require("path");

function Flash(from, to, target, verb)
{
  switch(target)
  {
    case "uno":
      execFlashArduino(from, to, "ATMEGA328P", "arduino", "19200", verb)
      break;
    case "mega1280":
      execFlashArduino(from, to, "m1280", "arduino", "57600", verb)
      break;
    case "mega2560":
      execFlashArduino(from, to, "m2560", "wiring", "115200", verb)
      break;
    case "nucleo-l152re":
    case "nucleo-l432kc":
      execFlashSTM32(from, to);
      break;
    default:
      console.log("Nothing to do for target : " + target);
      break;
  }
}

function execFlashArduino(from, to, model, driver, bauds, verb)
{
  var spawn = require('child_process').spawn;
  var _flash = spawn('avrdude', ['-p', model, "-c", driver, "-P", to, "-b", bauds, "-F", "-U", "flash:w:"+from]);

  _flash.stdout.on('data', function(data)
  {
    if(verb) process.stdout.write(data.toString());
  });

  _flash.stderr.on('data', function(data)
  {
    if(verb) process.stdout.write(data.toString());
  });

  _flash.on('error', function(err)
  {
    console.log("[!] Error :");
    console.log(err)
  });

  _flash.on('close', function(code)
  {
    console.log("[+] Flashed")
  });
}

function execFlashSTM32(from, to)
{
  try
  {
    fs.writeFileSync(path.join(to, from), fs.readFileSync(from));
    console.log("[+ Flashed]");
  }
  catch(e)
  {
    console.log("[!] Your file is compiled, but an error occured while flashing, please try again.")
  }

}
