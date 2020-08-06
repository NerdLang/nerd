// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S12.6.1_A6_T4;
* @section: 12.6.1;
* @assertion: Expression in "do-while" IterationStatement is bracketed with braces;
* @description: Checking if execution of "do{}while false" fails;
* @negative;
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
do break; while false;
//
//////////////////////////////////////////////////////////////////////////////
