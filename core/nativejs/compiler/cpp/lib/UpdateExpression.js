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

module.exports = UpdateExpression;
function UpdateExpression(obj, put, comma, type)
{
  if(type == undefined || type == null) type = "";
  if(put == undefined || put == null) put = true;
  if(comma == undefined || comma == null) comma = true;
  var str = "";
  var OP = "";
  if(obj.operator == "++" || obj.operator == "--")
  {
    if( (obj.argument.type != "Identifier" && obj.argument.type != "UpdateExpression") || put) OP = obj.operator;

    var ASSIGN = forgeExpression(obj.argument, null, put, comma);

    if(!obj.prefix)
    {
      str += "" + ASSIGN + type + OP;
    }
    else
    {
      str += "" + OP + ASSIGN + type;
    }
  }
  else
  {
    ERROR = true;
    njsError("Expression : " + obj.operator + " - Not Implemented Yet in BinaryExpression");
  }
  if(comma) str += ";";

  return str;
}

// OLD
/*
function UpdateExpression(obj, comma)
{
  if(comma == undefined) comma = true;
  var str = "";
  switch(obj.argument.type)
  {
    case "Identifier":
      str += obj.argument.name;
      break;
    case "Literal":
      str += obj.argument.value;
      break;
    default:
      ERROR = true;
      console.dir("UpdateExpression " + obj.argument.type + " is not defined yet");
      break;

  }
  if(obj.prefix)
    str = obj.operator + str;
  else
    str += obj.operator;
  if(comma) str += ";";
  return str;
}
*/
