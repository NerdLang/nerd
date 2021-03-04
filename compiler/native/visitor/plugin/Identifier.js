function Identifier(_path)
{
	if(_path.node.name.indexOf("$") > -1)
	{
		var _newId = _path.node.name.replace(/\$/, "__Nectar_DOLLAR_");
		VISITOR.addFunctionVarUse(_newId);
		_path.replaceWith(babel.types.identifier(_newId))
	}
	else VISITOR.addFunctionVarUse(_path.node.name);
}
module.exports = Identifier;