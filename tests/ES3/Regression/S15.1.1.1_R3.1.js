// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.1.1.1_R3.1;
 * @section: 15.1.1.1, 15.1.2.4;
 * @description: The NaN is not ReadOnly, check isNaN for resettability of result;
*/

// CHECK#1
NaN = 1;
isNaN();
if (NaN !== 1) {
  NaN = 1;
  isNaN();
  if (NaN === 1) {
    $ERROR('#1: isNaN resettability of result for NaN value');
  }
}
