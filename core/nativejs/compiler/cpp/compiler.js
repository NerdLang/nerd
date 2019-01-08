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
  global.PreParsing = require("./lib/pre.js");
  global.PostParsing = require("./lib/post.js");
  global.VariableDeclarator = require("./lib/VariableDeclarator.js");
  global.VariableDeclaration = require("./lib/VariableDeclaration.js");
  global.createVar = require("./lib/createVar.js");
  global.callFunction = require("./lib/callFunction.js");
  global.ExpressionStatement = require("./lib/ExpressionStatement.js");
  global.FunctionDeclaration = require("./lib/FunctionDeclaration.js");
  global.forgeExpression = require("./lib/forgeExpression.js");
  global.forgeProperty = require("./lib/forgeProperty.js");
  global.addArgs = require("./lib/addArgs.js");
  global.addParams = require("./lib/addParams.js");
  global.addPreParams = require("./lib/addPreParams.js");
  global.ArrayDeclarator = require("./lib/ArrayDeclarator.js");
  global.AssignmentExpression = require("./lib/AssignmentExpression.js");
  global.ReturnStatement = require("./lib/ReturnStatement.js");
  global.UnaryExpression = require("./lib/UnaryExpression.js");
  global.BinaryExpression = require("./lib/BinaryExpression.js");
  global.IfStatement = require("./lib/IfStatement.js");
  global.getVarValue = require("./lib/getVarValue.js");
  global.ForStatement = require("./lib/ForStatement.js");
  global.UpdateExpression = require("./lib/UpdateExpression.js");
  global.WhileStatement = require("./lib/WhileStatement.js");

  global.DEBUG = function(_log)
  {
    if(CLI.cli["--debug"])
    {
      console.log(_log);
    }
  }

  global.ObjectExpression = require("./lib/ObjectExpression.js");

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

  var EXISTING_ENV =
  {
    std: require("./env/std.js"),
    node: require("./env/node.js"),
    arduino: require("./env/arduino.js"),
    stm32: require("./env/stm32.js"),
  }
  global.NJS_ENV = EXISTING_ENV["std"];
  global.NJS_TARGET = null;
  global.NJS_SPEC = "";

  if (CLI.cli["--env"] && EXISTING_ENV[CLI.cli["--env"].argument])
  {
    NJS_ENV = EXISTING_ENV[CLI.cli["--env"].argument];
  }

  if (CLI.cli["--target"] && CLI.cli["--target"].argument)
  {
    NJS_TARGET = CLI.cli["--target"].argument;
  }

  if (CLI.cli["--spec"] && CLI.cli["--spec"].argument)
  {
    NJS_SPEC = CLI.cli["--spec"].argument;
  }


  this.Default = "g++ -O3";
  if(NJS_ENV.compiler) this.Default = NJS_ENV.compiler;

  this.Squel = NJS_ENV.base;
  this.End = ".cpp";

  this.SCOPE = [];
  global.GENERATED = "";

  this.Pre = PreParsing;
  this.Post = PostParsing;

  this.fnOptimizer = fnOptimizer;

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
            _str += FunctionDeclaration(obj[o]);
  				break;

  			case "ExpressionStatement":
            _str += ExpressionStatement(obj[o]);
  				break;
        case "ReturnStatement":
            _str += ReturnStatement(obj[o]);
          break;
        case "VariableDeclaration":
            _str += VariableDeclaration(obj[o]);
          break;
        case "VariableDeclarator":
              _str += VariableDeclarator(obj[o]);
          break;
        case "IfStatement":
            _str += IfStatement(obj[o])
          break;
        case "EmptyStatement":
          break;
        case "ForStatement":
            _str += ForStatement(obj[o]);
          break;
        case "WhileStatement":
              _str += WhileStatement(obj[o]);
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
    return squel;
  }

  this.CLI = function(compiler, out, TO, option)
  {
    var _cli = NJS_ENV.cli.replace(/__OUT__/g, out).replace(/__IN__/g, TO).replace(/__SPEC__/g, NJS_SPEC).replace(/__TARGET__/g, NJS_TARGET).replace(/__OPTION__/g, option).replace(/__COMPILER__/g, compiler);
    return _cli;
  }

  this.Run = function(out)
  {
    return "./" + out;
  }
}

module.exports = new Compiler();
