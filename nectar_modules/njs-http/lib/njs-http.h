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
 
#include "httplib.h"

using namespace httplib;

Server __NJS_HTTP_SRV;

var __NJS_HTTP_GET(var _uri, var _cb)
{
  static var __callback = _cb;

  __NJS_HTTP_SRV.Get(__NJS_Get_String(_uri), [&](const Request& request, Response& response)
  {
    std::function<var (var _str)> __NJS_HTTP_RES_END = [&](var _str)
    {
      response.set_content(__NJS_Get_String(_str), "text/plain");
      return var(UNDEFINED, 0);
    };

    var __f_NJS_HTTP_RES_END = __NJS_Create_Function(&__NJS_HTTP_RES_END);

    var _req = __NJS_Create_Object();
    var _res = __NJS_Create_Object();

    __NJS_Object_Set((char*)"end", __f_NJS_HTTP_RES_END, _res);
    __NJS_Call_Function(__callback, _req, _res); // __NJS_Call_Function(var _function, var _arg1, var _arg2 ...)

  });
  return __NJS_Create_Undefined();
}

var __NJS_HTTP_LISTEN(var _host, var _port)
{
  __NJS_HTTP_SRV.listen(__NJS_Get_String(_host), __NJS_Get_Int(_port));
  return var(UNDEFINED, 0);
}
