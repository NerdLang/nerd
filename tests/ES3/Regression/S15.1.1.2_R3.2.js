// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.1.1.2_R3.2;
 * @section: 15.1.1.2, 15.1.2.4;
 * @description: The Infinity is not ReadOnly, check isFinite for resettability of result
*/

// CHECK#1
Infinity = 0;
isFinite();
if (Infinity !== 0) {
  Infinity = 0;
  isFinite();
  if (Infinity === 0) {
    $ERROR('#1: isFinite resettability of result for Infinity value');
  }
}
