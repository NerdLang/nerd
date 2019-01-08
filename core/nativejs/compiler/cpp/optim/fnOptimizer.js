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

var TMP_STACK = [];
function fnOptimizer(obj)
{
  if(!obj) return;
  if(typeof obj != "object") return;

  for(var o in obj)
  {
    if(obj[o] && obj[o].type && obj[o].type == "CallExpression")
    {
      for(var a in obj[o].arguments)
      {
        if(obj[o].arguments[a].type == "Identifier")
        {
          if(TMP_STACK.indexOf(obj[o].arguments[a].name) > -1)
          {
            if(CBFN.indexOf(obj[o].arguments[a].name) < 0)
            {
              CBFN.push(obj[o].arguments[a].name);
            }
          }
        }
      }
    }
    if(obj[o] && (obj[o].type && obj[o].type == "FunctionDeclaration"))
    {
      TMP_STACK.push(obj[o].id.name)
    }
    if(obj[o] && (obj[o].type && obj[o].type == "VariableDeclaration"))
    {
      for(var d in obj[o].declarations)
      {
        if(obj[o].declarations[d].init && obj[o].declarations[d].init.type == "FunctionExpression")
        {

          if(CBFN.indexOf(obj[o].declarations[d].id.name) < 0)
          {
            CBFN.push(obj[o].declarations[d].id.name);
          }
        }
      }
    }
    fnOptimizer(obj[o]);
  }
}

module.exports = fnOptimizer;
