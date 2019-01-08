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

module.exports = ObjectExpression;
function ObjectExpression(obj, sub)
{
  if(NJS_ENV.name == "arduino")
  {
    console.log("Error : NectarJS doesn't support object for Arduino yes.");
    process.exit(1);
  }
  if(sub == undefined) sub = false;
  var str = "";
  var type = "OBJECT";

  if(!sub)
  {
    var _tmpArray = createRandomVar();
    var _var = "vector<shared_ptr<pair<var, var>>>* " + _tmpArray + "=new vector<shared_ptr<pair<var, var>>>();";
    str += _var + "var " + obj.id.name + " = var(OBJECT," + _tmpArray + ");";
  }
  else
  {
    str += "__NJS_Object_Set((char*)\"" + obj.id.name + "\"," + "var(OBJECT, new vector<shared_ptr<pair<var, var>>>()), " + obj.from + ");";
  }

  // ADD VALUE
  if(obj.init && obj.init.properties && obj.init.properties.length > 0)
  {
    var from = obj.id.name;
    for(var c = 0; c < obj.init.properties.length; c++)
    {
      if(obj.init.properties[c].value.type == "ObjectExpression")
      {
        obj.init.properties[c].value.from = obj.id.name;
        obj.init.properties[c].value.id = { name: obj.init.properties[c].key.name || obj.init.properties[c].key.value };
        str += forgeExpression(obj.init.properties[c].value);
      }
      else
      {
        if(obj.init.properties[c].value.type == "FunctionExpression")
        {
          var p= [];
        	for(var v in obj.init.properties[c].value.params)
        	{
        		p.push("var " + obj.init.properties[c].value.params[v].name);
        	}
          obj.init.properties[c].value.id = {name : createRandomVar()};
          str += FunctionDeclaration(obj.init.properties[c].value, "object");
          str += "__NJS_Object_Set((char*)\"" + obj.init.properties[c].key.name + "\"," + obj.init.properties[c].value.id.name + "," + from + ");";
        }
        else
        {
          var _name = obj.init.properties[c].key.value || obj.init.properties[c].key.name;
          str += "__NJS_Object_Set((char*)\"" + _name + "\"," + forgeExpression(obj.init.properties[c].value) + "," + from + ");";
        }

      }
    }
  }
  // RECURSIVE MANAGE PROPERTIES
  else if(obj.properties)
  {
    for(var c = 0; c < obj.properties.length; c++)
    {
      var from = "__NJS_Object_Get((char*)\"" + obj.id.name + "\"," + obj.from + ")";

      if(obj.properties[c].value.type == "ObjectExpression")
      {
        obj.properties[c].value.from = from;
        obj.properties[c].value.id = obj.properties[c].key;
        str += forgeExpression(obj.properties[c].value, true, true, false);
      }
      else
      {
        if(obj.properties[c].value.type == "FunctionExpression")
        {
          var p= [];
        	for(var v in obj.properties[c].value.params)
        	{
        		p.push("var " + obj.properties[c].value.params[v].name);
        	}
          obj.properties[c].value.id = {name : createRandomVar()};
          str += FunctionDeclaration(obj.properties[c].value, "object");
          str += "__NJS_Object_Set((char*)\"" + obj.properties[c].key.name + "\"," + obj.properties[c].value.id.name + "," + from + ");";
        }
        else
        {
          str += "__NJS_Object_Set((char*)\"" + obj.properties[c].key.name + "\", " + forgeExpression(obj.properties[c].value, true, true, false) + ", " + from + ");" ;
        }
      }
    }
  }
  return str;
}
