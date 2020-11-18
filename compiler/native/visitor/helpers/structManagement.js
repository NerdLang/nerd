var warning = false;
function sayExperimental()
{
	if(!warning)
	{
		warning = true;
		console.log("[*] NectarJS Struct API is experimental and may change, please use it with caution");
	}
}
var StructList = {};
var Key = 0;

function structShouldntExist(_name)
{
	if(StructList[_name])
	{
		console.log(`[!] Error: a Struct with name '${_name}' already exist`);
		process.exit(1);
	}
}

function structShouldExist(_name)
{
	if(!StructList[_name])
	{
		console.log(`[!] Error: a Struct with name '${_name}' does not exist`);
		process.exit(1);
	}
}

function memberExists(_name, _member)
{
	structShouldExist(_name)
	if(StructList[_name].members.indexOf(_member) < 0)
	{
		console.log(`[!] Error: member '${_member}' doesn't exist in Struct '${_name}'`);
		process.exit(1);
	}
}

function createStruct(_name, _members)
{
	sayExperimental();
	structShouldntExist(_name);
	
	StructList[_name] =
	{
		members: _members,
		key: Key,
	}
	Key++;
	var _m = "";
	for(var i = 0; i < _members.length; i++)
	{
		_m += `var ${_members[i]};`
	}
	COMPILER.DECL.push(`struct __NJS_STRUCT_${StructList[_name].key} { ${_m} };`);
	return `true`;
}

function initStruct(_name)
{
	sayExperimental();
	structShouldExist(_name);
	return `__NJS_Create_Struct(__NJS_STRUCT_${StructList[_name].key})`;
}

function accessStruct(_exp, _name, _member)
{
	memberExists(_name, _member)
	return `__NJS_Access_Struct(${_exp}, __NJS_STRUCT_${StructList[_name].key})`
}

function verifyArguments(_arguments)
{
	sayExperimental();
	var _args = [];
	for(var i = 0; i < _arguments.length; i++)
	{
		if(_arguments[i].type != "StringLiteral")
		{
			console.log(`[!] Error: parameters of Nectar.createStruct() have to be String Literals`);
			process.exit(1);
		}
		_args.push(_arguments[i].value);
	}
	return _args;
}

var StructMgmt = 
{
	createStruct: createStruct,
	initStruct: initStruct,
	accessStruct: accessStruct,
	verifyArguments: verifyArguments,
}

module.exports = StructMgmt;