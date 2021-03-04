function installModule(_name)
{
	try 
	{
		fs.mkdirSync("nectar_modules");
	}catch(e){}
	
	try 
	{
		fs.mkdirSync(".nectar");
	}catch(e){}
	
	var _zip = _name + ".zip"
	var _tmp = path.join(".nectar", _zip);
	var _dest = path.join("nectar_modules");
	
	const file = fs.createWriteStream(_tmp);
	
	var opt = 
	{
		"host": "modules.nectarjs.org",
		"path": "/" + _zip,
	}	
	
	function onError(_err)
	{
		console.log(_err);
		console.log("[!] Module " + _name + " does not exist");
	}
	
	function pipe(_res)
	{
		_res.pipe(file);
	}
	
	function onSuccess()
	{
		var unzip = new Zip(_tmp);
		unzip.extractAllTo(_dest, true);
		rmdir(_tmp, function() 
		{ 
			console.log("[+] Module " + _name + " installed"); 
		});
	}

	coreHttp.httpsUtil.httpReqPipe(opt, onError, pipe, onSuccess);
}

module.exports = installModule;