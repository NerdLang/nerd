'!_ffi_include lib/njs-http.h';

var njs_server = {};

njs_server.listen = function(_host, _port, _cb, _opt)
{
  __NJS_HTTP_LISTEN(_host, _port, _cb, _opt);
};


module.exports = njs_server;
