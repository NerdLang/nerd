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

//var _env.flowBracket = 0;
//var _env.flowObject = 0;
//var _env.flowParenthesis = 0;
//var _env.flowAccessor = 0;

var isNumber = require("./check/isNumber.js");
var isVariable = require("./check/isVariable.js");
var isString = require("./check/isString.js");
var isOperator = require("./check/isOperator.js");
var isUnary = require("./check/isUnary.js");
var isInitOperator = require("./check/isInitOperator.js");
var isObjectOperator = require("./check/isObjectOperator.js");
var isKeyword = require("./check/isKeyword.js");
var isDelimiter = require("./check/isDelimiter.js");
var isIncrement = require("./check/isIncrement.js");
var isAssignment = require("./check/isAssignment.js");
var isSemi = require("./check/isSemi.js");
var isNative = require("./check/isNative.js");

var CHECKERS = [ isSemi, isNumber, isAssignment, isKeyword, isVariable, isString, isDelimiter, isIncrement, isObjectOperator, isOperator, isUnary, isInitOperator, isNative, ];

function incToken(_env)
{
	_env.POSITION++;
	if(!_env.TOKENS[_env.POSITION])
	{
		_env.TOKENS[_env.POSITION] = [];
	}
	if(!_env.TOKENSMAP[_env.POSITION])
	{
		_env.TOKENSMAP[_env.POSITION] = [];
	}
}

function decToken(_env)
{
	_env.POSITION--;
}

function addToken(_code, _env)
{
	if(_code == "\n") return;
	if(_code.length > 0)
	{
		if(!_env.TOKENS[_env.POSITION])
		{
			_env.TOKENS[_env.POSITION] = [];
		}
		if(!_env.TOKENSMAP[_env.POSITION])
		{
			_env.TOKENSMAP[_env.POSITION] = [];
		}
		_env.TOKENS[_env.POSITION].push(_code);
		_env.TOKENSMAP[_env.POSITION].push( {line: _env.LINE, position: _env.CURSOR} );
	}
}

var noReduceParenthesis = ["INCLUDE", "FUNCTION", "ACCESSOR", "]", ")", "VARIABLE", "CALL", "IF", "WHILE", "FOR"];
var reduceParenthesis = function(_ast)
{
	for(var i = 0; i < _ast.length; i++)
	{
		if(_ast[i-1] && _ast[i-1] == "IF" &&_ast[i] == "(" && _ast[i+1] && _ast[i+1] == "(")
		{
			if(_ast[i+3] && _ast[i+3] == ")")
			{
				_ast = _ast.slice(0,2).concat([_ast[i+2]]).concat(_ast.slice(5));
				reduceParenthesis(_ast);
			}
		}
		else if( (!_ast[i-1] || (_ast[i-1] && noReduceParenthesis.indexOf(_ast[i-1]) < 0) ) && _ast[i] == "(" && _ast[i+2] && _ast[i+2] == ")" )
		{
			_ast = _ast.slice(0,i).concat([_ast[i+1]]).concat(_ast.slice(i+3));
			reduceParenthesis(_ast);
		}
	}
	return _ast;
}

function verifyToken(_token, i, j, map, _env)
{
	var check = {check: false, error: false};
	
	for(var k = 0; k < CHECKERS.length; k++)
	{
		check = CHECKERS[k](_token);
		if(check.error)
		{
			
			error(`[!] ${check.message}: ${_token} line:${map[i][j].line + 1} position:${map[i][j].position}${os.EOL}=> ${array_of_code[map[i][j].line]}`);
		}
		else if(check.check)
		{
			return check.type;
		}
	}
		
	if(!check.check)
	{
		console.trace();
		error(`[!] Unknown token: ${_token} line:${map[i][j].line + 1} position:${map[i][j].position}${os.EOL}=> ${array_of_code[map[i][j].line]}`);
	}
}

