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

module.exports = VariableDeclaration;
function VariableDeclaration(obj)
{
  var str = "";

  for(var i = 0; i < obj.declarations.length; i++)
  {
    // if is NULL
    if(obj.declarations[i].init === null || obj.declarations[i].init === undefined)
    {
	    str += "var " + obj.declarations[i].id.name + ";";
    }
    // else we create the var
    else
    {
      VARIABLE.push(obj.declarations[i].id.name);
    	switch(obj.declarations[i].init.type)
	    {

	      case "Literal":
          if(NJS_ENV.name == "arduino" && obj.kind && obj.kind == "const")
          {
            GLOBAL_GEN += "const var " + obj.declarations[i].id.name + " = " + createVar(obj.declarations[i].init.value) + ";";
          }
          else if(NJS_ENV.name == "arduino")
          {
            if(FUNCSTACK.length > 0)
            {
              str += "var ";
    	        str += obj.declarations[i].id.name + " = " + createVar(obj.declarations[i].init.value) + ";";
            }
            else
            {
              DECLARATION += "var ";
    	        DECLARATION += obj.declarations[i].id.name + " = " + createVar(obj.declarations[i].init.value) + ";";
            }
          }
          else
          {
            str += "var ";
  	        str += obj.declarations[i].id.name + " = " + createVar(obj.declarations[i].init.value) + ";";
          }

	        break;

	      case "Identifier":
          if(NJS_ENV.name == "arduino" && obj.kind && obj.kind == "const")
          {
            GLOBAL_GEN += "const var " + obj.declarations[i].id.name + " = " + obj.declarations[i].init.name + ";";
          }
          else if(NJS_ENV.name == "arduino")
          {
            if(FUNCSTACK.length > 0)
            {
              str += "var " + obj.declarations[i].id.name + " = " + obj.declarations[i].init.name + ";";
            }
            else
            {
              DECLARATION += "var " + obj.declarations[i].id.name + " = " + obj.declarations[i].init.name + ";";
            }
          }
          else
          {
	           str += "var " + obj.declarations[i].id.name + " = " + obj.declarations[i].init.name + ";";
          }
	        break;

          // faire un return de : {type: TYPE, str:"code"}
        case "BinaryExpression":
          if(obj.kind && obj.kind == "const")
          {
            GLOBAL_GEN += "var " + obj.declarations[i].id.name + " = " + BinaryExpression(obj.declarations[i].init) + ";";
          }
          else if(NJS_ENV.name == "arduino")
          {
            if(FUNCSTACK.length > 0)
            {
              str += "var " + obj.declarations[i].id.name + " = " + BinaryExpression(obj.declarations[i].init) + ";";
            }
            else
            {
              DECLARATION += "var " + obj.declarations[i].id.name + " = " + BinaryExpression(obj.declarations[i].init) + ";";
            }
          }
          else
          {
            str += "var " + obj.declarations[i].id.name + " = " + BinaryExpression(obj.declarations[i].init) + ";";
          }
          break;

        case "UnaryExpression":
          if(obj.kind && obj.kind == "const")
          {
            GLOBAL_GEN += "var " + obj.declarations[i].id.name + " = " + UnaryExpression(obj.declarations[i].init) + ";";
          }
          else if(NJS_ENV.name == "arduino")
          {
            if(FUNCSTACK.length > 0)
            {
              str += "var " + obj.declarations[i].id.name + " = " + UnaryExpression(obj.declarations[i].init) + ";";
            }
            else
            {
              DECLARATION += "var " + obj.declarations[i].id.name + " = " + UnaryExpression(obj.declarations[i].init) + ";";
            }
          }
          else
          {
            str += "var " + obj.declarations[i].id.name + " = " + UnaryExpression(obj.declarations[i].init) + ";";
          }
          break;

        case "FunctionExpression":
          obj.declarations[i].init.id = obj.declarations[i].id;
          str += FunctionDeclaration(obj.declarations[i].init, "var");
          break;

          case "CallExpression":
            if(obj.kind && obj.kind == "const")
            {
              GLOBAL_GEN += "const var " + obj.declarations[i].id.name + " = " + callFunction({expression: obj.declarations[i].init});
            }
            if(NJS_ENV.name == "arduino")
            {
              if(FUNCSTACK.length > 0)
              {
                str += "var " + obj.declarations[i].id.name + " = " + callFunction({expression: obj.declarations[i].init});
              }
              else
              {
                DECLARATION += "var " + obj.declarations[i].id.name + " = " + callFunction({expression: obj.declarations[i].init});
              }
            }
            else
            {
              str += "var " + obj.declarations[i].id.name + " = " + callFunction({expression: obj.declarations[i].init});
            }
            break;

        case "ArrayExpression":

          //if(SMARTOBJECT[obj.declarations[i].id.name + ":" + ref] && SMARTOBJECT[obj.declarations[i].id.name + ":" + ref].type == "ARRAY")
          if(obj.kind && obj.kind == "const")
          {
            GLOBAL_GEN += ArrayDeclarator(obj.declarations[i]);
          }
          if(NJS_ENV.name == "arduino")
          {
            if(FUNCSTACK.length > 0)
            {
              str += ArrayDeclarator(obj.declarations[i]);
            }
            else
            {
              DECLARATION += ArrayDeclarator(obj.declarations[i]);
            }
          }
          else
          {
            str += ArrayDeclarator(obj.declarations[i]);
          }
          //else
            //str += ObjectExpression(obj.declarations[i]);
          break;

        case "ObjectExpression":
          if(obj.kind && obj.kind == "const")
          {
            GLOBAL_GEN += ObjectExpression(obj.declarations[i]);
          }
          else
          {
            str += ObjectExpression(obj.declarations[i]);
          }
          break;

          // BOOLEAN
        case "false":
          str += "var(BOOLEAN, false);";
          break;
        case "true":
          str += "var(BOOLEAN, true);";
          break;

        case "NewExpression":
          var toConstruct = {expression: obj.declarations[i].init};
          toConstruct.expression.callee.name += "__NJS_THIS";
          str += "var " + obj.declarations[i].id.name + " = " + callFunction(toConstruct);
          break;

        case "ConditionalExpression":
          str += "var " + obj.declarations[i].id.name + " = ";
          str += BinaryExpression(obj.declarations[i].init.test) + " ? ";
          str += forgeExpression(obj.declarations[i].init.consequent) + " : ";
          str += forgeExpression(obj.declarations[i].init.alternate);
          str += ";";
          break;

        case "AssignmentExpression":
          str += forgeExpression(obj.declarations[i].init.left);
          str += " = ";
          str += forgeExpression(obj.declarations[i].init.right);
          break;

        case "MemberExpression":
          str += "var " + forgeExpression(obj.declarations[i].id, null, null, false);
          str += "=";
          str += forgeExpression(obj.declarations[i].init) + ";";
          break;

        case "UpdateExpression":
          str += "var " + forgeExpression(obj.declarations[i].id, null, null, false);
          str += "=";
          str += forgeExpression(obj.declarations[i].init) + ";";
            break;


	      default:
	        ERROR = true;
          console.dir(obj.declarations[i], {depth:null})
          console.log("Expression : " + obj.declarations[i].init.type + " - Not Implemented Yet for VariableDeclaration in NectarScript");
	        break;
	    }
    }
  }
  return str;
}
