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
 
global.strip = require("strip-comments");
global.babel = require( '@babel/core' );
babel.generate = require( '@babel/generator' ).default;

 var visitor = require("./visitor/visitor.js");
 
var genRequire = require("./lib/genRequire.js");
global.genMetaFunction = require("./lib/genMetaFunction.js");
global.genPackage = require("./lib/genPackage.js");
global.replaceObjAddr = require("./lib/replaceObjAddr.js");

var createFunction = require("./lib/createFunction.js");
var createAnon = require("./lib/createAnon.js");
var createClass = require("./lib/createClass.js");
var hoistingFunction = require("./lib/hoistingFunction.js");

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
	try 
	{
		COMPILER.REGISTER = parseInt(_value)
		console.log("[*] Set register at: " + COMPILER.REGISTER);
	}
	catch(e)
	{
		console.log("[!] Invalid register, integer needed");
		process.exit(1);
	}
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
	this.REGISTER = 100000;
	
	this.DECL = [];
	
	this.FFI = [];
	
	this.INIT = "";
	
	this.REQUIRE = "";

	this.READ_ONLY = [];
	
	this.INFO = 
	{
		Function: [],
		CACHE: {},
		VALUE: [],
		CALL: {},
		SCOPE: {},
		HOISTING: [],
	};
	
	this.GLOBAL = ["__NJS_THIS", "parseInt", "setImmediate", "setTimeout", "setInterval"];
	
	this.VAR_STATE = [[]];

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
	if(this.ENV.check && this.ENV.check.globals)
	{
		for(var g in this.ENV.check.globals)
		{
				this.VAR_STATE[0].push(g);
		}
	}
	
	this.CODE = "";
	
	this.FOOTER = "";
	
	/*** METHODS ***/
	this.Parse = function(_code)
	{
		_code = strip(_code);
		if(CLI.cli["--preset"] && CLI.cli["--preset"].argument == "speed") 
		{
			_code = babel.transformSync(_code, 
			{
			  plugins: [path.join(NECTAR_PATH, "node_modules", "babel-plugin-remove-unused-vars"), path.join(NECTAR_PATH, "node_modules", "babel-plugin-minify-dead-code-elimination"),path.join(NECTAR_PATH, "node_modules",  "babel-plugin-minify-guarded-expressions")],
			}).code;
		}

		if(!CLI.cli["--no-check"]) LINT(_code, this.IN);

		_code = hoistingFunction(_code);
		
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
		_handler.CODE = createClass(_handler.CODE, true);
		
		_handler.CODE = createFunction(_handler.CODE, true);
		_handler.CODE = createAnon(_handler.CODE, true);

		var _hoisting = "";
		for(var i = 0; i < COMPILER.INFO.HOISTING.length; i++)
		{
			_hoisting += "var " + COMPILER.INFO.HOISTING[i] + ";";
		}
		_handler.CODE = _handler.CODE;

		COMPILER.INIT += COMPILER.REQUIRE + _hoisting;
		
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
		copyDirSync(path.join(__dirname, "src"), _folder, true);
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
