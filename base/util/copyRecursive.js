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
 
var copyRecursiveSync = function(src, dest) 
{
	if(!fs.existsSync(src))
	{
			console.log("[!] Warning: " + src + " doesn't exist");
			return;
	}
	if(fs.lstatSync( src ).isDirectory())
	{
		var _newDest = path.dirname(dest);
		copyDirSync(src, _newDest, true);
	}
	else 
	{
		var _path = [];

		var _newDest = path.dirname(dest);

		_path.push(_newDest);

		while(path.dirname(_newDest) != _newDest)
		{
			_newDest = path.dirname(_newDest);
			if(_newDest.indexOf(NECTAR_PATH) == 0)
			{
			  _path.push(_newDest);
			}
		}

		for(var i = _path.length; i > -1; i--)
		{
			try 
			{
			  fs.mkdirSync(_path[i]);
			}
			catch(e){}
		}

		fs.copyFileSync(src, dest); 
	}
};

module.exports = copyRecursiveSync;
