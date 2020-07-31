// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.1.2.2_A9.6;
* @section: 15.1.2.2;
* @assertion: The parseInt property has not prototype property;
* @description: Checking parseInt.prototype;
*/

//CHECK#1
if (parseInt.prototype !== undefined) {
  $ERROR('#1: parseInt.prototype === undefined. Actual: ' + (parseInt.prototype));
}
