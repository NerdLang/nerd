
#if defined(_WIN32)  || defined(__CYGWIN__)
    #define WIN32_LEAN_AND_MEAN
    #include "windows.h"
#endif

#include "httplib.h"

using namespace httplib;

Server __NJS_HTTP_SRV;

function __NJS_HTTP_GET(_uri, _cb)
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
    __NJS_Call_Function(__callback, _req, _res);

  });
  return __NJS_Create_Undefined();
}

function __NJS_HTTP_LISTEN(_host, _port)
{
  __NJS_HTTP_SRV.listen(__NJS_Get_String(_host), __NJS_Get_Int(_port));
  return var(UNDEFINED, 0);
}
