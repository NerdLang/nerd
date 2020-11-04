var elements = [undefined, null, NaN, 1, "str", [], [0,1,2], {"key":"value"}, {}];

for(var i = 0; i < elements.length; i++)
{
	for(var j = 0; j < elements.length; j++)
	{
		console.log(elements[i], "+", elements[j], "=", elements[i] + elements[j], "- type:", typeof (elements[i] + elements[j]));
		console.log(elements[i], "-", elements[j], "=", elements[i] - elements[j], "- type:", typeof (elements[i] - elements[j]));
		console.log(elements[i], "*", elements[j], "=", elements[i] * elements[j], "- type:", typeof (elements[i] * elements[j]));
		console.log(elements[i], "/", elements[j], "=", elements[i] / elements[j], "- type:", typeof (elements[i] / elements[j]));
	}
}