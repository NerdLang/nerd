/*
 * This file is part of NectarJS
 * Copyright (c) 2017 - 2020 Adrien THIERRY
 * http://nectarjs.com - https://seraum.com/
 *
 * sources : https://github.com/nectarjs/nectarjs
 * 
 * NectarJS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * NectarJS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with NectarJS.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

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
