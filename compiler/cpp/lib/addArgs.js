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

module.exports = addArgs;
function addArgs(obj)
{
	var str = [];
  for(var o in obj)
  {
		if(obj[o].type == "FunctionExpression")
		{
			var _tmp = createRandomVar();
			var _tmp_var = createRandomVar();
			obj[o].id = {name: _tmp};
			obj[o].isParam = true;
			COMPILER.INIT += FunctionDeclaration(obj[o]);
			COMPILER.INIT += "var " + _tmp_var + "=var(FUNCTION, &" + _tmp + ");";
			str.push(_tmp_var);
		}
    else str.push(forgeExpression(obj[o], true, true, false));
  }
  return str.join(',');
}
