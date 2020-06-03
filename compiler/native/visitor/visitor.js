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

var IGNORE = ["__NJS_Call_Function", "__NJS_Object_Set", "__NJS_Obejct_Get"];
var FUNCTION_STATE = [];
var CURRENT_FUNCTION = -1;

function addFunctionVarInit(_name)
{
	if(CURRENT_FUNCTION > -1)
	{
		if(COMPILER.INFO.SCOPE[FUNCTION_STATE[CURRENT_FUNCTION]].init.indexOf(_name) < 0)
		COMPILER.INFO.SCOPE[FUNCTION_STATE[CURRENT_FUNCTION]].init.push(_name);
	}
}

function addFunctionVarUse(_value)
{
	if(CURRENT_FUNCTION > -1)
	{
		if(COMPILER.INFO.SCOPE[FUNCTION_STATE[CURRENT_FUNCTION]].use.indexOf(_value) < 0 && IGNORE.indexOf(_value) < 0)
		COMPILER.INFO.SCOPE[FUNCTION_STATE[CURRENT_FUNCTION]].use.push(_value);
	}
}

function addFunctionVarCall(_id, _type)
{
	if(COMPILER.INFO.SCOPE[_id] && COMPILER.INFO.SCOPE[_id].call.indexOf(_type) < 0)
	COMPILER.INFO.SCOPE[_id].call.push(_type);
}

function addFunctionVarParam(_id, _number)
{
	if(COMPILER.INFO.SCOPE[_id] && COMPILER.INFO.SCOPE[_id].param.indexOf(_number) < 0)
	COMPILER.INFO.SCOPE[_id].param.push(_number);
}

function readOnlyVar(_name)
{
	addFunctionVarInit(_name);
	if(COMPILER.READ_ONLY.indexOf(_name) > -1)
	{
		console.log("[!] Fatal error: " + _name + " is a read only variable");
		process.exit(1);
	}
}

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
		COMPILER.INFO.VALUE.push(_value);
	}
	else if(_path.value.extra) _value = _path.value.extra.raw;
	else if(_path.value.type == "ObjectProperty")
	{
		_code += objectExpression(_path.value, _key);
	}
	else if(_path.value.type == "FunctionExpression")
	{
		var _value = RND();
		COMPILER.INFO.FUNCTION.push(_value);
		_code += "var " + _value + " = " + babel.generate(_path.value).code + ";";		
	}
	else
	{
	  console.log("Visitor objectExpression not implemented yet for " + _path.value.type);
	}
	if(_value) _code += "__NJS_Object_Set(\"" + _key + "\"," + _value + "," + _name + ");"
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

