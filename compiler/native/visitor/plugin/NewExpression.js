function NewExpression(_path)
{
	_path.node.type = "CallExpression";
	_path.node.callee.name = `__Nectar_NEW(${_path.node.callee.name})`;
}
module.exports = NewExpression;