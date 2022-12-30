/*
	Copyright (c) 2021 NerdLang - Adrien THIERRY and contributors

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.

*/

var isVariable = require("./check/isVariable.js");
var isNumber = require("./check/isNumber.js");
var isString = require("./check/isString.js");
var isBoolean = require("./check/isBoolean.js");

function verifyExpression(_exp, _inst, _env)
{
	for(var i = 0; i < _env.FLOW[_inst].length; i++)
	{
		if(_env.FLOW[_inst][i] == "new")
		{
			_env.FLOW[_inst][i] = "";
			_env.FLOW[_inst][i+1] = "((NerdCore::Class::Function*)" + _env.FLOW[_inst][i+1] + ".data.ptr)->New"
		}
	}

	for(var z = 0; z < _exp.length; z++)
	{
		if(RESERVED.indexOf(_exp[z]) < 0 && BOOLEAN_KEYWORD.indexOf(_exp[z]) < 0 && isVariable(_exp[z]).check)
		{
			if( (!_exp[ z - 1] || _exp[ z - 1] != ".") && (!_exp[ z + 1] || _exp[ z + 1] != ":" ) && !varExists(_exp[z], _env))
			{
				if(_env.MAP[_inst][z])
				{
					error(`[!] Unknown variable: ${_exp[z]} line:${_env.MAP[_inst][z].line + 1} position:${_env.MAP[_inst][z].position}${os.EOL}=> ${array_of_code[_env.MAP[_inst][z].line]}`);
				}
				else
				{
					error(`[!] Unknown variable: ${_exp[z]}`);
				}
			}
		}
		if(_exp[z] == "__NERD_Multi_Line_Quote")
		{
			_env.FLOW[_inst][z + 2] = _exp[z + 2].slice(1, _exp[z + 2].length - 1)
		}
	}
}

function checkLogicalState(_token, _next, _env, _ast)
{
	var _logicalState = getLogical(_env);

	if(_logicalState.DO)
	{
		if(_token == "}")
		{
			if(_next != "WHILE")
			{
				return { error: true, message: "Unexpected token, waiting for while"};
			}
		}
		else if(_token == "WHILE")
		{
			return { error: false };
		}
		else
		{
			return { error: true, message: "Unexpected token, waiting for while"};
		}
	}
	
	if(_logicalState.TRY)
	{
		if(_token == "}")
		{
			if(_next != "CATCH")
			{
				return { error: true, message: "Unexpected token, waiting for catch"};
			}
		}
		else if(_token == "CATCH")
		{
			return { error: false };
		}
		else
		{
			return { error: true, message: "Unexpected token, waiting for catch"};
		}
	}
	if(_logicalState.FUNCTION)
	{
		if(_token == "}")
		{
			if(_ast && _ast[1] && (_ast[1] == "SEMI" || _ast[1] == ";"))
			{
				//good 
			}
			else if(_next && (_next == "SEMI" || _next == ";"))
			{
				// good
			}
			else
			{
				//return { error: true, message: "Unexpected token, waiting for ';' after "};
			}
		}
	}
	return { error: false };
}

function getFunctionThis(_flow, param, _env, _inst)
{
	var _end = -1;
	for(var i = 0; i < _flow.length; i++)
	{
		if(_flow[i] == "[" || _flow[i] == "\"" || isVariable(_flow[i], _env).check)
		{
			_end = i;
		}
		else if(_flow[i] == "(")
		{
			break;
		}
	}
	return _end;
}

function getFunctionArgs(_flow, param, _env, _inst, _call)
{
	var _return = {};
	
	var _this = getFunctionThis(_flow, param, _env, _inst);
	_return["this"] = "__NERD_THIS";
	
	if(_this > -1)
	{
		if(_this == 0)
		{
			_return["this"] = _flow[0];
		}
		else
		{
			_return["this"] = _flow.slice(0, _this).join(" ");
		}
	}

	var _parenthesis = 0;
	_return["args"] = [];
	for(var i = 0; i < _flow.length; i++)
	{
		if(_flow[i] == "(") _parenthesis++;
		else if(_flow[i] == ")") _parenthesis--;
		else if(_parenthesis > 0)
		{
			
			if(_flow[i][0] == '\"')
			{
				_return["args"].push(_flow[i]);
			}
			else if(_flow[i] == "new" && _flow[i+1])
			{
				var _end = 0;
				var _argP = 0;
				for(var j = i; j < _flow.length; j++)
				{
					if(_flow[j] == "(")
					{
						_argP++;
					}
					else if(_flow[j] == ")")
					{
						_argP--;
						if(_argP == 0)
						{
							_end = j + 1;
							break;
						}
					}
				}
				_new = "__NERD_FUNCTION(" + _flow[i+1] + ")->New" + _flow.slice(i + 2, _end).join(" ");
				_env.FLOW[_inst] = _flow.slice(0, i).concat(_new, ..._flow.slice(_end));
			}
			else if(param && isVariable(_flow[i]) && varExists(_flow[i], _env))
			{
				_return["args"].push(_flow[i]);
			}
			else if(param )
			{
				_return["args"].push(_flow[i]);
			}
			else if(!param)
			{
				_return["args"].push(_flow[i]);
			}
		}
		else if(_parenthesis < 0)
		{
			break;
		}
	}
	return _return;
}

