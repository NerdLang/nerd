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
 
module.exports = UnaryExpression;
function UnaryExpression(obj, put, comma)
{
  var str = "";
  var OP = "";
  if(obj.operator == "+" || obj.operator == "-" || obj.operator == "*" || obj.operator == "/" || obj.operator == "%" || obj.operator == "!")
  {
    OP = obj.operator;
    var ASSIGN = forgeExpression(obj.argument, null, put, comma);

    if(!obj.prefix)
    {
      str += ASSIGN + OP;
    }
    else
    {
      str += OP + ASSIGN;
    }
  }
  else if(obj.operator == "delete" && obj.argument.type == "Identifier")
  {
    console.log("delete is not implemented yet in NectarScript");
    process.exit(1);
    if(obj.prefix)
    {
      str += "_delete(" + obj.argument.name + ")";
    }
    else
    {
      console.dir("UnaryExpression : " + obj.operator + " with no prefix is not implemented yet");
    }
  }
  else if(obj.operator == "typeof")
  {
    if(obj.prefix)
    {
      str += "__NJS_Typeof(" + forgeExpression(obj.argument, null, null, false) + ")";
    }
    else
    {

      console.dir("UnaryExpression : " + obj.operator + " with no prefix is not implemented yet");
    }
  }
  else
  {
    ERROR = true;
    console.log("Expression : " + obj.operator + " - Not Implemented Yet in UnaryExpression");
    process.exit(1);
  }
  if(comma) str += ";";
  return str;
}
