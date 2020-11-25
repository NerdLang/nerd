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
 #include "nectar.cpp"
 
 using namespace NectarCore::Global;
 using namespace NectarCore::Functions;
 
 //#include "httplib.h"

var __NJS_ENV = "iOS";
var __NJS_PLATFORM = "{{__PLATFORM__}}";
 
 #define __NJS_Create_Object() new NectarCore::Class::Object()
 #define __NJS_Create_Array(_arr) new NectarCore::Class::Array(_arr)
 #define __NJS_InitVar() NectarCore::VAR()
 
 WKWebView * globalWK;

void launchServer()
{
	/*
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
	*/
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
	Nectar["onEvent"]([nString UTF8String]);
}

void loadedCallback(WKWebView *wkWV)
{
    // main NectarJS function
    // setup logic, events, init
    globalWK = wkWV;

    {INIT}

	{
		{CODE}
    }
	
	return;
}
