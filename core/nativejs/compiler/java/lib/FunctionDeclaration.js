/*
 * This file is part of NectarJS
 * Copyright (c) 2019 Adrien THIERRY
 * http://nectarjs.com - https://nectrium.com
 *
 * sources : https://github.com/nectarjs/nectarjs
 *
 * NectarJS
 * Copyright (C) 2019 Adrien THIERRY - Necrium
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

module.exports = FunctionDeclaration;
function FunctionDeclaration(obj, type)
{
	FUNCSTACK.push(obj.id.name);
	var LOCAL_COUNT = 0;
	var str = "";
	var p= [];
	for(var v in obj.params)
	{
		LOCAL_COUNT++;
		LOCAL_PARAM.push(obj.params[v].name)
		p.push("var " + obj.params[v].name);
	}
	if(obj.id.name.indexOf("__NJS_REQUIRE_") == 0)
	{
		GLOBAL_DECLARATION += "var " + obj.id.name + "(" + p.join(',') + ");";
		DECLARATION += "var " + obj.id.name + "(" + p.join(',') + ")" + "{";
		DECLARATION += COMPILER.Parse(obj.body);
		DECLARATION += "return var(UNDEFINED, 0);"
		DECLARATION += "};";
	}
	else if(type == "object" || CBFN.indexOf(obj.id.name) > -1)
	{
		str += "static var " + obj.id.name + "=var(UNDEFINED, 0);";
		var _tmp = createRandomVar();
		str += "static std::function<var (" + p.join(',') + ")> " + _tmp + ";";
		str += _tmp + "=[&](" + p.join(',') + "){";
		str += COMPILER.Parse(obj.body);
		str += "return var(UNDEFINED, 0);"
		str += "};";
		str += obj.id.name + "=var(FUNCTION, " + "&" + _tmp + ");";
	}
	else
	{
		if(FUNCSTACK.length > 1 || obj.isParam)
		{
			DECLARATION += "std::function<var (" + p.join(',') + ")> " + obj.id.name + ";";
			str += "static std::function<var (" + p.join(',') + ")> " + obj.id.name + "=[&](" + p.join(',') + "){";
			str += COMPILER.Parse(obj.body);
			str += "return var(UNDEFINED, 0);"
			str += "};";
		}
		else
		{
			GLOBAL_DECLARATION += "var " + obj.id.name + "(" + p.join(',') + ");";
			DECLARATION += "var " + obj.id.name + "(" + p.join(',') + ")" + "{";
			DECLARATION += COMPILER.Parse(obj.body);
			DECLARATION += "return var(UNDEFINED, 0);"
			DECLARATION += "};";
		}
	}

	/*
	else if(type == "var")
	{
		var _tmp = createRandomVar();
		str += "var " + obj.id.name + "=var(UNDEFINED, 0);";
		str += "std::function<var (" + p.join(',') + ")> " + _tmp + ";";
		str += _tmp + "=[&](" + p.join(',') + "){";
		str += COMPILER.Parse(obj.body);
		str += "return var(UNDEFINED, 0);"
		str += "};";
		str += obj.id.name + "=var(FUNCTION, " + "&" + _tmp + ");";
	}
	else if(type == "object")
	{
		//DECLARATION += "std::function<var (" + p.join(',') + ")> " + obj.id.name + ";";
		var _tmp = createRandomVar();
		str += "static std::function<var (" + p.join(',') + ")> " + _tmp + "=[&](" + p.join(',') + "){";
		str += COMPILER.Parse(obj.body);
		str += "return var(UNDEFINED, 0);"
		str += "};";
		str += "var " + obj.id.name + "=var(FUNCTION, " + "&" + _tmp + ");";
	}
	else //if(FUNCSTACK.length > 1)
	{
		str += "static var " + obj.id.name + "=var(UNDEFINED, 0);";
		var _tmp = createRandomVar();
		str += "static std::function<var (" + p.join(',') + ")> " + _tmp + ";";
		str += _tmp + "=[&](" + p.join(',') + "){";
		str += COMPILER.Parse(obj.body);
		str += "return var(UNDEFINED, 0);"
		str += "};";
		str += obj.id.name + "=var(FUNCTION, " + "&" + _tmp + ");";
		//////
		DECLARATION += "std::function<var (" + p.join(',') + ")> " + obj.id.name + ";";
		str += obj.id.name + "=[&](" + p.join(',') + "){";
		str += COMPILER.Parse(obj.body);
		str += "return var(UNDEFINED, 0);"
		str += "};";

	}

	else
	{
		//DECLARATION += "var " + obj.id.name + "(" + p.join(',') + ");";
		DECLARATION += "std::function<var (" + p.join(',') + ")> " + obj.id.name + ";";
		//str += "var " + obj.id.name + "(" + p.join(',') + "){";
		str += obj.id.name + "=[&](" + p.join(',') + "){";
		str += COMPILER.Parse(obj.body);
		str += "return var(UNDEFINED, 0);"
		str += "};";
	}
	*/
	LOCAL_PARAM.splice(-LOCAL_COUNT);
	FUNCSTACK = FUNCSTACK.splice(1, -1);
	return str;
}
