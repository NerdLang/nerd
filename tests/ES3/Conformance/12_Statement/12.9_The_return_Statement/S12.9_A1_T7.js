// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S12.9_A1_T7;
* @section: 12.9;
* @assertion: Appearing of "return" without a function body leads to syntax error;
* @description: Checking if execution of "return x" with no function, placed inside Block, fails;
* @negative;
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
{
    var x=1;
    return x;
    var y=2;
}
//
//////////////////////////////////////////////////////////////////////////////
