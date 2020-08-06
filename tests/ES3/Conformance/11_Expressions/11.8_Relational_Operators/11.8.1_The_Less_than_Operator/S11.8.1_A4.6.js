// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S11.8.1_A4.6;
* @section: 11.8.1, 11.8.5;
* @assertion: If y is +Infinity and x !== y, return true;
* @description: x is number primitive;
*/

//CHECK#1
if ((0 < Number.POSITIVE_INFINITY) !== true) {
  $ERROR('#1: (0 < +Infinity) === true');
}

//CHECK#2
if ((1.1 < Number.POSITIVE_INFINITY) !== true) {
  $ERROR('#2: (1.1 < +Infinity) === true');
}

//CHECK#3
if ((-1.1 < Number.POSITIVE_INFINITY) !== true) {
  $ERROR('#3: (-1.1 < +Infinity) === true');
}

//CHECK#4
if ((Number.NEGATIVE_INFINITY < Number.POSITIVE_INFINITY) !== true) {
  $ERROR('#4: (-Infinity < +Infinity) === true');
}

//CHECK#5
if ((Number.MAX_VALUE < Number.POSITIVE_INFINITY) !== true) {
  $ERROR('#5: (Number.MAX_VALUE < +Infinity) === true');
}

//CHECK#6
if ((Number.MIN_VALUE < Number.POSITIVE_INFINITY) !== true) {
  $ERROR('#6: (Number.MIN_VALUE < +Infinity) === true');
}