function _forgeArray(_var, _flow, _start, _inst, _env, _nested)
{
	if(!_nested)
	{
		_env.FLOW[_inst][_start - 1] = "new NerdCore::Class::Array()";
		_env.FLOW[_inst] = _env.FLOW[_inst].slice(0, _start);
		_env.FLOW[_inst].push(";");
	}

	if(_flow[_start] != "]" )
	{
		var a = 0;
		for(var i = _start; i < _flow.length - 1; i+=2)
		{
			if(_flow[i] == "[" && _flow[i + 1] == "]")
			{
				_env.FLOW[_inst].push(_var + "[" + a + "]");
				_env.FLOW[_inst].push("=");
				_env.FLOW[_inst].push("new NerdCore::Class::Array()");
				_env.FLOW[_inst].push(";");
			}
			else if(_flow[i] == "{")
			{
				var _end = -1;
				var _objBracket = 0;
				for(var k = i; k < _flow.length; k++)
				{
					if(_flow[k] == "{")
					{
						_objBracket++;
					}
					else if(_flow[k] == "}")
					{
						_objBracket--;
						if(_objBracket == 0)
						{
							_end = k;
							break;
						}
					}
				}

				_env.FLOW[_inst].push(_var + "[" + a + "]");
				_env.FLOW[_inst].push("=");
				_env.FLOW[_inst] = _env.FLOW[_inst].concat(_flow.slice(i, _end));
				forgeObject(_flow, i+6, _inst, _env);
				
				i = _end; // we jump to the end of this object
			}
			else if(_flow[i] == "[")
			{
				_env.FLOW[_inst].push(_var + "[" + a + "]");
				_env.FLOW[_inst].push("=");
				_env.FLOW[_inst].push("new NerdCore::Class::Array()");
				_env.FLOW[_inst].push(";");
				forgeArray( _var + "[" + a + "]", _flow, i+1, _inst, _env, true);
				
				var _endArrayIndex = -1;
				var _indArr = 1;
				for(var z = i+1; z < _flow.length; z++)
				{
					if(_flow[z] == "[")
					{
						_indArr++;
					}
					else if(_flow[z] == "]")
					{
						_indArr--;
						if(_indArr == 0)
						{
							_endArrayIndex = z;
							break;
						}
					}
				}
				if(_endArrayIndex > -1)
				{
					i += _endArrayIndex;
				}
			}
			else if(_flow[i] != "]" && _flow[i] != ",")
			{
					
				if(_env.LAMBDA[_flow[i]])
				{
					var _l = _env.LAMBDA[_flow[i]];
					_l.env.REGISTER = _l.env.REGISTER.concat(_env.REGISTER);
					for(var k = 0; k < _l.env.FLOW.length; k)
					{
						k = verifyFlow(_l.env.AST[k], _l.env.FLOW[k], k, _l.env.FLOW, _l.env);
					}

					for(var j = 0; j < _l.env.FLOW.length; j++)
					{
						_env.FLOW[_inst].push( _l.env.FLOW[j].join(" ")  );
					}
					
				}
				else if(isVariable(_flow[i]).check)
				{
					if(!varExists(_flow[i], _env))
					{
						error(`[!] Variable or token undefined: ${_flow[i]} line:${_env.MAP[_inst][i].line + 1} position:${_env.MAP[_inst][i].position}${os.EOL}=> ${array_of_code[_env.MAP[_inst][i].line]}`);
					}
				}

				_env.FLOW[_inst].push(_var + "[" + a + "]");
				_env.FLOW[_inst].push("=");
				_env.FLOW[_inst].push(_flow[i]);
				_env.FLOW[_inst].push(";");
			}
			a++;
		}
	}
}

