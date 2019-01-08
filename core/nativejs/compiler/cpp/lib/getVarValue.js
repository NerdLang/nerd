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

module.exports = getVarValue;
function getVarValue(obj, type)
{
    if(!type) type = { type: "NUMBER", value:"Number"};
    var str = "";
    switch(obj.type)
    {
      case "Identifier":
        str += obj.name;
        break;

      case "Literal":
        if(typeof obj.value == "string")
        {
          str += "__create_String((char*)\"" + obj.value + "\")";
        }
        else
        {
          str += "var(" + obj.value + ")";
        }

        break;

      case "CallExpression":
        str += callFunction({expression: obj}, false);
        break;

      case "UnaryExpression":
        str += UnaryExpression(obj);
        break;

      case "BinaryExpression":
        str += BinaryExpression(obj);
        break;

      case "MemberExpression":
        str += forgeProperty(obj);
        break;

      default:
        ERROR = true;
        console.log("Expression : " + obj.type + " - Not Implemented Yet in VAR");
        process.exit(1);
        break;
    }
  return str;
}
