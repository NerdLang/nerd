var _name = "NectarJS";
var _delay = 3000;

function delayed()
{
	console.log("I'm delayed by", _delay, "ms");
}

function immediateFN()
{
	console.log("Hello", _name, "!");
}

function normal()
{
	console.log("----------");
}

setTimeout(delayed, _delay);
setImmediate(immediateFN);
normal();