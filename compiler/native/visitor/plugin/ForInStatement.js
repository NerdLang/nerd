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
 
function ForInStatement(_path)
{
	var _rnd = RND();
	var _count = RND();
	var _left = _path.node.left.declarations[0].id.name;
	var _right = _path.node.right.name;
	var _pre = "var " + _rnd + " = __Nectar_Object_Keys(" + _right + ");";
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
}
module.exports = ForInStatement;