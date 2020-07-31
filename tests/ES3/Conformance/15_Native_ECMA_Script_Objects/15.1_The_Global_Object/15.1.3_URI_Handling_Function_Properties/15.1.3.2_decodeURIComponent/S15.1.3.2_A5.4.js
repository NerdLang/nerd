// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.1.3.2_A5.4;
 * @section: 15.1.3.2;
 * @assertion: The length property of decodeURIComponent is 1;
 * @description: decodeURIComponent.length === 1;
*/

//CHECK#1
if (decodeURIComponent.length !== 1) {
  $ERROR('#1: decodeURIComponent.length === 1. Actual: ' + (decodeURIComponent.length));
} 

