// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.1.3.4_A5.6;
* @section: 15.1.3.4;
* @assertion: The encodeURIComponent property has not prototype property;
* @description: Checking encodeURIComponent.prototype;
*/

//CHECK#1
if (encodeURIComponent.prototype !== undefined) {
  $ERROR('#1: encodeURIComponent.prototype === undefined. Actual: ' + (encodeURIComponent.prototype));
}
