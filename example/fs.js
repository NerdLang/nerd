var fs = require("fs-std");

var file = "fs.txt";

var write = fs.writeFileSync(file, "Some content");
if(write)
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