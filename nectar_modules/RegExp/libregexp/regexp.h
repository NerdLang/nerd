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
 
#include <regex>

function __Nectar_RegExp_Test(_search)
{
 	if( std::regex_match ( (std::string)_search, std::regex((std::string)__Nectar_THIS["__Nectar_Internal_Expression"], std::regex::ECMAScript) ) ) return __Nectar_Boolean_TRUE;
	else return __Nectar_Boolean_FALSE;
}

function __Nectar_RegExp_Exec(_search)
{
	var _res = __NJS_Create_Array();
	std::string s = (std::string)_search;
	std::smatch m;
 	while(std::regex_search ( s, m, std::regex((std::string)__Nectar_THIS["__Nectar_Internal_Expression"], std::regex::ECMAScript) ))
	{
		int i = 0;
		for(auto x:m)
		{
			_res[i] = (std::string)x;
			i++;
		}
		_res["index"] = (double)m.position();
		_res["input"] = _search;
		_res["groups"] = NectarCore::Global::undefined;
		
		s = m.suffix().str();
	}
	return _res;
}

/*
function __Nectar_RegExp_StringMatch(_search, _re)
{
	var _res = __NJS_Create_Array();
	std::string s = (string)_search;
	std::smatch m;
 	while(std::regex_search ( s, m, std::regex((string)_re, std::regex::ECMAScript) ))
	{
		for(auto x:m) ((NectarCore::Class::Array*)_res.data.ptr)->value.push_back((string)x);
		s = m.suffix().str();
	}
	return _res;
}
*/