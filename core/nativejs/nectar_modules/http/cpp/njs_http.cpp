#include <functional>

var __NJS_HTTP_LISTEN(char* _host, int _port, var _cb)
{

  http::Server server([&](auto &req, auto &res)
  {
    //res.setStatus(200);
    //res.setHeader("Content-Type", "text/plain");
    //res.setHeader("Connection", "keep-alive");

    //res << req.method << " " << req.url << endl;
    res << endl;
  });

  server.listen(_host, _port);

}
