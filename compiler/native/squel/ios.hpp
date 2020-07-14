/*
 * This file is part of NectarJS
 * Copyright (c) 2017-2020 Adrien THIERRY
 * http://nectarjs.com - https://www.linkedin.com/in/adrien-thierry-fr/
 *
 * sources : https://github.com/nectarjs/nectarjs/
 *
 * this program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * You can be released from the requirements of the license by purchasing
 * a commercial license. Buying such a license is mandatory as soon as you
 * develop commercial activities involving the NectarJS software without
 * disclosing the source code of your own applications. Visit http://seraum.com/
 * and feel free to contact us.
 *
 */
 
 #include <iostream>
 #include <string>
 #include <cstring>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <sstream>
 #include <vector>
 #include <memory>

 using namespace std;

 #include "njs.h"
 #include "httplib.h"
 
 using namespace NECTAR;

 WKWebView * globalWK;

void launchServer()
{
    using namespace httplib;
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFStringEncoding encodingMethod = CFStringGetSystemEncoding();
    CFURLRef rawURL = CFBundleCopyResourceURL(mainBundle, CFSTR("raw"), NULL, NULL);
    CFStringRef rawPath = CFURLCopyFileSystemPath(rawURL, kCFURLPOSIXPathStyle);

    const char *path = CFStringGetCStringPtr(rawPath, encodingMethod);
    var _path = path;
    _path += "/";
    Server svr;
    svr.set_mount_point("/", __NJS_Get_String(_path));
    svr.listen("localhost", 12001);
}

void drawNative(char* str)
{
    [globalWK loadHTMLString:[NSString stringWithCString:str    encoding:[NSString defaultCStringEncoding]]  baseURL:nil];
}

void navigateNative(char* str)
{
    NSString *urlString = [NSString stringWithCString:str   encoding:[NSString defaultCStringEncoding]];
    NSURL *url = [NSURL URLWithString:urlString];
    NSURLRequest *urlRequest = [NSURLRequest requestWithURL:url];
    [globalWK loadRequest:urlRequest];
}

 {INCLUDE}
 
 {DECL}

void njsCallback(WKWebView *wkWV, NSString* nString)
{
    globalWK = wkWV;
    __NJS_Call_Function(__NJS_Object_Get("onEvent", Nectar), [nString UTF8String]);
}

void loadedCallback(WKWebView *wkWV)
{
    // main NectarJS function
    // setup logic, events, init
    globalWK = wkWV;

    {INIT}

	{CODE}
    return;
}
