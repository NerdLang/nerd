// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S11.4.5_A4_T2;
* @section: 11.4.5, 11.6.3;
* @assertion: Operator --x returns ToNumber(x) - 1;
* @description: Type(x) is number primitive or Number object;
*/

//CHECK#1
var x = 0.1;
if (--x !== 0.1 - 1) {
  $ERROR('#1: var x = 0.1; --x === 0.1 - 1. Actual: ' + (--x));
}

//CHECK#2
var x = new Number(-1.1);
if (--x !== -1.1 - 1) {
  $ERROR('#2: var x = new Number(-1.1); --x === -1.1- 1. Actual: ' + (--x));
}
