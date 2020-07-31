// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.1.1.1_R2.1;
 * @section: 15.1.1.1, 15.1.2, 15.1.3;
 * @description: The NaN is not ReadOnly, check isNaN Functions that use ToNumber; 
*/

// CHECK#1
NaN = 1;
if (isNaN(NaN) !== false) {
  $ERROR('#1: NaN = 1; isNaN(NaN) === false'); 
}