var GRAMMAR =
{
	"(":
	[
		["(", "VARIABLE", ","],
		["(", "CALL", ","],
	],
	BOOLEAN:
	[
		["TRUE"],
		["FALSE"],
	],
	LITERAL:
	[
		["NUMBER"],
		["STRING"],
		["BOOLEAN"],
	],
	OBJECT:
	[
		["{", "LIST", "}"],
		["{", "ASSIGNMENT", "}"],
		["{", "LIST", ",", "}"],
		["{", "ASSIGNMENT", ",", "}"],
	],
	
	OBJECT_LIST:
	[
		["ASSIGNMENT", ",", "ASSIGNMENT"],
		["ASSIGNMENT", ",", "OBJECT_LIST"],
		["OBJECT_LIST", ",", "ASSIGNMENT"],
		["OBJECT_LIST", ",", "OBJECT_LIST"],
	],
	
	ARRAY:
	[
		["[", "LIST", "]"],
		["[", "LIST", ",", "]"],
		["[", "{", "OBJECT_LIST", "}", "]"],
	],
	
	ACCESSOR:
	[
		["[", "LITERAL", "]"],
		["[", "VARIABLE", "]"],
		["[", "EXPRESSION", "]"],
	],
	
	
	
	
	
	BREAK:
	[
		["SEMI", "BREAK"],
	],

	LAMBDA:
	[
		["FUNCTION", "(", ")", "{", "}"],
		["FUNCTION", "(", "LIST", ")", "{", "}"],
	],

	OPERATOR:
	[
		["OPERATOR", "OPERATOR"]
	],
	
	VARIABLE:
	[
		["VAR", "VARIABLE"],
		["VARIABLE", ".", "VARIABLE"],
		["VARIABLE", "ACCESSOR"],
		["CALL", ".", "VARIABLE"],
		["VARIABLE", ".", "CALL"],
		["UNARY", "VARIABLE"],
		["[", "]"],
		["THIS"],
		["VARIABLE", "INCREMENT"],
		["CALL", "ACCESSOR"],
	],
	
	CALL:
	[
		["VARIABLE", "(", "CALL", ")"],
		["VARIABLE", "(", "VARIABLE", ")"],
		["VARIABLE", "(", "LIST", ")"],
		["VARIABLE", "(", "EXPRESSION", ")"],
		["VARIABLE", "(", "VARIABLE", ")"],
		["VARIABLE", "(", "LITERAL", ")"],
		["VARIABLE", "(", "OBJECT", ")"],
		["VARIABLE", "(", "{", "OBJECT_LIST", "}", ")"],
		["VARIABLE", "(", "ARRAY", ")"],
		["VARIABLE", "(", ")"],

		["CALL", ".", "CALL"],
		["VARIABLE", ".", "CALL"],
		["UNARY", "CALL"],
		["NEW", "CALL"],
	],
	
	ASSIGNMENT:
	[
	
		["VARIABLE", ":", "LITERAL"],
		["VARIABLE", ":", "VARIABLE"],
		["VARIABLE", ":", "EXPRESSION"],
		["VARIABLE", ":", "CALL"],
		["VARIABLE", ":", "LAMBDA"],
		["VARIABLE", ":", "ARRAY"],
		["VARIABLE", ":", "OBJECT"],
		["VARIABLE", ":", "{", "}"],
		["VARIABLE", ":", "{", "ASSIGNMENT", "}"],
		["VARIABLE", ":", "{", "ASSIGNMENT", ",", "}"],

		["VARIABLE", ":", "LIST"],
		
		["LITERAL", ":", "LITERAL"],
		["LITERAL", ":", "EXPRESSION"],
		["LITERAL", ":", "CALL"],

	],
	
	LIST:
	[
		["LIST", ",", "{", "OBJECT_LIST", "}"],
		["{", "OBJECT_LIST", "}", ",", "LIST}"],
		["{", "OBJECT_LIST", "}", ",", "{", "OBJECT_LIST", "}"],
	],
	
}


var LIST_GEN = 
[
	 "LITERAL", "ARRAY", "VARIABLE", "CALL",  "LIST", 
]
var VAR_OPERATOR_GEN =
[
	"VARIABLE", "LITERAL",  "CALL", 
]

for(var i = 0; i < LIST_GEN.length; i++)
{
	for(var j = 0; j < LIST_GEN.length; j++)
	{
		GRAMMAR.LIST.push([LIST_GEN[i], ",", LIST_GEN[j]]);
	}
}

for(var i = 0; i < VAR_OPERATOR_GEN.length; i++)
{
	for(var j = 0; j < VAR_OPERATOR_GEN.length; j++)
	{
		GRAMMAR.VARIABLE.push([VAR_OPERATOR_GEN[i], "OPERATOR", VAR_OPERATOR_GEN[j]]);
	}
}

