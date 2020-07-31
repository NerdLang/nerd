// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S11.8.1_A2.4_T1;
 * @section: 11.8.1;
 * @assertion: First expression is evaluated first, and then second expression;
 * @description: Checking with "=";
*/

//CHECK#1
var x = 1; 
if ((x = 0) < x !== false) {
  $ERROR('#1: var x = 1; (x = 0) < x === false');
}

//CHECK#2
var x = 0; 
if (x < (x = 1) !== true) {
  $ERROR('#2: var x = 0; x < (x = 1) === true');
}

