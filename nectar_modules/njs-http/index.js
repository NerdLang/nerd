'!_ffi_include lib/njs-http.h';

var njs_server = {};

njs_server.get = function(_uri, _cb)
{
  __NJS_HTTP_GET(_uri, _cb);
};

njs_server.listen = function(_host, _port)
{
  __NJS_HTTP_LISTEN(_host, _port);
};

module.exports = njs_server;
