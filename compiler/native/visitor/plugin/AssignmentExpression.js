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
 
function AssignmentExpression(_path)
{

 if(_path.node.left.type == "MemberExpression")
 {
	VISITOR.memberExpression(_path.node.left);

	if(_path.node.right && _path.node.right.type == "ArrayExpression")
	{
		var _a = VISITOR.arrayExpression(_path.node.right);
		COMPILER.DECL.push(_a.setter);
		_path.node.right = babel.parse(_a.getter + "();");
	}
 }
 else if(_path.node.left.type == "Identifier")
 {
	 VISITOR.checkUndefVar(_path.node.left.name);
	VISITOR.readOnlyVar(_path.node.left.name);
	if(_path.node.right.type == "ArrayExpression")
	{
		var _a = VISITOR.arrayExpression(_path.node.right);
		_path.node.right = babel.parse(_a.getter + "();");
	}
	else if(_path.node.right.type == "ObjectExpression")
	{
		var _objAssign = "";
		for(var i = 0; i < _path.node.right.properties.length; i++)
		{
			_objAssign += VISITOR.objectExpression(_path.node.right.properties[i], _path.node.left.name);
		}
		_path.insertAfter(babel.parse(_objAssign));
		_path.node.right = babel.parse("__NJS_Create_Object()");
	}
 }
console.log(babel.generate(_path.node).code);
}
module.exports = AssignmentExpression;