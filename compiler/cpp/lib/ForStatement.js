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

module.exports = ForStatement;
function ForStatement(obj)
{
  str = "";
  var INIT = false;

  if(obj.init && obj.init[0] && obj.init[0].type == "VariableDeclarator" && obj.init[0].id.type == "Identifier")
  {
    INIT = true;
    str += COMPILER.Parse(obj.init);
  }
  str += "for(";
  if(obj.init)
  {
    if(INIT) str += obj.init[0].id.name + ";";
    else
    {
      if(obj.init[0] == undefined)
      {
        str += VariableDeclaration(obj.init);
      }
      else str += COMPILER.Parse(obj.init);
    }
  }
  else str += ";";
  if(obj.test) str += "__NJS_Boolean_Result(" + ExpressionStatement({"expression": obj.test}, false, true) + ")";//forgeExpression(obj.test);
  str += ";";
  if(obj.update)
  {
    str += ExpressionStatement({"expression": obj.update}, false, true);
  }

  str += ")";

  if(obj.body.type == "BlockStatement")
  {
    str += "{";
    str += COMPILER.Parse(obj.body.body);
    str += "}";
  }
  else
  {
    str += forgeExpression(obj.body.expression);
  }
  return str;
}
