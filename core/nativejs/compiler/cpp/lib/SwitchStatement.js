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

module.exports = SwitchStatement;
function SwitchStatement(obj)
{
  str = "";
  str += "switch(";
  if(obj.discriminant) str += getVarValue(obj.discriminant);
  str += "){";
  for(var i = 0; i < obj.cases.length; i++)
  {
    if(obj.cases[i].test)
    {
      str += "case " + ExpressionStatement({"expression": obj.cases[i].test}, false, true);
      str += ":";
      str += COMPILER.Parse(obj.cases[i].consequent);
    }
    else
    {
      str += "default:";
      str += COMPILER.Parse(obj.cases[i].consequent);
    }

  }
  str += "}";
  return str;
}
