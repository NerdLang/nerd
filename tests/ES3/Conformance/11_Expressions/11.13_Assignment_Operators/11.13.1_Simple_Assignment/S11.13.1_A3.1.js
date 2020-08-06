// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S11.13.1_A3.1;
 * @section: 11.13.1;
 * @assertion: Operator x = y PutValue(x, y);
 * @description: Checking Expression and Variable statements; 
*/

//CHECK#1
var x = 1;
if (x !== 1) {
  $ERROR('#1: var x = 1; x === 1. Actual: ' + (x));
}

//CHECK#2
y = 1;
if (y !== 1) {
  $ERROR('#2: y = 1; y === 1. Actual: ' + (y));
}
