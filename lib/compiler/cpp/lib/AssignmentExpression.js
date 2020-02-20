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
 
 module.exports = AssignmentExpression;
function AssignmentExpression(obj, comma)
{
  var rightType = false;
  //var leftType = false;
  var vtype  = { _var : "INT", _val: "Integer", def:0};

  if(obj.right.type == "Literal")
  {
    switch(typeof obj.right.value)
    {
      case "number":
        if(obj.right.value.toString().indexOf(".") > -1)
        {
          console.error("Not implemented yet in NectarScript");
          process.exit(1);
        }
        else if(obj.right.value > 10000000 || obj.right.value < -10000000)
        {
          console.error("Not implemented yet in NectarScript");
          process.exit(1);
        }
        else
        {
            rightType = "__create_Number(0)";
        }
        break;
      case "string":
        vtype  = { _var : "STRING", _val: "String", def: "\"\""};
        rightType = {type:"STRING", value : "String"};

        break;
      default:
        rightType = {type:"INT", value : "Integer"};
        break;
    }
  }
  else if(obj.right.type == "CallExpression")
  {

  }
  else
  {
    //console.error("Non Literal AssignmentExpression not implemented yet in NectarScript");
    //process.exit(1);
  }
  str = "";
  if(comma == undefined) comma = true;
  var left = forgeExpression(obj.left, null, null, false, "set", vtype);

  if(obj.right.type == "ArrayExpression" && obj.left.type == "MemberExpression" && obj.left.object && obj.left.object.type == "ThisExpression")
  {
    console.error("Array expression -> Not implemented yet in NectarScript");
    process.exit(1);
  }

  var right = "";

  if(obj.right.type)
  {
    obj.right.isParam = true;
    if(!obj.right.id) obj.right.id = {name:obj.left.name || obj.left.object.name };
    right = forgeExpression(obj.right, false);
  }

  if(obj.left.type == "MemberExpression")
  {
    if(obj.left.object && obj.left.object.type == "Identifier" && obj.left.object.name == "global")
    {
      GLOBAL_VAR.push(obj);
      left = obj.left.property.name
      right = forgeExpression(obj.right);
    }
    else if(obj.right.type == "FunctionExpression")
    {
      var _tmp = createRandomVar();
      obj.right.id = {name: _tmp};
      str = FunctionDeclaration(obj.right, "object");
      str += "__NJS_Object_Set((char*)\"" + obj.left.property.name + "\"," + _tmp + "," + obj.left.object.name + ");";
      return str;
    }
    else
    {
      if(obj.left.object.type == "ThisExpression" && COMPILER.FUNCSTACK[FUNCINDEX]._this != true)
      {
        var _tmpArray = createRandomVar();
        str += "vector<shared_ptr<pair<var, var>>>* " + _tmpArray + "=new vector<shared_ptr<pair<var, var>>>();";
        str += "var __NJS_THIS =  var(OBJECT," + _tmpArray + ");";
        COMPILER.FUNCSTACK[FUNCINDEX]._this = true;
        var _to_var = undefined;
        if(obj.left.property.name != null && obj.left.property.name != undefined) _to_var = obj.left.property.name;
        else if(obj.left.property.value != null && obj.left.property.value != undefined) _to_var = obj.left.property.value;
        else if(obj.left.property.key != null && obj.left.property.key != undefined) _to_var = obj.left.property.key;

        //console.log(forgeExpression(obj.left));

        str += "__NJS_Object_Set(" + createVar(_to_var) + "," + forgeExpression(obj.right, false, null, false) + "," + "__NJS_THIS" + ");";
      }
      else if(NJS_ENV.name != "arduino")
      {
        var _to_var = undefined;
        if(obj.left.property.name != null && obj.left.property.name != undefined) _to_var = obj.left.property.name;
        else if(obj.left.property.value != null && obj.left.property.value != undefined) _to_var = obj.left.property.value;
        else if(obj.left.property.key != null && obj.left.property.key != undefined) _to_var = obj.left.property.key;


        //console.log(obj.left);
        str += "__NJS_Object_Set(" + createVar(_to_var) + "," + forgeExpression(obj.right, false, null, false) + "," + obj.left.object.name + ");";
        //console.log(str)
      }



      return str;
    }
    //str += forgeExpression(obj.left);
  }

  str += left + obj.operator + right;

  if(comma) str += ";";

  return str;
}
