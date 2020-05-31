
#if defined(_WIN32)  || defined(__CYGWIN__)
  #define WIN32_LEAN_AND_MEAN
  #include "windows.h"
#endif

#include "httplib.h"

using namespace httplib;


var __NJS_HTTP_LISTEN(var _host, var _port, var _cb)
{
	Server __NJS_HTTP_SRV;
	
  __NJS_HTTP_SRV.Get(".*", [&](const Request& request, Response& response)
  {
	function<var (vector<var>)>* __NJS_HTTP_RES_END = new function<var (vector<var>)>([&](vector<var> __args)
	{
		var _str = "";
		if(__args.size() == 1) _str = __args[0];
		response.set_content(__NJS_Get_String(_str), "text/plain");
		return var();
	});
	var __f_NJS_HTTP_RES_END = __NJS_Create_Function(__NJS_HTTP_RES_END);

    var _req = __NJS_Create_Object();
    __NJS_Object_Set((char*)"method", "GET", _req);
    __NJS_Object_Set((char*)"url", request.path, _req);
    
    var _res = __NJS_Create_Object();

    __NJS_Object_Set((char*)"end", __f_NJS_HTTP_RES_END, _res);
    
    __NJS_Call_Function(_cb, _req, _res);
    return var();
  });
  
  __NJS_HTTP_SRV.listen(__NJS_Get_String(_host), __NJS_Get_Int(_port));
  return var();
}

