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
 
function AssignmentExpression(_path)
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
			VISITOR.checkUndefVar(_obj.name);
			prop.push(_obj.name);
			VISITOR.readOnlyVar(_obj.name);
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

	if(_path.node.right && _path.node.right.type == "ArrayExpression")
	{
		var _a = VISITOR.arrayExpression(_path.node.right);
		COMPILER.DECL.push(_a.setter);
		_path.node.right = babel.parse(_a.getter + "();");
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