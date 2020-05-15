/*
 * This file is part of NectarJS
 * Copyright (c) 2017-2020 Adrien THIERRY
 * http://nectarjs.com - https://www.linkedin.com/in/adrien-thierry-fr/
 *
 * sources : https://github.com/nectarjs/nectarjs/
 *
 * this program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * You can be released from the requirements of the license by purchasing
 * a commercial license. Buying such a license is mandatory as soon as you
 * develop commercial activities involving the NectarJS software without
 * disclosing the source code of your own applications. Visit http://seraum.com/
 * and feel free to contact us.
 *
 */
var NO_MODIFY_CALL = ["require", "Object"];
var NJS_START = ["__NJS", "__FFI"];

function objectExpression(_path, _name)
{
	var _code = "";
				  
	var _key;
	var _value;

	if(_path.key.name)
	{
	_key = _path.key.name;
	}
	else _key = _path.key.value;

	if(_path.value.name)
	{
	_value = _path.value.name;
	}
	else if(_path.value.extra) _value = _path.value.extra.raw;
	else if(_path.value.type == "ObjectProperty")
	{
		_code += objectExpression(_path.value, _key);
	}
	else if(_path.value.type == "FunctionExpression")
	{
		var _value = RND();
		_code += "var " + _value + " = " + babel.generate(_path.value).code + ";";		
	}
	else
	{
	  console.log("Visitor VariableDeclarator not implemented yet for " + _path.value.type);
	}
	if(_value) _code += "__NJS_Object_Set(\"" + _key + "\",__NJS_VAR(" + _value + ")," + _name + ");"
	return _code;
}

