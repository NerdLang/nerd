// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.4.4.7_A6.4;
* @section: 15.4.4.7;
* @assertion: The length property of push is 1;
* @description: push.length === 1;
*/

//CHECK#1
if (Array.prototype.push.length !== 1) {
  $ERROR('#1: Array.prototype.push.length === 1. Actual: ' + (Array.prototype.push.length));
}

