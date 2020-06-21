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
global.genMetaFunction = require("./lib/genMetaFunction.js");
global.genPackage = require("./lib/genPackage.js");

global.RND = function() { return "__" + Math.random().toString(36).substring(7); };

global.ENV = loadEnv();
function loadEnv()
{
	var _res = {};
	var _folder = path.join(__dirname, "/env/");
	var _list = fs.readdirSync(_folder);
	for(var _el in _list)
	{
		var _name = _list[_el].substring(0, _list[_el].length-3);
		var _e = require(path.join(_folder, _list[_el]));
		_res[_name] = _e;
	}
	return _res;
}

function setRegister(_value)
{
	var _reg;
	try 
	{
		_reg = parseInt(_value)
		console.log("[*] Set register at: " + _reg);
	}
	catch(e)
	{
		console.log("[!] Invalid register, integer needed");
		process.exit(1);
	}
	return _reg;
}

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

var FAST_CALL = ["BinaryExpression", "NumericLiteral"];
function checkFastFunction()
{
	for(var i in COMPILER.INFO.SCOPE)
	{
		for(var j = 0; j < COMPILER.INFO.SCOPE[i].use.length; j++)
		{
			if(COMPILER.INFO.SCOPE[i].init.indexOf(COMPILER.INFO.SCOPE[i].use[j]) < 0)
			{
				COMPILER.INFO.SCOPE[i].fast = false;
				break;
			}
		}

		for(var j = 0; j < COMPILER.INFO.SCOPE[i].call.length; j++)
		{
			if(FAST_CALL.indexOf(COMPILER.INFO.SCOPE[i].call[j]) < 0)
			{
				COMPILER.INFO.SCOPE[i].fast = false;
				break;
			}
		}
	}
}

