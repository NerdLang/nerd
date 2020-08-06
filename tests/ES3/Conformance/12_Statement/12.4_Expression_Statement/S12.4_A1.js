// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S12.4_A1;
* @section: 12.4;
* @assertion: An ExpressionStatement can not start with the function keyword because that might make it ambiguous with a FunctionDeclaration;
* @description: Checking if execution of "function(){}()" fails;
* @negative;
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
function(){}();
//
//////////////////////////////////////////////////////////////////////////////
