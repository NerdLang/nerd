
#include <cstring>

#define RESPONSE \
    "HTTP/1.1 200 OK\r\n" \
    "Content-Type: text/plain\r\n" \
    "Content-Length: 12\r\n" \
    "\r\n" \
    "Hello World\n" \

namespace http {

  using namespace std;

  const string CRLF = "\r\n";


  Server::Server (Listener fn) :
    listener(fn) {

    }


  Client::Client (string ustr, Listener fn) :
    listener(fn) {
      auto u = uri::ParseHttpUrl(ustr);
      opts.host = u.host;

      connect();
    }


  Client::Client (Client::Options o, Listener fn) :
    listener(fn) {
      opts = o;
      listener = fn;
      connect();
    }


  void free_context (uv_handle_t* handle) {
    auto* context = reinterpret_cast<Context*>(handle->data);
    context->writes.clear();
    free(context);
  }


  //
  // Events
  //
  template <class Type>
  void attachEvents(Type* instance, http_parser_settings& settings) {

    // http parser callback types
    static function<int(http_parser* parser)> on_message_complete;

    static auto callback = instance->listener;
    // called once a connection has been made and the message is complete.
    on_message_complete = [&](http_parser* parser) -> int {
      return instance->complete(parser, callback);
      return 0;
    };

    // called after the url has been parsed.
    settings.on_url =
      [](http_parser* parser, const char* at, size_t len) -> int {
        Context* context = static_cast<Context*>(parser->data);
        if (at && context) { context->url = string(at, len); }
        return 0;
      };

    // called when there are either fields or values in the request.
    settings.on_header_field =
      [](http_parser* parser, const char* at, size_t length) -> int {
        return 0;
      };

    // called when header value is given
    settings.on_header_value =
      [](http_parser* parser, const char* at, size_t length) -> int {
        return 0;
      };

    // called once all fields and values have been parsed.
    settings.on_headers_complete =
      [](http_parser* parser) -> int {
        Context* context = static_cast<Context*>(parser->data);
        context->method = string(http_method_str((enum http_method) parser->method));
        return 0;
      };

    // called when there is a body for the request.
    settings.on_body =
      [](http_parser* parser, const char* at, size_t len) -> int {
        Context* context = static_cast<Context*>(parser->data);
        if (at && context && (int) len > -1) {
          context->body << string(at, len);
        }
        return 0;
      };

    // called after all other events.
    settings.on_message_complete =
      [](http_parser* parser) -> int {
        return on_message_complete(parser);
      };
  }

  template void attachEvents<Client>(Client* instance, http_parser_settings& settings);
  template void attachEvents<Server>(Server* instance, http_parser_settings& settings);


  //
  // Response.
  //
  void Response::setHeader (const string key, const string val) {
    headersSet = true;
    if (writtenOrEnded) throw runtime_error("Can not set headers after write");

    if (key == "Content-Length") {
      contentLengthSet = true;
    }
    headers.insert({ key, val });
  }


  void Response::setStatus (int code) {

    statusSet = true;
    if (writtenOrEnded) throw runtime_error("Can not set status after write");
    statusCode = code;
  }


  void Response::setStatus (int code, string ad) {

    statusSet = true;
    if (writtenOrEnded) throw runtime_error("Can not set status after write");
    statusCode = code;
    statusAdjective = ad;
  }


  void Response::writeOrEnd(char* str, bool end)
{

    // response buffer
    uv_buf_t resbuf = {
      .base = (char*) RESPONSE,
      .len = strlen(RESPONSE)
    };

    Context* context = static_cast<Context*>(this->parser.data);

    auto id = write_count++;

    uv_write_t write_req;
    context->writes.insert({ id, write_req });

    if (end) {

      ended = true;

      uv_write(&context->writes.at(id), (uv_stream_t*) &context->handle, &resbuf, 1,
        [](uv_write_t* req, int status) {
          if (!uv_is_closing((uv_handle_t*) req->handle)) {
            uv_close((uv_handle_t*) req->handle, free_context);
          }
        }
      );
    }
    else {
      uv_write(&context->writes.at(id), (uv_stream_t*) &context->handle, &resbuf, 1, NULL);
    }
  }


  void Response::write(char* s) {
    this->writeOrEnd(s, false);
  }


  void Response::end(char* s) {
    this->writeOrEnd(s, true);
  }


  void Response::end() {
    this->writeOrEnd((char*)"", true);
  }

}
