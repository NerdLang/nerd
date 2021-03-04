function ExpressionStatement(_path)
{
	if(_path.node.expression && _path.node.expression.type == "CallExpression" && !_path.node.expression.id 
		&& _path.node.expression.callee && _path.node.expression.callee.type == "FunctionExpression")
	{
		var _nf = RND();
		var _code = "var " + _nf + " = "  + babel.generate(_path.node.expression.callee).code + ";";
		var _ncode = `${_nf}()`;
		_path.insertBefore(babel.parse(_code));
		_path.replaceWithSourceString(_ncode);
		_path.skip;
	}
}
module.exports = ExpressionStatement;