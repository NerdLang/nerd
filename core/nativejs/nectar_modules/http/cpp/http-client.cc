
namespace http {


  int Client::complete(http_parser* parser, Listener cb) {
    Context* context = reinterpret_cast<Context*>(parser->data);

    Response res;
    res.body = context->body.str();
    res.parser = *parser;

    cb(res);
    return 0;
  }


  void Client::on_connect(uv_connect_t* req, int status) {

    Context* context = reinterpret_cast<Context*>(req->handle->data);
    static http_parser_settings settings;
    attachEvents(this, settings);

    if (status == -1) {
      // @TODO
      // Error Callback
      uv_close((uv_handle_t*)req->handle, free_context);
      return;
    }

    static function<void(
      uv_stream_t* tcp, ssize_t nread, const uv_buf_t* buf)> read;

    read = [&](uv_stream_t* tcp, ssize_t nread, const uv_buf_t* buf) {

      Context* context = static_cast<Context*>(tcp->data);

      if (nread >= 0) {
        auto parsed = (ssize_t) http_parser_execute(
          &context->parser, &settings, buf->base, nread);

        if (parsed < nread) {
          uv_close((uv_handle_t*) &context->handle, free_context);
        }
        if (parsed != nread) {
          // @TODO
          // Error Callback
        }
      }
      else {
        if (nread != UV_EOF) {
          return; // maybe do something interesting here...
        }
        uv_close((uv_handle_t*) &context->handle, free_context);
      }
      free(buf->base);
    };

    uv_buf_t reqbuf;
    std::string reqstr =
      opts.method + " " + opts.url + " HTTP/1.1" + CRLF +
      //
      // @TODO
      // Add user's headers here
      //
      "Connection: keep-alive" + CRLF + CRLF;

    reqbuf.base = (char*) reqstr.c_str();
    reqbuf.len = reqstr.size();

    uv_read_start(
      req->handle,
      [](uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf) {
        *buf = uv_buf_init((char*) malloc(suggested_size), suggested_size);
      },
      [](uv_stream_t* tcp, ssize_t nread, const uv_buf_t* buf) {
        read(tcp, nread, buf);
      });

    uv_write(
      &context->write_req,
      req->handle,
      &reqbuf,
      1,
      NULL);
  }

  void Client::connect() {

    struct addrinfo ai;
    ai.ai_family = PF_INET;
    ai.ai_socktype = SOCK_STREAM;
    ai.ai_protocol = IPPROTO_TCP;
    ai.ai_flags = 0;

    UV_LOOP = uv_default_loop();

    static function<void(
      uv_getaddrinfo_t* req, int status, struct addrinfo* res)> on_resolved;

    static function<void(uv_connect_t* req, int status)> on_before_connect;

    on_before_connect = [&](uv_connect_t* req, int status) {

      // @TODO
      // Populate address and time info for logging / stats etc.

      on_connect(req, status);
    };

    on_resolved = [&](uv_getaddrinfo_t* req, int status, struct addrinfo* res) {

      char addr[17] = { '\0' };

      uv_ip4_name((struct sockaddr_in*) res->ai_addr, addr, 16);
      uv_freeaddrinfo(res);

      struct sockaddr_in dest;
      uv_ip4_addr(addr, 8000, &dest);

      Context* context = new Context();

      context->handle.data = context;
      http_parser_init(&context->parser, HTTP_RESPONSE);
      context->parser.data = context;

      uv_tcp_init(UV_LOOP, &context->handle);
      //uv_tcp_keepalive(&context->handle, 1, 60);

      uv_tcp_connect(
        &context->connect_req,
        &context->handle,
        (const struct sockaddr*) &dest,
        [](uv_connect_t* req, int status) {
          on_before_connect(req, status);
        });
    };

    auto cb = [](uv_getaddrinfo_t* req, int status, struct addrinfo* res) {
      on_resolved(req, status, res);
    };

    uv_getaddrinfo(UV_LOOP, &addr_req, cb, "localhost", "8000", &ai);
    uv_run(UV_LOOP, UV_RUN_DEFAULT);
  }

} // namespace http
