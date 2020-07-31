// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.1.2.4_A2.6;
* @section: 15.1.2.4;
* @assertion: The isNaN property has not prototype property;
* @description: Checking isNaN.prototype;
*/

//CHECK#1
if (isNaN.prototype !== undefined) {
  $ERROR('#1: isNaN.prototype === undefined. Actual: ' + (isNaN.prototype));
}
