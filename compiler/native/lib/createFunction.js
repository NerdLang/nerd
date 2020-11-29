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
 
function createFunction(_code, _scope)
{	
	var _return = ";return NectarCore::Global::undefined;}";
	var _searchFN = new RegExp(/function +(.[a-zA-Z0-9_\-]*) *\((.*)\)/);
	var _index = _code.search(_searchFN);
	while(_index > -1)
	{
		var _genFN = "__NJS_FN_" + RND();
		var _genVAR = "NectarCore::VAR_" + RND();

		var _var = "";
		var _count = 0;
		var _start = -1;
		var _end = -1;
	
		let _match = _searchFN.exec(_code);
		_match[2] = _match[2].split(",");
		var _getVar = "";
		var _parameters = "";
		var _variadic = false;

		var _FAST = false;

		if(!CLI.cli["--no-fast-function"] && COMPILER.INFO.SCOPE[_match[1]] && COMPILER.INFO.SCOPE[_match[1]].fast == true && COMPILER.INFO.SCOPE[_match[1]].param.length == 1 && COMPILER.INFO.SCOPE[_match[1]].param[0] == _match[2].length)
		{
			_FAST = true;
			for(var i = 0; i < _match[2].length; i++)
			{
				if(_match[2][i].length > 0)
				{
					if(i != 0) _var += ",";
					_var += "double " + _match[2][i];
				}
			}
			_parameters = _var;
		}
		else
		{
			
			_variadic = true;
			_parameters = "var __Nectar_THIS, NectarCore::VAR* __Nectar_VARARGS, int __Nectar_VARLENGTH";

			if(COMPILER.INFO.SCOPE[_match[1]] && COMPILER.INFO.SCOPE[_match[1]].param.length == 1)
			{
				for(var i = 0; i < _match[2].length; i++)
				{
					if(_match[2][i].length > 0)
					{
						if(i <= COMPILER.INFO.SCOPE[_match[1]].param.length)
						{
							_getVar += `var ${_match[2][i]} = __Nectar_VARARGS[${i}];`;
						}
						else _getVar += `var ${_match[2][i]}; if(__Nectar_VARLENGTH > ${i}) ${_match[2][i]} = __Nectar_VARARGS[${i}];`;
					}
				}
			}
			else 
			{
				for(var i = 0; i < _match[2].length; i++)
				{
					if(_match[2][i].length > 0)
					{
						_getVar += `var ${_match[2][i]}; if(__Nectar_VARLENGTH > ${i}) ${_match[2][i]} = __Nectar_VARARGS[${i}];`;
					}
				}
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
					
					_end = i;
					_count--;
					if(_count == 0)
					{

						if(!_FAST)
						{
							var _catch = "";
							if(_scope) _catch = "&";
							if(_code.indexOf("\"SCOPED_FUNCTION\";") > -1) 
							{
								_code = _code.replace(/'SCOPED_Function';/g, "                  ");
								_catch = "&";
							}
							_catch = "&";
							var _constructor = `${_match[1]}["prototype"]["constructor"] = __Nectar_Create_Var_Scoped_Anon(return __Nectar_THIS;);`;
							var _fn = "{" + _getVar + _code.substring(_start + 1, _end);

							COMPILER.DECL.push("var " + _match[1] +";");
							
							var __STR_MARKER = "__LIT" + RND();
							var _formated = `NectarCore::Type::function_t* ${_genFN} = new NectarCore::Type::function_t([${_catch}]( ${_parameters} ) -> NectarCore::VAR ${_fn} ${_return} );`;
							_formated += _match[1] + "=NectarCore::VAR(NectarCore::Enum::Type::Function, " + _genFN + ");";
							if(CLI.cli["--debug"]) _formated += `((NectarCore::Class::Function*)${_match[1]}._ptr)->code = R"${__STR_MARKER}(Function ${_match[1]}(${_match[2]}) ${_code.substring(_start, _end )}})${__STR_MARKER}";`
							//else _formated += `((NectarCore::Class::Function*)${_match[1]}._ptr)->code = R"([Function: ${_match[1]}])";`

							_code = [_code.slice(0, _index), _formated, _code.slice(_end + 1)].join('');
						}
						else 
						{
							// FAST CALL HERE
							var _fn = _code.substring(_start, _end);
							COMPILER.DECL.push(`__Nectar_FAST_INT ${_match[1]}(${_parameters})${_fn}; return 0;}`);
							_code = [_code.slice(0, _index), _code.slice(_end + 1)].join('');
						}

						break;
					}
				}
		}
		_index = _code.search(_searchFN);
	}
	_code = replaceObjAddr(_code);
	return _code;
}
module.exports = createFunction;