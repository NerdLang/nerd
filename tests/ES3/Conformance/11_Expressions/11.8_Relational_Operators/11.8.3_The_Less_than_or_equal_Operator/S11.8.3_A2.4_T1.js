// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S11.8.3_A2.4_T1;
 * @section: 11.8.3;
 * @assertion: First expression is evaluated first, and then second expression;
 * @description: Checking with "=";
*/

//CHECK#1
var x = 0; 
if ((x = 1) <= x !== true) {
  $ERROR('#1: var x = 0; (x = 1) <= x === true');
}

//CHECK#2
var x = 1; 
if (x <= (x = 0) !== false) {
  $ERROR('#2: var x = 1; x <= (x = 0) === false');
}

