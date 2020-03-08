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

function Compiler()
{
	var _handler = this;
	this.COMPILER = "g++";
	
	this.GEN = "";
	this.ENV = fs.readFileSync(path.join(__dirname, "src", "env.js")).toString();
	this.MAIN = fs.readFileSync(path.join(__dirname, "squel", "main.cpp")).toString();
	
	this.OUT = "";
	this.OPTION = "";
	
	this.HEADER = [];
	
	this.INIT = [];
	
	this.CODE = "";
	
	this.FOOTER = "";
	
	/*** METHODS ***/
	this.Parse = function(_code)
	{
	_code = _code.replace(/(\)[ \r\t\n]+\{)/g, "){");
	_code = parseObject(_code);
	_code = createFunction(_code);
	_code = createAnon(_code);
	_code = formatCatch(_code);
	_code = _code.split(os.EOL);

	function forgeObject(_arr, _var)
	{
		var _code = "";
		for(var i = 0; i < _arr.length; i++)
		{
			if(_arr[i][1] && _arr[i][1][0] == "{")
			{
				var _next = _var + ".__NJS_Get(\"" + _arr[i][0] + "\")";
				_code += _var + ".__NJS_Set(\"" + _arr[i][0] + "\", Object());";
				_code += forgeObject(parseObj(_arr[i][1]), _next);
			}
			else 
			{
				if(_arr[i][0])
				{
					_code += _var + ".__NJS_Set(\"" + _arr[i][0] + "\"," + _arr[i][1] + ");";
				}
			}
		}
		return _code;
	}

	function formatCatch(_code)
	{
		return _code.replace(/(;catch\([a-zA-Z0-9_\-]*\))/, "catch(var)"); // catch
	}

	function parseObject(_code)
	{
		var _search = new RegExp(/(?:var|) ([a-zA-Z0-9_\-]+) *= *\{/);
		var _index = _code.search(_search);
		while(_index > -1)
		{
			var _match = _search.exec(_code.slice(_index));
			var _open = 0;
			var _openIndex = -1;
			var _closeIndex = -1;
			
			for(var i = _index; i < _code.length; i++)
			{
				if(_code[i] == "{")
				{
					_open++;
					if(_open == 1)
					{
						_openIndex = i+1;
					}
				}
				if(_code[i] == "}")
				{
					_open--;
					if(_open == 0)
					{
						_closeIndex = i;
						break;
					}
				}
			}
			if(_closeIndex > _openIndex + 1)
			{
				var _obj = _code.substring(_openIndex-1, _closeIndex+1);
				var _ret = "Object();";
				_ret += forgeObject(parseObject(_obj), _match[1]);
				_code = [_code.slice(0, _openIndex-1), _ret, _code.slice(_closeIndex+1)].join('');
			}
			_index = _code.search(_search);
		}
		return _code;
	}
	
	function varParam(_var)
	{
		return _var.replace(/^ *([0-9]+|"[.]")/, "var($a)");
	}

	function createFunction(_code)
	{	
		var _return = ";return __NJS_Create_Undefined();};";
		var _searchFN = new RegExp(/function +([a-zA-Z0-9_\-]*) *\((.*)\)/);
		var _index = _code.search(_searchFN);
		while(_index > -1)
		{
			var _genFN = "__NJS_FN_" + Math.random().toString(36).substr(2, 10);
			var _var = "";
			var _count = 0;
			var _start = -1;
			var _end = -1;
			
			var _match = _searchFN.exec(_code);
			_match[2] = _match[2].split(",");
			for(var i = 0; i < _match[2].length; i++)
			{
				if(i != 0) _var += ",";
				_var += "var " + _match[2][i];
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
							var _fn = _code.substring(_start, _end);
							_handler.INIT.push("static var " + _match[1] +";");
							var _formated = "static __NJS_FUNCTION_MACRO<var (" + _var + ")> " + _genFN +" = [&](" + _var + ") -> var" + _fn + _return;
							_formated += _match[1] + "=var(&" + _genFN + ");";
							_code = [_code.slice(0, _index), _formated, _code.slice(_end + 1)].join('');				
							break;
						}
					}
			}
			_index = _code.search(_searchFN);
		}
		return _code;
	}

	function createAnon(_code)
	{	
		var _return = "return __NJS_Create_Undefined();};";
		var _searchAnonFN = new RegExp(/function *\(([a-zA-Z0-9_\-]*)\)/);
		var _index = _code.search(_searchAnonFN);
		while(_index > -1)
		{
			var _var = "";
			var _count = 0;
			var _start = -1;
			var _end = -1;
			var _genFN = "__NJS_FN_" + Math.random().toString(36).substr(2, 10);
			var _genVAR = "__NJS_VAR_" + Math.random().toString(36).substr(2, 10);
			
			var _match = _searchAnonFN.exec(_code);
			_match[1] = _match[1].split(",");
			for(var i = 0; i < _match[1].length; i++)
			{
				if(_match[1][i].length > 0)
				{
					if(i != 0) _var += ",";
					_var += "var " + _match[1][i];
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
							var _fn = _code.substring(_start, _end);
							_handler.INIT.push("static __NJS_FUNCTION_MACRO<var (" + _var + ")> " + _genFN +" = [&](" + _var + ") -> var" + _fn + os.EOL + _return);
							//var _formated = "var " + _genVAR + "=var(&" + _genFN + ");";
							var _formated = "var(&" + _genFN + ")";
							_code = [_code.slice(0, _index), _formated, _code.slice(_end + 1)].join('');				
							break;
						}
					}
			}
			_index = _code.search(_searchAnonFN);
		}
		return _code;
	}
	
	function selfCall(_code, _match, _reg, _index)
	{
		var _NJS = "__NJS_";
		var _noCall = ["var", "if", "else if", "else", "catch", "while", "for", "do"];
		if(_match[1].indexOf(_NJS) < 0 && _noCall.indexOf(_match[1]) < 0)
		{
			return _code.replace(_reg, "$1.__NJS_Self_Call($2)");
		}
		else return _code;		
	}
	
	var _parser = 
	[
		[/var +([a-zA-Z0-9_\-]+)? *$/g, "var $1 = Object()"], //var
		[/\. *\b((?!__NJS_)(.*?))\(( *)\) */g, '.__NJS_Call((char*)"$1")'],
		[/\. *\b((?!__NJS_)(.*?))\((.+)\) */g, '.__NJS_Call((char*)"$1", $3)'],
		[/\. *((?!__NJS_)[a-zA-Z0-9_\-]+) *(?:\=) *(.)/g, '.__NJS_Set((char*)"$1", $2)'],
		[/\b((?!__NJS_)[a-zA-Z0-9_\-]+|\)|\]) *(?:\.) *((?!__NJS_)[a-zA-Z0-9_\-]+)/g, '$1.__NJS_Get((char*)"$2")'],
		[/{[ \t\n]+}/g, "Object()"], // replace {} by Object(),
		[/typeof +([a-zA-Z0-9_\-]+)/g, "__NJS_Typeof($1)"], // typeof,
		[/\b((?!__NJS_)[a-zA-Z0-9_\-]+) *\((.*?)\)/g, selfCall], // typeof,
		[/catch *\(e\)/g, "catch(var)"], // typeof,
		[/\b(?!__NJS_)[ \t\n\=](?:\(|)(true|false)(?=[ &\n\;])/g, "__NJS_Create_Boolean($1)"],
		[/\b(?!__NJS_)[ \t\n\=](?:\(|)(true|false)[\)]/g, "__NJS_Create_Boolean($1)"],
	];

	var _match;
	for(var i = 0; i < _parser.length; i++)
	{
		var _reg = new RegExp(_parser[i][0]);
		for(var j = 0; j < _code.length; j++)
		{
			while(_match = _reg.exec(_code[j]))
			{
				if(typeof _parser[i][1] == "function")
				{
					_code[j] = _parser[i][1](_code[j], _match, _reg);
				}
				else if(typeof _parser[i][1] == "string")
				{
					_code[j] = _code[j].replace(_reg, _parser[i][1]);
					
				}
			}			
		}
		
		_handler.INIT = _handler.INIT.join(os.EOL).split(os.EOL);
		
		for(var j = 0; j < _handler.INIT.length; j++)
		{
			while(_match = _reg.exec(_code[j]))
			{
				if(typeof _parser[i][1] == "function")
					_handler.INIT[j] = _parser[i][1](_handler.INIT[j], _match, _reg);
				else if(typeof _parser[i][1] == "string")
					_handler.INIT[j] = _code[j].replace(_reg, _parser[i][1]);
			}
			
		}
	}

	_code = _code.filter(function (el) {return el.length > 0;}); // remove null lines
	_handler.CODE = _code.join("") + ";";
	_handler.INIT = _handler.INIT.join(";");
	_handler.MAIN = _handler.MAIN.replace("{CODE}", _handler.CODE);
	_handler.MAIN = _handler.MAIN.replace("{INIT}", _handler.INIT);
	}
	  
	this.Prepare = function(_folder)
	{
		fs.copyFileSync(__dirname + "/src/njs.h", path.join(_folder, "njs.h"));
	};

	this.Out = function(_name)
	{
		if(os.platform() == "win32" && path.extname(_name) != ".exe") _handler.OUT = _name + ".exe";
		return _handler.OUT;
	}

	this.CLI = function(compiler, out, target, option)
	{
		return `${compiler} ${target} -Wl,--gc-sections -ffunction-sections -fdata-sections -fpermissive -w -s -o ${out} ${option}`;
	}
	  
	this.Compile = function(_folder, _file)
	{
		
		fs.writeFileSync(_file, _handler.MAIN);
		process.chdir(_folder);
		var _exec = _handler.CLI(_handler.COMPILER, _handler.OUT, _file, _handler.OPTION);
		execSync(_exec);
		
	}
	/*** END METHODS ***/
	
}

module.exports = new Compiler();