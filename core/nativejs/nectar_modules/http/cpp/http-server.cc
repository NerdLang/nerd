
namespace http {


  int Server::complete (http_parser* parser, Listener cb) {
    Context* context = reinterpret_cast<Context*>(parser->data);
    Request req;
    Response res;

    req.url = context->url;
    req.method = context->method;
    res.parser = *parser;
    cb(req, res);
    return 0;
  }


  int Server::listen (const char* ip, int port) {

    //
    // parser settings needs to be static.
    //
    //
    static http_parser_settings settings;
    attachEvents(this, settings);

    int status = 0;

    #ifdef _WIN32
      SYSTEM_INFO sysinfo;
      GetSystemInfo( &sysinfo );
      int cores = sysinfo.dwNumberOfProcessors;
    #else
      int cores = sysconf(_SC_NPROCESSORS_ONLN);
    #endif

    std::stringstream cores_string;
    cores_string << cores;

    #ifdef _WIN32
      SetEnvironmentVariable("UV_THREADPOOL_SIZE", cores_string);
    #else
      setenv("UV_THREADPOOL_SIZE", cores_string.str().c_str(), 1);
    #endif

    struct sockaddr_in address;

    static function<void(uv_stream_t* socket, int status)> on_connect;
    static function<void(uv_stream_t* tcp, ssize_t nread, const uv_buf_t* buf)> read;

    UV_LOOP = uv_default_loop();
    uv_tcp_init(UV_LOOP, &socket_);

    //
    // @TODO - Not sure exactly how to use this,
    // after the initial timeout, it just
    // seems to kill the server.
    //
    //uv_tcp_keepalive(&socket_,1,60);

    status = uv_ip4_addr(ip, port, &address);
    ASSERT_STATUS(status, "Resolve Address");

    status = uv_tcp_bind(&socket_, (const struct sockaddr*) &address, 0);
    ASSERT_STATUS(status, "Bind");

    // called once a connection is made.
    on_connect = [&](uv_stream_t* handle, int status) {
      Context* context = new Context();

      // init tcp handle
      uv_tcp_init(UV_LOOP, &context->handle);

      // init http parser
      http_parser_init(&context->parser, HTTP_REQUEST);

      // client reference for parser routines
      context->parser.data = context;

      // client reference for handle data on requests
      context->handle.data = context;

      // accept connection passing in refernce to the client handle
      uv_accept(handle, (uv_stream_t*) &context->handle);

      // called for every read
      read = [&](uv_stream_t* tcp, ssize_t nread, const uv_buf_t* buf) {
        ssize_t parsed;
        Context* context = static_cast<Context*>(tcp->data);

        if (nread >= 0) {
          parsed = (ssize_t) http_parser_execute(&context->parser,
                                                 &settings,
                                                 buf->base,
                                                 nread);

          // close handle
          if (parsed < nread) {
            uv_close((uv_handle_t*) &context->handle, free_context);
          }
        } else {
          if (nread != UV_EOF) {
            // @TODO - debug error
          }

          // close handle
          uv_close((uv_handle_t*) &context->handle, free_context);
        }

        // free request buffer data
        free(buf->base);
      };

      // allocate memory and attempt to read.
      uv_read_start((uv_stream_t*) &context->handle,
          // allocator
          [](uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf) {
            *buf = uv_buf_init((char*) malloc(suggested_size), suggested_size);
          },

          // reader
          [](uv_stream_t* tcp, ssize_t nread, const uv_buf_t* buf) {
            read(tcp, nread, buf);
          });
    };

    status = uv_listen((uv_stream_t*) &socket_, MAX_WRITE_HANDLES,
        // listener
        [](uv_stream_t* socket, int status) {
          on_connect(socket, status);
        });

    ASSERT_STATUS(status, "Listen");

    // init loop
    uv_run(UV_LOOP, UV_RUN_DEFAULT);
    return 0;
  }

} // namespace http
