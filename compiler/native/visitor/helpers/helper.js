/*
 * This file is part of NectarJS
 * Copyright (c) 2017-2020 Adrien THIERRY
 * http://nectarjs.com - https://www.linkedin.com/in/adrien-thierry-fr/
 *
 * sources : https://github.com/nectarjs/nectarjs/
 *
 * this program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * You can be released from the requirements of the license by purchasing
 * a commercial license. Buying such a license is mandatory as soon as you
 * develop commercial activities involving the NectarJS software without
 * disclosing the source code of your own applications. Visit http://seraum.com/
 * and feel free to contact us.
 *
 */
 
VISITOR.pushDeclVar = function(_name, _index)
{
	if(_index == undefined)
	{
		var currentScope = VISITOR.CURRENT_FUNCTION + 1;
		COMPILER.VAR_STATE[currentScope].push(_name);
	}
	else COMPILER.VAR_STATE[_index].push(_name);
}

VISITOR.checkUndefVar = function(_name)
{
	var currentScope = VISITOR.CURRENT_FUNCTION + 1;
	var _exists = false;
	
	for(var i = currentScope; i > -1; i--)
	{
		if(COMPILER.VAR_STATE[i].indexOf(_name) > -1)
		{
			_exists = true;
			break;
		}
	}

	if(!_exists)
	{
		COMPILER.VAR_STATE[currentScope].push(_name);
		COMPILER.DECL.push( "var " + _name + ";");
		
	}
}

VISITOR.addFunctionVarInit = function(_name)
{
	if(VISITOR.CURRENT_FUNCTION > -1)
	{
		if(COMPILER.INFO.SCOPE[VISITOR.FUNCTION_STATE[VISITOR.CURRENT_FUNCTION]].init.indexOf(_name) < 0)
		COMPILER.INFO.SCOPE[VISITOR.FUNCTION_STATE[VISITOR.CURRENT_FUNCTION]].init.push(_name);
	}
}

VISITOR.addFunctionVarUse = function(_value)
{
	if(VISITOR.CURRENT_FUNCTION > -1)
	{
		if(COMPILER.INFO.SCOPE[VISITOR.FUNCTION_STATE[VISITOR.CURRENT_FUNCTION]].use.indexOf(_value) < 0 && VISITOR.IGNORE.indexOf(_value) < 0)
		COMPILER.INFO.SCOPE[VISITOR.FUNCTION_STATE[VISITOR.CURRENT_FUNCTION]].use.push(_value);
	}
}

VISITOR.addFunctionVarCall = function(_id, _type)
{
	if(COMPILER.INFO.SCOPE[_id] && COMPILER.INFO.SCOPE[_id].call.indexOf(_type) < 0)
	COMPILER.INFO.SCOPE[_id].call.push(_type);
}

VISITOR.addFunctionVarParam = function(_id, _number)
{
	if(COMPILER.INFO.SCOPE[_id] && COMPILER.INFO.SCOPE[_id].param.indexOf(_number) < 0)
	COMPILER.INFO.SCOPE[_id].param.push(_number);
}

VISITOR.readOnlyVar = function(_name)
{
	VISITOR.addFunctionVarInit(_name);
	if(COMPILER.READ_ONLY.indexOf(_name) > -1)
	{
		console.log("[!] Fatal error: " + _name + " is a read only variable");
		process.exit(1);
	}
}

VISITOR.objectExpression = require("./objectExpression");

VISITOR.memberExpression = require("./memberExpression");

VISITOR.arrayExpression = require("./arrayExpression");

VISITOR.callExpression = require("./callExpression");