function Compiler()
{
	var _handler = this;
	this.MAIN_PATH = __dirname;
	this.TARGET = "standard";
	this.SPEC;
	this.EXPOSE = "";
	this.STD = "";
	this.GEN = "";
	this.PATH = "";
	this.LIBS = "";
	this.STATE = "";
	this.PACK = [];

	if(CLI.stack[0]) this.PATH = path.dirname(CLI.stack[0]) + path.sep;
	
	this.ENV = ENV["std"];
	if(CLI.cli["--env"]) 
	{
		var _env = CLI.cli["--env"].argument;
		if(ENV[_env])
		{
			this.ENV = ENV[_env];
		}
		else 
		{
			console.log("[!] ENV: " + _env + " does not exist, please select one of [" + Object.keys(ENV).toString() + "]");
			process.exit(1);
		}
	}
	this.COMPILER = this.ENV.compiler;
	this.PRESET = "none";
	
	this.MAIN = fs.readFileSync(path.join(__dirname, "squel", this.ENV.main)).toString();
	
	this.IN = "";
	this.OUT = "";
	this.TMP_FOLDER = "";
	this.OPTION = "";
	
	this.DECL = [];
	
	this.FFI = [];
	
	this.INIT = "";
	
	this.REQUIRE = "";

	this.READ_ONLY = [];
	
	this.INFO = 
	{
		FUNCTION: [],
		VALUE: [],
		CALL: {},
		SCOPE: {},
	};

	if(this.ENV.stdlib)
	{
		for(var _s in this.ENV.stdlib)
		{
			if(typeof this.ENV.stdlib[_s] == "string")
			{
				this.DECL.push("var " + this.ENV.stdlib[_s] + ";");
				this.STD += this.ENV.stdlib[_s] +  " = require(\"" + this.ENV.stdlib[_s] + "\");";
			}
			else if(typeof this.ENV.stdlib[_s] == "object")
			{
				this.DECL.push("var " + this.ENV.stdlib[_s].bind + ";");
				this.STD += this.ENV.stdlib[_s].bind +  " = require(\"" + this.ENV.stdlib[_s].module + "\");";
			}
		}
	}
	
	this.CODE = "";
	
	this.FOOTER = "";
	
	/*** METHODS ***/
	this.Parse = function(_code)
	{
		if(!CLI.cli["--no-check"]) LINT(_code, this.IN);
		
		if(CLI.cli["--preset"] && CLI.cli["--preset"].argument == "speed") 
		{
			_code = babel.transformSync(_code, 
			{
			  plugins: [path.join(NECTAR_PATH, "node_modules", "babel-plugin-remove-unused-vars"), path.join(NECTAR_PATH, "node_modules", "babel-plugin-minify-dead-code-elimination"),path.join(NECTAR_PATH, "node_modules",  "babel-plugin-minify-guarded-expressions")],
			}).code;
		}
		_code = genRequire(_handler.PATH, COMPILER.STD) + genRequire(_handler.PATH, _code);

		COMPILER.STATE = "REQUIRE";
		COMPILER.REQUIRE = babel.transformSync(COMPILER.REQUIRE, visitor).code;
		checkFastFunction();
		COMPILER.REQUIRE = createClass(COMPILER.REQUIRE);
		COMPILER.REQUIRE = createFunction(COMPILER.REQUIRE);
		COMPILER.REQUIRE = createAnon(COMPILER.REQUIRE);
		
		COMPILER.STATE = "CODE";
		_handler.CODE = babel.transformSync(_code, visitor).code;
		checkFastFunction();
		_handler.CODE = createClass(_handler.CODE);
		_handler.CODE = createFunction(_handler.CODE);
		_handler.CODE = createAnon(_handler.CODE);
		
		COMPILER.INIT += COMPILER.REQUIRE;
		
		function createFunction(_code)
		{	
			var _matchThis = new RegExp(/(| |{|,)__NJS_THIS([\.(";)]|$)/);
			var _return = ";return __NJS_Create_Undefined();}";
			var _returnThis = ";return __NJS_THIS;}";
			var _searchFN = new RegExp(/function (.[a-zA-Z0-9_\-]*) *\((.*)\)/);
			var _index = _code.search(_searchFN);
			while(_index > -1)
			{
				var _genFN = "__NJS_FN_" + RND();
				var _genVAR = "__NJS_VAR_" + RND();
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
					var _replaceCall = new RegExp(`__NJS_Call_Function\\\(${_match[1]}(?![a-zA-Z_])`, "g");
					_code = _code.replace(_replaceCall, `__NJS_Call_Fast_Function(${_match[1]}`);
				}
				else
				{
					_variadic = true;
					_parameters = "vector<var> __NJS_VARARGS";
					for(var i = 0; i < _match[2].length; i++)
					{
						if(_match[2][i].length > 0)
						{
							_getVar += `var ${_match[2][i]}; if(__NJS_VARARGS.size() > ${i}) ${_match[2][i]} = __NJS_VARARGS[${i}];`;
						}
					}
				}
				/* TODO: more check to switch from call to fixed_call
				else if(COMPILER.INFO.CALL[_match[1]] && (COMPILER.INFO.CALL[_match[1]].length > 1 || COMPILER.INFO.CALL[_match[1]].length != _match[2].length))
				{
					_variadic = true;
					_parameters = "vector<var> __NJS_VARARGS";
					for(var i = 0; i < _match[2].length; i++)
					{
						if(_match[2][i].length > 0)
						{
							_getVar += `var ${_match[2][i]}; if(__NJS_VARARGS.size() > ${i}) ${_match[2][i]} = __NJS_VARARGS[${i}];`;
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
							_var += "__NJS_VAR " + _match[2][i];
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
									var _fn = "{" + _getVar + _code.substring(_start + 1, _end);
									var _fnThis = "{" + _getVar + " var __NJS_THIS = __NJS_Create_Object();" + _code.substring(_start + 1, _end);

									if(_code.search(_matchThis) > -1) _fn = _fnThis;

									_handler.DECL.push("var " + _match[1] +";");

									var _formated = `__NJS_DECL_FUNCTION<__NJS_VAR (${_parameters})>* ${_genFN} = new __NJS_DECL_FUNCTION<__NJS_VAR (${_parameters})>([=]( ${_parameters} ) -> __NJS_VAR ${_fn} ${_return} );`;
									_formated += _match[1] + "=__NJS_VAR(__NJS_FUNCTION, " + _genFN + ");";

									if(_match[1].indexOf("__MODULE") != 0)
									{
										var _genNew = "__NEW_" + _genFN;
										var _addNew = `__NJS_DECL_FUNCTION<__NJS_VAR (${_parameters})>* ${_genNew} = new __NJS_DECL_FUNCTION<__NJS_VAR (${_parameters})>([=]( ${_parameters} ) -> __NJS_VAR ${_fnThis} ${_returnThis} );`;
										_addNew += "var __NEW_" + _match[1] + "=__NJS_VAR(__NJS_FUNCTION, " + _genNew + ");";

										_formated += _addNew;
									}
									
									_code = [_code.slice(0, _index), _formated, _code.slice(_end + 1)].join('');
								}
								else 
								{
									// FAST CALL HERE
									var _fn = _code.substring(_start, _end);
									_handler.DECL.push(`int ${_match[1]}(${_parameters})${_fn}; return 0;}`);
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

		function createClass(_code)
		{	
			var _matchThis = new RegExp(/(| |{|,)__NJS_THIS([\.(";)]|$)/);
			var _return = ";return __NJS_Create_Undefined();}";
			var _returnThis = ";return __NJS_THIS;}";
			var _searchFN = new RegExp(/function *__NJS_CLASS_(.[a-zA-Z0-9_\-]*) *\((.*)\)/);
			var _index = _code.search(_searchFN);

			while(_index > -1)
			{
				var _genFN = "__NJS_FN_" + RND();
				var _var = "";
				var _count = 0;
				var _start = -1;
				var _end = -1;
			
				let _match = _searchFN.exec(_code);

				_match[2] = _match[2].split(",");
				var _getVar = "";
				for(var i = 0; i < _match[2].length; i++)
				{
					if(_match[2][i].length > 0)
					{
						_getVar += `var ${_match[2][i]}; if(__NJS_VARARGS.size() > ${i}) ${_match[2][i]} = __NJS_VARARGS[${i}];`;
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
								var _fn = "{" + _getVar + _code.substring(_start + 1, _end);

								_handler.DECL.push("var " + _match[1] +";");

								var _formated = "__NJS_DECL_FUNCTION<__NJS_VAR (vector<var>)>* " + _genFN +" = new __NJS_DECL_FUNCTION<__NJS_VAR (vector<var>)>([=]( vector<var> __NJS_VARARGS) -> __NJS_VAR" + _fn + _return + ");";
								_formated += _match[1] + "=__NJS_VAR(__NJS_FUNCTION, " + _genFN + ");";

								if(_match[1].indexOf("__MODULE") != 0)
								{
									
									var _genNew = "__NEW_" + _genFN;
									var _addNew = "__NJS_DECL_FUNCTION<__NJS_VAR (vector<var>)>* " + _genNew +" = new __NJS_DECL_FUNCTION<__NJS_VAR (vector<var>)>([=](vector<var> __NJS_VARARGS) -> __NJS_VAR" + _fn + _returnThis + ");";
									_addNew += "var __NEW_" + _match[1] + "=__NJS_VAR(__NJS_FUNCTION, " + _genNew + ");";

									_formated += _addNew;
								}
								
								_code = [_code.slice(0, _index), _formated, _code.slice(_end + 1)].join('');
								break;
							}
						}
				}
				_index = _code.search(_searchFN);
			}
			_code = replaceObjAddr(_code);
			return _code;
		}

		function createAnon(_code)
		{	
			var _matchThis = new RegExp(/(| |{|,)__NJS_THIS([\.(";)]|$)/);
			var _return = "return __NJS_Create_Undefined();}";
			var _searchAnonFN = new RegExp(/(var)* *([a-zA-Z0-9_]*) *= *function *\(([a-zA-Z0-9_\-, ]*)\)/);
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
								_formated += "__NJS_VAR(__NJS_FUNCTION, new function<__NJS_VAR (vector<var>)> ([=](vector<var> __NJS_VARARGS) -> __NJS_VAR" + _fn + os.EOL + _return + "));";
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

		_handler.DECL = _handler.DECL.filter(function(v,i)
		{
			return _handler.DECL.indexOf(v) === i;
		}).join(";");
		
		_handler.MAIN = _handler.MAIN.replace("{CODE}", _handler.CODE);
		_handler.MAIN = _handler.MAIN.replace("{INIT}", _handler.INIT);
		_handler.MAIN = _handler.MAIN.replace("{DECL}", _handler.DECL);
		_handler.MAIN = _handler.MAIN.replace("{INCLUDE}", _handler.FFI.join(os.EOL));
		_handler.MAIN = _handler.MAIN.replace("{{__PLATFORM__}}", os.platform());
	}
	  
	this.Prepare = function(_folder)
	{
		var _reg = 1000000;
		if(this.ENV.name == "arduino")
		{
			_reg = 250;
			if(!this.TARGET)
			{
				this.TARGET = "nano"
			}
			if(this.TARGET.substring(0, 4) == "nano") _reg = 50;
		}


		if(CLI.cli["--register"]) setRegister(CLI.cli["--register"].argument);
		if(CLI.cli["-r"]) setRegister(CLI.cli["-r"].argument);

		var _src = fs.readFileSync(__dirname + "/src/njs.h").toString();
		_src = _src.replace(/{{REGISTER}}/g, _reg);
		fs.writeFileSync(path.join(_folder, "njs.h"), _src);
	};

	this.Out = function(_name)
	{
		if(os.platform() == "win32" && path.extname(_name) != ".exe") _handler.OUT = _name + ".exe";
		else _handler.OUT = _name;
		if(COMPILER.ENV.out && typeof COMPILER.ENV.out == "function")
		{
			_handler.OUT = COMPILER.ENV.out(_name);
		}
		return _handler.OUT;
	}

	this.CLI = function(compiler, out, _in, option)
	{
		return this.ENV.cli(compiler, this.preset, out, _in, option, this.TARGET, this.SPEC);
	}
	  
	this.Compile = function(_folder, _file)
	{
		
		fs.writeFileSync(_file, _handler.MAIN);
		process.chdir(_folder);
		var _exec = _handler.CLI(_handler.COMPILER, _handler.OUT, _file, _handler.OPTION);
		execSync(_exec);
		
	}
	
	this.Package = function()
	{
		if(this.PACK && this.PACK.length)
		{
			for(var i = 0; i < this.PACK.length; i++)
			{
				copyRecursiveSync(this.PACK[i], this.OUT);
			}
		}
	}
	/*** END METHODS ***/
	
}

module.exports = new Compiler();
