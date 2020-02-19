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

module.exports = VariableDeclarator;
function VariableDeclarator(obj)
{
  var str = "";
  switch(obj.init.type)
  {
    case "Literal":
      if(obj.kind && obj.kind == "const")
      {
        GLOBAL_GEN += "const var " + obj.id.name + " = " + createVar(obj.init.value) + ";";
      }
      else
      {
        str += "var ";
        str += obj.id.name + " = " + createVar(obj.init.value) + ";";
      }
      break;

    case "Identifier":
      if(obj.kind && obj.kind == "const")
      {
        GLOBAL_GEN += "const var " + obj.id.name + " = " + obj.init.name + ";";
      }
      else
      {
        str += "var " + obj.id.name + " = " + obj.init.name + ";";
      }
      break;

      // BOOLEAN
    case "false":
      str += 0;
      break;
    case "true":
      str += 1;
      break;

    default:
      ERROR = true;
      njsError("Expression : " + obj.type + " - Not Implemented Yet for VariableDeclarator in NectarScript");
      break;
  }

  return str;
}
