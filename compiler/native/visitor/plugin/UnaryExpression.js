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