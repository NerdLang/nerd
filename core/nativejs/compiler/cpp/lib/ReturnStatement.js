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

module.exports = ReturnStatement;
function ReturnStatement(obj)
{
  str = "return ";
  if(!obj.argument)
  {
    str += ";"
    return str;
  }
  else
  {
    switch(obj.argument.type)
    {
      case "Literal":
        str +=  createVar(obj.argument.value);
        break;

      case "BinaryExpression":
        str += BinaryExpression(obj.argument);
        break;

      case "Identifier":
        str += obj.argument.name;
        break;

      case "ArrayExpression":
        var _name = createRandomVar()
        obj.argument.id = { name: _name };
        str = ArrayDeclarator(obj.argument);
        str += "return " + _name;
        break;

      case "CallExpression":
        str += callFunction({ "expression":obj.argument }, false);
        break;

      case "MemberExpression":
        obj.argument.return = true;
        str += forgeProperty(obj.argument, false);
        break;

      default:
        ERROR = true;
        njsError("Expression : " + obj.argument.type + " - Not Implemented Yet in ReturnStatement");
        console.dir("ReturnStatement " + obj.argument.type + " not defined yet");
        break;
    }
    str += ";";
    return str;
  }
}
