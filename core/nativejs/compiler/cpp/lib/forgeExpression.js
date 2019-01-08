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

module.exports = forgeExpression;
function forgeExpression(obj, expression, put, comma, action, vtype)
{
  if(vtype == undefined) vtype = {"_var" : "INT", "_val": "Integer" };
  if(put == undefined || put == null) put = true;
  if(comma == undefined || comma == null) comma = true;
  if(expression == undefined || comma == null) expression = true;
  var str = "";

  switch(obj.type)
    {
      case "Identifier":
        if(obj.name) str += obj.name;
        else if(obj.id.name) str += obj.id.name;
        else if(obj.expression.name) str += obj.expression.name;
        if(comma) str += ";";
        break;

      case "Literal":
        if(expression)
          str += createVar(obj.value, obj.index);
        else
        {
          if(typeof obj.value == "number") str += "__create_Number(" + obj.value + ")";
          else str += '__create_String((char*)"' + obj.value + '")';
        }
        break;

      case "CallExpression":
        str += callFunction({expression: obj}, false);
        break;

      case "BinaryExpression":
        str += BinaryExpression(obj, put, comma);
        break;

      case "UnaryExpression":
        str += UnaryExpression(obj, put, comma);
        break;

      case "UpdateExpression":
        str += UpdateExpression(obj, put, comma);
        break;

      case "MemberExpression":
        str += forgeProperty(obj, null, action, vtype);
        break;

      case "AssignmentExpression":
        str += AssignmentExpression(obj);
        break;

      case "ObjectExpression":
        if(!obj.id) obj.id = { name: obj.from };
        str += ObjectExpression(obj, true);
        break;

      case "ArrayExpression":
        if(!obj.id && obj.from)
        {
          obj.id = { name: obj.from };
        }
        else if(!obj.id) obj.id = { name: createRandomVar() };
        str += ArrayDeclarator(obj, true);
        break;

      case "FunctionExpression":
        var _new = createRandomVar();
        obj.id = {name: _new};
        var _fn = FunctionDeclaration(obj, "object");
        str += "(var){.type = FUNCTION, .value.f=(function<var ()>*)&" + _fn + "}";

        break;

      default:
        ERROR = true;
        console.log("Expression : " + obj.type + " - Not Implemented Yet for ForgeExpression in NectarScript");
        break;
    }
  return str;
}
