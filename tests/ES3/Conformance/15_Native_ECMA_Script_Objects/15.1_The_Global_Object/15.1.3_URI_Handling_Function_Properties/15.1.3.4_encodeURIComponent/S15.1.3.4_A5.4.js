// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.1.3.4_A5.4;
 * @section: 15.1.3.4;
 * @assertion: The length property of encodeURIComponent is 1;
 * @description: encodeURIComponent.length === 1;
*/

//CHECK#1
if (encodeURIComponent.length !== 1) {
  $ERROR('#1: encodeURIComponent.length === 1. Actual: ' + (encodeURIComponent.length));
} 

