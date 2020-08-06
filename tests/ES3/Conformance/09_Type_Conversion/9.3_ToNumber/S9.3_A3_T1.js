// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S9.3_A3_T1;
 * @section: 9.3, 15.7.1;
 * @assertion: Result of number conversion from boolean value is 1 if the argument is true, else is +0;
 * @description: False and true convert to Number by explicit transformation;
 */

// CHECK#1
if (Number(false) !== +0) {
  $ERROR('#1.1: Number(false) === 0. Actual: ' + (Number(false)));
} else {
  if (1/Number(false) !== Number.POSITIVE_INFINITY) {
    $ERROR('#1.2: Number(false) === +0. Actual: -0');
  }
}

// CHECK#2
if (Number(true) !== 1) {
  $ERROR('#2: Number(true) === 1. Actual: ' + (Number(true)));	
}
