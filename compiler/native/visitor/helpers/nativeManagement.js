var warning = false;
function sayExperimental()
{
	if(!warning)
	{
		warning = true;
		console.log("[*] NectarJS Native API is experimental and may change, please use it with caution");
	}
}

function initInt(_name, _value)
{
	sayExperimental();
	if(!_value)
	{
		_value = "0";
	}
	return `__Nectar_Init_Int(${_name}, ${_value})`;
}

function initDouble(_name, _value)
{
	sayExperimental();
	if(!_value)
	{
		_value = "0";
	}
	return `__Nectar_Init_Double(${_name}, ${_value})`;
}

function initString(_name, _value)
{
	sayExperimental();
	if(!_value)
	{
		_value = "\"\"";
	}
	return `__Nectar_Init_String(${_name}, ${_value})`;
}

function validateName(_name, fn)
{
	if(_name.type != "StringLiteral")
	{
		console.log(`[!] Error: ${fn} name parameter has to be a String Literal`);
		process.exit(1);
	}
}

var NativeMgmt = 
{
	initInt: initInt,
	initDouble: initDouble,
	initString: initString,
	validateName: validateName,
}

module.exports = NativeMgmt;