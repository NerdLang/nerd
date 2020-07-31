// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.1.3.1_A5.4;
 * @section: 15.1.3.1;
 * @assertion: The length property of decodeURI is 1;
 * @description: decodeURI.length === 1;
*/

//CHECK#1
if (decodeURI.length !== 1) {
  $ERROR('#1: decodeURI.length === 1. Actual: ' + (decodeURI.length));
} 

