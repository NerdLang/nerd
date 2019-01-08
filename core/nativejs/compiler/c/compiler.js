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

  this.Default = "gcc";
  this.Squel = "squel.c";
  this.End = ".c";

  this.SCOPE = [];

  this.Parse = function(obj)
  {
    var _str = "";
    if(obj.body) obj = obj.body;

    for(var o in obj)
  	{
  		switch(obj[o].type)
  		{
  			case "FunctionDeclaration":
            console.log("Parser for FunctionDeclaration is not implemented yet");
  				break;

  			case "ExpressionStatement":
            console.log("Parser for ExpressionStatement is not implemented yet");
  				break;
        case "ReturnStatement":
              console.log("Parser for ReturnStatement is not implemented yet");
          break;
        case "VariableDeclaration":
            console.log("Parser for VariableDeclaration is not implemented yet");
          break;
        case "VariableDeclarator":
              console.log("Parser for VariableDeclarator is not implemented yet");
          break;
        case "IfStatement":
            console.log("Parser for IfStatement is not implemented yet");
          break;
        case "EmptyStatement":
          break;
        case "ForStatement":
              console.log("Parser for ForStatement is not implemented yet");
          break;
        case "WhileStatement":
              console.log("Parser for WhileStatement is not implemented yet");
          break;
        case "DoWhileStatement":
              console.log("Parser for DoWhileStatement is not implemented yet");
          break;
        case "BreakStatement":
              console.log("Parser for BreakStatement is not implemented yet");
          break;
        case "SwitchStatement":
              console.log("Parser for SwitchStatement is not implemented yet");
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
    return compiler + " -o " + out + " " + TO + " " + option;
  }

  this.Run = function(out)
  {
    return "./" + out;
  }
}

module.exports = new Compiler();
