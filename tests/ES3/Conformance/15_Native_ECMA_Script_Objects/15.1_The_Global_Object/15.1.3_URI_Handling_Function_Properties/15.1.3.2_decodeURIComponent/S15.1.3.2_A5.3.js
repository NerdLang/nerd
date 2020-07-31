// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.1.3.2_A5.3;
 * @section: 15.1.3.2;
 * @assertion: The length property of decodeURIComponent has the attribute ReadOnly;
 * @description: Checking if varying the length property fails;
*/

//CHECK#1
x = decodeURIComponent.length;
decodeURIComponent.length = Infinity;
if (decodeURIComponent.length !== x) {
  $ERROR('#1: x = decodeURIComponent.length; decodeURIComponent.length = Infinity; decodeURIComponent.length === x. Actual: ' + (decodeURIComponent.length));
}

