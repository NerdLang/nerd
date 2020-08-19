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
 
var fs = require("fs");
var path = require("path");
var exec = require("child_process").execSync;
var MAIN_PATH = path.resolve(path.join(__dirname, ".."));

var NODE = process.argv[0];

var TEST_PATH = path.join(MAIN_PATH, "tests", "NJS");

var error = false;
var errList = [];

var _list = fs.readdirSync(TEST_PATH);

for(var i = 0; i < _list.length; i++)
{
	try 
	{
		process.chdir(MAIN_PATH);
		console.log("[*] Testing: " + _list[i]);

		exec("\"" + NODE + "\" nectar.js --compiler clang++ --run \"" + path.join(TEST_PATH, _list[i]) + "\"");
		
		console.log("[+] Test passed: " + _list[i]);
	}
	catch(e)
	{
		error = true;
		errList.push(_list[i]);
		console.log("[!] Test error: " + _list[i]);
	}
}

if(error)
{
	console.log("[!] tests exited with errors");
	console.log("[ERRORS]");
	console.dir(errList);
	process.exit(1);
}
else 
{
	console.log("[*] tests exited without errors");
	process.exit(0);
}
