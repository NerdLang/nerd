// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.4.4_A1.3_T1;
 * @section: 15.4.4;
 * @assertion: Array prototype object has length property whose value is +0;
 * @description: Array.prototype.length === 0;
*/

//CHECK#1
if (Array.prototype.length !== 0) {
  $ERROR('#1.1: Array.prototype.length === 0. Actual: ' + (Array.prototype.length));
} else {
  if (1 / Array.prototype.length !== Number.POSITIVE_INFINITY) {
    $ERROR('#1.2: Array.prototype.length === +0. Actual: ' + (Array.prototype.length));
  }
} 
   
