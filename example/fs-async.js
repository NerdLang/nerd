var fs = require("fs");

fs.readFile("nectar.js", function(err, data)
{
	if(!err) console.log(data.toString())
	else console.log(err);
})