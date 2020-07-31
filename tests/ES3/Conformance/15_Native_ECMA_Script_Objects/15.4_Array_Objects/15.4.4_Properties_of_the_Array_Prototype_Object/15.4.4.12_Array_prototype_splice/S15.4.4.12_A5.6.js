// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.4.4.12_A5.6;
* @section: 15.4.4.12;
* @assertion: The splice property of Array has not prototype property;
* @description: Checking Array.prototype.splice.prototype;
*/

//CHECK#1
if (Array.prototype.splice.prototype !== undefined) {
  $ERROR('#1: Array.prototype.splice.prototype === undefined. Actual: ' + (Array.prototype.splice.prototype));
}
