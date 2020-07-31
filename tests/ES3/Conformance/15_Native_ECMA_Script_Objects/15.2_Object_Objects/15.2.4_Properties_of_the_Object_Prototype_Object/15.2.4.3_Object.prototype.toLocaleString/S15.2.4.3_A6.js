// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.2.4.3_A6;
* @section: 15.2.4.3, 13.2;
* @assertion: Object.prototype.toLocaleString has not prototype property;
* @description: Checking if obtaining the prototype property of Object.prototype.toLocaleString fails;
*/

//CHECK#1
if (Object.prototype.toLocaleString.prototype !== undefined) {
  $ERROR('#1: Object.prototype.toLocaleString has not prototype property'+Object.prototype.toLocaleString.prototype);
}
//
