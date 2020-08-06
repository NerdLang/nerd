// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.3.4.2_A6;
* @section: 15.3.4.2, 13.2;
* @assertion: Function.prototype.toString has not prototype property;
* @description: Checking if obtaining the prototype property of Function.prototype.toString fails;
*/

//CHECK#1
if (Function.prototype.toString.prototype !== undefined) {
  $ERROR('#1: Function.prototype.toString has not prototype property'+Function.prototype.toString.prototype);
}
