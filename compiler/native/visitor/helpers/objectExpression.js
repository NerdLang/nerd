/*
 * This file is part of NectarJS
 * Copyright (c) 2017 - 2020 Adrien THIERRY
 * http://nectarjs.com - https://seraum.com/
 *
 * sources : https://github.com/nectarjs/nectarjs
 * 
 * NectarJS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * NectarJS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with NectarJS.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
 
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
	
	else if(_path.value.type == "ObjectProperty")
	{
		_code += VISITOR.objectExpression(_path.value, _key);
	}
	else if(_path.value.type == "ArrayExpression")
	{
		var _arr = VISITOR.arrayExpression(_path.value, _key);
		COMPILER.DECL.push(_arr.setter + ";");
		_code += _name + "[\"" + _key + "\"] = " + _arr.getter + "();" ;
	}
	else if(_path.value.type == "FunctionExpression")
	{
		var _value = RND();
		COMPILER.INFO.Function.push(_value);
		_code += "var " + _value + " = " + babel.generate(_path.value).code + ";";		
	}
	else if(_path.value.type == "ObjectExpression")
	{
		var _subRND = RND();
		_code += "var " + _subRND + " = __NJS_Create_Object();";
		for(var i = 0; i < _path.value.properties.length; i++)
		{
			_code += VISITOR.objectExpression(_path.value.properties[i], _subRND); 
		}
		_code += _name + "[\"" + _key + "\"] = " + _subRND + ";";
	}
	else if(_path.value.type == "MemberExpression")
	{
		VISITOR.memberExpression(_path.value);
		_code += _name + "[\"" + _key + "\"] = " + babel.generate(_path.value).code + ";";
	}
	else if(_path.value.type == "BooleanLiteral")
	{
		_value = _path.value.value;
	}
	else if(_path.value.type == "BinaryExpression")
	{
		if(_path.value.operator == "===")
		{
			var _eq = "__Nectar_EQUAL_VALUE_AND_TYPE(";
			_eq += babel.generate(_path.node.left).code + ","
			_eq += babel.generate(_path.node.right).code + ")";
			_path.replaceWithSourceString(_eq);
		}
		else if(_path.value.operator == "!==")
		{
			var _not_eq = "__Nectar_NOT_EQUAL_VALUE_AND_TYPE(";
			_not_eq += babel.generate(_path.node.left).code + ","
			_not_eq += babel.generate(_path.node.right).code + ")";
			_path.replaceWithSourceString(_not_eq);
		}
		if(_path.value.left.type == "MemberExpression") VISITOR.memberExpression(_path.value.left, _name);
		if(_path.value.right.type == "MemberExpression") VISITOR.memberExpression(_path.value.right, _name);
		
		_code += _name + "[\"" + _key + "\"] = " + babel.generate(_path.value).code + ";";
	}
	else if(_path.value.type == "UnaryExpression")
	{
		_code += _name + "[\"" + _key + "\"] = " + babel.generate(_path.value).code + ";";
	}
	else if(_path.value.extra) _value = _path.value.extra.raw;
	else
	{
	  console.log("Visitor VISITOR.objectExpression not implemented yet for " + _path.value.type);
	  process.exit(0);
	}
	if(_value) _code += _name + "[\"" + _key + "\"] = " + _value + ";";
	return _code;
}
module.exports = objectExpression;