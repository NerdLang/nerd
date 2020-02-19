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
	this.folder = "cpp";
	this.defaultCompiler = "g++";
	this.end = ".cpp";
	
	this.GEN = "";
	this.ENV = fs.readFileSync(path.join(__dirname, "src", "env.js")).toString();
	
	this.STACK = "";
	this.DEFINE = [];
	this.FUNCSTACK = [];
	this.VARIABLE = [];
	this.LOCAL_PARAM = [];
	this.CBFN = [];
	
	this.HEADER = "";
	
	this.INIT = "";
	
	this.CODE = "";
	
	this.FOOTER = "";
	
	/*** LIB & TPL LOADER ***/
	this.lib = {};
	this.tpl = {};
	this.src = {};
	
	var libDir = path.join(path.resolve(__dirname), "lib");
	var libs = fs.readdirSync(libDir);
	
	for(var i = 0; i < libs.length; i++)
	{
		var _add = path.join(libDir, libs[i]);
		var _name = libs[i].substring(0, libs[i].length - 3);
		this.lib[_name] = require(_add);
		global[_name] = require(_add);
	}
	
	var tplDir = path.join(path.resolve(__dirname), "tpl");
	var tpls = fs.readdirSync(tplDir);
	
	for(var i = 0; i < tpls.length; i++)
	{
		var _add = path.join(tplDir, tpls[i]);
		var _name = tpls[i].substring(0, tpls[i].length - 3);
		this.tpl[_name] = require(_add);
	}
	
	var srcDir = path.join(path.resolve(__dirname), "src");
	var srcs = fs.readdirSync(srcDir);
	
	for(var i = 0; i < srcs.length; i++)
	{
		var _add = path.join(srcDir, srcs[i]);
		var _name = srcs[i].substring(0, srcs[i].length - 4);
		this.src[_name] = fs.readFileSync(_add).toString();
	}
	/*** END LIB & TPL LOADER ***/
	
	/*** METHODS ***/
  this.Parse = function(obj)
  {
    var _code = "";
    if(obj.body) obj = obj.body;

    for(var o in obj)
  	{
      WHERE = "MAIN";
  		switch(obj[o].type)
  		{
  			case "FunctionDeclaration":
            WHERE = "function";
				_code += FunctionDeclaration(obj[o]);
  				break;

  			case "ExpressionStatement":
				_code += ExpressionStatement(obj[o]);
  				break;
        case "ReturnStatement":
            _code += ReturnStatement(obj[o]);
          break;
        case "VariableDeclaration":
            _code += VariableDeclaration(obj[o]);
          break;
        case "VariableDeclarator":
              _code += VariableDeclarator(obj[o]);
          break;
        case "IfStatement":
            _code += IfStatement(obj[o]);
          break;
        case "EmptyStatement":
          break;
        case "ForStatement":
            _code += ForStatement(obj[o]);
          break;
        case "WhileStatement":
              _code += WhileStatement(obj[o]);
          break;
        case "DoWhileStatement":
              console.error("Parser for DoWhileStatement is not implemented yet");
              process.exit(1);
          break;
        case "BreakStatement":
              console.error("Parser for BreakStatement is not implemented yet");
              process.exit(1);
          break;
        case "SwitchStatement":
              console.error("Parser for SwitchStatement is not implemented yet");
              process.exit(1);
          break;
  			default:
          ERROR = true;
  				console.log("Parser for " + obj[o].type + " is not implemented yet");
  				break;
  		}
  	}

    return _code;
  }
	  
	  this.Prepare = function(_folder, _file)
	  {
		  console.log(_folder, "njs.cpp");
		  fs.copyFileSync("./compiler/" + COMPILER.folder + "/src/njs.h", path.join(_folder, "njs.h"));
		return fs.readFileSync("./compiler/" + COMPILER.folder + "/squel/main.txt").toString();
	  };
	  
	  this.CLI = function(compiler, out, TO, option)
	  {
		return `${compiler} ${TO} -Wl,--gc-sections -ffunction-sections -fdata-sections -o ${out}`;
	  }
	  
	/*** END METHODS ***/
	
	this.define = function(_var)
	{
		if(this.DEFINE.indexOf(_var) < 0)
		{
			this.DEFINE.push(_var);
		}
	}
	
	/*** FUNCTIONS ***/
	
	this.genDep = function()
	{
		
	}
	
	/*** END FUNCTIONS***/
}

module.exports = Compiler;