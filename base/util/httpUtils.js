var http = require("http");
var https = require("https");

module.exports.httpUtil = new httpUtil(http);
module.exports.httpsUtil = new httpUtil(https);

/**
 * httpUtil Catalog of standard http call
 * @class httpUtil
 * @name httpUtil
 *
*/
function httpUtil(httpHandler)
{

    /**
     * Send a http request.
     * @memberof httpUtil
     *
    */
    this.httpReq = function(opt, cbError, cbOk, encoding)
    {
        var data = "";
        if(opt.data) data = opt.data;

        if(!encoding) encoding = "utf8";
        opt.path = encodeURI(opt.path);
        var request = httpHandler.request(opt);
        request.on("error", function(err)
        {
            cbError(err);

        });
        request.on("response", function(response)
        {
            var data = "";
            response.on("data", function(chunk)
            {
                data += chunk.toString(encoding);
            });
            response.on("end", function()
            {
                cbOk(data);
            });
        });
        request.end(data);
        return;
    };

    /**
     * Send a http request and redirect output in a pipe, then call a callback when finished.
     * @memberof httpUtil
     *
    */
    this.httpReqPipe = function(opt, cbError,cbPipe, cbOk)
    {
        var data = "";
        if(opt.data) data = opt.data;
        opt.path = encodeURI(opt.path);
        var request = httpHandler.request(opt);
        request.on("error", function(err)
        {
            cbError(err);

        });
        request.on("response", function(response)
        {
            if(cbPipe)
                cbPipe(response);
            response.on("end", function()
            {
                if(cbOk)
                    cbOk();
            });
        });
        request.end(data);
        return;
    };
}
