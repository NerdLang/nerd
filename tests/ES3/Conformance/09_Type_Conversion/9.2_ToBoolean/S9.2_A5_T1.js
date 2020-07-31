// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S9.2_A5_T1;
 * @section: 9.2, 15.6.1;
 * @assertion: Result of boolean conversion from nonempty string value (length is not zero) is true; from empty String (length is zero) is false;
 * @description: "" is converted to Boolean by explicit transformation;
*/

// CHECK#1
if (Boolean("") !== false) {
  $ERROR('#1: Boolean("") === false. Actual: ' + (Boolean("")));
}
