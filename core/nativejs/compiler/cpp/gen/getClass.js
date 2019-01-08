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

module.exports = getClass;
var classStack = [];
var classIndex = -1;
var smartClass = [];

function getClass(obj)
{
  for(var o in obj)
  {
    if(obj[o] && obj[o].type && obj[o].type == "FunctionDeclaration" && obj[o].body && obj[o].body.body && obj[o].body.body.length)
    {
      classStack.push(obj[o].id.name);
      classIndex++;
      getClass(obj[o].body.body);
      classStack.splice(classIndex, 1);
      classIndex--;
    }
    if(obj[o] && obj[o].type && obj[o].type == "VariableDeclarator" && obj[o].init && obj[o].init.type == "FunctionExpression" && obj[o].init.body && obj[o].init.body.body)
    {
      classStack.push(obj[o].id.name);
      classIndex++;
      getClass(obj[o].init.body.body);
      classStack.splice(classIndex, 1);
      classIndex--;
    }
    else if(obj[o] && obj[o].type && obj[o].type == "ThisExpression")
    {
      if(smartClass.indexOf(classStack[classIndex]) < 0)
      {
        smartClass.push(classStack[classIndex]);
      }
    }
    else if(typeof obj[o] == "object")
    {
      getClass(obj[o]);
    }
  }
  return smartClass;
}
