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
 
 module.exports = FunctionDeclaration;
function FunctionDeclaration(obj, type)
{
	COMPILER.FUNCSTACK.push(obj.id.name);
	var LOCAL_COUNT = 0;
	var str = "";
	var p= [];
	for(var v in obj.params)
	{
		LOCAL_COUNT++;
		COMPILER.LOCAL_PARAM.push(obj.params[v].name)
		p.push("var " + obj.params[v].name);
	}
	if(NJS_ENV.name == "arduino")
	{
		GLOBAL_COMPILER.INIT += "var " + obj.id.name + "(" + p.join(',') + ");";
		COMPILER.INIT += "var " + obj.id.name + "(" + p.join(',') + ")" + "{";
		COMPILER.INIT += COMPILER.Parse(obj.body);
		COMPILER.INIT += "return var(UNDEFINED, 0);"
		COMPILER.INIT += "};";
	}
	else if(obj.id.name.indexOf("__NJS_REQUIRE_") == 0)
	{
		COMPILER.INIT += "var " + obj.id.name + "(" + p.join(',') + ");";
		COMPILER.INIT += "var " + obj.id.name + "(" + p.join(',') + ")" + "{";
		COMPILER.INIT += COMPILER.Parse(obj.body);
		COMPILER.INIT += "return var(UNDEFINED, 0);"
		COMPILER.INIT += "};";
	}
	else if(type == "object" || COMPILER.CBFN.indexOf(obj.id.name) > -1)
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
		if(true || COMPILER.FUNCSTACK.length > 1 || obj.isParam)
		{
			COMPILER.INIT += "std::function<var (" + p.join(',') + ")> " + obj.id.name + ";";
			str += "static std::function<var (" + p.join(',') + ")> " + obj.id.name + "=[&](" + p.join(',') + "){";
			str += COMPILER.Parse(obj.body);
			str += "return var(UNDEFINED, 0);"
			str += "};";
		}
		else
		{
			COMPILER.INIT += "var " + obj.id.name + "(" + p.join(',') + ");";
			COMPILER.INIT += "var " + obj.id.name + "(" + p.join(',') + ")" + "{";
			COMPILER.INIT += COMPILER.Parse(obj.body);
			COMPILER.INIT += "return var(UNDEFINED, 0);"
			COMPILER.INIT += "};";
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
		//COMPILER.INIT += "std::function<var (" + p.join(',') + ")> " + obj.id.name + ";";
		var _tmp = createRandomVar();
		str += "static std::function<var (" + p.join(',') + ")> " + _tmp + "=[&](" + p.join(',') + "){";
		str += COMPILER.Parse(obj.body);
		str += "return var(UNDEFINED, 0);"
		str += "};";
		str += "var " + obj.id.name + "=var(FUNCTION, " + "&" + _tmp + ");";
	}
	else //if(COMPILER.FUNCSTACK.length > 1)
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
		COMPILER.INIT += "std::function<var (" + p.join(',') + ")> " + obj.id.name + ";";
		str += obj.id.name + "=[&](" + p.join(',') + "){";
		str += COMPILER.Parse(obj.body);
		str += "return var(UNDEFINED, 0);"
		str += "};";

	}

	else
	{
		//COMPILER.INIT += "var " + obj.id.name + "(" + p.join(',') + ");";
		COMPILER.INIT += "std::function<var (" + p.join(',') + ")> " + obj.id.name + ";";
		//str += "var " + obj.id.name + "(" + p.join(',') + "){";
		str += obj.id.name + "=[&](" + p.join(',') + "){";
		str += COMPILER.Parse(obj.body);
		str += "return var(UNDEFINED, 0);"
		str += "};";
	}
	*/
	COMPILER.LOCAL_PARAM.splice(-LOCAL_COUNT);
	COMPILER.FUNCSTACK = COMPILER.FUNCSTACK.splice(1, -1);
	return str;
}
