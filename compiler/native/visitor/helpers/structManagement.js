/*
 * This file is part of NectarJS
 * Copyright (c) 2017 - 2020 Adrien THIERRY
 * http://nectarjs.com - https://seraum.com/
 *
 * sources : https://github.com/nectarjs/nectarjs
 * 
 * NectarJS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * NectarJS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with NectarJS.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
var supportedType = ["int", "double", "string"];
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
		return false;
	}
	else return true;
}

function createStruct(_name, _members)
{
	sayExperimental();
	structShouldntExist(_name);
	
	var _mOnly = [];
	for(var i = 0; i < _members.length; i++)
	{
		_mOnly.push( _members[i].split(":")[0]);
	}
	
	StructList[_name] =
	{
		members: _mOnly,
		key: Key,
	}
	Key++;
	var _m = "";
	for(var i = 0; i < _members.length; i++)
	{
		if(_members[i].indexOf(":") > 0)
		{
			_members[i] = _members[i].split(":");
			var _v = _members[i].splice(0,1);
			_members[i] = _members[i].join(":");
			if(supportedType.indexOf(_members[i]) < 0)
			{
				console.log(`[!] Error: unsupported struct type '${_members[i]}', supported are: ${supportedType}`);
				process.exit(1);
			}
			if(_members[i] == "string") _members[i] = "std::string";
			_m += `${_members[i]} ${_v};`
		}
		else _m += `var ${_members[i]};`
	}
	COMPILER.DECL.push(`struct __Nectar_STRUCT_${StructList[_name].key} { ${_m} };`);
	return `true`;
}

function initStruct(_name)
{
	sayExperimental();
	structShouldExist(_name);
	return `__Nectar_Create_Struct(__Nectar_STRUCT_${StructList[_name].key})`;
}

function accessStruct(_exp, _name, _member)
{
	if(memberExists(_name, _member))
	{
		return {code: `__Nectar_Access_Struct(${_exp}, __Nectar_STRUCT_${StructList[_name].key})`, struct:true};
	}
	else 
	{
		return {code: _exp, struct:false};
	}
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