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
				_path.node.kind = "";
				COMPILER.DECL.push(" var " + _path.node.declarations[d].id.name + ";");
			}
			else if(VISITOR.CURRENT_FUNCTION < 0)
			{
				_path.node.kind = "";
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