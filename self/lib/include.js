/*
	Copyright (c) 2021 NerdLang - Adrien THIERRY and contributors

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.

*/

var _SEARCH = new RegExp(/['"]!_ffi_include *(.*)['"]/);
var _SEARCHCINC = new RegExp(/#include *\"(.*)\"/g);

function genInclude(from, src, full)
{
	console.log(from, src, full);
	if(CLI.cli["--profile"] && CLI.cli["--profile"].argument == "use")
	{
		return src;
	}
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
		   var _include = fs.readFileSync(path.resolve(path.join(full, _cfile[1]))).toString();
		  _include = genMetaFunction(_include);
		   _include = genInclude(path.dirname(path.resolve(path.join(full, _cfile[1]))), _include, path.dirname(path.resolve(path.join(full, _cfile[1]))));
		  fs.writeFileSync(path.resolve(path.join(full, _cfile[1])), _include);
		  _cmatch = src.match(_SEARCHCINC);
        }
      }
    }
  }
  
  return src;
}
module.exports = genInclude;