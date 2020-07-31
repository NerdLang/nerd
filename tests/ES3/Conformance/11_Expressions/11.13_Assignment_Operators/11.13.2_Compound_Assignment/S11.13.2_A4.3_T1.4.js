// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S11.13.2_A4.3_T1.4;
 * @section: 11.13.2, 11.5.3;
 * @assertion: The production x %= y is the same as x = x % y; 
 * @description: Type(x) and Type(y) vary between Null and Undefined;
 */

//CHECK#1
x = null;
x %= undefined;
if (isNaN(x) !== true) {
  $ERROR('#1: x = null; x %= undefined; x === Not-a-Number. Actual: ' + (x));
}

//CHECK#2
x = undefined;
x %= null;
if (isNaN(x) !== true) {
  $ERROR('#2: x = undefined; x %= null; x === Not-a-Number. Actual: ' + (x));
}

//CHECK#3
x = undefined;
x %= undefined;
if (isNaN(x) !== true) {
  $ERROR('#3: x = undefined; x %= undefined; x === Not-a-Number. Actual: ' + (x));
}

//CHECK#4
x = null;
x %= null;
if (isNaN(x) !== true) {
  $ERROR('#4: x = null; x %= null; x === Not-a-Number. Actual: ' + (x));
}