var VALIDATION = 
{
	VARIABLE:
	[
		["VARIABLE", "SEMI"],
		["VARIABLE", "ASSIGNMENT", "LITERAL", "SEMI"],
		["VARIABLE", "ASSIGNMENT", "VARIABLE", "SEMI"],
		["VARIABLE", "ASSIGNMENT", "ACCESSOR", "SEMI"],
		["VARIABLE", "ASSIGNMENT", "OBJECT", "SEMI"],
		["VARIABLE", "ASSIGNMENT", "ARRAY", "SEMI"],
		["VARIABLE", "ASSIGNMENT", "EXPRESSION", "SEMI"],
		["VARIABLE", "ASSIGNMENT", "CALL", "SEMI"],
		
		["VARIABLE", "ASSIGNMENT", "[", "LITERAL", "]", "SEMI"],
		["VARIABLE", "ASSIGNMENT", "[", "LIST", "]", "SEMI"],
		
		
		["VARIABLE", "ASSIGNMENT", "FUNCTION", "(", "LIST", ")", "{"],
		["VARIABLE", "ASSIGNMENT", "FUNCTION", "(", "LITERAL", ")", "{"],
		["VARIABLE", "ASSIGNMENT", "FUNCTION", "(", "VARIABLE", ")", "{"],
		["VARIABLE", "ASSIGNMENT", "FUNCTION", "(", "ARRAY", ")", "{"],
		["VARIABLE", "ASSIGNMENT", "FUNCTION", "(", "OBJECT", ")", "{"],
		["VARIABLE", "ASSIGNMENT", "FUNCTION", "(", ")", "{"],
		
		["VARIABLE", "ASSIGNMENT", "{", "OBJECT_LIST", "}", "SEMI"],
		["VARIABLE", "ASSIGNMENT", "{", "OBJECT_LIST", ",", "}", "SEMI"],
		["VARIABLE", "ASSIGNMENT", "{", "}", "SEMI"],
	],
	ASSIGNMENT:
	[
		["ASSIGNMENT", "SEMI"],
		["ASSIGNMENT", "{"],
	],
	EXPRESSION:
	[
		["EXPRESSION", "SEMI"],
	],
	WHILE:
	[
		[ "WHILE", "(", "LITERAL", ")", "{" ],
		[ "WHILE", "(", "VARIABLE", ")", "{" ],
		[ "WHILE", "(", "EXPRESSION", ")", "{" ],
		
		[ "WHILE", "(", "LITERAL", ")", "SEMI" ],
		[ "WHILE", "(", "VARIABLE", ")", "SEMI" ],
		[ "WHILE", "(", "EXPRESSION", ")", "SEMI" ],
	],
	SWITCH:
	[
		["SWITCH", "(", "VARIABLE", ")", "{"],
		["SWITCH", "(", "EXPRESSION", ")", "{"],
		["SWITCH", "(", "LITERAL", ")", "{"],
		["SWITCH", "(", "CALL", ")", "{"],
	],
	CASE:
	[
		["CASE", "LITERAL", ":"],
		["CASE", "VARIABLE", ":"],
		["CASE", "EXPRESSION", ":"],
		["CASE", "CALL", ":"],
	],
	DEFAULT:
	[
		["DEFAULT", ":"],
	],
	DO:
	[
		[ "DO", "{" ],
	],
	IF:
	[
		[ "IF", "(", "LITERAL", ")", "{" ],
		[ "IF", "(", "VARIABLE", ")", "{" ],
		[ "IF", "(", "EXPRESSION", ")", "{" ],
		[ "IF", "(", "CALL", ")", "{" ],
		
		[ "IF", "(", "LITERAL", ")", "ASSIGNMENT", "SEMI" ],
		[ "IF", "(", "VARIABLE", ")", "ASSIGNMENT", "SEMI" ],
		[ "IF", "(", "VARIABLE", ")", "VARIABLE", "SEMI" ],
		[ "IF", "(", "VARIABLE", ")", "RETURN", "SEMI" ],
		[ "IF", "(", "EXPRESSION", ")", "ASSIGNMENT", "SEMI" ],
		[ "IF", "(", "CALL", ")", "ASSIGNMENT", "SEMI" ],
		[ "IF", "(", "CALL", ")", "CALL", "SEMI" ],
		[ "IF", "(", "VARIABLE", ")", "CALL", "SEMI" ],
		[ "IF", "(", "EXPRESSION", ")", "CALL", "SEMI" ],
		[ "IF", "(", "EXPRESSION", ")", "RETURN", "SEMI" ],
		
		
		[ "IF", "(", "VARIABLE", ")", "VARIABLE", "ASSIGNMENT", "LITERAL", "SEMI" ],
		[ "IF", "(", "VARIABLE", ")", "VARIABLE", "ASSIGNMENT", "VARIABLE", "SEMI" ],
		[ "IF", "(", "VARIABLE", ")", "VARIABLE", "ASSIGNMENT", "CALL", "SEMI" ],
		
		[ "IF", "(", "EXPRESSION", ")", "VARIABLE", "ASSIGNMENT", "STRING", "SEMI" ],
		[ "IF", "(", "EXPRESSION", ")", "VARIABLE", "ASSIGNMENT", "VARIABLE", "SEMI" ],
		[ "IF", "(", "EXPRESSION", ")", "VARIABLE", "ASSIGNMENT", "CALL", "SEMI" ],
		[ "IF", "(", "EXPRESSION", ")", "VARIABLE", "ASSIGNMENT", "EXPRESSION", "SEMI" ],
		
	],
	ELSE:
	[
		[ "ELSE", "IF", "(", "LITERAL", ")", "{" ],
		[ "ELSE", "IF", "(", "VARIABLE", ")", "{" ],
		[ "ELSE", "IF", "(", "EXPRESSION", ")", "{" ],
		[ "ELSE", "IF", "(", "CALL", ")", "{" ],
		
		[ "ELSE", "IF", "(", "LITERAL", ")", "ASSIGNMENT", "SEMI" ],
		[ "ELSE", "IF", "(", "VARIABLE", ")", "ASSIGNMENT", "SEMI" ],
		[ "ELSE", "IF", "(", "EXPRESSION", ")", "ASSIGNMENT", "SEMI" ],
		[ "ELSE", "IF", "(", "EXPRESSION", ")", "VARIABLE", "EXPRESSION", "SEMI" ],
		[ "ELSE", "IF", "(", "CALL", ")", "ASSIGNMENT", "SEMI" ],
		[ "ELSE", "IF", "(", "CALL", ")", "CALL", "SEMI" ],
		[ "ELSE", "IF", "(", "VARIABLE", ")", "CALL", "SEMI" ],

		[ "ELSE", "IF", "(", "VARIABLE", ")", "VARIABLE", "ASSIGNMENT", "LITERAL", "SEMI" ],
		[ "ELSE", "IF", "(", "VARIABLE", ")", "VARIABLE", "ASSIGNMENT", "VARIABLE", "SEMI" ],
		[ "ELSE", "IF", "(", "EXPRESSION", ")", "VARIABLE", "ASSIGNMENT", "VARIABLE", "SEMI" ],
		[ "ELSE", "IF", "(", "EXPRESSION", ")", "VARIABLE", "ASSIGNMENT", "LITERAL", "SEMI" ],
		
		[ "ELSE", "{" ],
		[ "ELSE", "TRY", "{" ],
		[ "ELSE", "VARIABLE", "SEMI" ],
		[ "ELSE", "ASSIGNMENT", "SEMI" ],
		[ "ELSE", "CALL", "SEMI" ],
		[ "ELSE", "VARIABLE", "ASSIGNMENT", "VARIABLE", "SEMI" ],
		[ "ELSE", "VARIABLE", "ASSIGNMENT", "CALL", "SEMI" ],
		[ "ELSE", "VARIABLE", "EXPRESSION", "SEMI" ],
	],
	FOR:
	[
		["FOR", "(", "VARIABLE", "ASSIGNMENT", "LITERAL", "SEMI", "VARIABLE", "SEMI", "VARIABLE", ")", "{"],
		["FOR", "(", "VARIABLE", "ASSIGNMENT", "LITERAL", "SEMI", "CALL", "SEMI", "VARIABLE", ")", "{"],
		["FOR", "(", "VARIABLE", "ASSIGNMENT", "VARIABLE", "SEMI", "VARIABLE", "SEMI", "VARIABLE", ")", "{"],
		["FOR", "(", "VARIABLE", "ASSIGNMENT", "VARIABLE", "SEMI", "CALL", "SEMI", "VARIABLE", ")", "{"],
		["FOR", "(", "VARIABLE", "ASSIGNMENT", "LITERAL", "SEMI", "VARIABLE", "SEMI", "EXPRESSION", ")", "{"],
		["FOR", "(", "VARIABLE", "ASSIGNMENT", "VARIABLE", "SEMI", "VARIABLE", "SEMI", "EXPRESSION", ")", "{"],
		["FOR", "(", "VARIABLE", "ASSIGNMENT", "LITERAL", "SEMI", "EXPRESSION", "SEMI", "VARIABLE", ")", "{"],
		["FOR", "(", "VARIABLE", "ASSIGNMENT", "VARIABLE", "SEMI", "EXPRESSION", "SEMI", "VARIABLE", ")", "{"],
		["FOR", "(", "VARIABLE", "ASSIGNMENT", "LITERAL", "SEMI", "EXPRESSION", "SEMI", "EXPRESSION", ")", "{"],
		["FOR", "(", "VARIABLE", "ASSIGNMENT", "VARIABLE", "SEMI", "EXPRESSION", "SEMI", "EXPRESSION", ")", "{"],
		["FOR", "(", "VARIABLE", "SEMI", "EXPRESSION", "SEMI", "EXPRESSION", ")", "{"],
		["FOR", "(", "VARIABLE", "IN", "VARIABLE", ")", "{"],
	],
	FUNCTION:
	[
		["FUNCTION", "CALL", "{"],
	],
	CALL:
	[
		["CALL", "SEMI"],
	],
	INCLUDE:
	[
		["INCLUDE", "(", "LITERAL", ")", "SEMI"],
	],
	DEFINE:
	[
		["DEFINE", "(", "STRING", ")", "SEMI"],
	],
	RETURN:
	[
		["RETURN", "LITERAL", "SEMI"],
		["RETURN", "SEMI"],
		["RETURN", "VARIABLE", "SEMI"],
		["RETURN", "EXPRESSION", "SEMI"],
		["RETURN", "CALL", "SEMI"],
		["RETURN", "OBJECT", "SEMI"],
		["RETURN", "OBJECT", ",", "SEMI"],
		["RETURN", "{", "ASSIGNMENT", ",", "}", "SEMI"],
		["RETURN", "{", "ASSIGNMENT", "}", "SEMI"],
		["RETURN", "{", "OBJECT_LIST", ",", "}", "SEMI"],
		["RETURN", "{", "OBJECT_LIST","}", "SEMI"],
	],
	TRY:
	[
		["TRY", "{"],
	],
	CATCH:
	[
		["CATCH", "(", "VARIABLE", ")", "{"],
	],
	"NATIVE":
	[
		["NATIVE"],
	],
	"{":
	[
		["{"],
	],
	"}":
	[
		["}"],
		["}", "SEMI"],
	],
	BREAK:
	[
		["BREAK"],
		["BREAK", "SEMI"],
	],
	SEMI:
	[
		["SEMI"],
	]
}

