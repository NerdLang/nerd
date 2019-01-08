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

module.exports = callFunction;

function callFunction(obj, comma)
{
  if(comma == undefined) comma = true;
	var str = "";
	switch(obj.expression.callee.type)
	{
		case "Identifier":

      if(obj.expression.callee.name.indexOf("__NJS_") == 0 || obj.expression.callee.name.indexOf("__NATIVE_") == 0 || (LOCAL_PARAM.indexOf(obj.expression.callee.name) < 0 && CBFN.indexOf(obj.expression.callee.name) < 0))
      {
        str += obj.expression.callee.name + "(";
        str += addParams(obj.expression.arguments, true);
        str += ")";
        if(comma) str+=";";
      }
      else
      {
        var _args = "";
        for(var i = 0; i<obj.expression.arguments.length; i++)
        {
          if(i > 0) _args += ",";
          _args += "var " + createRandomVar();
        }
        str += "(*static_cast<function<var (" + _args +")>*>(";
        str += "( " + obj.expression.callee.name + ").value.f))(";
        str += addParams(obj.expression.arguments, true);
        str += ")";
        if(comma) str+=";";
      }

			break;

		case "MemberExpression":
      var _args = "";
      for(var i = 0; i<obj.expression.arguments.length; i++)
      {
        if(i > 0) _args += ",";
        _args += "var " + createRandomVar();
      }
      str += "(*static_cast<function<var (" + _args +")>*>(";
      str += forgeProperty(obj.expression.callee);
      str += ".value.f))";
			str += "(" + addArgs(obj.expression.arguments);
      if(obj.expression.index && obj.expression.callee.name.indexOf(C_START) == 0 )
      {
        if(obj.expression.arguments.length > 0) str += ",";
        str += createVar(obj.expression.index, false);
      }
      str += ")";
      if(comma) str+=";";
			break;

    case "FunctionExpression":
      str += ExpressionStatement({expression: obj.expression.callee});
      break;


    default:
      ERROR = true;
      console.log("Function : " + obj.expression.callee.type + " - Not Implemented Yet in NectarScript");
      break;
	}

	return str;
}
