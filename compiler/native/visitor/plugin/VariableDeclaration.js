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
 
function VariableDeclaration(_path)
{
  if(_path.node.declarations)
  {
	  var _hoisting = false;
	  for(var d = 0; d < _path.node.declarations.length; d++)
	  {
		if(_path.node.declarations[d].id && _path.node.declarations[d].id.name)
		{
			VISITOR.pushDeclVar(_path.node.declarations[d].id.name);
			VISITOR.readOnlyVar(_path.node.declarations[d].id.name);
			if(COMPILER.ENV.name == "android" && COMPILER.STATE == "CODE")
			{
				if(VISITOR.CURRENT_Function < 0) _path.node.kind = "";
				COMPILER.DECL.push(" var " + _path.node.declarations[d].id.name + ";");
			}
			else if(VISITOR.CURRENT_Function < 0)
			{
				if(_path.node.kind == "const")
				{
					_path.node.kind = "__Nectar_CONST";
					_path.insertAfter( babel.parse(`__Nectar_SET_CONST(${_path.node.declarations[d].id.name});`));
				}
				else if(VISITOR.CURRENT_Function < 0) _path.node.kind = "";
				
				if(COMPILER.INFO.HOISTING.indexOf(_path.node.declarations[d].id.name) < 0)
				{
					COMPILER.INFO.HOISTING.push(_path.node.declarations[d].id.name);
				}
			}
			else if(_path.parent.type != "ForStatement" && (_path.node.kind == "var" || _path.node.kind == "const"))
			{
				const fnParent = _path.findParent(p => p && (p.type === 'Program' || p.type.includes('Function')));
				if(fnParent.node.VAR)
				{
					if(!_hoisting) _hoisting = true;
					if(_path.node.kind == "var")
						fnParent.node.VAR.var.push(_path.node.declarations[d].id.name);
					else
						fnParent.node.VAR.const.push(_path.node.declarations[d].id.name);
				}
			}
		}
		
		if(_path.node.declarations.length == 1 && _path.node.declarations[0].init && _path.node.declarations[0].init.type == "NumericLiteral")
		{
			if(_path.parent.type == "ForStatement")
			{
				
				_path.node.kind = "int";
				var _kind = "int"
				var _right = babel.generate(_path.parentPath.node.test.right).code;
				try 
				{
					var _nbr = parseInt(_right);
					if(_nbr > 2147483647 && _nbr < -2147483646)
					{
						_path.node.kind = "var";
						_kind = "var"
					}
				}
				catch(e)
				{
					_path.node.kind = "var";
					_kind = "var"
				}
				if(_path.parentPath.node.test && _path.parentPath.node.test.type == "BinaryExpression")
				{
					var _new_int = "__Nectar_LOOP_INT" + RND();
					try 
					{
						_path.parentPath.insertBefore(babel.parse(_new_int + " = " + babel.generate(_path.parentPath.node.test.right).code).program.body);
						_path.parentPath.node.test = babel.parse( "(" +  babel.generate(_path.parentPath.node.test.left).code + _path.parentPath.node.test.operator + _new_int + ")").program.body[0].expression;
						COMPILER.DECL.push(_kind + " " + _new_int + ";");
						COMPILER.GLOBAL.push(_new_int);
					}catch(e){}
				}
				
			}
		}
		if(!(_path.node.declarations[d].init)) _path.node.declarations[d].init = babel.parse("__NJS_InitVar()");
	  }
	  if(_hoisting) _path.node.kind = "";
  }
}
module.exports = VariableDeclaration;