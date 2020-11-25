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
 
function replaceObjAddr(_code)
{
	var Function = [];

	var _searchReg = / *__Nectar_Object_Set *\( *([a-zA-Z0-9_\-" ]*) *, *([a-zA-Z0-9_\-\(\)" ]*) *, *([a-zA-Z0-9_\-" ]*) *\)/g;
	var _searchFN = / *([a-zA-Z0-9_\-" ]*) * = NectarCore::VAR\(NectarCore::Enum::Type::Function/g;
	
	var _allFN = _code.match(new RegExp(_searchFN));
	if(_allFN)
	{
		for(var i = 0; i < _allFN.length; i++)
		{
			var _localSearch = new RegExp(_searchFN);
			var _fn = _localSearch.exec(_allFN[i]);
			if(_fn);
			{
				Function.push(_fn[1]);
			}
		}
	}

	var _searchObject = new RegExp(_searchReg);
	var _match = _code.match(_searchObject);
	if(_match)
	{
		for(var i = 0; i < _match.length; i++)
		{
			var _localSearch = new RegExp(_searchReg);
			var _var = _localSearch.exec(_match[i]);
			if(_var);
			{
				if(_var[1] != "\"exports\"" && Function.indexOf(_var[2]) > -1)
				{	
					var _getObject = new RegExp("__Nectar_Object_Get\\\(" + _var[1]+ ", " + _var[3] + "\\\)", "gm");
					_code = _code.replace(_getObject, _var[2]);
				}
			}
		}
	}
	return _code;
}
module.exports = replaceObjAddr;