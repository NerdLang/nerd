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
 
function installModule(_name)
{
	try 
	{
		fs.mkdirSync("nectar_modules");
	}catch(e){}
	
	try 
	{
		fs.mkdirSync(".nectar");
	}catch(e){}
	
	var _zip = _name + ".zip"
	var _tmp = path.join(".nectar", _zip);
	var _dest = path.join("nectar_modules");
	
	const file = fs.createWriteStream(_tmp);
	
	var opt = 
	{
		"host": "modules.nectarjs.org",
		"path": "/" + _zip,
	}	
	
	function onError(_err)
	{
		console.log(_err);
		console.log("[!] Module " + _name + " does not exist");
	}
	
	function pipe(_res)
	{
		_res.pipe(file);
	}
	
	function onSuccess()
	{
		var unzip = new Zip(_tmp);
		unzip.extractAllTo(_dest, true);
		rmdir(_tmp, function() 
		{ 
			console.log("[+] Module " + _name + " installed"); 
		});
	}

	coreHttp.httpsUtil.httpReqPipe(opt, onError, pipe, onSuccess);
}

module.exports = installModule;