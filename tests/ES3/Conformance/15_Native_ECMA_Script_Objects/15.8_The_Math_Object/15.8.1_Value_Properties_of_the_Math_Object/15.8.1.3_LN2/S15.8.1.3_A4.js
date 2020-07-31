// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.8.1.3_A4;
 * @section: 15.8.1.3;
 * @assertion: Value Property LN2 of the Math Object has the attribute ReadOnly;
 * @description: Checking if Math.LN2 property has the attribute DontDelete;
 */

// CHECK#1
x = Math.LN2;
Math.LN2 = 1;
if (Math.LN2 !== x) {
  $ERROR('#1: Math.LN2 hasn\'t ReadOnly: \'x = Math.LN2;Math.LN2 = 1;Math.LN2 === x\'');
}
