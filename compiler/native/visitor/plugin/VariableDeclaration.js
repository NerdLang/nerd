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
 
function VariableDeclaration(_path)
{
  if(_path.node.declarations)
  {
	  for(var d = 0; d < _path.node.declarations.length; d++)
	  {
		if(_path.node.declarations[d].id && _path.node.declarations[d].id.name)
		{
			VISITOR.pushDeclVar(_path.node.declarations[d].id.name);
			VISITOR.readOnlyVar(_path.node.declarations[d].id.name);
			if(COMPILER.ENV.name == "android" && COMPILER.STATE == "CODE")
			{
				//_path.node.kind = "";
				COMPILER.DECL.push(" var " + _path.node.declarations[d].id.name + ";");
			}
			else if(VISITOR.CURRENT_Function < 0)
			{
				//_path.node.kind = "";
				if(COMPILER.INFO.HOISTING.indexOf(_path.node.declarations[d].id.name) < 0)
				{
					COMPILER.INFO.HOISTING.push(_path.node.declarations[d].id.name);
				}
			}	
		}
		if(!(_path.node.declarations[d].init)) _path.node.declarations[d].init = babel.parse("__NJS_VAR()");
	  }
  }
}
module.exports = VariableDeclaration;