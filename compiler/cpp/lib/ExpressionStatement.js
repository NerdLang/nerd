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

module.exports = ExpressionStatement;
function ExpressionStatement(obj, comma, put)
{
  if(put == undefined || put == null) put = true;
  if(comma == undefined || comma == null) comma = true;
	var str = "";
	switch(obj.expression.type)
	{
    case "BinaryExpression":
			str += BinaryExpression(obj.expression);
      if(comma) str += ";";
			break;

    case "Literal":
			str += obj.expression.raw;
      if(comma) str += ";";
			break;

    case "VariableDeclaration":
      for(var d in obj.declarations)
      {
        str += VariableDeclaration(obj.declarations[d]);
      }
      if(comma) str += ";";
			break;

    case "Identifier":
			str += obj.expression.name
      if(comma) str += ";";
			break;

		case "CallExpression":
			str += callFunction(obj, comma);
      if(comma) str += ";";
			break;

    case "UpdateExpression":
      str += UpdateExpression(obj.expression, put, false);
      if(comma) str += ";";
      break;

    case "AssignmentExpression":
      str += AssignmentExpression(obj.expression, comma);
      break;

    case "LogicalExpression":
       str += IfStatement({"test": obj.expression.left}, "") + obj.expression.operator + IfStatement({"test":obj.expression.right}, "");
      break;

    case "UnaryExpression":
      str += UnaryExpression(obj.expression, put, comma);
      break;

    case "FunctionExpression":

      var name = createRandomVar();

      var p= [];
      for(var v in obj.params)
      {
        p.push("var " + obj.params[v].name);
      }

      DECLARATION += "var " + name + "(" + p.join(',') + "){";
	    DECLARATION += COMPILER.Parse(obj.expression.body.body, true, false);
	    DECLARATION += "}";

      str += name + "(" + p.join(',') + ")";
      if(comma) str += ";";

      break;

		default:
      ERROR = true;
      console.error("Expression : " + obj.expression.type + " - Not Implemented Yet in ExpressionStatement");
			break;
	}
	return str;
}
