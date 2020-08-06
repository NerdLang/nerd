// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.1.1.2_R2.2;
 * @section: 15.1.1.2, 15.1.2, 15.1.3;
 * @description: The Infinity is not ReadOnly, check isFinite Functions that use ToNumber; 
*/

// CHECK#1
Infinity = 0;
if (isFinite(Infinity) !== true) {
  $ERROR('#1: Infinity = 0; isFinite(Infinity) === true'); 
}
