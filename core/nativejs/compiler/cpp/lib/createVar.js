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

module.exports = createVar;
function createVar(value, index)
{
  if(typeof value == "object")
  {
    switch (value.type)
    {
      case "Literal":
          switch(typeof value.value)
          {
            case "boolean":
              type = "BOOL";
              _length = 1;
              var __value = "false";
              if(value.value == true) __value = "true";
              _value = "__create_Boolean(" + __value + ")"; // TRUE || FALSE
              break;

            case "number":
              return "__create_Number(" + value.raw + ")"
              break;

            case "string":
              return "__create_String((char *)" + value.raw + ")";
              break;

            case "undefined":
            default:
              return "__create_Undefined()";
              break;
          }

        break;
      default:
        return "__create_Undefined()";
        break;

    }
  }

  if(!index) index = "";
  var type = "";
  var _value = "";
  var _str = "";
  var _length = 0;
  switch(typeof value)
  {
    case "boolean":
      type = "BOOL";
      _length = 1;
      var __value = "false";
      if(value == true) __value = "true";
      _value = "__create_Boolean(" + __value + ")"; // TRUE || FALSE
      break;

    case "string":
      type = "STRING";
      var STR = value.substring(1, value.length - 1);
      var backLength = STR.split("\\").length - 1;
      _length = STR.length - backLength;
      _value = "__create_String((char *)\"" + value.split("\n").join("\\n") + "\")";
      break;

    case "number":
      _length = 1;
      _value = "__create_Number(" + value + ")";
      break;

    case "undefined":
      type = "_UNDEFINED";
      _value = "__create_Undefined()"; // .Integer = value
      break;

    default:
      ERROR = true;
      console.log("VariableDeclaration " + value + " not defined yet");
      break;
  }

  _str = _value;
  return _str;
}
