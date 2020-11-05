var thread = require("Thread");

var _hello = "Hello";

function test()
{
	thread.lock(); // example lock
	console.log(_hello, "!");
}

thread.run(test);