function checkExpression(_ast, _flow, _arr)
{
	var _startAst = 0;
	var _endAst = 0;
	var _match = false;
	
	var _newAst = [];

	for(var g = 0; g < Object.keys(_arr).length; g++)
	{		
		var _grammarName = Object.keys(_arr)[g];
		var _grammar = _arr[_grammarName];

		for(var t = 0; t < _grammar.length; t++)
		{
			for(var i = 0; i < _ast.length ; i++)
			{
				_startAst = 0;
				_endAst = 0;
				_match = false;
				if(_ast[i] == _grammar[t][0])
				{
					_match = true;
					_startAst = i;
					_endAst = i;
					for(var m = 0; m < _grammar[t].length; m++)
					{
						if(!_ast[i + m])
						{
							_match = false;
							break
						}
						else if( _ast[i + m] == _grammar[t][m])
						{
							_endAst++;
						}		
						else
						{
							_match = false;
							break;
						}
					}
					if(_match)
					{
						_newAst = _ast.slice(0, _startAst);
						_newAst.push( _grammarName );
						_newAst = _newAst.concat( _ast.slice( _endAst ));
						
						_ast = _newAst;
						_ast = reduceParenthesis(_ast);

						return checkExpression(_ast, _flow, _arr);
					}
				}
			}
		}
	}
	return _ast;
}

