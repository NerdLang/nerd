function ArrayExpression(_path)
{
	var _arr = VISITOR.arrayExpression(_path.node, _path);
	COMPILER.DECL.push(_arr.setter + ";");
	_path.replaceWithSourceString(_arr.getter + "()");
}

module.exports = ArrayExpression;