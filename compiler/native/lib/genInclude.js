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
var _SEARCH = new RegExp(/['"]!_ffi_include *(.*)['"]/);
var _SEARCHCINC = new RegExp(/#include *\"(.*)\"/g);

function genInclude(from, src, full)
{
  var _match = src.match(_SEARCH);
  while(_match)
  {
    var _var = "#include \"" + path.resolve(path.join(COMPILER.TMP_FOLDER, _match[1]) + "\"");
    COMPILER.FFI.push(_var);
    copyRecursiveSync(path.resolve(path.join(from, _match[1])), path.join(COMPILER.TMP_FOLDER, _match[1]));
    var _include = fs.readFileSync(path.resolve(path.join(COMPILER.TMP_FOLDER, _match[1]))).toString();
    _include = genMetaFunction(_include);
	  _include = genInclude(path.dirname(path.resolve(path.join(from, _match[1]))), _include, path.dirname(path.resolve(path.join(COMPILER.TMP_FOLDER, _match[1]))));
    fs.writeFileSync(path.resolve(path.join(COMPILER.TMP_FOLDER, _match[1])), _include);
    src = src.replace(/['"]!_ffi_include *(.*)['"]/, "");	
    _match = src.match(_SEARCH);
  }
  
  
  var _cmatch = src.match(_SEARCHCINC);
  if(_cmatch)
  {
    for(var i = 0; i < _cmatch.length; i++)
    {
      var _getPath = new RegExp(/#include *\"(.*)\"/g);
      var _cfile = _getPath.exec(_cmatch[i]);
      if(_cfile[1])
      {
        var _incFile = path.resolve(path.join(from, _cfile[1]));
        if(fs.existsSync(_incFile))
        {
          copyRecursiveSync(_incFile, path.join(full, _cfile[1]));
        }
      }
    }
  }
  
  return src;
}
module.exports = genInclude;
