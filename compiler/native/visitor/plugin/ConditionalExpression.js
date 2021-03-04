function ConditionalExpression(_path)
{
	if(_path.node.consequent.type != _path.node.alternate.type)
	{
		
		if(_path.node.alternate.type == "NumericLiteral" || _path.node.alternate.type == "StringLiteral" || _path.node.alternate.type == "UnaryExpression")
		{
			var _rnd = "__Nectar_TERNARY" + RND();
			COMPILER.DECL.push(`var ${_rnd} = ${_path.node.alternate.value}`);
			_path.node.alternate.type = "Identifier";
			_path.node.alternate.name = _rnd;
		}
		if(_path.node.consequent.type == "NumericLiteral" || _path.node.consequent.type == "StringLiteral" || _path.node.consequent.type == "UnaryExpression")
		{
			var _rnd = "__Nectar_TERNARY" + RND();
			COMPILER.DECL.push(`var ${_rnd} = ${_path.node.consequent.value}`);
			_path.node.consequent.type = "Identifier";
			_path.node.consequent.name = _rnd;
		}
		
	}
}
module.exports = ConditionalExpression;