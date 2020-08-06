// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S9.2_A5_T2;
 * @section: 9.2, 11.4.9;
 * @assertion: Result of boolean conversion from nonempty string value (length is not zero) is true; from empty String (length is zero) is false;
 * @description: "" convert to Boolean by implicit transformation;
*/

// CHECK#1
if (!("") !== true) {
  $ERROR('#1: !("") === true. Actual: ' + (!("")));
}
