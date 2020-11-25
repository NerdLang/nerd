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

var FunctionDeclaration=
{
	enter(_path)
	{
		_path.node.VAR = {var:[], const:[]};
		if(_path.node.id)
		{
			COMPILER.VAR_STATE.push([]);
			VISITOR.pushDeclVar(_path.node.id.name, 0);
			
			VISITOR.CURRENT_Function++;
			VISITOR.Function_STATE.push(_path.node.id.name);
			
			if(!COMPILER.INFO.SCOPE[_path.node.id.name]) COMPILER.INFO.SCOPE[_path.node.id.name] = {init:[], use:[], call:[], param: [], fast: true};
			VISITOR.addFunctionVarInit(_path.node.id.name);
			if(_path.node.params.length > 0)
			{
				for(var i = 0; i < _path.node.params.length; i++)
				{
					VISITOR.addFunctionVarInit(_path.node.params[i].name);
				}
			}
		}
		
	},
	exit(_path)
	{
		var _hoistingVar = "";
		for(var i = 0; i < _path.node.VAR.var.length; i++)
		{
			_hoistingVar += "var " + _path.node.VAR.var[i] + ";";
		}
		for(var i = 0; i < _path.node.VAR.const.length; i++)
		{
			_hoistingVar += "__Nectar_CONST " + _path.node.VAR.const[i] + ";";
		}
		if(_hoistingVar.length > 0) _path.node.body.body.splice(0, 0, babel.parse(_hoistingVar));
		if(_path.node.id)
		{
			VISITOR.CURRENT_Function--;
			VISITOR.Function_STATE.pop();
			COMPILER.VAR_STATE.pop();
		}
	},
}
module.exports = FunctionDeclaration;