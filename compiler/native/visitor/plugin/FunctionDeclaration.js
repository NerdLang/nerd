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
		if(_path.node.id)
		{
			COMPILER.VAR_STATE.push([]);
			VISITOR.pushDeclVar(_path.node.id.name, 0);
			
			VISITOR.CURRENT_FUNCTION++;
			VISITOR.FUNCTION_STATE.push(_path.node.id.name);
			
			if(!COMPILER.INFO.SCOPE[_path.node.id.name]) COMPILER.INFO.SCOPE[_path.node.id.name] = {init:[], use:[], call:[], param: [], fast: true};
			VISITOR.addFunctionVarInit(_path.node.id.name);
			if(_path.node.params.length > 0)
			{
				for(var i = 0; i < _path.node.params.length; i++)
				{
					VISITOR.addFunctionVarInit(_path.node.params[i].name);
				}
			}
			if(VISITOR.CURRENT_FUNCTION > 0)
			{
			
			}
		}
		
	},
	exit(_path)
	{
		if(_path.node.id)
		{
			VISITOR.CURRENT_FUNCTION--;
			VISITOR.FUNCTION_STATE.pop();
			COMPILER.VAR_STATE.pop();
		}
	},
}
module.exports = FunctionDeclaration;