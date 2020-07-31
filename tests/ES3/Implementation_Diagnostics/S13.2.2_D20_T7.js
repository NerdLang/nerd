// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S13.2.2_D20_T7;
* @section: 13.2.2;
* @assertion: function declaration inside of "with" statement is a fuction declaration inside of current execution context;
*/

var a = 1;

var __obj = {a:2};

with (__obj)
{
    function __func()
    {
        return a;
    }
}

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (__obj.hasOwnProperty('__func')) {
	$ERROR('#1: function declaration inside of "with" statement is a fuction declaration inside of current execution context');
}
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//CHECK#2
if (!(this.hasOwnProperty('__func'))) {
	$ERROR('#2: function declaration inside of "with" statement is a fuction declaration inside of current execution context');
}
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//CHECK#3
if (__func in __obj) {
	$ERROR('#3: function declaration inside of "with" statement is a fuction declaration inside of current execution context');
}
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//CHECK#4
if (this.__func === undefined) {
	$ERROR('#4: function declaration inside of "with" statement is a fuction declaration inside of current execution context');
}
//
//////////////////////////////////////////////////////////////////////////////
