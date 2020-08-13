/*
 * This file is part of NectarJS
 * Copyright (c) 2017-2020 Adrien THIERRY
 * http://nectarjs.com - https://www.linkedin.com/in/adrien-thierry-fr/
 *
 * sources : https://github.com/nectarjs/nectarjs/
 *
 * this program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * You can be released from the requirements of the license by purchasing
 * a commercial license. Buying such a license is mandatory as soon as you
 * develop commercial activities involving the NectarJS software without
 * disclosing the source code of your own applications. Visit http://seraum.com/
 * and feel free to contact us.
 *
 */
 
function replaceObjAddr(_code)
{
	var FUNCTION = [];

	var _searchReg = / *__NJS_Object_Set *\( *([a-zA-Z0-9_\-" ]*) *, *([a-zA-Z0-9_\-\(\)" ]*) *, *([a-zA-Z0-9_\-" ]*) *\)/g;
	var _searchFN = / *([a-zA-Z0-9_\-" ]*) * = __NJS_VAR\(__NJS_FUNCTION/g;
	
	var _allFN = _code.match(new RegExp(_searchFN));
	if(_allFN)
	{
		for(var i = 0; i < _allFN.length; i++)
		{
			var _localSearch = new RegExp(_searchFN);
			var _fn = _localSearch.exec(_allFN[i]);
			if(_fn);
			{
				FUNCTION.push(_fn[1]);
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
				if(_var[1] != "\"exports\"" && FUNCTION.indexOf(_var[2]) > -1)
				{	
					var _getObject = new RegExp("__NJS_Object_Get\\\(" + _var[1]+ ", " + _var[3] + "\\\)", "gm");
					_code = _code.replace(_getObject, _var[2]);
				}
			}
		}
	}
	return _code;
}
module.exports = replaceObjAddr;