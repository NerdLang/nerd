function BinaryExpression(_path)
{
	if(_path.node.right.type == "StringLiteral" && _path.node.left.type == "NumericLiteral")
	{
		var _rnd = "__Nectar_TMP_NUMLIT" + RND();
		COMPILER.DECL.push("var " + _rnd + " = \"" + _path.node.left.value + "\";");
		_path.node.left.type = "Identifier";
		_path.node.left.name = _rnd;
	}
		
	if(_path.node.operator == "===")
	{
		var _eq = "__Nectar_EQUAL_VALUE_AND_TYPE(";
		_eq += babel.generate(_path.node.left).code + ","
		_eq += babel.generate(_path.node.right).code + ")";
		_path.replaceWithSourceString(_eq);
	}
	else if(_path.node.operator == "!==")
	{
		var _not_eq = "__Nectar_NOT_EQUAL_VALUE_AND_TYPE(";
		_not_eq += babel.generate(_path.node.left).code + ","
		_not_eq += babel.generate(_path.node.right).code + ")";
		_path.replaceWithSourceString(_not_eq);
	}
	// instanceof
	else if(_path.node.operator == "instanceof")
	{
		_path.replaceWithSourceString(`__Nectar_instanceof(${babel.generate(_path.node.left).code},${babel.generate(_path.node.right).code})`);
	}
}
module.exports = BinaryExpression;