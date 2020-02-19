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

/*** REQUIRE STD LIBS ***/
var fs = require("fs");
var https = require("https");
var path = require("path");
var spawn = require("child_process").spawnSync;

/*** REQUIRE NECTAR LIBS ***/
var parseCli = require("./lib/cli/cliParser");

/*** PARSE CLI ***/
var CLI = parseCli(process.argv);

/*** CHECK CLI ERRORS ***/
if(CLI.error)
{
	console.log(CLI.msg);
	process.exit(1);
}

var AVAILABLE = ["linux_x64", "win32_x64"];
var DL = ["nectar-linux-x64-0_2_2", "nectar-win-x64-0_2_2.exe"];
var DLHOST = "https://download.nectarjs.com/";

var os = require("os");
var platform = os.platform();
var arch = os.arch();

var target = platform + "_" + arch;
var file_to_dl = AVAILABLE.indexOf(target);

if(file_to_dl < 0)
{
	console.log();
	console.log("[!] Your platform is not compatible yet: " + target);
	console.log("[!] Please open an issue: https://github.com/nectarjs/nectarjs");
	process.exit(1);
}
var target_dir = path.join(__dirname, "bin");
var target_file = path.join(target_dir, DL[file_to_dl]);

if(CLI.cli["--install"])
{
	try 
	{
		fs.mkdirSync(target_dir);
	}
	catch(e){}

	const dest = fs.createWriteStream(target_file);
	console.log("[+] Downloading " + DL[file_to_dl]);
	
	const request = https.get(DLHOST + DL[file_to_dl], function(response) {
	response.pipe(dest);
	response.on("end", function()
	{
	 console.log("[*] NectarJS successfully installed");
	});
	}).on("error", function(_err)
	{
			console.log(_err);
			process.exit(1);
	});
}
else 
{
	if(!fs.existsSync(target_file))
	{
		console.log("[!] Please install NectarJS first with: nectar --install");
		process.exit(1);
	}
	else 
	{
		var _args = process.argv.splice(2);
		var _exec = spawn(target_file, _args, {stdio: [process.stdin, process.stdout, process.stderr]});
	}
}




