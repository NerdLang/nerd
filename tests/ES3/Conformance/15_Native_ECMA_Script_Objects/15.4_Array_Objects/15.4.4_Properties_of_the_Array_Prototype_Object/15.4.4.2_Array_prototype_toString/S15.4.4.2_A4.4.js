// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.4.4.2_A4.4;
* @section: 15.4.4.2;
* @assertion: The length property of toString is 0;
* @description: toString.length === 1;
*/

//CHECK#1
if (Array.prototype.toString.length !== 0) {
  $ERROR('#1: Array.prototype.toString.length === 0. Actual: ' + (Array.prototype.toString.length));
}

