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
	this.DIR = [];

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
		
	this.INIT = "";
	this.DECL = "";
	this.REQUIRE = "";
	this.INCLUDE = "";
	
	this.INFO = 
	{
		FUNCTION: [],
		CACHE: {},
		VALUE: [],
		CALL: {},
		SCOPE: {},
		HOISTING: [],
	};

	if(this.ENV.stdlib)
	{
		for(var _s in this.ENV.stdlib)
		{
			if(typeof this.ENV.stdlib[_s] == "string")
			{
				this.DECL += "var " + this.ENV.stdlib[_s] + ";";
				this.STD += this.ENV.stdlib[_s] +  " = require(\"" + this.ENV.stdlib[_s] + "\");";
			}
			else if(typeof this.ENV.stdlib[_s] == "object")
			{
				this.DECL += "var " + this.ENV.stdlib[_s].bind + ";";
				this.STD += this.ENV.stdlib[_s].bind +  " = require(\"" + this.ENV.stdlib[_s].module + "\");";
			}
		}
	}
	
	this.CODE = "";
	
	this.FOOTER = "";
	
	/*** METHODS ***/
	this.Parse = function(code, _file)
	{
		var _env = createEnv(_handler.PATH, _file);
		code = this.STD + code;
		parseCode(code, 0, _env);
		parseAST(_env);
		var _generated = generateCode(_env);
		_handler.MAIN = _handler.MAIN.replace("{CODE}", _generated);
		_handler.MAIN = _handler.MAIN.replace("{INIT}", COMPILER.INIT);
		_handler.MAIN = _handler.MAIN.replace("{DECL}", COMPILER.DECL);
		_handler.MAIN = _handler.MAIN.replace("{INCLUDE}", COMPILER.INCLUDE);
		_handler.MAIN = _handler.MAIN.replace("{{__PLATFORM__}}", os.platform());
	}
	  
	this.Prepare = function(_folder)
	{
		if((!CLI.cli["--profile"]) || CLI.cli["--profile"].argument != "use")
		{
			copyDirSync(path.join(__dirname, "nerdcore"), _folder, false);
		}
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
