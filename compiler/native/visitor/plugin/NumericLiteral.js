function NumericLiteral(_path)
{
	if(_path.parent.type == "MemberExpression")
	{
		//_path.replaceWithSourceString("__Nectar_InitVar(" + _path.node.extra.raw + ")");
		//_path.skip();
	}
	else if(_path.parent.type == "BinaryExpression")
	{
		var start = _path.node.start;
		var end = _path.node.end;
		if(_path.parent.left.start == start && _path.parent.left.end == end)
		{
			//_path.replaceWithSourceString("__Nectar_InitVar(" + _path.node.extra.raw + ")");
			//_path.skip();
		}
	}
}
module.exports = NumericLiteral;