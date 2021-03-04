function RegExpLiteral(_path) 
{
	_path.replaceWithSourceString(`"${_path.node.extra.raw.replace(/\\/g, "\\\\")}"`);
}
module.exports = RegExpLiteral;