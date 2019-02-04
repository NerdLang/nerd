/*
 * This file is part of NectarJS
 * Copyright (c) 2019 Adrien THIERRY
 * http://nectarjs.com - https://nectrium.com
 *
 * sources : https://github.com/nectarjs/nectarjs
 *
 * NectarJS
 * Copyright (C) 2019 Adrien THIERRY - Necrium
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

module.exports = genStdRequire;
function genStdRequire(src)
{
  if(src.indexOf('require("fs")') > -1)
  {
     if(CLIB.indexOf("stdio.h") < 0) CLIB.push("stdio.h");
     NCLIB.push("stdlib/fs.c");
  }
  if(src.indexOf('require("process")') > -1)
  {
     if(CLIB.indexOf("stdio.h") < 0) CLIB.push("stdio.h");
     NCLIB.push("stdlib/process.c");
  }
  if(src.indexOf('require("arduino")') > -1) NCLIB.push("stdlib/arduino.c");
  if(src.indexOf('require("arduino-lcd")') > -1) NCLIB.push("stdlib/arduino-lcd.c");

  src = src.replace(/require\("fs"\)/gi, "require(\"" + MAIN_PATH + "/base/libjs/fs.js\")");
  src = src.replace(/require\("process"\)/gi, "require(\"" + MAIN_PATH + "/base/libjs/process.js\")");
  src = src.replace(/require\("arduino"\)/gi, "require(\"" + MAIN_PATH + "/base/libjs/arduino.js\")");
  src = src.replace(/require\("arduino-lcd"\)/gi, "require(\"" + MAIN_PATH + "/base/libjs/arduino-lcd.js\")");

  return src;
}
