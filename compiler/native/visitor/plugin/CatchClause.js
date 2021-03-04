function CatchClause(_path) 
{
	const paramPath = _path.get("param");
	if(!paramPath.node.name || paramPath.node.name != "e")
	{
		console.log("[Error] Catch clause needs an 'e' Exception argument.");
		process.exit(1);
	}

	paramPath.replaceWithSourceString("__Nectar_EXCEPTION_PARAMETER");
}
module.exports = CatchClause;