function memberExpression(_path)
{
	var prop = [];
	var _obj = _path;

	while(_obj)
	{
		if(_obj.property) 
		{
			if(_obj.property.type == "Identifier")
			{
				if(_obj.computed) prop.push(_obj.property.name);
				else prop.push("\"" + _obj.property.name + "\"");
			}
			else if(_obj.property && _obj.property.extra) prop.push(_obj.property.extra.raw);
		}
		if(_obj.object)
		{
			if(_obj.object.type == "CallExpression")
			{
				prop.push(callExpression(_obj.object));
			}
		}
		
		if(_obj.name) prop.push(_obj.name);
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

function callExpression(_path)
{
	if(_path.callee && _path.callee.name && (NJS_START.indexOf(_path.callee.name.substring(0, 5)) > -1 || NO_MODIFY_CALL.indexOf(_path.callee.name) > -1))
	{
	  return "";
	}
	var prop = [];
	var _obj = _path.callee;

	while(_obj)
	{
		if(_obj.property) 
		{
			if(_obj.property.type == "Identifier")
			{
				if(_obj.computed) prop.push(_obj.property.name);
				else prop.push("\"" + _obj.property.name + "\"");
			}
			else if(_obj.property && _obj.property.extra) prop.push(_obj.property.extra.raw);
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

	if(_path.arguments.length > 0)
	{
		var _args = "";
		for(var i = 0; i < _path.arguments.length; i++)
		{
			if(_path.arguments[i].type == "Identifier")	
			{
				_args += "," + _path.arguments[i].name;
			}
			else if(_path.arguments[i].extra)
			{
				_args += "," + _path.arguments[i].extra.raw;
			}
			else if(_path.arguments[i].type == "MemberExpression")
			{
				if(_path.arguments[i].object && _path.arguments[i].object.type == "ThisExpression")
				{
				  _args += ", __NJS_Object_Get(" + memberExpression(_path.arguments[i]) + ", __NJS_THIS)";
				}
				else _args += "," + memberExpression(_path.arguments[i]);
			}
			else 
			{
				_args += "," + babel.generate(_path.arguments[i]).code;
			}
		}
		_caller += _args;
	}
	_caller += ")";
	return _caller;
}

var visitor = 
{
  plugins: [
    function NectarJS() {
      return {
        visitor: {
			ClassDeclaration(_path)
			{
				var _class = " function __NJS_CLASS_" + _path.node.id.name + "(";
				var _constructor = false;
				var _body = "";

				if(_path.node.body && _path.node.body.body)
				{
					for(var o = 0; o < _path.node.body.body.length; o++)
					{
						if(_path.node.body.body[o].kind == "constructor")
						{
							_constructor = true;
							_path.node.body.body[o].key == babel.parse(_path.node.id.name);
							
							var _params = "";
							for(var p = 0; p < _path.node.body.body[o].params.length; p++)
							{
								if(p > 1) _params += ",";
								_params += _path.node.body.body[o].params[p].name;
							}
							_class += _params + "){\nvar __NJS_THIS = __NJS_Create_Object();\n";
							var _newBody = babel.generate(_path.node.body.body[o].body).code;
							_newBody = _newBody.substring(1, _newBody.length -1);
							 _class += _newBody;
						}
						else if(_path.node.body.body[o].kind == "method")
						{
							var _method = "__NJS_THIS." + _path.node.body.body[o].key.name + "= function(";
							
							var _params = "";
							for(var p = 0; p < _path.node.body.body[o].params.length; p++)
							{
								if(p > 1) _params += ",";
								_params += _path.node.body.body[o].params[p].name;
							}
							_method += _params + ")\n";
							_method += "{\n'__NJS_CLASS_ANON__';"
							_method += babel.generate(_path.node.body.body[o].body).code.substring(1);
							_body += _method + "\n";
						} 
					}
				}
				if(!_constructor)
				{
					_class += "){\nvar __NJS_THIS = __NJS_Create_Object();\n";
				}
				_class += _body;
				_class += "}";

				var _n = babel.parse(_class);
				_path.replaceWith(_n.program);
			},
		  NewExpression(_path)
		  {
			_path.node.type = "CallExpression";
			_path.node.callee.name = "__NEW_" + _path.node.callee.name;
			var _new = callExpression(_path.node);
			if(_new.length > 0) _path.replaceWithSourceString(_new);
		  },
		  StringLiteral(_path)
		  {

			if(_path.node.extra.raw[0] && _path.node.extra.raw[0] == "'")
			{
				_path.node.extra.raw = '"' + _path.node.value.replace(/\\/g, '\\\\').replace(/"/g, '\\\"') + '"';
			}

		  },
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

								";__NJS_Object_Set(" + i + ",__NJS_VAR(" + _el[i].value + ")," + _name + ")"
								
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
					  else if(_el[i].value.extra) _value = _el[i].value.extra.raw;
					  else if(_el[i].type == "ObjectProperty")
					  {
						  _code += objectExpression(_el[i], _name);
					  }
					  else
					  {
						  console.log("Visitor VariableDeclarator not implemented yet for " + _el[i].type);
					  }
					  
					  if(_value) _code += "__NJS_Object_Set(\"" + _key + "\",__NJS_VAR(" + _value + ")," + _name + ");"
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
						if(_obj.property.type == "Identifier")
						{
							if(_obj.computed) prop.push(_obj.property.name);
							else prop.push("\"" + _obj.property.name + "\"");
						}
						else if(_obj.property.extra) prop.push(_obj.property.extra.raw);
					}
					if(_obj.name) prop.push(_obj.name);
					else if(_obj.type == "ThisExpression") prop.push("__NJS_THIS");
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
			  var _new = callExpression(_path.node);
			  if(_new.length > 0) _path.replaceWithSourceString(_new);
		  },
		  UnaryExpression(_path) 
		  { 
			if (_path.node.operator == "typeof")
			{
				if(_path.node.argument.type == "Identifier")	
				{
					_path.replaceWithSourceString("__NJS_Typeof(" + _path.node.argument.name + ")");
				}
				else if(_path.node.argument.extra)
				{
					_path.replaceWithSourceString("__NJS_Typeof(" + _path.node.argument.extra.raw + ")");
				}
				else if (_path.node.argument.type == "MemberExpression")
				{
					_path.replaceWithSourceString("__NJS_Typeof(" + memberExpression(_path.node.argument) + ")");
				}
				else if (_path.node.argument.type == "CallExpression")
				{
					_path.replaceWithSourceString("__NJS_Typeof(" + callExpression(_path.node.argument) + ")");
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
		  ThisExpression(_path)
		  {
			console.log("this");
		  },
		  MemberExpression(_path)
		  {  
			  if(_path.node.object && _path.node.object.type == "ThisExpression")
			  {
				_path.replaceWithSourceString( "__NJS_Object_Get(" + memberExpression(_path.node) + ", __NJS_THIS)");
			  }
			  else _path.replaceWithSourceString(memberExpression(_path.node));
		  }
        },
      };
    },
  ],
}
module.exports = visitor;