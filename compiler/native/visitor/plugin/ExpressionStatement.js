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
 
function ExpressionStatement(_path)
{
	if(_path.node.expression && _path.node.expression.type == "CallExpression" && !_path.node.expression.id 
		&& _path.node.expression.callee && _path.node.expression.callee.type == "FunctionExpression")
	{
		var _nf = RND();
		var _code = "var " + _nf + " = "  + babel.generate(_path.node.expression.callee).code + ";";
		var _ncode = `${_nf}()`;
		_path.insertBefore(babel.parse(_code));
		_path.replaceWithSourceString(_ncode);
		_path.skip;
	}
}
module.exports = ExpressionStatement;