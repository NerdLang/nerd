var elements = [undefined, null, NaN, 1, "str", [], [0,1,2], {"key":"value"}, {}];

// Binary operators
for(var i = 0; i < elements.length; i++)
{
	for(var j = 0; j < elements.length; j++)
	{
		console.log(elements[i], "+", elements[j], "=", elements[i] + elements[j], "- type:", typeof (elements[i] + elements[j]));
		console.log(elements[i], "-", elements[j], "=", elements[i] - elements[j], "- type:", typeof (elements[i] - elements[j]));
		console.log(elements[i], "*", elements[j], "=", elements[i] * elements[j], "- type:", typeof (elements[i] * elements[j]));
		console.log(elements[i], "/", elements[j], "=", elements[i] / elements[j], "- type:", typeof (elements[i] / elements[j]));
		console.log(elements[i], ">", elements[j], "=", elements[i] > elements[j], "- type:", typeof (elements[i] > elements[j]));
		console.log(elements[i], "<", elements[j], "=", elements[i] < elements[j], "- type:", typeof (elements[i] < elements[j]));
		console.log(elements[i], "%", elements[j], "=", elements[i] % elements[j], "- type:", typeof (elements[i] % elements[j]));
		console.log(elements[i], "^", elements[j], "=", elements[i] ^ elements[j], "- type:", typeof (elements[i] ^ elements[j]));
		console.log(elements[i], "&", elements[j], "=", elements[i] & elements[j], "- type:", typeof (elements[i] & elements[j]));
		
		console.log(elements[i], ">>", elements[j], "=", elements[i] >> elements[j], "- type:", typeof (elements[i] >> elements[j]));
		console.log(elements[i], "<<", elements[j], "=", elements[i] << elements[j], "- type:", typeof (elements[i] << elements[j]));
		console.log(elements[i], "==", elements[j], "=", elements[i] == elements[j], "- type:", typeof (elements[i] == elements[j]));
		console.log(elements[i], "!=", elements[j], "=", elements[i] != elements[j], "- type:", typeof (elements[i] != elements[j]));
		console.log(elements[i], "===", elements[j], "=", elements[i] === elements[j], "- type:", typeof (elements[i] === elements[j]));
		console.log(elements[i], "!==", elements[j], "=", elements[i] !== elements[j], "- type:", typeof (elements[i] !== elements[j]));
	}
}

// Increment operators
for(var i = 0; i < elements.length; i++)
{
	var _left = Object.clone(elements[i]);
	console.log(_left, "+=", elements[j], "=", _left += elements[j], "- type:", typeof _left);
	_left = Object.clone(elements[i]);
	console.log(_left, "*=", elements[j], "=", _left *= elements[j], "- type:", typeof _left);
	_left = Object.clone(elements[i]);
	console.log(_left, "-=", elements[j], "=", _left -= elements[j], "- type:", typeof _left);
	_left = Object.clone(elements[i]);
	console.log(_left, "/=", elements[j], "=", _left /= elements[j], "- type:", typeof _left);
	_left = Object.clone(elements[i]);
	console.log(_left, "%=", elements[j], "=", _left %= elements[j], "- type:", typeof _left);
	_left = Object.clone(elements[i]);
	console.log(_left, "^=", elements[j], "=", _left ^= elements[j], "- type:", typeof _left);
	_left = Object.clone(elements[i]);
	console.log(_left, "&=", elements[j], "=", _left &= elements[j], "- type:", typeof _left);
}

// Unary operators
for(var i = 0; i < elements.length; i++)
{
	var _left = Object.clone(elements[i]);
	console.log(_left, "++", "=", _left++, "- type:", typeof (_left));
	_left = Object.clone(elements[i]);
	console.log(_left, "--", "=", _left--, "- type:", typeof (_left));
}
