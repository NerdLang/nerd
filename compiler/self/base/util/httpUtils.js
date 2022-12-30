/*
	Copyright (c) 2021 NerdLang - Adrien THIERRY and contributors

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.

*/

var http = require("http");
var https = require("https");

module.exports.httpUtil = new httpUtil(http);
module.exports.httpsUtil = new httpUtil(https);

/**
 * httpUtil Catalog of standard http call
 * @class httpUtil
 * @name httpUtil
 * @memberof WF
 *
*/
function httpUtil(httpHandler)
{

    /**
     * Send a http request.
     * @memberof httpUtil
     * @example wf.httpUtil.httpReq(opt, cbError, cbOk, "utf-8");
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
     * @example wf.httpUtil.httpReqPipe(opt, cbError, cbPipe, cbOk);
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
