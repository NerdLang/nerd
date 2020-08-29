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
 
function ClassDeclaration(_path)
{
	var _class = " function __NJS_CLASS_" + _path.node.id.name + "(";
	var _constructor = false;
	var _body = "";

	if(_path.node.body && _path.node.body.body)
	{
		for(var o = 0; o < _path.node.body.body.length; o++)
		{
			if(_path.node.body.body[o].kind == "constructor")
			{
				_constructor = true;
				_path.node.body.body[o].key == babel.parse(_path.node.id.name);
				
				var _params = "";
				for(var p = 0; p < _path.node.body.body[o].params.length; p++)
				{
					if(p > 1) _params += ",";
					_params += _path.node.body.body[o].params[p].name;
				}
				_class += _params + "){\nvar __NJS_THIS = __NJS_Create_Object();\n";
				var _newBody = babel.generate(_path.node.body.body[o].body).code;
				_newBody = _newBody.substring(1, _newBody.length -1);
				 _class += _newBody;
			}
			else if(_path.node.body.body[o].kind == "method")
			{
				var _method = "__NJS_THIS." + _path.node.body.body[o].key.name + "= function(";
				
				var _params = "";
				for(var p = 0; p < _path.node.body.body[o].params.length; p++)
				{
					if(p > 1) _params += ",";
					_params += _path.node.body.body[o].params[p].name;
				}
				_method += _params + ")\n";
				_method += "{\n";//"{\n'__NJS_CLASS_ANON__';"
				_method += babel.generate(_path.node.body.body[o].body).code.substring(1);
				_body += _method + "\n";
			} 
		}
	}
	if(!_constructor)
	{
		_class += "){\nvar __NJS_THIS = __NJS_Create_Object();\n";
	}
	_class += _body;
	_class += "}";

	var _n = babel.parse(_class);
	_path.replaceWith(_n.program);
}
module.exports = ClassDeclaration;