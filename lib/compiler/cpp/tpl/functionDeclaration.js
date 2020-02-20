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
 
function functionDeclaration(_obj, _compiler)
{
	var p= [];
	for(var v in _obj.params)
	{
		p.push("var " + _obj.params[v].name);
	}
	
	var _random = createRandomVar();
	_compiler.INIT.push(
		`var ${_obj.id.name} = var(UNDEFINED, 0);`
	);
	_compiler.INIT.push(
		`static std::function<var(${p.join(',')})> ${_random};`
	);
	_compiler.CODE.push(
		`${_random}=[&](${p.join(',')})
		{
		`
	);
		
	_compiler.Parse(_obj.body);
	
	_compiler.CODE.push(
		`return var(UNDEFINED, 0);
		};
		${_obj.id.name}=var(FUNCTION, &${_random});
		`
	);
	
	
}

module.exports = functionDeclaration;