function arrayExpression(_path)
{
	var prop = [];
	var _rnd = RND();
	var _set = "__NJS_" + RND();

	var _setter = `inline var ${_set}() { var ${_rnd} = __NJS_Create_Array();`;
	for(var i = 0; i < _path.elements.length; i++)
	{
		if(_path.elements[i] == "NumericLiteral") _setter += `__NJS_Object_Set(${i}, ${_path.elements[i].extra.raw}, ${_rnd});`;
		else _setter += `__NJS_Object_Set(${i}, ${babel.generate(_path.elements[i]).code}, ${_rnd});`;
	}
	_setter += `return ${_rnd};}`;

	return {setter: _setter, getter: _set};
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
	var _fName = _caller;
	_caller = "__NJS_Call_Function(" + _caller + ",";

	if(!COMPILER.INFO.CALL[_fName]) COMPILER.INFO.CALL[_fName] = [];
	addFunctionVarParam(_fName, _path.arguments.length);
	if(_path.arguments.length > 0)
	{
		if(COMPILER.INFO.CALL[_fName].indexOf(_path.arguments.length) < 0)
		{
			COMPILER.INFO.CALL[_fName].push(_path.arguments.length);
		}
		
		var _args = "";
		for(var i = 0; i < _path.arguments.length; i++)
		{
			addFunctionVarCall(_fName, _path.arguments[i].type);
			if(i > 0) _args += ",";
			if(_path.arguments[i].type == "Identifier")	
			{
				_args += _path.arguments[i].name;
			}
			else if(_path.arguments[i].extra)
			{
				_args += _path.arguments[i].extra.raw;
			}
			else if(_path.arguments[i].type == "MemberExpression")
			{
				if(_path.arguments[i].object && _path.arguments[i].object.type == "ThisExpression")
				{
				  _args += " __NJS_Object_Get(" + memberExpression(_path.arguments[i]) + ", __NJS_THIS)";
				}
				else _args += memberExpression(_path.arguments[i]);
			}
			else if(_path.arguments[i].type == "ArrayExpression")
			{
				var _arr = arrayExpression(_path.arguments[i]);
				_args += _arr.getter + "()";
				COMPILER.DECL += _arr.setter;
			}
			else 
			{
				_args += babel.generate(_path.arguments[i]).code;
			}
		}
		_caller += _args;
	}
	else
	{
		if(COMPILER.INFO.CALL[_fName].indexOf(0) < 0)
		{
			COMPILER.INFO.CALL[_fName].push(0);
		}
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
			ForInStatement(_path)
			{
				var _rnd = RND();
				var _count = RND();
				var _left = _path.node.left.declarations[0].id.name;
				var _right = _path.node.right.name;
				var _pre = "var " + _rnd + " = __NJS_Object_Keys(" + _right + ");";
				var _loop = `for(var ${_count} = 0; ${_count} < ${_rnd}.length; ${_count}++){var ${_left} = ${_rnd}[${_count}];`
				var _body = babel.generate(_path.node.body).code;
				var _end = "";
				if(_body[0] == "{")
				{
					_body = _body.substring(1);
				}
				else _end = "}";
				_loop += _body + _end;
				_path.insertBefore(babel.parse(_pre));
				_path.replaceWith(babel.parse(_loop));
			},
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

								";__NJS_Object_Set(" + i + ",_" + _el[i].value + "," + _name + ")"
								
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

				  //var _obj = [];
				  
				  for(var i = 0; i < _el.length; i++)
				  {
					  var _o = false;
					  var _key;
					  var _value;
					  
					  if(_el[i].key &&_el[i].key.name)
					  {
						_key = _el[i].key.name;
					  }
					  else _key = _el[i].key.value;
					  
					  if(_el[i].value && _el[i].value.name)
					  {
						_value = _el[i].value.name;
					  }
					  else if(_el[i].value &&_el[i].value.extra) _value = _el[i].value.extra.raw;
					  else if(_el[i].type == "ObjectProperty")
					  {
						 _o = true;
						  _code += objectExpression(_el[i], _name);
					  }
					  else
					  {
						  console.log("Visitor VariableDeclarator not implemented yet for " + _el[i].type);
					  }
					  
					  if(_value && !_o)
					  {
						  _code += "__NJS_Object_Set(\"" + _key + "\"," + _value + "," + _name + ");"
						  COMPILER.INFO.VALUE.push(_value);
					  }
				  }

				   _path.replaceWith(babel.parse(_code));
			  }
		  },
		  VariableDeclaration(_path)
		  {
			  if(_path.node.declarations)
			  {
				  for(var d = 0; d < _path.node.declarations.length; d++)
				  {
					if(_path.node.declarations[d].id && _path.node.declarations[d].id.name)
					{
						readOnlyVar(_path.node.declarations[d].id.name);
						if(COMPILER.ENV.name == "android" && COMPILER.STATE == "CODE")
						{
							_path.node.kind = "";
							COMPILER.DECL += " var " + _path.node.declarations[d].id.name + ";";
						}
					}
					if(!(_path.node.declarations[d].init)) _path.node.declarations[d].init = babel.parse("__NJS_VAR()");
				  }
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
						var _property;
						if(_obj.property.type == "Identifier")
						{
							if(_obj.computed)
							{
								_property = _obj.property.name;
								COMPILER.INFO.VALUE.push(_property);
							}
							else 
							{
								_property = "\"" + _obj.property.name + "\"";
								COMPILER.INFO.VALUE.push(_obj.property.name);
							}
							
						}
						else if(_obj.property.extra)
						{
							_property = _obj.property.extra.raw;
							COMPILER.INFO.VALUE.push(_property);
						}
						
						if(_property)
						{
							prop.push(_property);
						}
						
					}
					if(_obj.name)
					{
						prop.push(_obj.name);
						readOnlyVar(_obj.name);
					}
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
			 else if(_path.node.left.type == "Identifier")
			 {
				 readOnlyVar(_path.node.left.name)
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
		  MemberExpression(_path)
		  {  
			  if(_path.node.object && _path.node.object.type == "ThisExpression")
			  {
				_path.replaceWithSourceString( "__NJS_Object_Get(" + memberExpression(_path.node) + ", __NJS_THIS)");
			  }
			  else _path.replaceWithSourceString(memberExpression(_path.node));
		  },
		  Identifier(_path)
		  {
			addFunctionVarUse(_path.node.name);
		  },
		  FunctionDeclaration:
		  {
			enter(_path)
			{
				if(_path.node.id)
				{
					CURRENT_FUNCTION++;
					FUNCTION_STATE.push(_path.node.id.name);
					
					if(!COMPILER.INFO.SCOPE[_path.node.id.name]) COMPILER.INFO.SCOPE[_path.node.id.name] = {init:[], use:[], call:[], param: [], fast: true};
					addFunctionVarInit(_path.node.id.name);
					if(_path.node.params.length > 0)
					{
						for(var i = 0; i < _path.node.params.length; i++)
						{
							addFunctionVarInit(_path.node.params[i].name);
						}
					}
				}
				
			},
			exit(_path)
			{
				if(_path.node.id)
				{
					CURRENT_FUNCTION--;
					FUNCTION_STATE.pop();
				}
			},
		  }
        },
      };
    },
  ],
}
module.exports = visitor;
