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
 
function initModule(_author, _name)
{
	try 
	{
		fs.mkdirSync("nectar_modules");
	} catch(e){}
	
	var _dest = path.join("nectar_modules", _name);
	try 
	{
		fs.mkdirSync(_dest);
	}
	catch(e)
	{
		console.log("[!] An error occured while trying to create the module folder: " + _name);
		console.log(e);
		process.exit(-1);
	}
	
	var _pkg = fs.readFileSync(path.join(NECTAR_PATH, "base", "squel", "package.json")).toString();
	
	_pkg = _pkg.replace(/{{AUTHOR}}/g, _author).replace(/{{MODULE_NAME}}/g, _name)

	fs.writeFileSync(path.join(_dest, "package.json"), _pkg);
	fs.appendFileSync(path.join(_dest, "index.js"), "// Write your module code here");
	console.log("[+] Module " + _name + " correctly initialized in " + _dest);
}

module.exports = initModule;