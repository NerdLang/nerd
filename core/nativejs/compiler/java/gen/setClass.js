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

module.exports = setClass;
function Clone(obj)
{
  var result = {};
  if(obj instanceof Array) result = [];
  for (var i in obj)
  {
    if (obj[i] && typeof obj[i] == "object")
    {
      result[i] = Clone(obj[i]);
    }
    else
    {
      result[i] = obj[i];
    }
  }
  return result;
};

function modReturn(obj)
{
  var ret = false;
  for(var o in obj)
  {
    if(obj[o] && obj[o].type && obj[o].type == "ReturnStatement")
    {
      ret = true;
      obj[o].argument = { type: 'Identifier', name: '__NJS_THIS',loc: { source: null, start: null, end: null } };
    }
    else if(typeof obj[o] == "object")
    {
      modReturn(obj[o]);
    }
  }
  return ret;
}

function setClass(obj, sArray)
{
  var _length = obj.length;
  for(var o = 0; o < _length; o++)
  {

    if(obj[o] && obj[o].type && obj[o].type == "FunctionDeclaration" && obj[o].body && obj[o].body && obj[o].body.body.length)
    {
      if(sArray.indexOf(obj[o].id.name) > -1)
      {
        var copied = Clone(obj[o]);
        copied.id.name = copied.id.name + "__NJS_THIS";
        var ret = modReturn(copied.body);
        if(!ret)
        {
          var retStat = { type: 'ReturnStatement',argument: { type: 'Identifier', name: '__NJS_THIS',loc: { source: null, start: null, end: null } },loc: { source: null,start: null,end: null } };
          copied.body.body.push(retStat);
        }
        obj.splice(0, 0, copied);
        o++;
        _length++;
      }
      setClass(obj[o].body.body, sArray)
    }
    if(obj[o] && obj[o].type && obj[o].type == "VariableDeclarator" && obj[o].init && obj[o].init.type == "FunctionExpression" && obj[o].init.body && obj[o].init.body.body)
    {
      if(sArray.indexOf(obj[o].id.name) > -1)
      {
        var copied = Clone(obj[o]);
        copied.id.name = copied.id.name + "__NJS_THIS";
        var ret = modReturn(copied.init.body);
        if(!ret)
        {
          var retStat = { type: 'ReturnStatement',argument: { type: 'Identifier', name: '__NJS_THIS',loc: { source: null, start: null, end: null } },loc: { source: null,start: null,end: null } };
          copied.init.body.body.push(retStat);
        }
        obj.splice(0, 0, copied);
        o++;
        _length++;
      }
      setClass(obj[o].init.body.body, sArray)
    }
    else if(typeof obj[o] == "object")
    {
      if(obj[o].declarations) setClass(obj[o].declarations, sArray);
    }
    else
    {
    }
  }
}