function _forgeObject(_var, _flow, _start, _inst, _env)
{
	if(typeof _var != "object")
	{
		_var = [_var];
	}

	//var newFlow = _env.FLOW[_inst].slice(0, _start - 1);
	//newFlow.push("((NerdCore::Class::Function*)Object.data.ptr)->New()");
	//newFlow.push(";");

	for(var f = _start; f < _env.FLOW[_inst].length; f+=4)
	{
		if(_env.FLOW[_inst][f+1] && _env.FLOW[_inst][f+1] == ":" /*&& (_env.FLOW[_inst][f+2] != "}" && _env.FLOW[_inst][f+2] != "," )*/ )
		{
			_env.FLOW[_inst][f] = 
			_env.FLOW[_inst][f+1] = ",";
			if(_env.FLOW[_inst][f + 2] && isVariable(_env.FLOW[_inst][f + 2]).check)
			{
				if(_env.LAMBDA[_env.FLOW[_inst][f + 2]])
				{
					var _l = _env.LAMBDA[_env.FLOW[_inst][f + 2]];
					_l.env.REGISTER = _l.env.REGISTER.concat(_env.REGISTER);
					for(var i = 0; i < _l.env.FLOW.length; i)
					{
						i = verifyFlow(_l.env.AST[i], _l.env.FLOW[i], i, _l.env.FLOW, _l.env);
					}

					for(var j = 0; j < _l.env.FLOW.length; j++)
					{
						newFlow.push( _l.env.FLOW[j].join(" ")  );
					}
					
				}
				else if(!varExists(_env.FLOW[_inst][f + 2], _env))
				{
					error(`[!] Variable or token undefined: ${_env.FLOW[_inst][f + 2]} line:${_env.MAP[_inst][f+2].line + 1} position:${_env.MAP[_inst][f+2].position}${os.EOL}=> ${array_of_code[_env.MAP[_inst][f+2].line]}`);
				}
			}
			
			if(_env.FLOW[_inst][f + 2] && _env.FLOW[_inst][f + 2] == "{")
			{
				if(isVariable(_env.FLOW[_inst][f]).check)
				{
					_var.push("[\"" + _env.FLOW[_inst][f] + "\"]");
					newFlow.push(_var.join("") + " = new NerdCore::Class::Object();");
				}
				else
				{
					_var.push("[" + _env.FLOW[_inst][f] + "]");
					newFlow.push(_var.join("") + " = new NerdCore::Class::Object();");
				}

				if(_env.FLOW[_inst][f + 3] != ",")
				{
					f--;
				}
			}
			else if(_env.FLOW[_inst][f + 2] && _env.FLOW[_inst][f + 2] == "[")
			{
				if(isVariable(_env.FLOW[_inst][f]).check)
				{
					_var.push("[\"" + _env.FLOW[_inst][f] + "\"]");
					newFlow.push(_var.join("") + " = new NerdCore::Class::Array();");
				}
				else
				{
					_var.push("[" + _env.FLOW[_inst][f] + "]");
					newFlow.push(_var.join("") + " = new NerdCore::Class::Array();");
				}
				
				var _endArray = -1;
				var _count = 0;

				for(var indArray = f+2; indArray < _env.FLOW[_inst].length - 1; indArray++)
				{
					if(_env.FLOW[_inst][indArray] == "[")
					{
						_count++;
					}
					else if(_env.FLOW[_inst][indArray] == "]")
					{
						_count--;

						if(_count == 0)
						{
							_endArray = indArray;
							break;
						}
					}
				}
				
				
				if(_endArray > -1)
				{
					var _virtualFlow = _env.FLOW[_inst].slice(f+2, _endArray + 1 );
					var _newFlowArray = {LAMBDA: _env.LAMBDA, FLOW:[[]]};
					forgeArray(_var.join(""), _virtualFlow, 1, 0, _newFlowArray, true)
					newFlow.push(_newFlowArray.FLOW[0].join(""));
				}
				
				while(_env.FLOW[_inst][f + 3] != "," && f < _env.FLOW[_inst].length)
				{
					f++;
				}
				_var.pop();
			}
			else 
			{
				if(isVariable(_env.FLOW[_inst][f]).check)
				{
					newFlow.push(_var.join("") + "[\"" + _env.FLOW[_inst][f] + "\"] = " + _env.FLOW[_inst][f + 2]);
					
					var _bracket = f + 3;
					var _closing = -1;
					while(_env.FLOW[_inst][_bracket] == "[")
					{
						newFlow.push("[");
						_closing = _bracket + 1;
						while(_env.FLOW[_inst][_closing] != "]" && _closing < _env.FLOW[_inst].length)
						{
							_closing++;
						}
						if(_closing != _bracket + 1)
						{
							verifyExpression(_env.FLOW[_inst].slice(_bracket+1, _closing), _inst, _env);
							newFlow.push(_env.FLOW[_inst].slice(_bracket+1, _closing).join(" "));
						}
						newFlow.push("]");
						
						_bracket ++;
					}
					
					newFlow.push(";");
					
				}
				else newFlow.push(_var.join("") + "[" + _env.FLOW[_inst][f] + "] = " + _env.FLOW[_inst][f + 2] + ";");
			}
		}
		else
		{
			if(_env.FLOW[_inst][f] == "}" || _env.FLOW[_inst][f] == ",")
			{
				if(_env.FLOW[_inst][f] == "}")
				{
					_var.pop();
				}
				f-=3;
			}
		}
	}
	_env.FLOW[_inst] = newFlow;
}

function forgeArray(_flow, _start, _inst, _env)
{
	if(_flow[_start] == "[" && _flow[_start + 1] == "]")
	{
		_flow[_start] = "new NerdCore::Class::Array(";
		_flow[_start + 1] = ")";
		return;
	}
	var _brack = 0;
	for(var i = _start; i < _flow.length; i++)
	{
		if(_flow[i] == "[")
		{
			_brack++;
			_flow[i] = "new NerdCore::Class::Array({";
		}
		else if(_flow[i] == "]")
		{
			_brack--;
			_flow[i] = "})";
		}
		if(_brack == 0)
		{
			return i;
		}
		else if(_brack == 1)
		{
			if(_flow[i] == "{")
			{
				i = forgeObject(_flow, i, _inst, _env);
				_flow[i] = "})";
			}
			else if(_flow[i] == "[")
			{
				if(_flow[i + 1] == "]")
				{
					_flow[i] = "new NerdCore::Class::Array(";
					_flow[i + 1] = ")";
					i++;
				}
				else
				{
					i = forgeArray(_flow, i, _inst, _env);
					_flow[i] = ")";
				}
			}
			else if(_env.LAMBDA[_flow[i]])
			{
				var _l = _env.LAMBDA[_flow[i]];
				_l.env.REGISTER = _l.env.REGISTER.concat(_env.REGISTER);
				
				for(var k = 0; k < _l.env.FLOW.length; k)
				{
					k = verifyFlow(_l.env.AST[k], _l.env.FLOW[k], k, _l.env.FLOW, _l.env);
				}
				
				var _lambdaBody = "";
				if(_l.env.FLOW[_l.env.FLOW.length-1][0] == "}")
				{
					_l.env.FLOW[_l.env.FLOW.length-1] = ["return NerdCore::Global::null;", "}", ")", ";"];
				}
				for(var jj = 0; jj < _l.env.FLOW.length; jj++)
				{
					_lambdaBody +=  _l.env.FLOW[jj].join(" ");
				}
				_flow[0] = _lambdaBody + _flow[0];
			}
		}
	}
}

