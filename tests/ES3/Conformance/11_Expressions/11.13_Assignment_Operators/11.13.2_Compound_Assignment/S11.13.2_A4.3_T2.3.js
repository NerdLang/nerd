// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S11.13.2_A4.3_T2.3;
 * @section: 11.13.2, 11.5.3;
 * @assertion: The production x %= y is the same as x = x % y; 
 * @description: Type(x) is different from Type(y) and both types vary between Number (primitive or object) and Null;
 */

//CHECK#1
x = 1;
x %= null;
if (isNaN(x) !== true) {
  $ERROR('#1: x = 1; x %= null; x === Not-a-Number. Actual: ' + (x));
}

//CHECK#2
x = null;
x %= 1;
if (x !== 0) {
  $ERROR('#2: x = null; x %= 1; x === 0. Actual: ' + (x));
}

//CHECK#3
x = new Number(1);
x %= null;
if (isNaN(x) !== true) {
  $ERROR('#3: x = new Number(1); x %= null; x === Not-a-Number. Actual: ' + (x));
}

//CHECK#4
x = null;
x %= new Number(1);
if (x !== 0) {
  $ERROR('#4: x = null; x %= new Number(1); x === 0. Actual: ' + (x));
}
