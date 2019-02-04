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

function genInclude(from, src, full)
{
  if(full == undefined) full = false;
  var removeStart = -1;
  var removeEnd = -1;
  var index = -1;
  do
  {
    index = src.indexOf("//!_c_include \"", index);
    if(index > -1)
    {
      removeStart = index;
      index += 15;
      var target = index;
      var search = true;
      while(search)
      {
        if(src[target] == '"')
        {
          var startVar = index;
          var endVar = target;
          removeEnd = target + 1;
          var _var = from + src.substring(index, target);
          //src = src.replace(src.substring(removeStart, removeEnd), "");
          USERLIB.push(_var);

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
module.exports = genInclude;
