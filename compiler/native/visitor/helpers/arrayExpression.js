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
 
function arrayExpression(_path)
{
	var prop = [];
	var _rnd = RND();
	var _set = "__NJS_RND_" + RND();

	var _setter = `inline __NJS_VAR ${_set}() { __NJS_VAR ${_rnd} = __NJS_Create_Array();`;
	for(var i = 0; i < _path.elements.length; i++)
	{
		if(_path.elements[i].type == "NumericLiteral") _setter += `__NJS_Object_Set(${i}, ${_path.elements[i].extra.raw}, ${_rnd});`;
		else if(_path.elements[i].type == "ArrayExpression")
		{
			var _a = VISITOR.arrayExpression(_path.elements[i]);
			COMPILER.DECL.push(_a.setter);
			_setter += `__NJS_Object_Set(${i}, ${_a.getter}(), ${_rnd});`;
		}
		else _setter += `__NJS_Object_Set(${i}, ${babel.generate(_path.elements[i]).code}, ${_rnd});`;
	}
	_setter += `return ${_rnd};}`;
	return {setter: _setter, getter: _set};
}
module.exports = arrayExpression;