
#if defined(_WIN32)  || defined(__CYGWIN__)
  #define WIN32_LEAN_AND_MEAN
  #include "windows.h"
#endif

#include "httplib.h"

using namespace httplib;


var __NJS_HTTP_LISTEN(var _host, var _port, var _cb, var _opt)
{
	Server __NJS_HTTP_SRV;
	
	if(_opt.type == __NJS_OBJECT)
	{
		var _static = __NJS_Object_Get("static", _opt);
		if(_static.type == __NJS_STRING) 
		{
			auto ret = __NJS_HTTP_SRV.set_mount_point("/", __NJS_Get_String(_static));
			if (!ret) 
			{
			  __NJS_Log_Console("Warning: path " + _static + " doesn't exist");
			}
		}
		
	}
  /*** LOAD GET ***/
  __NJS_HTTP_SRV.Get([&](const Request& request, Response& response)
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
  
  /*** LOAD POST ***/
  __NJS_HTTP_SRV.Post([&](const Request& request, Response& response, const ContentReader &content_reader)
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
    __NJS_Object_Set((char*)"method", "POST", _req);
    __NJS_Object_Set((char*)"url", request.path, _req);
    
    
    // GET DATA
    if (request.is_multipart_form_data()) 
    {
		__NJS_Object_Set((char*)"isMultipart", true, _req);
		var _multi = __NJS_Create_Object();
		
      MultipartFormDataItems files;
      content_reader(
        [&](const MultipartFormData &file) 
        {
          files.push_back(file);
          return true;
        },
        [&](const char *data, size_t data_length) 
        {
          files.back().content.append(data, data_length);
          MultipartFormData _f = files.back();
          var _file = __NJS_Create_Object();
          
          __NJS_Object_Set((char*)"data", _f.content, _file);
          __NJS_Object_Set((char*)"mime", _f.content_type, _file);
          
          __NJS_Object_Set((char*)_f.filename.c_str(), _file, _multi);
          
          return true;
        });
        __NJS_Object_Set((char*)"data", _multi, _req);
    } 
    else 
    {
		__NJS_Object_Set((char*)"isMultipart", false, _req);
      string body;
      content_reader([&](const char *data, size_t data_length) 
      {
        body.append(data, data_length);
        return true;
      });
      __NJS_Object_Set((char*)"data", body, _req);
    }
    
    
    var _res = __NJS_Create_Object();
    __NJS_Object_Set((char*)"end", __f_NJS_HTTP_RES_END, _res);
    
    __NJS_Call_Function(_cb, _req, _res);
    return var();
  });
  
  /*** LOAD PUT ***/
  __NJS_HTTP_SRV.Put([&](const Request& request, Response& response, const ContentReader &content_reader)
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
    __NJS_Object_Set((char*)"method", "PUT", _req);
    __NJS_Object_Set((char*)"url", request.path, _req);
    
    // GET DATA
    if (request.is_multipart_form_data()) 
    {
		__NJS_Object_Set((char*)"isMultipart", true, _req);
		var _multi = __NJS_Create_Object();
		
      MultipartFormDataItems files;
      content_reader(
        [&](const MultipartFormData &file) 
        {
          files.push_back(file);
          return true;
        },
        [&](const char *data, size_t data_length) 
        {
          files.back().content.append(data, data_length);
          MultipartFormData _f = files.back();
          var _file = __NJS_Create_Object();
          
          __NJS_Object_Set((char*)"data", _f.content, _file);
          __NJS_Object_Set((char*)"mime", _f.content_type, _file);
          
          __NJS_Object_Set((char*)_f.filename.c_str(), _file, _multi);
          
          return true;
        });
        __NJS_Object_Set((char*)"data", _multi, _req);
    } 
    else 
    {
		__NJS_Object_Set((char*)"isMultipart", false, _req);
      string body;
      content_reader([&](const char *data, size_t data_length) 
      {
        body.append(data, data_length);
        return true;
      });
      __NJS_Object_Set((char*)"data", body, _req);
    }
    
    var _res = __NJS_Create_Object();
    __NJS_Object_Set((char*)"end", __f_NJS_HTTP_RES_END, _res);
    
    __NJS_Call_Function(_cb, _req, _res);
    return var();
  });
  
  /*** LOAD DELETE ***/
  __NJS_HTTP_SRV.Delete([&](const Request& request, Response& response)
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
    __NJS_Object_Set((char*)"method", "DELETE", _req);
    __NJS_Object_Set((char*)"url", request.path, _req);
    
    var _res = __NJS_Create_Object();

    __NJS_Object_Set((char*)"end", __f_NJS_HTTP_RES_END, _res);
    
    __NJS_Call_Function(_cb, _req, _res);
    return var();
  });
  
  __NJS_HTTP_SRV.listen(__NJS_Get_String(_host), __NJS_Get_Int(_port));
  return var();
}

