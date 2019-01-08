//!_njs_env ["node"]
//!_c_include "cpp/http.h"
//!_c_include "cpp/http.cc"
//!_c_include "cpp/http-server.cc"
//!_c_include "cpp/http-client.cc"
//!_c_include "cpp/njs_http.cpp"

var http =
{

  server:
  {
    createServer: function(_host, _port)
    {
      var _return =
      {
        listen : function(_cb)
        {
          __NJS_HTTP_LISTEN(__NJS_Get_String(_host), __NJS_Get_Int(_port), _cb);
        }
      }
      return _return;
    }
  }
};

module.exports = http;
