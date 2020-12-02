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
 
var VariableDeclarator =
{
	enter(_path) 
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
			  else if(_el[i].type == "NullLiteral") _value = "null";
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
			  else if(_el[i].type == "ObjectExpression")
			  {
				var _obj = "__Nectar_TMP_OBJ_" + RND();
				var _set = "__Nectar_SET_OBJ_" + RND();
				VISITOR.pushDeclVar(_set);
				var _setter = `inline NectarCore::VAR ${_set}() { var ${_obj} = __NJS_Create_Object();`;
				
				for(var j = 0; j < _el[i].properties.length; j++)
				{
					var _tmp = VISITOR.objectExpression(_el[i].properties[j], _obj);
					_setter += _tmp + ";"
				}
				
				_setter += `return ${_obj};}`;
				COMPILER.DECL.push( _setter );
				_value = _set + "()";
			  }
			  else
			  {
				  console.log("Visitor VariableDeclarator not implemented yet for " + _el[i].type);
				  process.exit(0);
			  }
			_code += `${_name}[${i}] = ${_value};`;

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
			  else if(_el[i].type == "NullLiteral") _value = "null";
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
				  _code += `${_name}["${_key}"] = ${_value};`;
				  COMPILER.INFO.VALUE.push(_value);
			  }
		  }

		   _path.replaceWith(babel.parse(_code));
	  }
	  else if(_path.node.init.type == "FunctionExpression")
	  {
		_path.node.nectarId = "__Nectar_UNKNOWN" + RND();
		COMPILER.VAR_STATE.push([]);
		VISITOR.pushDeclVar(_path.node.nectarId, 0);
		VISITOR.CURRENT_Function++;
		VISITOR.Function_STATE.push(_path.node.nectarId);
		if(!COMPILER.INFO.SCOPE[_path.node.nectarId]) COMPILER.INFO.SCOPE[_path.node.nectarId] = {init:[], use:[], call:[], param: [], fast: true};
		
		if(VISITOR.CURRENT_Function > -1)
		{
			var _directive = "\"SCOPED_FUNCTION\";";
			_path.node.init.body.body.splice(0, 0, babel.parse(_directive));
		}
	  }

	  if(_path.node.init && _path.node.init.type == "File")
	  {
		var _decl = babel.generate(_path.node).code;
		if(_decl[_decl.length - 1] == ";") _decl = _decl.substring(0, _decl.length - 1);
		_path.replaceWithSourceString(_decl);
	  }
	},
	exit(_path)
	{
		if(_path.node.init.type == "FunctionExpression")
		{
			VISITOR.CURRENT_Function--;
			VISITOR.Function_STATE.pop();
			COMPILER.VAR_STATE.pop();
		}
	}
}
module.exports = VariableDeclarator;