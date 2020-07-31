// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.4.4.3_A4.4;
* @section: 15.4.4.3;
* @assertion: The length property of toLocaleString is 0;
* @description: toLocaleString.length === 1;
*/

//CHECK#1
if (Array.prototype.toLocaleString.length !== 0) {
  $ERROR('#1: Array.prototype.toLocaleString.length === 0. Actual: ' + (Array.prototype.toLocaleString.length));
}

