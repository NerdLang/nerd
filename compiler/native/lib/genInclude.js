/*
 * This file is part of NativeJS
 * Copyright (c) 2017-2020 Adrien THIERRY
 * http://nectarjs.com - https://www.linkedin.com/in/adrien-thierry-fr/
 *
 * sources : https://github.com/nectarjs/old_nativejs
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
 * develop commercial activities involving the FortressJS software without
 * disclosing the source code of your own applications. Visit http://seraum.com/
 * and feel free to contact us.
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
    index = src.indexOf("//!_ffi_include \"", index);
    if(index > -1)
    {
      removeStart = index;
      index += 17;
      var target = index;
      var search = true;
      while(search)
      {
        if(src[target] == '"')
        {
          var startVar = index;
          var endVar = target;
          removeEnd = target + 1;
          var _var = "#include \"" + path.resolve(path.join(from, src.substring(index, target))) + "\"";
          src = src.replace(src.substring(removeStart, removeEnd), "");
          COMPILER.FFI.push(_var);
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
