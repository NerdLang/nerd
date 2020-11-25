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
 
var ClassDeclaration =
{
	enter(_path)
	{
		COMPILER.VAR_STATE.push([]);
		VISITOR.pushDeclVar(_path.node.id.name, 0);
		VISITOR.CURRENT_Function++;
		VISITOR.Function_STATE.push(_path.node.id.name);
		if(!COMPILER.INFO.SCOPE[_path.node.id.name]) COMPILER.INFO.SCOPE[_path.node.id.name] = {init:[], use:[], call:[], param: [], fast: true};
		var _class = " function __Nectar_CLASS_" + _path.node.id.name + "(";
		var _ctor = "";
		var _body = "";
		var _static = "";
		var _globalParams = "";
		
		if(_path.node.body && _path.node.body.body)
		{
			for(var o = 0; o < _path.node.body.body.length; o++)
			{
				if(_path.node.body.body[o].kind == "constructor")
				{
					_path.node.body.body[o].key == babel.parse(_path.node.id.name);
					
					for(var p = 0; p < _path.node.body.body[o].params.length; p++)
					{
						if(p > 0) _globalParams += ",";
						_globalParams += _path.node.body.body[o].params[p].name;
					}
					
					var _newBody = babel.generate(_path.node.body.body[o].body).code;
					_newBody = _newBody.substring(1, _newBody.length -1);
					 _ctor += _newBody;
				}
				else if(_path.node.body.body[o].kind == "method")
				{
					var _method = "";
					if(_path.node.body.body[o].static)
					{
						_method = _path.node.id.name + "." + _path.node.body.body[o].key.name + "= function(";
					}
					else _method = "__Nectar_THIS." + _path.node.body.body[o].key.name + "= function(";
					
					var _params = "";
					for(var p = 0; p < _path.node.body.body[o].params.length; p++)
					{
						if(p > 0) _params += ",";
						_params += _path.node.body.body[o].params[p].name;
					}
					_method += _params + ")\n";
					_method += "{\n'__NJS_CLASS_ANON__';"
					_method += babel.generate(_path.node.body.body[o].body).code.substring(1);
					
					if(_path.node.body.body[o].static) _static += _method + "\n";
					else _body += _method + "\n";
				} 
			}
		}
		_class += _globalParams + "){\n";
		_class += _body;
		_class += _ctor;
		_class += "}";

		var _n = babel.parse(_class);
		_path.replaceWith(_n.program);
		if(_static.length > 0) _path.insertAfter(babel.parse(_static));
	},
	exit(_path)
	{
		VISITOR.CURRENT_Function--;
		VISITOR.Function_STATE.pop();
		COMPILER.VAR_STATE.pop();
	}
}
module.exports = ClassDeclaration;