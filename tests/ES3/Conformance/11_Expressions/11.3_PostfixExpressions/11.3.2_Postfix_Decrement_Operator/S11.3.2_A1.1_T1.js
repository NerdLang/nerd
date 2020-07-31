// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S11.3.2_A1.1_T1;
* @section: 11.3.2, 11.6.3, 7.3;
* @assertion: Line Terminator between LeftHandSideExpression and "--" is not allowed;
* @description: Checking Line Feed;
* @negative
*/

//CHECK#1
eval("var x = 1; x\u000A--");
