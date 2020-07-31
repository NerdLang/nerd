// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.1.2.5_A2.6;
* @section: 15.1.2.5;
* @assertion: The isFinite property has not prototype property;
* @description: Checking isFinit.prototype;
*/

//CHECK#1
if (isFinite.prototype !== undefined) {
  $ERROR('#1: isFinite.prototype === undefined. Actual: ' + (isFinite.prototype));
}
