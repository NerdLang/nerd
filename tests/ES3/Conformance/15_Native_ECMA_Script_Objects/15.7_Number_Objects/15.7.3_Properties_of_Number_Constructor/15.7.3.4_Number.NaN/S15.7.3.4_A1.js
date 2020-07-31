// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.7.3.4_A1;
 * @section: 15.7.3.4;
 * @assertion: Number.NaN is Not-a-Number;
 * @description: Checking isNaN(Number.NaN);
*/

// CHECK#1
if (isNaN(Number.NaN) !== true) {
  $ERROR('#1: Number.NaN === Not-a-Number');
}
