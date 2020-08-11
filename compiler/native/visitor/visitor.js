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
 
global.VISITOR = {};
 
VISITOR.NO_MODIFY_CALL = ["require", "Object"];
VISITOR.NJS_START = ["__NJS", "__FFI"];

VISITOR.IGNORE = ["__NJS_Call_Function", "__NJS_Object_Set", "__NJS_Obejct_Get", "__NJS_VAR"];
VISITOR.FUNCTION_STATE = [];

VISITOR.CURRENT_FUNCTION = -1;

require("./helpers/helper.js");

var njsVisitor = 
{
	AssignmentExpression: require("./plugin/AssignmentExpression.js"),
	BinaryExpression: require("./plugin/BinaryExpression.js"),
	BooleanLiteral: require("./plugin/BooleanLiteral.js"),
	CallExpression: require("./plugin/CallExpression.js"),
	CatchClause: require("./plugin/CatchClause.js"),
	ClassDeclaration: require("./plugin/ClassDeclaration.js"),
	ExpressionStatement: require("./plugin/ExpressionStatement.js"),
	ForInStatement: require("./plugin/ForInStatement.js"),
	FunctionDeclaration: require("./plugin/FunctionDeclaration.js"),
	Identifier: require("./plugin/Identifier.js"),
	MemberExpression: require("./plugin/MemberExpression.js"),
	NewExpression: require("./plugin/NewExpression.js"),
	ReturnStatement: require("./plugin/ReturnStatement.js"),
	StringLiteral: require("./plugin/StringLiteral.js"),
	ThrowStatement: require("./plugin/ThrowStatement.js"),
	UnaryExpression: require("./plugin/UnaryExpression.js"),
	VariableDeclaration: require("./plugin/VariableDeclaration.js"),
	VariableDeclarator: require("./plugin/VariableDeclarator.js"),
};

var visitor = 
{
  plugins: [
    function NectarJS() {
      return {
        visitor: njsVisitor,
      };
    },
  ],
}
module.exports = visitor;
