var fs = require("fs");

fs.readFile("nectar.js");
/*
var file = "fs.txt";

var write = fs.writeFileSync(file, "Some content");
var append = fs.appendFileSync(file, "\nContent added");
if(write && append)
{
	console.log("[+] File '" + file + "' written.");
	var content = fs.readFileSync(file);
	
	console.log("[+] File content: ");
	console.log(content);
	

	console.log("[*] Removing file");
	fs.unlinkSync(file);
}
else 
{
	console.log("[!] couldn't write '" + file + "'");
}
*/