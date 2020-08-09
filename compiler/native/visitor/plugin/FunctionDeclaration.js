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