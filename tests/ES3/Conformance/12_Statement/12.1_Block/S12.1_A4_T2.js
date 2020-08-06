// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S12.1_A4_T2;
* @section: 12.1;
* @assertion: The production Block can't be inside of expression;
* @description: Checking if execution of "y={x}" fails;
* @negative;
*/

x=1;

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
y={x};
//
//////////////////////////////////////////////////////////////////////////////
