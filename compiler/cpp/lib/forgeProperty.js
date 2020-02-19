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

module.exports = forgeProperty;
function forgeProperty(obj, type, action, vtype)
{

  if(vtype == undefined) vtype  = { _val : "INT", "_val": "Integer", def:0};
  if(type == undefined || type == null) type = "Array";
  if(action == undefined || type == null) action = "get";

  if(obj.object && ( obj.object.name || obj.object.object) && !obj.computed ) type = "Object";
  if(obj.object && obj.object.type && obj.object.type == "ThisExpression")
  {
    if(NJS_ENV.name == "arduino")
  	{
      console.error("[!] Prototypes are disabled for Arduino env");
      process.exit();
    }
    type = "This";
  }

  var _str = "";
  var rec = "";

  if(obj.object)
  {
    if(obj.object.property)
    {

      //SCOPE.push(obj.object.property.name);
      if(!obj.object.property.from)
      {

      }
      rec = forgeProperty(obj.object, type);
    }

    else if(obj.object.type == "CallExpression")
    {
      rec = callFunction({ expression: obj.object }, false);
    }

  }
  if(!obj.object) obj.object = {};
  if(!obj.object.name) obj.object.name = rec;

  if(obj.property)
  {
    switch(obj.property.type)
    {
      case "Identifier":
        if(type == "Array")
        {
          if(obj.property.value)
          {
            _str += "__NJS_Object_Get((char*)\"" + obj.property.name + "\"," + obj.object.value +")";
          }
          else
          {
            _str += "__NJS_Object_Get(" + obj.property.name + "," + obj.object.name +")";
          }

        }
        else if(type == "This")
        {
          if(action == "set")
          {
            //var __value = "(val){ ." + vtype._val + " = " + vtype.def +"}";
            //var __var = "(var){ .type = " + vtype._var + ", .value = " + __value + "}";

            if(obj.from)
            {
                _str += "__NJS_Object_Set((char*)\"" + obj.id.name + "\"," + "__NJS_THIS, " + obj.from + ");";
            }
            else
            {
              _str += "__NJS_THIS";
            }
          }
          else if(action == "get")
          {
            _str += "__NJS_Object_Get((char*)\"" + obj.property.name + "\"," + obj.object.name +")";
          }
        }
        else
        {
          _str += "__NJS_Object_Get((char*)\"" + obj.property.name + "\"," + obj.object.name +")";
        }
        break;

      case "Literal":
        _str += "__NJS_Object_Get(" + createVar(obj.property.value) + "," + obj.object.name +")";
        break;

      default:
        njsError("Expression : " + obj.property.type + " - Not Implemented Yet in ForgeProperty");
        ERROR = true;
        break;
    }
  }
  else
  {
    njsError("Expression : " + "undefined" + " - Not Implemented Yet in ForgeProperty");
    ERROR = true;
  }

  return _str;
}
