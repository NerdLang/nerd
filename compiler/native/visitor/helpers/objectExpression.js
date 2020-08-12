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
		_code += VISITOR.objectExpression(_path.value, _key);
	}
	else if(_path.value.type == "FunctionExpression")
	{
		var _value = RND();
		COMPILER.INFO.FUNCTION.push(_value);
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
		_code += _name + "['" + _key + "'] = " + _subRND + ";";
	}
	else if(_path.value.type == "MemberExpression")
	{
		VISITOR.memberExpression(_path.value);

	}
	else if(_path.value.type == "BooleanLiteral")
	{
		_value = _path.value.value;
	}
	else
	{
	  console.log("Visitor VISITOR.objectExpression not implemented yet for " + _path.value.type);
	  process.exit(0);
	}
	if(_value) _code += _name + "['" + _key + "'] = " + _value + ";";
	return _code;
}
module.exports = objectExpression;