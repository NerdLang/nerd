//!_c_include "./lib/njs-http.h"

var njs_server = {};

njs_server.get = function(_uri, _cb)
{
  __NJS_HTTP_GET(_uri, _cb);
};

njs_server.listen = function(_host, _port)
{
  __NJS_HTTP_LISTEN(_host, _port);
};

njs_server.setBaseDir = function(_dir)
{
  __NJS_HTTP_SET_BASE_DIR(_dir);
};

module.exports = njs_server;
