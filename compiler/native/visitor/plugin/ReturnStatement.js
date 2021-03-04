function ReturnStatement(_path)
{
	if(_path.node && _path.node.argument && _path.node.argument.type == "MemberExpression")
	{
		const _arg = _path.get("argument");
		VISITOR.memberExpression(_path.node.argument);
	}
	else if(!_path.node.argument)
	{
		_path.node.argument =
		{
			"type":"Identifier",
			"name": "undefined",
		}
	}
}
module.exports = ReturnStatement;