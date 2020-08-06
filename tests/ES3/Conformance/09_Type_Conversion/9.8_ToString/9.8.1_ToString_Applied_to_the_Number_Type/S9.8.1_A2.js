// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S9.8.1_A2;
 * @section: 9.8.1;
 * @assertion: If m is +0 or -0, return the string "0";
 * @description: +0 and -0 convert to String by explicit transformation;
*/

// CHECK#1
if (String(+0) !== "0") {
  $ERROR('#1: String(+0) === "0". Actual: ' + (String(+0)));
}

// CHECK#2
if (String(-0) !== "0") {
  $ERROR('#2: String(-0) === "0". Actual: ' + (String(-0)));
}
