// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S9.3_A2_T1;
 * @section: 9.3, 15.7.1;
 * @assertion: Result of number conversion from null value is +0;
 * @description: null convert to Number by explicit transformation;
 */

// CHECK #1
if (Number(null) !== 0) {
  $ERROR('#1.1: Number(null) === 0. Actual: ' + (Number(null))); 
} else {
  if (1/Number(null) !== Number.POSITIVE_INFINITY) {
    $ERROR('#1.2: Number(null) === +0. Actual: -0');
  }	
}
