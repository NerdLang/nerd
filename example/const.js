const number = 42;
console.log(number);

// number = 3; /* parse error */

const test = function()
{
	console.log("Const test:", number);
}

test();