function StringLiteral(_path)
{
	if(_path.node.extra.raw[0] && _path.node.extra.raw[0] == "'")
	{
		_path.node.extra.raw = '"' + _path.node.value.replace(/\\/g, '\\\\').replace(/"/g, '\\\"') + '"';
	}

	if(_path.parent.type == "MemberExpression" || _path.parent.type == "CallExpression" 
	|| _path.parent.type == "AssignmentExpression" || _path.parent.type == "VariableDeclarator")
	{
		//nothing to do
	}
	else 
	{
		_path.replaceWithSourceString("__Nectar_InitVar(" + _path.node.extra.raw + ")");
		_path.skip();
	}
}
module.exports = StringLiteral;