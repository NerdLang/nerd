function UnaryExpression(_path) 
{ 
	// typeof
	if (_path.node.operator == "typeof")
	{
		if (_path.node.argument.type == "MemberExpression")
		{
			VISITOR.memberExpression(_path.node.argument);
			_path.replaceWithSourceString("__Nectar_typeof(" + babel.generate(_path.node.argument).code + ")");
		}
		else
		{
			_path.replaceWithSourceString("__Nectar_typeof(" + babel.generate(_path.node.argument).code + ")");
		}
		
		
		//_path.skip();
	}
	// void
	else if(_path.node.operator == "void")
	{
		var _rnd = "__Nectar_VOID_" + RND();
		COMPILER.DECL.push(`NectarCore::VAR ${_rnd}() { ${babel.generate(_path.node.arguments).code} return NectarCore::Global::undefined;};`);
		VISITOR.pushDeclVar(_rnd);
		_path.replaceWithSourceString(`${_rnd}()`);
	}
	else if(_path.node.operator == "delete")
	{
		if (_path.node.argument.type == "MemberExpression")
		{
			VISITOR.memberExpression(_path.node.argument);
			
			var _left = babel.generate(_path.node.argument.object).code;
			var _right = _path.node.argument.property.extra.raw;
			_path.replaceWithSourceString(`__Nectar_delete(${_left}, ${_right})`);
		}
		else 
		{
			_path.replaceWithSourceString("__Nectar_Boolean_FALSE");
		}
	}
}
module.exports = UnaryExpression;