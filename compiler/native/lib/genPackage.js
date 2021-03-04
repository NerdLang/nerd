var _SEARCH = new RegExp(/['"]!_package *(.*)['"]/);

function genPackage(from, src)
{
  var _match = src.match(_SEARCH);
  while(_match)
  {
    var _target = _match[1].replace(/{__ARCH__}/g, os.arch());
    copyRecursiveSync(path.resolve(path.join(from, _target)), path.join(COMPILER.TMP_FOLDER, _target));
    COMPILER.PACK.push(path.join(COMPILER.TMP_FOLDER, _target));
    src = src.replace(/['"]!_package *(.*)['"]/, "");	
    _match = src.match(_SEARCH);
  }
  
  return src;
}
module.exports = genPackage;
