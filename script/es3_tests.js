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

var MAIN_TEST_PATH = path.join(MAIN_PATH, "tests", "ES3");

var walkSync = function(dir, filelist) 
{
    files = fs.readdirSync(dir);
	filelist = filelist || [];
    files.forEach(function(file) 
	{
		if (fs.statSync(dir + file).isDirectory()) 
		{
		  filelist = walkSync(dir + file + '/', filelist);
		}
		else {
		  filelist.push(dir + file);
		}
	});
	return filelist;
};

var _LIST = walkSync(MAIN_TEST_PATH + "/");

var error = false;
var errList = [];

process.chdir(MAIN_PATH);

for(var i = 0; i < _LIST.length; i++)
{
	try 
	{

		console.log("[*] Testing: " + path.basename(_LIST[i]));

		exec("\"" + NODE + "\" nectar.js --env test --run \"" + _LIST[i] + "\"");
		
		console.log("[+] Test passed: " + path.basename(_LIST[i]));
	}
	catch(e)
	{
		error = true;
		errList.push(path.basename(_LIST[i]));
		console.log("[!] Test error: " + path.basename(_LIST[i]));
	}
}

if(error)
{
	console.log("[!] tests exited with errors");
	console.log("[ERRORS]");
	console.dir(errList);
	console.log("" + errList.length + " / " + _LIST.length);
	process.exit(1);
}
else 
{
	console.log("[*] tests exited without errors");
	process.exit(0);
}