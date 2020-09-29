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