function forgeObject(_flow, _start, _inst, _env)
{
	if(_flow[_start] == "{" && _flow[_start + 1] == "}")
	{
		_flow[_start] = "new NerdCore::Class::Object(";
		_flow[_start + 1] = ")";
		return;
	}
	var _brack = 0;
	if(_flow[_start + 2] == ":")
	{
		for(var i = _start; i < _flow.length; i++)
		{
			if(_flow[i] == "{")
			{
				_brack++;
				_flow[i] = "new NerdCore::Class::Object({";
			}
			else if(_flow[i] == "}")
			{
				_brack--;
			}
			if(_brack == 0)
			{
				if(_flow[i] == "}")
				{
				_flow[i] = "})";
				}
				return i;
			}
			else if(_brack == 1)
			{
				if(_flow[i] == ":")
				{
					_flow[i] = ",";
					if(_flow[i - 1][0] != "\"")
					{
						_flow[i - 1] = "\"" + _flow[i - 1] + "\"";
					}
					_flow[i - 1] = "{" + _flow[i - 1];
					// if nested object
					if(_flow[i + 1] == "{")
					{
						if(_flow[i + 2] == "}")
						{
							_flow[i + 1] = "new NerdCore::Class::Object(";
							_flow[i + 2] = ")}";
							i += 2;
						}
						else 
						{
							i = forgeObject(_flow, i+1, _inst, _env);
							_flow[i] = "})";
						}
						
					}
					
					else
					{
						
						if(_env.LAMBDA[_flow[i + 1]])
						{
							var _l = _env.LAMBDA[_flow[i + 1]];
							_l.env.REGISTER = _l.env.REGISTER.concat(_env.REGISTER);
							
							_flow[i + 1] = "var(" + _flow[i + 1] + ")";
							
							for(var k = 0; k < _l.env.FLOW.length; k)
							{
								k = verifyFlow(_l.env.AST[k], _l.env.FLOW[k], k, _l.env.FLOW, _l.env);
							}
							
							var _lambdaBody = "";
							if(_l.env.FLOW[_l.env.FLOW.length-1][0] == "}")
							{
								_l.env.FLOW[_l.env.FLOW.length-1] = ["return NerdCore::Global::null;", "}", ")", ";"];
							}
							for(var jj = 0; jj < _l.env.FLOW.length; jj++)
							{
								_lambdaBody +=  _l.env.FLOW[jj].join(" ");
							}
							_flow[0] = _lambdaBody + _flow[0];
						}
						else if(_flow[i + 1] && isVariable(_flow[i + 1]).check && !varExists(_flow[i + 1], _env).error)
						{
							if(_flow[i + 2] == "[")
							{
								var _acc = 0;
								i++;
								while(++i && i < _flow.length)
								{
									if(_flow[i] == "[")
									{
										_acc++;
									}
									else if(_flow[i] == "]")
									{
										_acc--;
									}
									if(_acc == 0)
									{
										break;
									}
								}
							}
						}
						
						else if(_flow[i + 1] == "[")
						{
							if(_flow[i + 2] == "]")
							{
								_flow[i + 1] = "new NerdCore::Class::Array(";
								_flow[i + 2] = ")}";
								i += 2;
								continue;
							}
							else
							{
								i = forgeArray(_flow, i+1, _inst, _env);
								_flow[i] = ")}";
							}
						}
						
						if(_flow[i + 1] != "}")
						{
							_flow[i + 1] = _flow[i + 1] + "}";
							if(_flow[i] != ",")
							{
								_flow[i + 1] += ",";
							}
						}
					}
					
				}
			}
		}
	}
}

var _NO_THIS = ["if", "else", "while", "for", "while", "typeof", "type_of", "size_of", "length_of", "catch"];
var _NO_CALL = ["require", "function"];
var checkCalls = function(_eq, _flow, _inst, _env)
{
	var _callTree = [];
	var _current = 0;
	var _lastThis;
	for(var i = 0; i < _flow.length; i++)
	{
		var _start = -1;
		var _end = -1;
		var _par = 0;
		if(_flow[i] == "(")
		{
			_par++;
			_start = i - 1;
			var _end = -1;
			for(var j = i+1; j < _flow.length; j++)
			{
				if(_flow[j] == "(")
				{
					_par++;
				}
				if(_flow[j] == ")")
				{
					_par--;
				}
				if(_par == 0)
				{
					_end = j;
					break;
				}
			}
			if(_end != -1)
			{
				var _var = i-1;
				while(--_var > -1)
				{
					if(_flow[_var] == "]" || _flow[_var] == "[" || _flow[_var][0] == "\"" || isVariable(_flow[_var], _env).check)
					{
						// nothing to do
					}
					else
					{
						break;
					}
				}
				_var++;
				if(_NO_CALL.indexOf(_flow[_var]) < 0)
				{
					// FORGE LAMBDAS
					for(var a = 0; a < _env.FLOW[_inst].length; a++)
					{
						if(isVariable(_env.FLOW[_inst][a]).check)
						{
							if(_env.LAMBDA[_env.FLOW[_inst][a]])
							{
								var _l = _env.LAMBDA[_env.FLOW[_inst][a]];
								_l.env.REGISTER = _l.env.REGISTER.concat(_env.REGISTER);
								
								for(var k = 0; k < _l.env.FLOW.length; k)
								{
									k = verifyFlow(_l.env.AST[k], _l.env.FLOW[k], k, _l.env.FLOW, _l.env);
								}
								
								var _lambdaBody = "";
								if(_l.env.FLOW[_l.env.FLOW.length-1][0] == "}")
								{
									_l.env.FLOW[_l.env.FLOW.length-1] = ["return NerdCore::Global::null;", "}", ")", ";"];
								}
								for(var jj = 0; jj < _l.env.FLOW.length; jj++)
								{
									_lambdaBody +=  _l.env.FLOW[jj].join(" ");
								}

								_env.FLOW[_inst-1].push(_lambdaBody);
							
							}
						}
					}
					
					var _args = getFunctionArgs(_flow.slice(_var, _end + 1), true, _env, _inst, true);					
					if(_args.this == "[")
					{
						if(_lastThis)
						{
							_args.this = _lastThis;
						}
						else
						{
							_args.this == "__NERD_THIS";
						}
					}
					else
					{
						_lastThis = _args.this;
					}
					// forge arrays
					for(var a = 0; a < _env.FLOW[_inst].length; a++)
					{
						if(_env.FLOW[_inst][a] == "[" && _env.FLOW[_inst][a-1] && (_env.FLOW[_inst][a-1] == "(" || _env.FLOW[_inst][a-1] == ","))
						{
							var _brack = 1;
							for(var b = a+1; b < _env.FLOW[_inst].length; b++)
							{
								if(_env.FLOW[_inst][b] == "[")
								{
									_brack++;
								}
								else if(_env.FLOW[_inst][b] == "]")
								{
									_brack--;
								}
								if(_brack == 0)
								{
									a = forgeArray(_env.FLOW[_inst], a, _inst, _env)
									break;
								}
							}
						}
						
					}
					
					if(_NO_THIS.indexOf(_args.this) < 0)
					{
						_flow[i] = _flow[i] + _args.this;
						if(_args.args.length > 0)
						{
							_flow[i] += ","
						}
					}
					for(var a = 0; a < _args.args.length; a+=2)
					{
						if(RESERVED.indexOf(_args.args[a]) < 0 && isVariable(_args.args[a]).check && !varExists(_args.args[a], _env))
						{
							error(`[!] Unknown variable or token: ${_args.args[a]} line:${_env.MAP[_inst][_eq + a].line + 1} position:${_env.MAP[_inst][_eq + a].position}${os.EOL}=> ${array_of_code[_env.MAP[_inst][_eq + a].line]}`);
						}

					}
				}
			}
		}
	}

	return _inst + 1;

}

