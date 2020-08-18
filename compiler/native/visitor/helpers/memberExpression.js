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
 
function memberExpression(_path, _root)
{
	var _obj = _path;

	if(_obj.object && _obj.object.type == "Identifier")
	{
		VISITOR.checkUndefVar(_obj.object.name);
		VISITOR.readOnlyVar(_obj.object.name);
	}
	else if(_obj.object && _obj.object.type == "ThisExpression" && _root)
	{
		_obj.object.type = "Identifier";
		_obj.object.name = _root; 
	}

	
	while(_obj)
	{
		if(_obj.property && !_obj.computed) 
		{
			if(_obj.property.type == "Identifier")
			{
				_obj.property.type = "StringLiteral";
				_obj.property.extra = { rawValue: _obj.property.name, raw: '"' + _obj.property.name +'"'};
				_obj.property.value = _obj.property.name;
				_obj.computed = true;
			}
		}
		
		if(_obj.object) _obj=_obj.object;
		else { _obj = null; break; }
	}
}
module.exports = memberExpression;