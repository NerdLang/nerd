// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.7.3.4_A2;
 * @section: 15.7.3.4;
 * @assertion: Number.NaN is ReadOnly;
 * @description: Checking if varying Number.NaN fails;
*/

// CHECK#1
Number.NaN = 1;
if (isNaN(Number.NaN) !== true) {
  $ERROR('#1: Number.NaN = 1; Number.NaN === Not-a-Number');
}