function verifyFlow(_ast, _flow, _inst, _scope, _env, _main)
{
	if(_ast.length < 1)
	{
		return _inst + 1;
	}
	for(var z = 0; z < _flow.length; z++)
	{
		if(_flow[z] == ".")
		{
			_scope[_inst] = _scope[_inst].slice(0, z-1);
			_scope[_inst].push(_flow[z-1]);
			
			for(var v = z; v < _flow.length; v++)
			{
				if(_flow[v] == ".")
				{
					_scope[_inst].push("[");
					_scope[_inst].push("\"" + _flow[v+1] + "\"");
					_scope[_inst].push("]");
					v++;
				}
				else
				{
					_scope[_inst].push(_flow[v]);
				}
			}
			break;
		}
	}
	_flow = _scope[_inst];

	for(var i = 0; i < _flow.length; i++)
	{
		if(_flow[i] == "this")
		{
			_flow[i] = "__NERD_THIS";
		}
	}

	var _next;
	if(_scope[_inst+1] && _scope[_inst+1][0])
	{
		_next = _scope[_inst+1][0];
	}
	var _logicalError = checkLogicalState(_ast[0], _next, _env, _ast);
	if(_logicalError.error)
	{
		error(`[!] ${_logicalError.message}: ${_flow[0]} line:${_env.MAP[_inst][0].line + 1} position:${_env.MAP[_inst][0].position}${os.EOL}=> ${array_of_code[_env.MAP[_inst][0].line]}`);
	}

	switch(_flow[0])
	{
		case "var":
			if(RESERVED.indexOf(_flow[1]) > -1)
			{
				error(`[!] ${_flow[1]} is a reserved keyword: ${_flow[1]} line:${_env.MAP[_inst][1].line + 1} position:${_env.MAP[_inst][1].position}${os.EOL}=> ${array_of_code[_env.MAP[_inst][1].line]}`);
			}

			if(_flow[2] != "=")
			{
				addVar(_flow[1], _env);
				return _inst + 1;
			}
			else if(_flow[2] == "=")
			{
				var _existsVar =  checkVarExists(_flow[1], _env, _flow);
				if(_existsVar.error)
				{
					error(`[!] ${_existsVar.message}: line:${_env.MAP[_inst][1].line + 1} position:${_env.MAP[_inst][1].position}${os.EOL}=> ${array_of_code[_env.MAP[_inst][1].line]}`);
				}

				if(_flow[3] == "function")
				{
					var _newFlow = [_flow[0], _flow[1], _flow[2], "__NERD_Create_Var_Scoped_Copy_Anon_With_Ref", "(" + _flow[1] + ",{"];
					var _args = getFunctionArgs(_flow, false, _env, _inst);
					addVar(_flow[1], _env, 1, _inst);
					nextScope(_env);
					addLogical("FUNCTION", _env);
					_scope[_inst] = _newFlow;
					var item = 0;
					for(var a = 0; a < _args.args.length; a+=2)
					{
						addVar(_args.args[a], _env, 5, _inst);
						_scope[_inst] = _scope[_inst].concat(["var", _args.args[a], ";", "if", "(", "__NERD_VARLENGTH", ">", item,")", _args.args[a], "=", `__NERD_VARARGS[${item}];`]);
						item++;
					}

					//verifyExpression(_flow.slice(6), _inst, _env);
					return _inst + 1;
				}
				else if(_flow[3] == "[" )
				{
					addVar(_flow[1], _env);
					forgeArray(_flow, 3, _inst, _env);
					return _inst + 1;
				}
				else if(_flow[3] == "{}")
				{
					addVar(_flow[1], _env);
					forgeObject(_flow, 3, _inst, _env);
					return _inst + 1;
				}
				else if(_flow[3] == "{")
				{
					addVar(_flow[1], _env);
					forgeObject(_flow, 3, _inst, _env);
					return _inst + 1;
				}
				else if(_flow[3] == "exit")
				{
					error(`[!] Invalid use of exit: line:${_env.MAP[_inst][eq].line + 1} position:${_env.MAP[_inst][eq].position}${os.EOL}=> ${array_of_code[_env.MAP[_inst][eq].line]}`);
				}
				else if(_flow[3] == "require")
				{
					addVar(_flow[1], _env);
					verifyExpression(_flow.slice(3), _inst, _env);
					var _args = getFunctionArgs(_flow, true, _env, _inst);
					if(_args.args.length != 1)
					{
						error(`[!] Invalid number of parameter, only one required: ${_flow[3]} line:${_env.MAP[_inst][3].line + 1} position:${_env.MAP[_inst][3].position}${os.EOL}=> ${array_of_code[_env.MAP[_inst][3].line]}`);
					}
					var _required = genRequire(COMPILER.PATH, _args.args[0].slice(1, _args.args[0].length - 1), _env, _flow[1]);
					if(_required.add)
					{
						COMPILER.DECL += _required.code;
					}
					_scope[_inst] = _flow.slice(0, 3);
					_scope[_inst].push(_required.module);
					_scope[_inst].push(";");
				}
				else
				{
					addVar(_flow[1], _env);
					verifyExpression(_flow.slice(3), _inst, _env);
					if(_flow[3] != "arguments" && _flow[3] != "Array")
					{
						checkCalls(3, _flow, _inst, _env);
					}
				}
				
				return _inst + 1;
			}
		break;

			nextScope(_env);
				
		break;
		
		case "}":
			if(getLogical(_env).FUNCTION)
			{
				_scope[_inst] = ["return NerdCore::Global::null;"].concat(_flow).concat([")", ";"]);
				removeLogical("FUNCTION", _env);
			}

			if(_scope[_inst - 1] && (_scope[_inst - 1][0] == "case" || _scope[_inst - 1][0] == "default"))
			{
				_scope[_inst - 1].push("break;");
				_env.SWITCH_MAP.pop();
			}
			popScope(_env);

		break;
	
		case "exit": 
			verifyExpression(_flow.slice(1), _inst, _env);
			var _args = getFunctionArgs(_flow, true, _env, _inst);
			if(_args.args.length < 1)
			{
				error(`[!] Invalid number of parameter, only one required: ${_flow[3]} line:${_env.MAP[_inst][3].line + 1} position:${_env.MAP[_inst][3].position}${os.EOL}=> ${array_of_code[_env.MAP[_inst][3].line]}`);
			}
		break;
		case "require":
		
			var _args = getFunctionArgs(_flow, true, _env, _inst);
			if(_args.args.length < 1)
			{
				error(`[!] Missing file parameter: ${_flow[3]} line:${_env.MAP[_inst][3].line + 1} position:${_env.MAP[_inst][3].position}${os.EOL}=> ${array_of_code[_env.MAP[_inst][3].line]}`);
			}
			verifyExpression(_flow.slice(1), _inst, _env);

			var _required = genRequire(COMPILER.PATH, _args.args[0].slice(1, _args.args[0].length - 1), _env, _flow[0]);
			if(_required.add)
			{
				COMPILER.DECL += _required.code;
			}
			_scope[_inst] = [];
			_scope[_inst].push(_required.module);
			_scope[_inst].push(";");
			
		break;
		/*
		case "function":
			var _hoisting = [];

			var _bracketState = 0;
			var _end = -1;
			for(var s = _inst; s < _scope.length; s++)
			{
				for(var b = i; b < _scope[s].length; b++)
				{
					if(_scope[s][b] == "{")
					{
						_bracketState++;
					}
					else if(_scope[s][b] == "}")
					{
						_bracketState--;
						if(_bracketState == 0)
						{
							_end = s+1;
							break;
						}
					}
				}
				if(s > -1)
				{
					break;
				}
			}
			
			_hoisting = _hoisting.concat(_scope.slice(0, _inst), _scope.slice(_end));
			var _newScope = [].concat(_scope.slice(0, _inst), _scope.slice(_end));
			
			_env.FLOW = _env.FLOW.slice(0, _inst).concat(_env.FLOW.slice(_end));
			_env.AST = _env.AST.slice(0, _inst).concat(_env.AST.slice(_end));

			return _inst;
		break;
		*/
	
		case "define":
		
			_scope[_inst] = [];
			if(_flow[2] == "__NERD_Multi_Line_Quote")
			{
				COMPILER.DECL += "\n" + _flow[4].slice(1, _flow[4].length -1) + "\n";
			}
			else COMPILER.DECL += "\n" + _flow[2].slice(1, _flow[2].length - 1) + "\n";
			return _inst + 1;
			
		break;
	
		case "include":
		
			_scope[_inst] = [""];
			if(_flow[2][1] == "<")
			{
				COMPILER.INCLUDE += "#include " + _flow[2].slice(1, _flow[2].length - 1) + "\n";
			}
			else 
			{
				var _toInclude = _flow[2].slice(1, _flow[2].length - 1);
				var _pathToInclude = path.resolve(path.join( _env.PATH, _toInclude));

				if(fs.existsSync(_pathToInclude))
				{
					COMPILER.INCLUDE += "#include \"" + _pathToInclude + "\"\n"
				}
				else COMPILER.INCLUDE += "#include " + _flow[2] + "\n";
			}
			return _inst + 1;
			
		break;
	
		case "for":
			if(_flow[2] == "auto")
			{
				break;
			};
			nextScope(_env);	
			
			var _for = _flow.slice(2);

			if(_flow[4] == "in")
			{
				addVar(_flow[3], _env);
				var _functionID = "__NERD_IT_FUNC_" + Math.random().toString(36).slice(2, 12);

				var _iterator = _for.slice(3, 4);
				verifyExpression(_iterator, _inst, _env);
				_scope[_inst] =
				[
					"var", _functionID, "=", "function", "(", _for[1], ")", "{",
				];
				var _nextScope =
				[
					"{{if(" + _iterator[0] + ".type == NerdCore::Enum::Type::Object){ for(auto __NERD_ITERATOR = ((NerdCore::Class::Object*)" + _iterator[0] + ".data.ptr)->object.begin(); __NERD_ITERATOR != ((NerdCore::Class::Object*)" + _iterator[0] + ".data.ptr)->object.end(); ++__NERD_ITERATOR) {if(__NERD_ITERATOR->first.compare(\"__proto__\") != 0) {var " + _for[1] + " = __NERD_ITERATOR->first;" + _functionID + "(null," + _for[1] + ");}}}else if(" + _iterator[0] + ".type == NerdCore::Enum::Type::Array){for(std::size_t __NERD_ITERATOR = 0; __NERD_ITERATOR < ((NerdCore::Class::Array*)" + _iterator[0] + ".data.ptr)->value.size(); __NERD_ITERATOR++) {" + _functionID + "(null,__NERD_ITERATOR);}}else if(" + _iterator[0] + ".type == NerdCore::Enum::Type::String){for(std::size_t __NERD_ITERATOR = 0; __NERD_ITERATOR < ((NerdCore::Class::String*)" + _iterator[0] + ".data.ptr)->value.length(); __NERD_ITERATOR++) {var " + _for[1] + " = __NERD_ITERATOR;" + _functionID + "(null," + _for[1] + ");}}}}",
				];
				
				

				var sIndex = 1;
				var endOfScope = 0;
				for(var f = _inst+1; f < _scope.length; f++)
				{
					endOfScope = f;
					if(_scope[f][_scope[f].length - 1] == "}")
					{
						sIndex--;
					}
					if(sIndex == 0)
					{
						break;
					}
				}
				
				_env.FLOW.splice(endOfScope+1, 0, _nextScope);
				_env.AST.splice(endOfScope+1, 0, ["NATIVE"]);
				
				return _inst;
			}

			
			
			var _firstComa = _for.indexOf(";");
			var _init = _for.slice(0, _firstComa);

			_for = _for.slice(_firstComa + 1);
			
			var _secondComa = _for.indexOf(";");
			var _loop = _for.slice(0, _secondComa);
			
			var _it = _for.slice(_secondComa + 1, _for.length - 2);
			
			if(_init[0] == "var")
			{
				addVar(_init[1], _env);
			}
			else
			{
				verifyExpression(_init, _inst, _env);
			}
			
			verifyExpression(_loop, _inst, _env);
			verifyExpression(_it, _inst, _env);
			
			return _inst + 1;
		break;

		case "if":
			verifyExpression(_flow.slice(2, _flow.length - 2), _inst, _env);
			checkCalls(2, _flow, _inst, _env);
			addLogical("IF", _env);
			nextScope(_env);
			return _inst + 1;
		break;
		
		case "else":
			if(!getLogical(_env).IF)
			{
				error(`[!] Use if before else/else if: ${_flow[0]} line:${_env.MAP[_inst][0].line + 1} position:${_env.MAP[_inst][0].position}${os.EOL}=> ${array_of_code[_env.MAP[_inst][0].line]}`);
			}
			if(_flow[1] && _flow[1] == "if")
			{
				verifyExpression(_flow.slice(2, _flow.length - 2), _inst, _env);
				checkCalls(3, _flow, _inst, _env);
				nextScope(_env);
			}
			else
			{				
				nextScope(_env);
			}
			
			return _inst + 1;
		break;
		
		case "do":
		
			addLogical("DO", _env);

			nextScope(_env);
			return _inst + 1;
			
		break;
		
		case "while":			
			verifyExpression(_flow.slice(2, _flow.length - 2), _inst, _env);
			if(getLogical(_env).DO)
			{
				removeLogical("DO", _env);
			}
			else
			{				
				nextScope(_env);
			}
			return _inst + 1;
		break;
		
		case ";":
		
		break;
		
		case "try":
		
			addLogical("TRY", _env);
			
			nextScope(_env);
			return _inst + 1;
		break;
		
		case "catch":
			addVar(_scope[_inst][2], _env);
			_scope[_inst][2] = "var " + _scope[_inst][2];
			
			if(getLogical(_env).TRY)
			{
				removeLogical("TRY", _env);
			}
			else
			{				
				error(`[!] Missing try statement before catch: ${_flow[0]} line:${_env.MAP[_inst][0].line + 1} position:${_env.MAP[_inst][0].position}${os.EOL}=> ${array_of_code[_env.MAP[_inst][0].line]}`);
			}
			nextScope(_env);
			return _inst + 1;
		break;
		
		case "return":
				if(_flow[1] == "{")
				{
					//var _returnVar = "__NERD_RETURN_" + _env.MAP[_inst][0].line;
					//_env.FLOW[_inst] = ["var", _returnVar, "="].concat(_env.FLOW[_inst].slice(1));
					forgeObject(_flow, 1, _inst, _env);
					//_env.FLOW[_inst].push("return");
					//_env.FLOW[_inst].push(" ");
					//_env.FLOW[_inst].push(_returnVar);
					//_env.FLOW[_inst].push(";");
				}
				else if(_flow[1] == ";")
				{
					_flow[1] = "null;";
				}
				else 
				{
					verifyExpression(_flow.slice(1), _inst, _env);
					if(_ast[1] != "VARIABLE" && _ast[1] != "EXPRESSION")
					{
						_flow[1] = "var(" + _flow[1] + ")";
					}
				}
				return _inst + 1;
		break;
		case "switch":
			nextScope(_env);
			var _current = _flow[2];
			if(isString(_current).check || isBoolean(_current).check || isNumber(_current).check)
			{
				_current = "var(" + _current + ")";
			}
			_env.SWITCH_MAP.push(_current);
			_scope[_inst] = ["if", "(", "false", ")", "{"]; // switch hack, case will be else if
			//_scope[_inst] = ["var", "__NERD_TEST", "=", _flow[2], ";"];
		break;
		
		case "case":
			if(_env.SWITCH_MAP.length < 1)
			{
				error("[!] case without switch");
			}
			if(_scope[_inst-1] && (!_scope[_inst-1][0] || (_scope[_inst-1][0] && (_scope[_inst-1][0] != "case"))))
			{
				_scope[_inst-1].push("}");
			}
			
			var _current = _flow[1];
			
			if(isString(_current).check || isBoolean(_current).check || isNumber(_current).check)
			{
				_current = "var(" + _current + ")";
			}
			
			_scope[_inst] = ["else", "if", "(", _current, "==", _env.SWITCH_MAP[_env.SWITCH_MAP.length - 1]];
			while(_scope[_inst+1] && _scope[_inst+1][0] && _scope[_inst+1][0] == "case")
			{
				_scope[_inst].push(" || ");
				if(isString(_scope[_inst+1][1]).check || isBoolean(_scope[_inst+1][1]).check || isNumber(_scope[_inst+1][1]).check)
				{
					_scope[_inst].push("var");
					_scope[_inst].push("(");
					_scope[_inst].push(_scope[_inst+1][1]);
					_scope[_inst].push(")");
				}
				else 
				{
					_scope[_inst].push(_scope[_inst+1][1]);
				}
				
				_scope[_inst].push("==");
				_scope[_inst].push(_env.SWITCH_MAP[_env.SWITCH_MAP.length - 1]);
				_scope[_inst+1] = [];
				_inst++;
			}
			_scope[_inst].push(")");
			_scope[_inst].push("{");
			
		break;
		
		case "default":
			if(_scope[_inst-1] && (!_scope[_inst-1][0] || (_scope[_inst-1][0] && (_scope[_inst-1][0] != "case"))))
			{
				_scope[_inst-1].push("}");
			}
			_scope[_inst] = ["else", "{"];
		break;
		
		
		case "break":
			_scope[_inst] = [];
		break;
		
		case "true":
		case "false":
		case "new":
		
		break;
		
		case "this":
			_flow[0] = "__NERD_THIS";
		break;
		
		default:
			if(varExists(_flow[0], _env))
			{			
				/*
				if(!CLI.cli["--env"] || CLI.cli["--env"].argument != "js")
				{
					if(_flow[0][0] == "_" && _flow[1] && _flow[1] == "=")
					{
						error(`[!] Cannot reassign value to constant: ${_flow[0]} line:${_env.MAP[_inst][0].line + 1} position:${_env.MAP[_inst][0].position}${os.EOL}=> ${array_of_code[_env.MAP[_inst][0].line]}`);
					}
				}
				*/
				
				if(_flow[1])
				{
					for(var i = 0; i < _flow.length - 1; i++)
					{
						if(_flow[i] == "require")
						{
							verifyExpression(_flow.slice(i), _inst, _env);
							var _args = getFunctionArgs(_flow, true, _env, _inst);
							if(_args.args.length != 1)
							{
								error(`[!] Invalid number of parameter, only one required: ${_flow[3]} line:${_env.MAP[_inst][3].line + 1} position:${_env.MAP[_inst][3].position}${os.EOL}=> ${array_of_code[_env.MAP[_inst][3].line]}`);
							}
							var _required = genRequire(COMPILER.PATH, _args.args[0].slice(1, _args.args[0].length - 1), _env);
							if(_required.add)
							{
								COMPILER.DECL += _required.code;
							}
							_scope[_inst] = _flow.slice(0, i);
							_scope[_inst].push(_required.module);
							_scope[_inst].push(";");
							break;
						}
					}
					
					var _eq = -1;
					while(_eq <  _flow.length)
					{
						for(var e = _eq; e < _flow.length; e++)
						{
							if(_flow[e] == "=")
							{
								_eq = e;
								break;
							}
						}
						
						var _left = _flow.slice(0, _eq).join(" ");
						
						if(_flow[_eq] == "=")
						{
							if(_flow[_eq + 1] == "{")
							{
								forgeObject(_flow, _eq + 1, _inst, _env);
							}
							else if(_flow[_eq + 1] == "[")
							{
								forgeArray( _flow, _eq + 1, _inst, _env)
							}
							else if(_flow[_eq + 1] == "[]")
							{
								forgeArray( _flow, _eq + 1, _inst, _env);
							}
							else if(_flow[_eq + 1] == "function")
							{
								var _newFlow = _flow.slice(0, _eq + 1).concat(["__NERD_Create_Var_Scoped_Copy_Anon", "({"]);
								var _args = getFunctionArgs(_flow, false, _env, _inst);
								nextScope(_env);
								addLogical("FUNCTION", _env);
								_scope[_inst] = _newFlow;
								var item = 0;
								for(var a = 0; a < _args.args.length; a+=2)
								{
									addVar(_args.args[a], _env, 4, _inst);
									_scope[_inst] = _scope[_inst].concat(["var", _args.args[a], ";", "if", "(", "__NERD_VARLENGTH", ">", item,")", _args.args[a], "=", `__NERD_VARARGS[${item}];`]);
									item++;
								}
								verifyExpression(_flow.slice(_eq + 1), _inst, _env);
							}
							break;
							//return _inst + 1;
						}
						_eq++;
					}
					
					if(_eq == _flow.length)
					{
						_eq = 0;
					}
					else
					{
						_eq++;
					}

					checkCalls(_eq, _flow, _inst, _env);
					
				}
			}
			else if(_ast[0] == "NATIVE")
			{
				// nothing to do
			}
			else
			{
				error(`[!] Unknown variable or token: ${_flow[0]} line:${_env.MAP[_inst][0].line + 1} position:${_env.MAP[_inst][0].position}${os.EOL}=> ${array_of_code[_env.MAP[_inst][0].line]}`);
			}
		
		break;
	}
	verifyExpression(_flow, _inst, _env);
	return _inst+1;
}

module.exports = verifyFlow;