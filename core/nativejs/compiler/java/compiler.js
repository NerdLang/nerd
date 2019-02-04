/*
 * This file is part of NectarJS
 * Copyright (c) 2019 Adrien THIERRY
 * http://nectarjs.com - https://nectrium.com
 *
 * sources : https://github.com/nectarjs/nectarjs
 *
 * NectarJS
 * Copyright (C) 2019 Adrien THIERRY - Necrium
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

function Compiler()
{
  this.Default = "javac";
  this.End = ".java";

  var EXISTING_ENV =
  {
    java: require("./env/java.js"),
  }
  global.NJS_ENV = EXISTING_ENV["java"];

  global.createRandomVar = require("./tools/createRandomVar.js");

  global.getClass = require("./gen/getClass.js");
  global.setClass = require("./gen/setClass.js");
  global.genRequire = require('./gen/genRequire.js');
  global.genInclude = require("./gen/genInclude.js");
  global.getLibC = require("./gen/getLibC.js");
  global.genStdLib = require("./gen/genStdLib.js");
  global.genGlobal = require("./gen/genGlobal.js");
  global.genTarget = require("./gen/genTarget.js");

  global.CBFN = [];
  global.LOCAL_PARAM = [];
  global.fnOptimizer = require("./optim/fnOptimizer.js");

  global.VARIABLE = [];
  global.FUNCSTACK = [];
  global.FUNCINDEX = 0;
  global.DECLARATION = "";
  global.INTERMEDIATE = "";
  global.RANDOMVAR = [];


  global.GLOBAL_DECLARATION = "";
  global.GLOBAL_GEN = "";
  global.GLOBAL_VAR = [];

  global.GENERATED = "";


  this.Squel = NJS_ENV.base;

  this.Parse = function(obj)
  {
    var _str = "";
    if(obj.body) obj = obj.body;

    for(var o in obj)
  	{
      WHERE = "MAIN";
  		switch(obj[o].type)
  		{
  			case "FunctionDeclaration":
				WHERE = "function";
				//_str += FunctionDeclaration(obj[o]);
  				break;

  			case "ExpressionStatement":
				//_str += ExpressionStatement(obj[o]);
  				break;
			case "ReturnStatement":
				//_str += ReturnStatement(obj[o]);
			  break;
			case "VariableDeclaration":
				//_str += VariableDeclaration(obj[o]);
			  break;
			case "VariableDeclarator":
				  //_str += VariableDeclarator(obj[o]);
			  break;
			case "IfStatement":
				//_str += IfStatement(obj[o])
			  break;
			case "EmptyStatement":
			  break;
			case "ForStatement":
				//_str += ForStatement(obj[o]);
			  break;
			case "WhileStatement":
				  //_str += WhileStatement(obj[o]);
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

    return _str;
  }

  this.Compile = function()
  {

  }

  this.Prepare = function(name, squel)
  {
    return squel.replace("__CLASSNAME__", name);
  }

  this.CLI = function(compiler, out, TO, option)
  {
	execSync("cpp -P .nectar/" + out + ".java > .nectar/" + out + ".java && cpp -P compiler/java/src/VAR.java > .nectar/VAR.java");
	
    return compiler + " -d " + path.dirname(out) + " " + option + " .nectar/VAR.java " + TO;
  }

  this.Run = function(out)
  {
    var tmp = path.basename(out).split(".");
    var _class = "";
    for(var i = 0; i < tmp.length - 1; i++)
    {
      if(i > 0) i += ".";
      _class += tmp[i];
    }
    return "cd " + path.dirname(out) + " && java " + out.split(".class")[0];
  }
 
}

module.exports = new Compiler();
