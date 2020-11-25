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