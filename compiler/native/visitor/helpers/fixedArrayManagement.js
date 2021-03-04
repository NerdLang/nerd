var warning = false;
function sayExperimental()
{
	if(!warning)
	{
		warning = true;
		console.log("[*] NectarJS FixedArray API is experimental and may change, please use it with caution");
	}
}

function initFixedArray(_length)
{
	sayExperimental();
	return `__Nectar_Create_FixedArray(${_length})`;
}

function validateLength(_length)
{
	if(_length.type == "StringLiteral")
	{
		console.log(`[!] Error: ${fn} name parameter can't be a String Literal`);
		process.exit(1);
	}
	if(_length.value <= 0)
	{
		console.log(`[!] Error: Fixed Array length must be > 0`);
		process.exit(1);
	}
}

var fixedArrayMgmt = 
{
	initFixedArray: initFixedArray,
	validateLength: validateLength,
}

module.exports = fixedArrayMgmt;