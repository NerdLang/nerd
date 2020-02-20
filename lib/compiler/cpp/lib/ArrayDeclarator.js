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
 
 module.exports = ArrayDeclarator;
function ArrayDeclarator(obj, sub)
{

  if(sub == undefined) sub = false;
  if(!obj.init && obj.elements) obj.init = {elements: obj.elements};
  if(!obj.init || !obj.init.elements)
  {
    obj.init = { elements:[]};
  }

  var str = "";
  var type = "ARRAY";

  var count = obj.init.elements.length;
  if(count == 0) count = 10;

  var _tmpArray = createRandomVar();

  var _var = "vector<var>* " + _tmpArray + "=new vector<var>();";

  if(obj.init.elements.length > 0)
  {
    for(var c = 0; c < obj.init.elements.length; c++)
    {
      if(obj.init.elements[c].type == "ArrayExpression" && !obj.init.elements[c].id)
      {
        var _expName = createRandomVar();
        obj.init.elements[c].id = { name: _expName};
        str += ArrayDeclarator(obj.init.elements[c]);
        obj.init.elements[c].type = "Identifier";
      }
    }

  }


  // ADD VALUE
  if(obj.init.elements.length > 0)
  {
    for(var c = 0; c < obj.init.elements.length; c++)
    {
      _var += _tmpArray + "->push_back(" + forgeExpression(obj.init.elements[c], true, true, false) + ");";
    }
  }
  str += _var;
  if(!sub) str += "var " + obj.id.name + " = ";
  str += "var(" + _tmpArray + ")" + ";";
  return str;
}
