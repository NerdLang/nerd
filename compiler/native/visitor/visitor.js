var NO_MODIFY_CALL = ["require", "Object"];
var PRIVATE_START = ["__NJS", "__FFI"];
function memberExpression(_path)
{
	var prop = [];
	var _obj = _path;

	while(_obj)
	{
		if(_obj.property) 
		{
			if(_obj.property.type == "Identifier") prop.push("\"" + _obj.property.name + "\"");
		}
		if(_obj.name) prop.push(_obj.name);
		else if(_obj.property.extra) prop.push(_obj.property.extra.raw);
		if(_obj.object) _obj=_obj.object;
		else { _obj = null; break; }
	}
	
	var _setter = "{{PROPERTY}}";
	for(var i = 0; i < prop.length; i++)
	{
		if(i == prop.length - 1)
		{
			_setter = _setter.replace("{{PROPERTY}}", prop[i]);
		}
		else 
		{
			var _p = "__NJS_Object_Get(" + prop[i] + ", {{PROPERTY}})"; 
			_setter = _setter.replace("{{PROPERTY}}", _p);
		}
	}
	return _setter;
}


var visitor = 
{
  plugins: [
    function NectarJS() {
      return {
        visitor: {
          VariableDeclarator(_path) 
		  {
			  // Creating Arrays
			  if(_path.node.id && _path.node.id.name && _path.node.init && _path.node.init.type == "ArrayExpression")
			  {
				  var _name = _path.node.id.name;
				  var _el = _path.node.init.elements;
				  _path.node.init.type = "CallExpression";
				  _path.node.init.argument = [];
				  _path.node.init.callee = 
				  {
					  type:"Identifier",
					  name:"__NJS_Create_Array"
				  };
				  var _obj = [];
				  for(var i = 0; i < _el.length; i++)
				  {
					  
					   _obj.push(babel.parse(

								";__NJS_Object_Set(" + i + "," + _el[i].value + "," + _name + ")"
								
							));
				  }
				   _path.insertAfter(_obj);
				  
			  }
			  // Creating Object
			  else if(_path.node.id && _path.node.id.name && _path.node.init && _path.node.init.type == "ObjectExpression")
			  {
				  var _name = _path.node.id.name;

				  var _el = _path.node.init.properties;
				  var _code = _path.node.id.name + " = __NJS_Create_Object();"

				  var _obj = [];
				  
				  for(var i = 0; i < _el.length; i++)
				  {
					  var _key;
					  var _value;
					  
					  if(_el[i].key.name)
					  {
						_key = _el[i].key.name;
					  }
					  else _key = _el[i].key.value;
					  
					  if(_el[i].value.name)
					  {
						_value = _el[i].value.name;
					  }
					  else _value = _el[i].value.extra.raw;
					  
					  _code += "__NJS_Object_Set(\"" + _key + "\"," + _value + "," + _name + ");"
				  }
				  
				   _path.replaceWith(babel.parse(_code));
			  }
          },
		  AssignmentExpression(_path)
		  {
			 if(_path.node.left.type == "MemberExpression")
			 {
				var prop = [];
				var _obj = _path.node.left;
				while(_obj)
				{
					if(_obj.property) 
					{
						if(_obj.property.type == "Identifier") prop.push("\"" + _obj.property.name + "\"");
					}
					if(_obj.name) prop.push(_obj.name);
					else if(_obj.property.extra) prop.push(_obj.property.extra.raw);
					if(_obj.object) _obj=_obj.object;
					else { _obj = null; break; }
				}
				var _setter = "";
				for(var i = 0; i < prop.length; i++)
				{
					if(i == 0)
					{
						_setter = "__NJS_Object_Set(" + prop[i] + ", {{LEFT}}, {{PROPERTY}})"; 
					}
					else if(i == prop.length - 1)
					{
						_setter = _setter.replace("{{PROPERTY}}", prop[i]);
					}
					else 
					{
						var _p = "__NJS_Object_Get(" + prop[i] + ", {{PROPERTY}})"; 
						_setter = _setter.replace("{{PROPERTY}}", _p);
					}
				}
				var _n = RND();
				_path.insertBefore(babel.parse("var " + _n + ";"));
				_path.node.left = babel.types.identifier(_n);
				_path.insertAfter(babel.parse(_setter.replace("{{LEFT}}", _n)));
			 }
		  },
		  CallExpression(_path)
		  {
			  if(_path.node.callee && _path.node.callee.name && (PRIVATE_START.indexOf(_path.node.callee.name.substring(0, 5)) > -1 || NO_MODIFY_CALL.indexOf(_path.node.callee.name) > -1))
			  {
				  return;
			  }
				var prop = [];
				var _obj = _path.node.callee;

				while(_obj)
				{
					if(_obj.property) 
					{
						if(_obj.property.type == "Identifier") prop.push("\"" + _obj.property.name + "\"");
					}
					if(_obj.name) prop.push(_obj.name);
					if(_obj.object) _obj=_obj.object;
					else { _obj = null; break; }
				}
				
				var _caller = "{{PROPERTY}}";
				for(var i = 0; i < prop.length; i++)
				{
					if(i == prop.length - 1)
					{
						_caller = _caller.replace("{{PROPERTY}}", prop[i]);
					}
					else 
					{
						var _p = "__NJS_Object_Get(" + prop[i] + ", {{PROPERTY}})"; 
						_caller = _caller.replace("{{PROPERTY}}", _p);
					}
				}
				_caller = "__NJS_Call_Function(" + _caller;

				if(_path.node.arguments.length > 0)
				{
					var _args = "";
					for(var i = 0; i < _path.node.arguments.length; i++)
					{
						if(_path.node.arguments[i].type == "Identifier")	
						{
							_args += "," + _path.node.arguments[i].name;
						}
						else if(_path.node.arguments[i].extra)
						{
							_args += "," + _path.node.arguments[i].extra.raw;
						}
						else if(_path.node.arguments[i].type == "MemberExpression")
						{
							_args += "," + memberExpression(_path.node.arguments[i]);
						}
						else 
						{
							_args += "," + babel.generate(_path.node.arguments[i]).code;
						}
					}
					_caller += _args;
				}
				_caller += ")";
				_path.replaceWithSourceString(_caller);
		  },
		  UnaryExpression(_path) 
		  { 
			if (_path.node.operator == "typeof")
			{
				if(_path.node.argument.type == "Identifier")	
				{
					_path.replaceWithSourceString("__NJS_Typeof(" + _path.node.argument.name + ")");
				}
				else 
				{
					_path.replaceWithSourceString("__NJS_Typeof(" + _path.node.argument.extra.raw + ")");
				}
				_path.skip();
			}
		  },
		  CatchClause(_path) 
		  {
			const paramPath = _path.get("param");
			paramPath.replaceWithSourceString("__NJS_VAR");
		  },
		  ReturnStatement(_path)
		  {
			if(_path.node.argument.type == "MemberExpression")
			{
				const _arg = _path.get("argument");
				_arg.replaceWithSourceString(memberExpression(_path.node.argument));
			}
		  },
        },
      };
    },
  ],
}
module.exports = visitor;