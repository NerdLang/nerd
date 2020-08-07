var fs = require("fs");
var path = require("path");
var exec = require("child_process").execSync;
var MAIN_PATH = path.resolve(path.join(__dirname, ".."));

var NODE = process.argv[0];

var TEST_PATH = path.join(MAIN_PATH, "tests", "NJS");

var error = false;
var errList = [];

var _list = fs.readdirSync(TEST_PATH);

for(var i = 0; i < _list.length; i++)
{
	try 
	{
		process.chdir(MAIN_PATH);
		console.log("[*] Testing: " + _list[i]);

		exec("\"" + NODE + "\" nectar.js --compiler clang++ --run \"" + path.join(TEST_PATH, _list[i]) + "\"");
		
		console.log("[+] Test passed: " + _list[i]);
	}
	catch(e)
	{
		error = true;
		errList.push(_list[i]);
		console.log("[!] Test error: " + _list[i]);
	}
}

if(error)
{
	console.log("[!] tests exited with errors");
	console.log("[ERRORS]");
	console.dir(errList);
	process.exit(1);
}
else 
{
	console.log("[*] tests exited without errors");
	process.exit(0);
}
