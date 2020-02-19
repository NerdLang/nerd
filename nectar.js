#!/usr/bin/env node

/*
 * This file is part of NectarJS
 * Copyright (c) 2020 Adrien THIERRY
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

var VERSION = "0.2.2";

var AVAILABLE = ["linux_x64", "win32_x64"];
var DL = ["nectar-linux-x64-0-2-2.zip", "nectar-win-x64-0-2-2.zip"];
var DLHOST = "https://download.nectarjs.com/";

var os = require("os");
var platform = os.platform();
var arch = os.arch();

var target = platform + "_" + arch;

if(AVAILABLE.indexOf(target) < 0)
{
	console.log();
	console.log("[!] Your platform is not compatible yet: " + target);
	console.log("[!] Please open an issue: https://github.com/nectarjs/nectarjs");
	process.exit(1);
}

/*** if --install 
	download DL file and put it in a folder ./bin/ and unzip it

	else verify the executable and call it
***/





