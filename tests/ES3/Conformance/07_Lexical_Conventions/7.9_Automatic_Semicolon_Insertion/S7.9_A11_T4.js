// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S7.9_A11_T4;
 * @section: 7.9, 12.5;
 * @assertion: Check If Statement for automatic semicolon insertion;
 * @description: Checking if execution of "if (false) x = 1 else x = -1" fails;
 * @negative
*/

//CHECK#1
x = 0;
if (false) x = 1 else x = -1
