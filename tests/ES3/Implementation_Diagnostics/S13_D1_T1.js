// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S13_D1_T1;
* @section: 13,12.10;
* @assertion: Function declaration inside of "with" statement interprets as function expression;
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#0
if (typeof __func !== "undefined") {
	$ERROR('#0: Function declaration inside of "with" statement interprets as function expression');
}
//
//////////////////////////////////////////////////////////////////////////////

var a = 1, b = "a";

var __obj = {a:2,b:"x"};

with (__obj)
{
        function __func()
        {
            return a;
        }
}

delete __obj;

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (__func() !== 2) {
	$ERROR('#1: Function declaration inside of "with" statement interprets as function expression');
}
//
//////////////////////////////////////////////////////////////////////////////

var __obj = {a:3,b:"b"};

with (__obj)
{
        function __func()
        {
            return b;
        }
}

delete __obj;

//////////////////////////////////////////////////////////////////////////////
//CHECK#2
if (__func()!=="b") {
	$ERROR('#2: Function declaration inside of "with" statement interprets as function expression');
}
//
//////////////////////////////////////////////////////////////////////////////

with ({a:99,b:"c"})
{
    //////////////////////////////////////////////////////////////////////////////
    //CHECK#2
    if (__func() !== "c") {
    	$ERROR('#2: Function declaration inside of "with" statement interprets as function expression');
    }
    //
    //////////////////////////////////////////////////////////////////////////////
}
