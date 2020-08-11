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
 
function callExpression(_path)
{
	if(_path.callee && _path.callee.name && (VISITOR.NJS_START.indexOf(_path.callee.name.substring(0, 5)) > -1 || VISITOR.NO_MODIFY_CALL.indexOf(_path.callee.name) > -1))
	{
	  return "";
	}
	var prop = [];

	var _obj = _path.callee;
	if(_obj.name) VISITOR.checkUndefVar(_obj.name);

	function whileObj(_obj)
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
		if(_obj.type == "CallExpression")
		{
			prop.push(VISITOR.callExpression(_obj));
		}
		
		if(_obj.object) whileObj(_obj.object);
		if(_obj.name)
		{
			prop.push(_obj.name);
			VISITOR.checkUndefVar(_obj.name);
		}
		
	}
	whileObj(_obj);

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
	VISITOR.addFunctionVarParam(_fName, _path.arguments.length);
	if(_path.arguments.length > 0)
	{
		if(COMPILER.INFO.CALL[_fName].indexOf(_path.arguments.length) < 0)
		{
			COMPILER.INFO.CALL[_fName].push(_path.arguments.length);
		}
		
		var _args = "";
		for(var i = 0; i < _path.arguments.length; i++)
		{
			VISITOR.addFunctionVarCall(_fName, _path.arguments[i].type);
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
				  _args += " __NJS_Object_Get(" + VISITOR.memberExpression(_path.arguments[i]) + ", __NJS_THIS)";
				}
				else _args += VISITOR.memberExpression(_path.arguments[i]);
			}
			else if(_path.arguments[i].type == "ArrayExpression")
			{
				var _arr = VISITOR.arrayExpression(_path.arguments[i]);
				_args += _arr.getter + "()";
				COMPILER.DECL.push(_arr.setter);
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
module.exports = callExpression;