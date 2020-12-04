var http = require("http");
var port = 8080;

function listening()
{
	console.log("Listening on port:", port);
}

function cbGet(req, res)
{
	res.end("Hello World!");
}

http.createServer().get("/", "Hello Nectar!").get("/cb", cbGet).listen(port, listening).run();
