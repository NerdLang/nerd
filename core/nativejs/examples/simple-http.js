var srv = require("njs-http");

srv.get("/", function(req, res)
{
  res.end("Hello Nectar !");
});

var host = "localhost";
var port = 8080;

console.log("[+] Listening on " + host + ":" + port);
srv.listen(host, port);
