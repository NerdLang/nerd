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
 
function arrayExpression(_path, _main)
{
	var prop = [];
	var _rnd = RND();
	var _set = "__NJS_GEN_RND_" + RND();

	var _setter = `inline NectarCore::VAR ${_set}() { NectarCore::VAR ${_rnd} = __NJS_Create_Array();`;
	for(var i = 0; i < _path.elements.length; i++)
	{
		if(_path.elements[i].type == "NumericLiteral") _setter += `${_rnd}[${i}] =  ${_path.elements[i].extra.raw};`;
		else if(_path.elements[i].type == "ArrayExpression")
		{
			var _a = VISITOR.arrayExpression(_path.elements[i], _main);
			COMPILER.DECL.push(_a.setter);
			_setter += `${_rnd}[${i}] =  ${_a.getter}();`;
		}
		else if (_path.elements[i].type == "StringLiteral")
		{
			if(_path.elements[i].extra.raw[0] && _path.elements[i].extra.raw[0] == "'")
			{
				_path.elements[i].extra.raw = '"' + _path.elements[i].value.replace(/\\/g, '\\\\').replace(/"/g, '\\\"') + '"';
			}
			_setter += `${_rnd}[${i}] = ${babel.generate(_path.elements[i]).code};`;
		}
		else _setter += `${_rnd}[${i}] = ${babel.generate(_path.elements[i]).code};`;
	}
	_setter += `return ${_rnd};}`;
	return {setter: _setter, getter: _set};
}
module.exports = arrayExpression;