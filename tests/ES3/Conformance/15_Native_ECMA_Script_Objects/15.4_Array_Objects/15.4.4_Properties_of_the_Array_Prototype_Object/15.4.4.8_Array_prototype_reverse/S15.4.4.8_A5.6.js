// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.4.4.8_A5.6;
* @section: 15.4.4.8;
* @assertion: The reverse property of Array has not prototype property;
* @description: Checking Array.prototype.reverse.prototype;
*/

//CHECK#1
if (Array.prototype.reverse.prototype !== undefined) {
  $ERROR('#1: Array.prototype.reverse.prototype === undefined. Actual: ' + (Array.prototype.reverse.prototype));
}
