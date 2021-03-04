global.VISITOR = {};
 
VISITOR.NO_MODIFY_CALL = ["require", "Object", "Array"];
VISITOR.Nectar_START = ["__NJS_GEN", "__FFI"];

VISITOR.IGNORE = ["__Nectar_Call_Function", "__Nectar_Object_Set", "__Nectar_Object_Get", "__Nectar_VAR"];
VISITOR.Function_STATE = [];

VISITOR.CURRENT_Function = -1;

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
	RegExpLiteral: require("./plugin/RegExpLiteral.js"),
	ReturnStatement: require("./plugin/ReturnStatement.js"),
	StringLiteral: require("./plugin/StringLiteral.js"),
	ThisExpression: require("./plugin/ThisExpression.js"),
	ThrowStatement: require("./plugin/ThrowStatement.js"),
	UnaryExpression: require("./plugin/UnaryExpression.js"),
	VariableDeclaration: require("./plugin/VariableDeclaration.js"),
	VariableDeclarator: require("./plugin/VariableDeclarator.js"),
	NumericLiteral: require("./plugin/NumericLiteral.js"),
	ArrayExpression: require("./plugin/ArrayExpression.js"),
	ConditionalExpression: require("./plugin/ConditionalExpression.js"),
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
