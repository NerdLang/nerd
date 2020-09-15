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
 
function VariableDeclarator(_path) 
{
  // Creating Arrays
  if(_path.node.id && _path.node.id.name && _path.node.init && _path.node.init.type == "ArrayExpression")
  {
	  var _newArray = "";
	  var _name = _path.node.id.name;
	  var _el = _path.node.init.elements;
	  var _code = _name + " = __NJS_Create_Array();"
	  
	  for(var i = 0; i < _el.length; i++)
	  {
		  var _value;
		  if(_el[i].name)
		  {
			_value = _el[i].name;
		  }
		  else if(_el[i].extra) _value = _el[i].extra.raw;
		  else if(_el[i].type == "ObjectProperty")
		  {
			 _o = true;
			  _code += VISITOR.objectExpression(_el[i], _name);
		  }
		  else if(_el[i].type == "ArrayExpression")
		  {
			var _a = VISITOR.arrayExpression(_el[i]);
			COMPILER.DECL.push(_a.setter + ";");
			_value = _a.getter + "()";
		  }
		  else
		  {
			  console.log("Visitor VariableDeclarator not implemented yet for " + _el[i].type);
			  process.exit(0);
		  }

		_code += "__NJS_Object_Set(" + i + ", " + _value + "," + _name + ");";

	  }
	   _path.replaceWith(babel.parse(_code));
  }
  // Creating Object
  else if(_path.node.id && _path.node.id.name && _path.node.init && _path.node.init.type == "ObjectExpression")
  {
	  var _name = _path.node.id.name;			  
	  var _el = _path.node.init.properties;
	  var _code = _path.node.id.name + " = __NJS_Create_Object();"
	  
	  for(var i = 0; i < _el.length; i++)
	  {
		  var _o = false;
		  var _key;
		  var _value;
		  
		  if(_el[i].key &&_el[i].key.name)
		  {
			_key = _el[i].key.name;
		  }
		  else _key = _el[i].key.value;
		  
		  if(_el[i].value && _el[i].value.name)
		  {
			_value = _el[i].value.name;
		  }
		  else if(_el[i].type == "ObjectProperty")
		  {
			 _o = true;
			  _code += VISITOR.objectExpression(_el[i], _name);
		  }
		  else if(_el[i].value &&_el[i].value.extra) _value = _el[i].value.extra.raw;
		  else
		  {
			  console.log("Visitor VariableDeclarator not implemented yet for " + _el[i].type);
		  }
		  
		  if(_value && !_o)
		  {
			  _code += "__NJS_Object_Set(\"" + _key + "\"," + _value + "," + _name + ");"
			  COMPILER.INFO.VALUE.push(_value);
		  }
	  }

	   _path.replaceWith(babel.parse(_code));
  }
  else if(_path.node.init.type == "FunctionExpression")
  {
	if(VISITOR.CURRENT_Function > -1)
	{
		var _directive = "'SCOPED_Function';";
		_path.node.init.body.body.splice(0, 0, babel.parse(_directive));
	}
  }
}
module.exports = VariableDeclarator;