// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.1.3.1_A5.6;
* @section: 15.1.3.1;
* @assertion: The decodeURI property has not prototype property;
* @description: Checking decodeURI.prototype;
*/

//CHECK#1
if (decodeURI.prototype !== undefined) {
  $ERROR('#1: decodeURI.prototype === undefined. Actual: ' + (decodeURI.prototype));
}
