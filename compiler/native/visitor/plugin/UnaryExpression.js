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
		if(_path.node.argument.type == "Identifier")	
		{
			_path.replaceWithSourceString("__NJS_typeof(" + _path.node.argument.name + ")");
		}
		else if(_path.node.argument.extra)
		{
			_path.replaceWithSourceString("__NJS_typeof(" + _path.node.argument.extra.raw + ")");
		}
		else if (_path.node.argument.type == "MemberExpression")
		{
			VISITOR.memberExpression(_path.node.argument);
			_path.replaceWithSourceString("__NJS_typeof(" + babel.generate(_path.node.argument).code + ")");
		}
		else if (_path.node.argument.type == "CallExpression")
		{
			_path.replaceWithSourceString("__NJS_typeof(" + babel.generate(_path.node.argument).code + ")");
		}
		_path.skip();
	}
	// void
	else if(_path.node.operator == "void")
	{
		var _rnd = "__NJS_VOID_" + RND();
		COMPILER.DECL.push(`__NJS_VAR ${_rnd}() { ${babel.generate(_path.node.arguments).code} return undefined;};`);
		VISITOR.pushDeclVar(_rnd);
		_path.replaceWithSourceString(`${_rnd}()`);
	}
	else if(_path.node.operator == "delete")
	{
		if (_path.node.argument.type == "MemberExpression")
		{
			VISITOR.memberExpression(_path.node.argument);
			var _left = babel.generate(_path.node.argument).code.split("[\"");
			var _right = _left.splice(-1).join();
			_right = "\"" + _right.substring(0, _right.length - 1);
			_left = _left.join("[\"");

			_path.replaceWithSourceString(`__NJS_delete(${_left}, ${_right})`);
		}
		else 
		{
			_path.replaceWithSourceString("__NJS_Boolean_FALSE");
		}
	}
}
module.exports = UnaryExpression;