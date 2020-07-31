// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.1.2.3_A5_T1;
 * @section: 15.1.2.3, 9.3.1;
 * @assertion: Return the number value for the MV of Result(4);
 * @description: Checking Infinity;
*/

//CHECK#1
if (parseFloat("Infinity") !== Number.POSITIVE_INFINITY) {
  $ERROR('#1: parseFloat("Infinity") === Number.POSITIVE_INFINITY. Actual: ' + (parseFloat("Infinity")));
}

//CHECK#2
if (parseFloat("+Infinity") !== Number.POSITIVE_INFINITY) {
  $ERROR('#2: parseFloat("+Infinity") === Number.POSITIVE_INFINITY. Actual: ' + (parseFloat("+Infinity")));
}

//CHECK#3
if (parseFloat("-Infinity") !== Number.NEGATIVE_INFINITY) {
  $ERROR('#3: parseFloat("-Infinity") === Number.NEGATIVE_INFINITY. Actual: ' + (parseFloat("-Infinity")));
}
