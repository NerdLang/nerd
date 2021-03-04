function initModule(_author, _name)
{
	try 
	{
		fs.mkdirSync("nectar_modules");
	} catch(e){}
	
	var _dest = path.join("nectar_modules", _name);
	try 
	{
		fs.mkdirSync(_dest);
	}
	catch(e)
	{
		console.log("[!] An error occured while trying to create the module folder: " + _name);
		console.log(e);
		process.exit(-1);
	}
	
	var _pkg = fs.readFileSync(path.join(NECTAR_PATH, "base", "squel", "package.json")).toString();
	
	_pkg = _pkg.replace(/{{AUTHOR}}/g, _author).replace(/{{MODULE_NAME}}/g, _name)

	fs.writeFileSync(path.join(_dest, "package.json"), _pkg);
	fs.appendFileSync(path.join(_dest, "index.js"), "// Write your module code here");
	console.log("[+] Module " + _name + " correctly initialized in " + _dest);
}

module.exports = initModule;