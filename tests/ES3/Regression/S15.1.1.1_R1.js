// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.1.1.1_R1;
 * @section: 15.1.1.1, 9.3;
 * @description: The NaN is not ReadOnly, check Number for resettability of result;
*/

// CHECK#1
NaN = true;
Number();
if (NaN !== true) {
  NaN = true;
  Number();
  if (NaN === true) {
    $ERROR('#1: Resettability of result');
  }
}
