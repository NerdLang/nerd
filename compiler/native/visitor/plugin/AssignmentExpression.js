function AssignmentExpression(_path)
{

 if(_path.node.left.type == "MemberExpression")
 {
	VISITOR.memberExpression(_path.node.left);

	if(_path.node.right && _path.node.right.type == "ArrayExpression")
	{
		var _a = VISITOR.arrayExpression(_path.node.right);
		COMPILER.DECL.push(_a.setter);
		_path.node.right = babel.parse(_a.getter + "();");
	}
	else if(_path.node.right && _path.node.right.type == "ObjectExpression")
	{
		var _objAssign = "";
		for(var i = 0; i < _path.node.right.properties.length; i++)
		{
			_objAssign += VISITOR.objectExpression(_path.node.right.properties[i], _path.node.left.name);
		}
		_path.insertAfter(babel.parse(_objAssign));
		_path.node.right = babel.parse("__NJS_Create_Object()");
	}
 }
 else if(_path.node.left.type == "Identifier")
 {
	 VISITOR.checkUndefVar(_path.node.left.name);
	VISITOR.readOnlyVar(_path.node.left.name);
	if(_path.node.right.type == "ArrayExpression")
	{
		var _a = VISITOR.arrayExpression(_path.node.right);
		_path.node.right = babel.parse(_a.getter + "();");
	}
	else if(_path.node.right.type == "ObjectExpression")
	{
		var _objAssign = "";
		for(var i = 0; i < _path.node.right.properties.length; i++)
		{
			_objAssign += VISITOR.objectExpression(_path.node.right.properties[i], _path.node.left.name);
		}
		_path.insertAfter(babel.parse(_objAssign));
		_path.node.right = babel.parse("__NJS_Create_Object()");
	}
 }

}
module.exports = AssignmentExpression;