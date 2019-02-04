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

function genTarget(name, from, src)
{
  var removeStart = -1;
  var removeEnd = -1;
  var index = -1;
  do
  {
    index = src.indexOf("//!_njs_target ", index);
    if(index > -1)
    {
      removeStart = index;
      index += 15;
      var target = index;
      var search = true;
      while(search)
      {
        if(src[target] == '\n')
        {
          var startVar = index;
          var endVar = target;
          removeEnd = target + 1;
          var _var = src.substring(index, target);
          //src = src.replace(src.substring(removeStart, removeEnd), "");
          var result = eval(_var);

          if(AVAILABLE_TARGETS.length == 0)
          {
            AVAILABLE_TARGETS = result;
          }
          else
          {
              for(var r in result)
              {
                if(AVAILABLE_TARGETS.indexOf(result[r]) < 0)
                {
                  console.error("NectarJS:\n\n[!] File " + name + " is not compatible with targets : " + AVAILABLE_TARGETS + " defined in " + from);
                  process.exit(1);
                }
              }
          }
          return src;
          search = false;
          removeStart = -1;
          removeEnd = -1;
        }
        target++;
        if(target < 0) search = false;
      }
      index++;
    }
  }
  while(index > -1)
  return src;
}
module.exports = genTarget;
