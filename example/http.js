var http = require("njs-http");
var host = "localhost";
var port = 1337;

function cb (req, res)
{
	console.log("Log: " + req.method + req.url);
	res.end("Hello NectarJS !");
};

var options =
{
		static: "./",
};

console.log("Listening on " + host + ":" + port);
http.listen(host, port, cb, options);
