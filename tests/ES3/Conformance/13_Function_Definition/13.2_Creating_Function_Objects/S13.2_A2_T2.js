// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S13.2_A2_T2;
* @section: 13.2;
* @assertion: Nested function are admitted;
* @description: Nesting level is three;
*/

__ROBOT="C3PO";

function __FUNC(){
    function __GUNC(){
        return arguments[0];
    };
    function __HUNC(){
        return __GUNC;
    };
    return __HUNC;
};

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (__FUNC()()(__ROBOT) !== __ROBOT) {
	$ERROR('#1: __FUNC()()(__ROBOT) === __ROBOT. Actual: __FUNC()()(__ROBOT) ==='+__FUNC()()(__ROBOT));
}
//
//////////////////////////////////////////////////////////////////////////////
