// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S9.2_A4_T1;
 * @section: 9.2, 15.6.1;
 * @assertion: Result of boolean conversion from number value is false if the argument is +0, -0, or NaN; otherwise, is true;
 * @description: +0, -0 and NaN convert to Boolean by explicit transformation;
*/

// CHECK#1
if (Boolean(+0) !== false) {
  $ERROR('#1: Boolean(+0) === false. Actual: ' + (Boolean(+0))); 	 
}

// CHECK#2
if (Boolean(-0) !== false) {
  $ERROR('#2: Boolean(-0) === false. Actual: ' + (Boolean(-0)));
}

// CHECK#3
if (Boolean(Number.NaN) !== false) {
  $ERROR('#3: Boolean(Number.NaN) === false. Actual: ' + (Boolean(Number.NaN)));
}
