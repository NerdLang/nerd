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
 
function createAnon(_code, _scope)
{	
	var _matchThis = new RegExp(/(| |{|,)__NJS_THIS([\.(";)]|$)/);
	var _return = "return __NJS_Create_Undefined();}";
	var _searchAnonFN = new RegExp(/(var)* *([\[\]a-zA-Z0-9_"]*) *= *function +\(([a-zA-Z0-9_\-, ]*)\)/);
	var _index = _code.search(_searchAnonFN);

	while(_index > -1)
	{
		var _var = "";
		var _count = 0;
		var _start = -1;
		var _end = -1;
		var _genFN = "__NJS_FN_" + RND();
		var _genVAR = "__NJS_VAR_" + RND();
		
		var _match = _searchAnonFN.exec(_code);
		_match[3] = _match[3].split(",");
		var _getVar = "";
		for(var i = 0; i < _match[3].length; i++)
		{
			if(_match[3][i].length > 0)
			{
				_getVar += `var ${_match[3][i]}; if(__NJS_VARARGS.size() > ${i}) ${_match[3][i]} = __NJS_VARARGS[${i}];`;
			}
		}

		for(var i = _index; i < _code.length; i++)
		{
				if(_code[i] == "{")
				{
						if(_start == -1) _start = i;
						_count++;
				}
				else if(_code[i] == "}")
				{
					var _catch = "";
					if(_scope) _catch = "=";
					else if(_code.indexOf("'SCOPED_FUNCTION';") > -1) _catch = "=";
					
					_end = i;
					_count--;
					if(_count == 0)
					{
						
						var _fn = "{" + _getVar + _code.substring(_start + 1, _end);
						var _fnThis = "{" + _getVar + " var __NJS_THIS = __NJS_Create_Object();" + _code.substring(_start + 1, _end);

						if(_code.indexOf("'__NJS_CLASS_ANON__';"))
						{
							_code.replace("'__NJS_CLASS_ANON__';", "");
						}
						else if(_code.search(_matchThis) > -1) _fn = _fnThis;
						
						var _formated = "";

						if(_match[1]) COMPILER.DECL.push(`var ${_match[2]};`);
						if(_match[2]) _formated += _match[2] + " = ";
						_formated += "__NJS_VAR(__NJS_FUNCTION, new function<__NJS_VAR (vector<var>)> ([" + _catch + "](vector<var> __NJS_VARARGS) -> __NJS_VAR" + _fn + os.EOL + _return + "));";
						_code = [_code.slice(0, _index), _formated, _code.slice(_end + 1)].join('');		
						break;
					}
				}
		}
		_index = _code.search(_searchAnonFN);
	}
	_code = replaceObjAddr(_code);
	return _code;
}
module.exports = createAnon;