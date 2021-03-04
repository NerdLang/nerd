function memberExpression(_path, _root)
{
	
	if(_path.type == "MemberExpression")
	{
		if(_path.object.type == "CallExpression")
		{
			if(_path.object.callee.property.type == "Identifier" && _path.object.callee.property.name == "NStruct" )
			{
				return;
			}
		}
	}
	
	var _obj = _path;

	if(_obj.object && _obj.object.type == "Identifier")
	{
		VISITOR.checkUndefVar(_obj.object.name);
		VISITOR.readOnlyVar(_obj.object.name);
	}
	else if(_obj.object && _obj.object.type == "ThisExpression" && _root)
	{
		_obj.object.type = "Identifier";
		_obj.object.name = _root; 
	}
	
	while(_obj)
	{
		if(_obj.property && !_obj.computed) 
		{
			if(_obj.property.type == "Identifier")
			{
				if(_obj.object.type == "CallExpression" && _obj.object.callee.property.name == "NStruct")
				{
					// nothing to do
				}
				else 
				{
					_obj.property.type = "StringLiteral";
					_obj.property.extra = { rawValue: _obj.property.name, raw: '"' + _obj.property.name +'"'};
					_obj.property.value = _obj.property.name;
					_obj.computed = true;
				}
			}
		}
		
		if(_obj.object) _obj=_obj.object;
		else { _obj = null; break; }
	}
}
module.exports = memberExpression;