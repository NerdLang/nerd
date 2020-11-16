var thread = require("Thread");

var _hello = "Hello";
var a = 0;

function count()
{
	for(var i = 0; i < 1000; i++)
	{
		a+=i;
	}
}

function test()
{
	thread.lock(); // example lock
	console.log(_hello, "!");
}

thread.run(test);

for(var i = 0; i < 4; i++) // run 4 threads of count()
{
	thread.run(count);
}

thread.waitForAll(); // wait for all threads to finish

console.log(a);