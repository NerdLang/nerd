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

global.genRequire = require("./require.js");

global.KEYWORD = ["var", "new", "this", "case", "default", "true", "false", "break", "function", "switch", "for", "do", "while", "in", "if", "else", "null", "Infinity", "NaN", "return", "include", "try", "catch"];
global.RESERVED = ["var", "new", "this", "case", "default", "Prototype", "break", "function", "switch", "for", "do", "while", "in", "if", "else", "null", "true", "false", "argc", "argv", "main", "Object", "Array",  "Infinity", "NaN", "include", "try", "catch", "arguments", "return", "address_of", "length_of", "size_of", "type_of", "typeof", "__NERD_Multi_Line_Quote", "require", "exit"];
global.ASSIGNMENT_OPERATOR = ["=", "+=", "-=", "/=", "*="];
global.OBJECT_OPERATOR = [":"];
global.ITERATOR = ["in"];
global.INIT_OPERATOR = ["[]", "{}"];
global.CONDITIONAL_TOKENS = ["==", "<", ">", "<<", ">>", "<=", ">=", "!="];
global.OPERATOR_TOKENS = ["+", "-", "*", "/"];
global.UNARY_TOKENS = ["!"];
global.INCREMENT_TOKENS = ["++", "--"];
global.CONDITIONAL_LOGIC = ["&&", "||"];
global.BOOLEAN_KEYWORD = ["true", "false"];
global.PARENTHESIS_LOGIC = ["(", ")"];
global.DELIMITER = ["(", ")", "{", "}", "[", "]", ",", "."];
global.ALL_TOKEN_LOGIC = global.CONDITIONAL_TOKENS.concat(global.OPERATOR_TOKENS, global.CONDITIONAL_LOGIC);
global.NUMBERS = ["0","1","2","3","4","5","6","7","8","9", "."];
global.FIRST_VAR_CHAR = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
global.FULL_VAR_CHAR = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789";
global.VALUES = ["NUMBER", "VARIABLE", "STRING", "BOOLEAN", "NULL"];

global.createEnv = function(_path, _file)
{
	var envObject = 
	{
		REGISTER: 
		[
			["global", "__dirname", "FixedArray", "Array", "Object", "__NERD_THIS", "Prototype"],
			[],
		],
		FLOW: [],
		AST: [],
		LOGICAL_FLOW: [{DO:false, IF:false, FUNCTION:false, MAIN:true, TRY: false}],
		MAP: [],
		IN_OBJECT: false,
		IN_STRING: false,
		IN_BLOCK_QUOTE: false,
		IN_NATIVE: false,
		CURRENT_OBJECT: "",
		IN_DO: false,
		IN_IF: false,
		TOKENS: [],
		TOKENSMAP: [],
		SWITCH_MAP: [],
		POSITION: 0,
		LINE: 0,
		CURSOR: 0,
		FOR: 0,
		SWITCH: 0,
		IN_CASE: false,
		PATH: _path,
		FILE: _file,
		flowObject: 0,
		flowBracket: 0,
		flowParenthesis: 0,
		flowAccessor: 0,
		LAMBDA: {},
	};
	envObject.REGISTER[0] = envObject.REGISTER[0].concat(global.COMPILER.ENV.stdlib);
	return envObject;
}

global.generateCode = function(_env)
{
	var code = "";
	for(var i = 0; i < _env.FLOW.length; i++)
	{
		if(_env.AST[i] && _env.AST[i][0] && _env.AST[i][0] == "NATIVE")
		{
			code += _env.FLOW[i][0].slice( 2, _env.FLOW[i][0].length - 2);
		}
		else 
		{
			code += _env.FLOW[i].join(" ");
			code += "\n";
		}
	}
	return code;
}

global.parseAST = function(_env)
{
	for(var i = 0; i < _env.FLOW.length; i)
	{
		i = global.verifyFlow(_env.AST[i], _env.FLOW[i], i, _env.FLOW, _env);
	}
}

global.error = function(_msg)
{
	console.error(_msg); 
	process.exit(1);
}

global.nextScope = function(_env)
{
	_env.REGISTER.push([]);
	_env.LOGICAL_FLOW.push({"DO":false, "IF": false, "FUNCTION":false, MAIN: false, TRY: false});
}

global.popScope = function(_env)
{
	_env.REGISTER.pop();
	_env.LOGICAL_FLOW.pop();
}

global.getLogical = function(_env)
{
	return _env.LOGICAL_FLOW[_env.LOGICAL_FLOW.length - 1];
}

global.addLogical = function(_type, _env)
{
	_env.LOGICAL_FLOW[_env.LOGICAL_FLOW.length - 1][_type] = true;
}

global.removeLogical = function(_type, _env)
{
	_env.LOGICAL_FLOW[_env.LOGICAL_FLOW.length - 1][_type] = false;
}

global.checkVarExists = function(_name, _env, _flow)
{
	//for(var i = 0; i < _env.REGISTER.length; i++)
	//{
		if(_env.REGISTER[_env.REGISTER.length - 1].indexOf(_name) > -1)
		{
			return { error: true, message: `Variable ${_name} already defined` };
		}
	//}
	return { error: false };
}

global.addVar = function(_name, _env)
{
	if(_env.REGISTER[_env.REGISTER.length - 1].indexOf(_name) < 0)
	{
		_env.REGISTER[_env.REGISTER.length - 1].push(_name);
	}
}

global.varExists = function(_name, _env)
{
	for(var i = 0; i < _env.REGISTER.length; i++)
	{
		if(_env.REGISTER[i].indexOf(_name) > -1)
		{
			return true;
		}
	}

	return false;
}