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

var os = require("os");

var optim = "-Wl,--gc-sections";
if(os.type() == "Darwin") optim = "-Wl,-dead_strip"
var STD =
{
  name: "std",
  base: "std.cpp",
  cli: "__COMPILER__ __OPTION__ __IN__ -lpthread -ffunction-sections -fdata-sections " + optim + " -o __OUT__",
  compiler: "g++-8.1",
  stdlib: ["console"],
  check: "std.json",
}

module.exports = STD;
