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
 
 module.exports = IfStatement;
function IfStatement(obj, id)
{
  if(id == undefined) id = "if";
  var str = "";
  if(obj.test)
  {
    switch(obj.test.type)
    {
      case "Identifier":
        str += id + "(__NJS_Boolean_Result(" + obj.test.name + "))";
        break;

      case "UnaryExpression":
        str += id + "(__NJS_Boolean_Result(" + UnaryExpression(obj.test) + "))";
        break;

      case "BinaryExpression":
        str += id + "(__NJS_Boolean_Result(" + BinaryExpression(obj.test) + "))";
        break;

      case "UpdateExpression":
        str += id + "(__NJS_Boolean_Result(" + UpdateExpression(obj.test, true, false) + "))";
        break;

      case "LogicalExpression":
        str += id + "(__NJS_Boolean_Result(" + IfStatement({"test": obj.test.left}, "") + obj.test.operator + IfStatement({"test":obj.test.right}, "") + "))";
        break;

      case "Literal":
        str += obj.test.value;
        break;

      case "MemberExpression":
        str += id + "(__NJS_Boolean_Result(" + forgeProperty(obj.test) + "))";
        break;

      default:
        ERROR = true;
        njsError("Expression : " + obj.test.type + " - Not Implemented Yet in ConditionalStatement");
        break;
    }
  }
  if(obj.consequent)
  {
    switch(obj.consequent.type)
    {
      case "ExpressionStatement":
        str += ExpressionStatement(obj.consequent);
        break;

      case "ReturnStatement":
        str += ReturnStatement(obj.consequent);
        break;

      case "BlockStatement":
        str += "{" + COMPILER.Parse(obj.consequent.body) + "}";
        break;

      case "BreakStatement":
        str += BreakStatement(obj.consequent);;
        break;

      default:
        ERROR = true;
        njsError("Expression : " + obj.consequent.type + " : " + obj.type + " - Not Implemented Yet in ConsequentStatement in NectarScript");
        break;
    }
  }

  if(obj.alternate && obj.alternate.test)
  {
    str += IfStatement(obj.alternate, "else if");
  }
  if(obj.alternate && !obj.alternate.test && obj.alternate.type)
  {
    switch(obj.alternate.type)
    {
      case "ReturnStatement":
        str += "else " + ReturnStatement(obj.alternate);
        break;

      case "BlockStatement":
        str += "else " + COMPILER.Parse(obj.alternate.body);
        break;

      default:
        njsError("Expression : " + obj.consequent.type + " : " + obj.type + " - Not Implemented Yet in AlternateStatement in NectarScript");
        break;
    }
  }

  return str;
}
