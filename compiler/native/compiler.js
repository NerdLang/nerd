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
global.babel = require( '@babel/core' );
babel.generate = require( '@babel/generator' ).default;

 var visitor = require("./visitor/visitor.js");
 
var genRequire = require("./lib/genRequire.js");
var parseObj = require("./lib/parseObj.js");

global.RND = function() { return "__" + Math.random().toString(36).substring(7); };

function Compiler()
{
	var _handler = this;
	this.COMPILER = "g++";
	
	this.GEN = "";
	this.PATH = "";
	if(CLI.stack[0]) this.PATH = path.dirname(CLI.stack[0]) + path.sep;
	this.ENV = fs.readFileSync(path.join(__dirname, "src", "env.js")).toString();
	this.MAIN = fs.readFileSync(path.join(__dirname, "squel", "main.cpp")).toString();
	
	this.OUT = "";
	this.OPTION = "";
	
	this.DECL = "";
	
	this.FFI = [];
	
	this.INIT = "";
	
	this.REQUIRE = "";
	
	this.CODE = "";
	
	this.FOOTER = "";
	
	/*** METHODS ***/
	this.Parse = function(_code)
	{
	_code = genRequire(_handler.PATH, _code);
	
	COMPILER.REQUIRE = babel.transformSync(COMPILER.REQUIRE, visitor).code;
	COMPILER.REQUIRE = createFunction(COMPILER.REQUIRE);
	COMPILER.REQUIRE = createAnon(COMPILER.REQUIRE);

	_handler.CODE = babel.transformSync(_code, visitor).code;
	_handler.CODE = createFunction(_handler.CODE);
	_handler.CODE = createAnon(_handler.CODE);
	
	COMPILER.INIT = babel.transformSync(COMPILER.INIT, visitor).code;
	COMPILER.INIT += COMPILER.REQUIRE;
	
	function createFunction(_code)
	{	
		var _return = ";return __NJS_Create_Undefined();};";
		var _searchFN = new RegExp(/function +([a-zA-Z0-9_\-]*) *\((.*)\)/);
		var _index = _code.search(_searchFN);
		while(_index > -1)
		{
			var _genFN = "__NJS_FN_" + RND();
			var _var = "";
			var _count = 0;
			var _start = -1;
			var _end = -1;
			
			var _match = _searchFN.exec(_code);
			_match[2] = _match[2].split(",");
			for(var i = 0; i < _match[2].length; i++)
			{
				if(_match[2][i].length > 0)
				{
					if(i != 0) _var += ",";
					_var += "var " + _match[2][i];
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
							_handler.DECL += "static var " + _match[1] +";";
							var _formated = "__NJS_FUNCTION_MACRO<var (" + _var + ")> " + _genFN +" = [&](" + _var + ") -> var" + _fn + _return;
							_formated += _match[1] + "=var(__NJS_FUNCTION, &" + _genFN + ");";
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
			var _genFN = "__NJS_FN_" + RND();
			var _genVAR = "__NJS_VAR_" + RND();
			
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
							_handler.INIT += "__NJS_FUNCTION_MACRO<var (" + _var + ")> " + _genFN +" = [&](" + _var + ") -> var" + _fn + os.EOL + _return;
							var _formated = "static var(__NJS_FUNCTION, &" + _genFN + ")";
							_code = [_code.slice(0, _index), _formated, _code.slice(_end + 1)].join('');				
							break;
						}
					}
			}
			_index = _code.search(_searchAnonFN);
		}
		return _code;
	}
	
	_handler.MAIN = _handler.MAIN.replace("{CODE}", _handler.CODE);
	_handler.MAIN = _handler.MAIN.replace("{INIT}", _handler.INIT);
	_handler.MAIN = _handler.MAIN.replace("{DECL}", _handler.DECL);
	_handler.MAIN = _handler.MAIN.replace("{INCLUDE}", _handler.FFI.join(os.EOL));
	}
	  
	this.Prepare = function(_folder)
	{
		fs.copyFileSync(__dirname + "/src/njs.h", path.join(_folder, "njs.h"));
	};

	this.Out = function(_name)
	{
		if(os.platform() == "win32" && path.extname(_name) != ".exe") _handler.OUT = _name + ".exe";
		else _handler.OUT = _name;
		return _handler.OUT;
	}

	this.CLI = function(compiler, out, target, option)
	{
		return `${compiler} ${target} ${option} -Wl,--gc-sections -ffunction-sections -fdata-sections -fpermissive -w -s -o ${out}`;
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