function checkSyntax(_ast, _flow, _scope, _env)
{
	if(_ast.length < 1)
	{
		return;
	}
	if(VALIDATION[_ast[0]])
	{
		var _check = VALIDATION[_ast[0]];
		var _good = true;
		
		for(var c = 0; c < _check.length; c++)
		{
			_good = true;
			for(var t = 0; t < _ast.length; t++)
			{
				if(!_check[c][t] || _ast[t] != _check[c][t])
				{
					_good = false;
					break;
				}
			}
			if(_good)
			{
				break;
			}
		}
		
		if(!_good)
		{
			var _debug = "\n";
			if(global.DEBUG)
			{
				_debug += _ast.join(" ");
			}
			error(`[!] Unexpected token: line: ${_scope[0].line + 1} in ${_env.FILE}\n${_flow.join(" ")}${_debug}`);
		}
	}
	else
	{
		var _debug = "\n";
		if(global.DEBUG)
		{
			_debug += _ast.join(" ");
		}
		error(`[!] Unexpected token: line: ${_scope[0].line + 1} position: 0 in ${_env.FILE}\n${_flow.join(" ")}${_debug}`);
	}
}


function addFlow(_env)
{
	if(_env.TOKENS.length > 0 && _env.TOKENS[0])
	{
		var _ast = [];
		for(var i = 0; i < _env.TOKENS.length; i++)
		{
			_ast[i] = [];

			
			for(var j = 0; j < _env.TOKENS[i].length; j++)
			{
				_ast[i][j] = verifyToken(_env.TOKENS[i][j], i, j, _env.TOKENSMAP, _env);
			}
			
			_ast[i] = checkExpression(_ast[i], _env.TOKENS[i], GRAMMAR);
			//_ast[i] = checkExpression(_ast[i], _env.TOKENS[i], ASSIGN);

			//_ast[i] = checkExpression(_ast[i], _env.TOKENS[i], SECOND);

			checkSyntax(_ast[i], _env.TOKENS[i], _env.TOKENSMAP[i], _env);
		}
		
		_env.FLOW = _env.FLOW.concat(_env.TOKENS);
		_env.MAP = _env.MAP.concat(_env.TOKENSMAP);
		_env.AST = _env.AST.concat(_ast);
	}
	_env.TOKENS = [];
	_env.TOKENSMAP = [];
	_env.POSITION = 0;

}

function findNextLine(_code, _from, _env)
{
	for(var i = _from; i < _code.length; i++)
	{
		if(_code[i] == "\r" && _code[i+1] && _code[i+1] == "\n")
		{
			_env.LINE++;
			_env.CURSOR = 0;
			return i+2;
		}
		else if(_code[i] == "\n")
		{
			_env.LINE++;
			_env.CURSOR = 0;
			return i+1;
		}
	}
	// ERROR
	return _code.length - 1;
}

function findEndComment(_code, _from, _env)
{
	for(var i = _from; i < _code.length; i++)
	{
		if(_code[i] == "\n")
		{
			_env.LINE++;
			_env.CURSOR = 0;
		}
		else if(_code[i] == "\r" && _code[i + 1] && _code[i + 1] == "\n")
		{
			_env.LINE++;
			_env.CURSOR = 0;
			i++;
		}
		else if(_code[i] == "*" && _code[i+1] && _code[i+1] == "/")
		{
			return i+2;
		}
		_env.CURSOR++;
	}
	// ERROR
	return _code.length - 1;
}

