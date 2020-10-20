var _name = "NectarJS";
var _delay = 500;
var _delayRepeat = 1000;

function repeat()
{
	console.log("Repeated");
}

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

setInterval(repeat, _delayRepeat);
setTimeout(delayed, _delay);
setImmediate(immediateFN);
normal();
