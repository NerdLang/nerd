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
 var structManagement = require("./structManagement.js");
function callExpression(_path, _main)
{
	
	if(!_path.callee || !_path.callee.name)
	{
		VISITOR.disableFastFunction(_path.callee.name);
	}
	
	if(_path.callee && _path.callee.name && (VISITOR.NJS_START.indexOf(_path.callee.name.substring(0, 5)) > -1 || VISITOR.NO_MODIFY_CALL.indexOf(_path.callee.name) > -1))
	{
	  return "";
	}

	var _obj = _path.callee;

	// If using Nectar.functionStruct
	if(_obj.type == "MemberExpression" && _obj.object.type == "Identifier"
		&& _obj.object.name == "Nectar")
	{
		if(_obj.property.type == "Identifier")
		{
			if(_obj.property.name == "createStruct")
			{
				var _args = structManagement.verifyArguments(_path.arguments);
				if(_args.length < 2)
				{
					console.log("[!] Error: createStruct requires at least 2 parameters: name, member");
					process.exit(1);
				}
				else
				{
					var _name = _args.splice(0,1)[0];
					var _res = structManagement.createStruct(_name, _args);
					_main.replaceWithSourceString(_res);
				}
			}
			else if(_obj.property.name == "initStruct")
			{
				var _args = structManagement.verifyArguments(_path.arguments);
				
				if(_args.length != 1)
				{
					console.log("[!] Error: initStruct requires 1 parameter: name");
					process.exit(1);
				}
				else
				{
					var _name = _args.splice(0,1)[0];
					var _res = structManagement.initStruct(_name);
					_main.replaceWithSourceString(_res);
				}
			}
		}
	}
	
	// If using obj.NStruct()
	if(_obj.type == "MemberExpression" && _obj.property.type == "Identifier"
		&& _obj.property.name == "NStruct")
	{
		var _args = structManagement.verifyArguments(_path.arguments);
		if(_args.length != 1)
		{
			console.log("[!] Error: NStruct requires only 1 parameters: name");
			process.exit(1);
		}
		var exp = babel.generate(_path).code.split(".");
		var index = -1;
		for(var i = 0; i < exp.length; i++)
		{
			if(exp[i].indexOf("NStruct(") == 0)
			{
				index = i;
				break;
			}
		}
		var name = exp.splice(index, 1);
		exp = exp.join(".");
		if(_main.container.property)
		{
			var _member = _main.container.property.name;
			_main.replaceWithSourceString(structManagement.accessStruct(exp, _args[0], _member));
		}
		else 
		{
			console.log("[!] Error: NStruct() call needs to be followed by a member accessor");
			process.exit(1);
		}
		return;
	}
	
	if(_obj.name) VISITOR.checkUndefVar(_obj.name);


	var _fName = _path.callee.name;

	if(!COMPILER.INFO.CALL[_fName]) COMPILER.INFO.CALL[_fName] = [];
	VISITOR.addFunctionVarParam(_fName, _path.arguments.length);
	
	if(_path.arguments.length > 0)
	{
		if(COMPILER.INFO.CALL[_fName].indexOf(_path.arguments.length) < 0)
		{
			COMPILER.INFO.CALL[_fName].push(_path.arguments.length);
		}
		
		for(var i = 0; i < _path.arguments.length; i++)
		{
			VISITOR.addFunctionVarCall(_fName, _path.arguments[i].type);

			if(_path.arguments[i].type == "ArrayExpression")
			{
				var _arr = VISITOR.arrayExpression(_path.arguments[i]);

				COMPILER.DECL.push(_arr.setter);
			}
			else if(_path.arguments[i].type == "FunctionExpression")
			{
				var _tmp = "__NJS_TMP_LAMBDA" + RND();
				var _gen = `${_tmp} = ${babel.generate(_path.arguments[i]).code}`;
				_main.insertBefore(babel.parse(_gen).program.body[0].expression);
				_path.arguments[i].type = "Identifier";
				_path.arguments[i].name = _tmp;
			}
		}
	}
	else
	{
		if(COMPILER.INFO.CALL[_fName].indexOf(0) < 0)
		{
			COMPILER.INFO.CALL[_fName].push(0);
		}
	}
}
module.exports = callExpression;