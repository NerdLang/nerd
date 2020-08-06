// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.4.4.10_A5.6;
* @section: 15.4.4.10;
* @assertion: The slice property of Array has not prototype property;
* @description: Checking Array.prototype.slice.prototype;
*/

//CHECK#1
if (Array.prototype.slice.prototype !== undefined) {
  $ERROR('#1: Array.prototype.slice.prototype === undefined. Actual: ' + (Array.prototype.slice.prototype));
}
