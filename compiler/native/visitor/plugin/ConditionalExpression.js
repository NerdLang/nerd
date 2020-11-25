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
 
function ConditionalExpression(_path)
{
	if(_path.node.consequent.type != _path.node.alternate.type)
	{
		
		if(_path.node.alternate.type == "NumericLiteral" || _path.node.alternate.type == "StringLiteral" || _path.node.alternate.type == "UnaryExpression")
		{
			var _rnd = "__Nectar_TERNARY" + RND();
			COMPILER.DECL.push(`var ${_rnd} = ${_path.node.alternate.value}`);
			_path.node.alternate.type = "Identifier";
			_path.node.alternate.name = _rnd;
		}
		if(_path.node.consequent.type == "NumericLiteral" || _path.node.consequent.type == "StringLiteral" || _path.node.consequent.type == "UnaryExpression")
		{
			var _rnd = "__Nectar_TERNARY" + RND();
			COMPILER.DECL.push(`var ${_rnd} = ${_path.node.consequent.value}`);
			_path.node.consequent.type = "Identifier";
			_path.node.consequent.name = _rnd;
		}
		
	}
}
module.exports = ConditionalExpression;