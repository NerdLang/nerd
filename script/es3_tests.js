var fs = require("fs");
var path = require("path");
var exec = require("child_process").execSync;
var MAIN_PATH = path.resolve(path.join(__dirname, ".."));

var NODE = process.argv[0];

var MAIN_TEST_PATH = path.join(MAIN_PATH, "tests", "ES3");

var walkSync = function(dir, filelist) 
{
    files = fs.readdirSync(dir);
	filelist = filelist || [];
    files.forEach(function(file) 
	{
		if (fs.statSync(dir + file).isDirectory()) 
		{
		  filelist = walkSync(dir + file + '/', filelist);
		}
		else {
		  filelist.push(dir + file);
		}
	});
	return filelist;
};

var _LIST = walkSync(MAIN_TEST_PATH + "/");

var error = false;
var errList = [];

process.chdir(MAIN_PATH);

for(var i = 0; i < _LIST.length; i++)
{
	try 
	{

		console.log("[*] Testing: " + path.basename(_LIST[i]));

		exec("\"" + NODE + "\" nectar.js --env test --run \"" + _LIST[i] + "\"");
		
		console.log("[+] Test passed: " + path.basename(_LIST[i]));
	}
	catch(e)
	{
		error = true;
		errList.push(path.basename(_LIST[i]));
		console.log("[!] Test error: " + path.basename(_LIST[i]));
	}
}

if(error)
{
	console.log("[!] tests exited with errors");
	console.log("[ERRORS]");
	console.dir(_list);
	process.exit(1);
}
else 
{
	console.log("[*] tests exited without errors");
	process.exit(0);
}