function setFor(_current, _env)
{
	if(_current == "for" && _env.FOR == 0)
	{
		_env.FOR = 2;
	}
}

function setSwitch(_current, _env)
{
	if(_current == "switch")
	{
		_env.SWITCH ++;
	}
}

function setCase(_current, _env)
{
	if(_current == "case")
	{
		if(_env.SWITCH > 0)
		{
			_env.IN_CASE = true;
		}
		else
		{
			error(`'case' keyworkds require to be in a switch statement`);
		}
	}
}

function unsetCase(_current, _env)
{
	if(_current == "break")
	{
		if(_env.IN_CASE == true)
		{
			_env.IN_CASE = false;
		}
	}
}

function parseCode(_code, _from, _env)
{
	var _current = "";
	_env.POSITION = 0;

	for(var i = _from; i < _code.length; i++)
	{
		var _tokens = _env.TOKENS[_env.TOKENS.length - 1];
		var _before;

		if(_tokens && _tokens[_tokens.length - 1])
		{
			_before = _tokens[_tokens.length - 1];
		}
		
		switch(_code[i])
		{
			case " ":
				if(!_env.IN_STRING && !_env.IN_BLOCK_QUOTE && !_env.IN_NATIVE)
				{
					setFor(_current, _env);
					setSwitch(_current, _env);
					addToken(_current, _env);
					_current = "";
				}
				else
				{
					_current += _code[i];
				}
			break;
			case "\t":
				if(!_env.IN_STRING && !_env.IN_BLOCK_QUOTE && !_env.IN_NATIVE)
				{
					setFor(_current, _env);
					setSwitch(_current, _env);
					addToken(_current, _env);
					_current = "";
				}
				else if(_env.IN_STRING || _env.IN_NATIVE)
				{
					_current += _code[i];
				}
				else if(_env.IN_BLOCK_QUOTE)
				{
					_current += "\\t";
				}
			break;
			
			case "\n":
				if(!_env.IN_BLOCK_QUOTE && !_env.IN_NATIVE)
				{
					_env.LINE++;
					_env.CURSOR = 0;
					addToken(_current, _env);
					_current = "";
				}
				else if(_env.IN_NATIVE)
				{
					_current += _code[i];
				}
				else 
				{
					_current += "\\n";
				}
			break;
			
			case "\r":
				if(!_env.IN_BLOCK_QUOTE && !_env.IN_NATIVE)
				{
					_env.LINE++;
					_env.CURSOR = 0;
					if(_code[i+1] && _code[i+1] == "\n")
					{
						addToken(_current, _env);
						_current = "";
						i++
						break;
					}
				}
				else if(_env.IN_NATIVE)
				{
					_current += _code[i];
				}
				else 
				{
					_current += "\\r";
				}
			break;
			
			case "\\":
				if(_env.IN_BLOCK_QUOTE)
				{
					_current += "\\\\";
				}
				_current += "\\";
			break;

			case "\"":
				if(_env.IN_STRING && !_env.IN_NATIVE)
				{
					_env.IN_STRING = false;
				}
				else if(!_env.IN_BLOCK_QUOTE && !_env.IN_NATIVE)
				{
					_env.IN_STRING = true;
				}
				if(_env.IN_BLOCK_QUOTE)
				{
					_current += "\\\"";
				}
				else
				{
					_current += _code[i];
				}
			break;
			
			case "`":
				if(_env.IN_BLOCK_QUOTE && !_env.IN_NATIVE)
				{
					_env.IN_BLOCK_QUOTE = false;
					addToken(_current + "\"", _env);
					_current = "";
				}
				else if(!_env.IN_STRING && !_env.IN_NATIVE)
				{
					_env.IN_BLOCK_QUOTE = true;
					addToken(_current, _env);
					_current = "\"";
					
					for(var q = i+1; q < _code.length; q++)
					{
						if(_code[q] == "`")
						{
							break;
						}
						if(_code[q] == "$" && _code[q+1] == "{")
						{									
							for(var end = q; end < _code.length; end++)
							{
								
								if(_code[end] == "}")
								{	
									_code[q] = "\"";
									_code[q+1] = "+";	
									_code = _code.slice(0, q) + "` + " + _code.slice(q+2, end) + " + `" + _code.slice(end+1);
									break;
								}	
							}
							
						}
					}
				}
				else _current += _code[i];
			break;
			
			case "/":
				if(!_env.IN_STRING && !_env.IN_BLOCK_QUOTE && !_env.IN_NATIVE)
				{
					if(_code[i+1])
					{
						if(_code[i + 1] && _code[i + 1] == "=")
						{
							// /=
							addToken(_code[i] + _code[i + 1], _env);
							i++;
						}
						else if(_code[i+1] == "/")
						{
							addToken(_current, _env);
							addFlow(_env);
							_current = "";
							parseCode(_code, findNextLine(_code, i, _env), _env);
							return;
						}
						else if(_code[i+1] == "*")
						{
							addToken(_current, _env);
							addFlow(_env);
							_current = "";
							i = parseCode(_code, findEndComment(_code, i, _env), _env);
							return;
						}
						else 
						{
							addToken(_current, _env);
							addToken(_code[i], _env);
							_current = "";
						}
					}
				}
				else 
				{
					_current += _code[i];
				}
				
			break;
			
			case "0":
			case "1":
			case "2":
			case "3":
			case "4":
			case "5":
			case "6":
			case "7":
			case "8":
			case "9":
				_current += _code[i];
			break;
			
			case "{":
			case "}":
				
				if(!_env.IN_STRING && !_env.IN_BLOCK_QUOTE && !_env.IN_NATIVE)
				{
					
					if(_code[i] == "{" && _code[i + 1] && _code[i + 1] == _code[i])
					{
						_env.IN_NATIVE = true;

						addToken(_current, _env);
						_current = "{{";
						
						i++;
					}
					else if(_code[i] == "{" && _code[i + 1] && _code[i + 1] != "}" && _code[i -  1] && (_code[i - 1] == "=" || _code[i - 1] == "," || _code[i -  1] == "return"))
					{
						// obj
						_env.flowObject++;
						_current += "{";
					}
					else if(_code[i] == "{" && _code[i + 1] && _code[i + 1] != "}" && (_before == "=" || _before == "," || _before == "return" || _before == "("))
					{
						// obj 
						_env.flowObject++;
						_current += "{";
						addToken(_current, _env),
						_current = "";
					}
					else if(_code[i] == "{" && _before && _before == ")")
					{
						// function() = {}; or catch(e){}
						addToken(_current, _env);
						if(_code[i+1] == "}")
						{
							addToken("{", _env);
							if(_env.flowObject < 1)
							{
								incToken(_env);
							}
							addToken("}", _env);
							addFlow(_env);
							i++;
						}
						else
						{
							addToken(_code[i], _env);
							if(_env.flowObject < 1)
							{
								incToken(_env);
							}
							_env.flowBracket++;
						}
						_current = "";
					}
					else if(_code[i] == "{" && _code[i + 1] && _code[i + 1] == "}" && _env.flowObject < 1)
					{
						// obj
						addToken(_current, _env);
						addToken("{", _env);
						addToken("}", _env);
						i++;
						_current = "";
					}
					else 
					{
						if(_code[i] == "{")
						{
							if(_env.flowObject < 1)
							{
								addToken(_current, _env);
								addToken(_code[i], _env);
								incToken(_env);
								_env.flowBracket++;
								
								_current+= "";
								
							}
							else
							{
								addToken(_current, _env);
								addToken("{", _env);
								_env.flowObject++;
								//_current += _code[i];
								_current = "";
							}
						}
						else 
						{
							if(_env.flowObject > 0 || _env.flowAccessor > 0 )
							{								
								//_current += _code[i];
								addToken(_current, _env);
								addToken("}", _env);
								//addFlow(_env);
								_env.flowObject--;
								_current = "";
							}
							else 
							{
								if(_env.SWITCH > 0)
								{
									_env.SWITCH--;
								}
								//_current += "}";
								addToken(_current, _env);
								addToken("}", _env);
								addFlow(_env);

								//incToken(_env);
								_env.flowBracket--;

								_current = "";
							}
							
						}
					}
					
				}
				else if(_env.IN_NATIVE && _code[i] == "}" && _code[i + 1] && _code[i + 1] == _code[i])
				{
					_env.IN_NATIVE = false;
					_current += "}}";
					addToken(_current, _env);
					addFlow(_env);
					_current = "";
					i++;
				}
				else 
				{
					_current += _code[i];
				}
			break;
			
			case "[":
			case "]":
			case "(":
			case ")":
				if(!_env.IN_STRING && !_env.IN_BLOCK_QUOTE && !_env.IN_NATIVE)
				{
					if(_code[i] == "(")
					{
						setFor(_current, _env);
						setSwitch(_current, _env);
						_env.flowParenthesis++;
					}
					else if(_code[i] == ")")
					{
						_env.flowParenthesis--;
					}
					else if(_code[i] == "[")
					{
						_env.flowAccessor++;
					}
					else if(_code[i] == "]")
					{
						_env.flowAccessor--;
					}

					addToken(_current, _env);
					addToken(_code[i], _env);
					_current = "";
				}
				else 
				{
					_current += _code[i];
				}
			break;
			
			case ";":
				if(!_env.IN_STRING && !_env.IN_BLOCK_QUOTE && !_env.IN_NATIVE)
				{
					addToken(_current, _env);
					addToken(";", _env);
					_current = "";
					if(_env.FOR == 0)
					{
						addFlow(_env);
					}
					else 
					{
						_env.FOR--;
					}
					
				}
				else 
				{
					_current += _code[i];
				}
			break;
			
			case ":":
				if(!_env.IN_STRING && !_env.IN_BLOCK_QUOTE && !_env.IN_NATIVE && _env.SWITCH == 0)
				{
					addToken(_current, _env);
					addToken(":", _env);
					_current = "";
				}
				else if(!_env.IN_STRING && !_env.IN_BLOCK_QUOTE && !_env.IN_NATIVE && _env.SWITCH > 0)
				{
					addToken(_current, _env);
					addToken(":", _env);
					_current = "";
					addFlow(_env);
				}
				else 
				{
					_current += _code[i];
				}
			break;
			
			case ",":
				if(!_env.IN_STRING && !_env.IN_BLOCK_QUOTE && !_env.IN_NATIVE)
				{
					addToken(_current, _env);
					addToken(",", _env);
					_current = "";
				}
				else 
				{
					_current += _code[i];
				}
			break;
			
			case "!":
			case "+":
			case "-":
			
				if(!_env.IN_STRING && !_env.IN_BLOCK_QUOTE && !_env.IN_NATIVE)
				{
					addToken(_current, _env);
					if(_code[i + 1] && _code[i + 1] == _code[i])
					{
						addToken(_code[i] + _code[i + 1], _env);
						i++;
					}
					else if(_code[i + 1] && _code[i + 1] == "=")
					{
						// += -=
						addToken(_code[i] + _code[i + 1], _env);
						i++;
					}
					else 
					{
						addToken(_code[i], _env);
					}
					_current = "";
				}
				else 
				{
					_current += _code[i];
				}
			break;
			case "*":
			case ".":
				if(!_env.IN_STRING && !_env.IN_BLOCK_QUOTE && !_env.IN_NATIVE)
				{
					var _number = isNumber(_current);
					if(_number.check)
					{
						_current += _code[i];
					}
					else 
					{
						addToken(_current, _env);
						addToken(_code[i], _env);
						_current = "";
					}
				}
				else 
				{
					_current += _code[i];
				}
			break;
			
			default:
				_current += _code[i];
				var _currentScope = [];
				if(_env.TOKENS.length > 0)
				{
					_currentScope = _env.TOKENS[_env.TOKENS.length - 1];
				}
				
				var _lastToken;
				if(_currentScope.length > 0)
				{
					_currentScope = _currentScope[_currentScope.length - 1];
				}
				
				if(_current == "in" && _code[i+1] == " ")
				{
					_env.FOR = 0;
				}
				
				if(!_env.IN_STRING && !_env.IN_BLOCK_QUOTE && !_env.IN_NATIVE && _current == "function" && (_currentScope == ":" || _currentScope == "," || _currentScope == "["))
				{
					var _functionID = "__NERD_LAMBDA_FUNC_" + Math.random().toString(36).slice(2, 12);
					var _bracketState = 0;
					var _end = -1;
					for(var b = i; b < _code.length; b++)
					{
						if(_code[b] == "{")
						{
							_bracketState++;
						}
						else if(_code[b] == "}")
						{
							_bracketState--;
							if(_bracketState == 0)
							{
								_end = b+1;
								break;
							}
						}
					}
					var bodyLambda = "var " + _functionID + " = " + _code.substring(i-8, _end);
					_current = "";
					_code = _code.substring(0, i+1) + _functionID + _code.substring(_end);
					var _tmpEnv = createEnv();
					_tmpEnv.REGISTER = _tmpEnv.REGISTER.concat(_env.REGISTER);
					var _tmpFn = parseCode(bodyLambda, 0, _tmpEnv);
					_env.LAMBDA[_functionID] = { code: bodyLambda, env: _tmpEnv };
				}
				
			break;
		}
		_env.CURSOR++;
	}

	addFlow(_env);
	if(_current.length > 0 && i == _code.length)
	{
		error("[!] untermined instruction");
	}
	if(_env.flowBracket < 0)
	{
		error("[!] Missing opening bracket {");
	}
	else if(_env.flowBracket > 0)
	{
		error("[!] Missing closing bracket }");
	}
	
	if(_env.flowObject < 0)
	{
		error("[!] Missing opening bracket {");
	}
	else if(_env.flowObject > 0)
	{
		error("[!] Missing closing bracket }");
	}
	
	if(_env.flowParenthesis < 0)
	{
		error("[!] Missing opening parenthesis (");
	}
	else if(_env.flowParenthesis > 0)
	{
		error("[!] Missing closing parenthesis )");
	}
	
	if(_env.flowAccessor < 0)
	{
		error("[!] Missing opening accessor [");
	}
	else if(_env.flowAccessor > 0)
	{
		error("[!] Missing closing accessor ]");
	}
	
	if(_env.IN_NATIVE)
	{
		error("[!] Missing closing native block }} ]");
	}
	
	if(_env.IN_STRING)
	{
		error("[!] Missing closing string \" }} ]");
	}
	
	if(_env.IN_BLOCK_QUOTE)
	{
		error("[!] Missing closing block quote ` }} ]");
	}
	
}

module.exports = parseCode;
