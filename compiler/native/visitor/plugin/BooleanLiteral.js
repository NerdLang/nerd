const TRUE = "__Nectar_Boolean_TRUE";
const FALSE = "__Nectar_Boolean_FALSE";
function BooleanLiteral(_path)
{
	_path.replaceWithSourceString(_path.node.value ? TRUE : FALSE);
}
module.exports = BooleanLiteral;