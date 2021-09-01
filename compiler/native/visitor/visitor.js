global.VISITOR = {};
 
VISITOR.NO_MODIFY_CALL = ["require", "Object", "Array"];
VISITOR.Nectar_START = ["__NJS_GEN", "__FFI"];

VISITOR.IGNORE = ["__Nectar_Call_Function", "__Nectar_Object_Set", "__Nectar_Object_Get", "__Nectar_VAR"];
VISITOR.Function_STATE = [];

VISITOR.CURRENT_Function = -1;

require("./helpers/helper.js");

var njsVisitor = 
{
	CallExpression: require("./plugin/CallExpression.js"),
	CatchClause: require("./plugin/CatchClause.js"),
	ClassDeclaration: require("./plugin/ClassDeclaration.js"),
	ForInStatement: require("./plugin/ForInStatement.js"),
	NewExpression: require("./plugin/NewExpression.js"),
	RegExpLiteral: require("./plugin/RegExpLiteral.js"),
	UnaryExpression: require("./plugin/UnaryExpression.js"),
	VariableDeclaration: require("./plugin/VariableDeclaration.js"),
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
