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