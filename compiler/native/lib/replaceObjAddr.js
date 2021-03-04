function replaceObjAddr(_code)
{
	var Function = [];

	var _searchReg = / *__Nectar_Object_Set *\( *([a-zA-Z0-9_\-" ]*) *, *([a-zA-Z0-9_\-\(\)" ]*) *, *([a-zA-Z0-9_\-" ]*) *\)/g;
	var _searchFN = / *([a-zA-Z0-9_\-" ]*) * = NectarCore::VAR\(NectarCore::Enum::Type::Function/g;
	
	var _allFN = _code.match(new RegExp(_searchFN));
	if(_allFN)
	{
		for(var i = 0; i < _allFN.length; i++)
		{
			var _localSearch = new RegExp(_searchFN);
			var _fn = _localSearch.exec(_allFN[i]);
			if(_fn);
			{
				Function.push(_fn[1]);
			}
		}
	}

	var _searchObject = new RegExp(_searchReg);
	var _match = _code.match(_searchObject);
	if(_match)
	{
		for(var i = 0; i < _match.length; i++)
		{
			var _localSearch = new RegExp(_searchReg);
			var _var = _localSearch.exec(_match[i]);
			if(_var);
			{
				if(_var[1] != "\"exports\"" && Function.indexOf(_var[2]) > -1)
				{	
					var _getObject = new RegExp("__Nectar_Object_Get\\\(" + _var[1]+ ", " + _var[3] + "\\\)", "gm");
					_code = _code.replace(_getObject, _var[2]);
				}
			}
		}
	}
	return _code;
}
module.exports = replaceObjAddr;