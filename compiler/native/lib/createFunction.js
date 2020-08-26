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
	var _matchThis = new RegExp(/(| |{|,)__NJS_THIS([\.(";)]|$)/);
	var _return = ";return __NJS_Create_Undefined();}";
	var _returnThis = ";return __NJS_THIS;}";
	var _searchFN = new RegExp(/function +(.[a-zA-Z0-9_\-]*) *\((.*)\)/);
	var _index = _code.search(_searchFN);
	while(_index > -1)
	{
		var _genFN = "__NJS_FN_" + RND();
		var _genVAR = "NJS::VAR_" + RND();

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

		if(COMPILER.INFO.SCOPE[_match[1]] && COMPILER.INFO.SCOPE[_match[1]].fast == true && COMPILER.INFO.SCOPE[_match[1]].param.length == 1 && COMPILER.INFO.SCOPE[_match[1]].param[0] == _match[2].length)
		{
			_FAST = true;
			for(var i = 0; i < _match[2].length; i++)
			{
				if(_match[2][i].length > 0)
				{
					if(i != 0) _var += ",";
					_var += "int " + _match[2][i];
				}
			}
			_parameters = _var;
			//var _replaceCall = new RegExp(`${_match[1]}(?![a-zA-Z_])`, "g");
			//_code = _code.replace(_replaceCall, `__NJS_Call_Fast_Function(${_match[1]}`);
		}
		else
		{
			_variadic = true;
			_parameters = "vector<var> _NJS_VARARGS";
			for(var i = 0; i < _match[2].length; i++)
			{
				if(_match[2][i].length > 0)
				{
					_getVar += `var ${_match[2][i]}; if(_NJS_VARARGS.size() > ${i}) ${_match[2][i]} = _NJS_VARARGS[${i}];`;
				}
			}
		}
		/* TODO: more check to switch from call to fixed_call
		else if(COMPILER.INFO.CALL[_match[1]] && (COMPILER.INFO.CALL[_match[1]].length > 1 || COMPILER.INFO.CALL[_match[1]].length != _match[2].length))
		{
			_variadic = true;
			_parameters = "vector<var> _NJS_VARARGS";
			for(var i = 0; i < _match[2].length; i++)
			{
				if(_match[2][i].length > 0)
				{
					_getVar += `var ${_match[2][i]}; if(_NJS_VARARGS.size() > ${i}) ${_match[2][i]} = _NJS_VARARGS[${i}];`;
				}
			}
		}
		else 
		{
			for(var i = 0; i < _match[2].length; i++)
			{
				if(_match[2][i].length > 0)
				{
					if(i != 0) _var += ",";
					_var += "NJS::VAR " + _match[2][i];
				}
			}
			_parameters = _var;
			var _replaceCall = new RegExp(`__NJS_Call_Function\\\(${_match[1]}(?![a-zA-Z_])`, "g");
			_code = _code.replace(_replaceCall, `__NJS_Call_Fixed_Function(${_match[1]}`);
		}
		*/


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
							else if(_code.indexOf("'SCOPED_FUNCTION';") > -1) _catch = "=";
							
							var _constructor = `${_match[1]}["prototype"]["constructor"] = __NJS_Create_Var_Scoped_Anon(return __NJS_THIS;);`;
							var _fn = "{" + _getVar + " var __NJS_THIS = __NJS_Create_Object();" + _code.substring(_start + 1, _end);
							var _fnThis = "{" + _getVar + " var __NJS_THIS = __NJS_Create_Object();" + _code.substring(_start + 1, _end);

							if(_code.search(_matchThis) > -1) _fn = _fnThis;

							COMPILER.DECL.push("var " + _match[1] +";");

							var _formated = `__NJS_DECL_FUNCTION<NJS::VAR (${_parameters})>* ${_genFN} = new __NJS_DECL_FUNCTION<NJS::VAR (${_parameters})>([${_catch}]( ${_parameters} ) -> NJS::VAR ${_fn} ${_return} );`;
							_formated += _match[1] + "=NJS::VAR(NJS::Enum::Type::FUNCTION, " + _genFN + ");";
							if(CLI.cli["--debug"]) _formated += `${_match[1]}.get().f->code = R"(Function ${_match[1]}(${_match[2]}) ${_code.substring(_start, _end)}})";`
							else _formated += `${_match[1]}.get().f->code = R"([Function: ${_match[1]}])";`

							if(_match[1].indexOf("__MODULE") != 0)
							{
								var _genNew = "__NEW_" + _genFN;
								var _addNew = `__NJS_DECL_FUNCTION<NJS::VAR (${_parameters})>* ${_genNew} = new __NJS_DECL_FUNCTION<NJS::VAR (${_parameters})>([${_catch}]( ${_parameters} ) -> NJS::VAR ${_fnThis}; __NJS_Object_Construct(__NJS_THIS, __NJS_Object_Clone(__NJS_Object_Get("prototype", ${_match[1]}))); ${_constructor}; return ${_match[1]}["prototype"]["constructor"](); } );`;
								_addNew += "var __NEW_" + _match[1] + "=NJS::VAR(NJS::Enum::Type::FUNCTION, " + _genNew + ");";

								_formated += _addNew;
							}
							
							_code = [_code.slice(0, _index), _formated, _code.slice(_end + 1)].join('');
						}
						else 
						{
							// FAST CALL HERE
							var _fn = _code.substring(_start, _end);
							COMPILER.DECL.push(`__NJS_FAST_INT ${_match[1]}(${_parameters})${_fn}; return 0;}`);
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