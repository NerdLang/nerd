// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S13.2.2_D20_T8;
* @section: 13.2.2;
* @assertion: function declaration inside of "with" statement is a fuction declaration inside of current execution context;
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#0
if (typeof __func !== "function") {
	$ERROR('#0: function declaration inside of "with" statement is a fuction declaration inside of current execution context');
}
//
//////////////////////////////////////////////////////////////////////////////

var a = 1, b = "a";

var __obj = {a:2};

with (__obj)
{
    while(0){
        function __func()
        {
            return a;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (__func() !== "a") {
	$ERROR('#1: function declaration inside of "with" statement is a fuction declaration inside of current execution context');
}
//
//////////////////////////////////////////////////////////////////////////////

delete __obj;

var __obj = {a:3,b:"b"};

with (__obj)
{
    for(b in null){
        function __func()
        {
            return b;
        }
    }
}

with (__obj)
{
    result = __func();
}

//////////////////////////////////////////////////////////////////////////////
//CHECK#2
if (result !== "a") {
	$ERROR('#2: function declaration inside of "with" statement is a fuction declaration inside of current execution context');
}
//
//////////////////////////////////////////////////////////////////////////////
