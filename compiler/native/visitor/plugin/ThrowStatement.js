function ThrowStatement(_path) 
{
	var _err = "__Nectar_ERROR_" + RND();
	_path.insertBefore(babel.parse("var " + _err + " = " + babel.generate(_path.node.argument).code));
	_path.node.argument = babel.parse(_err);
}
module.exports = ThrowStatement;