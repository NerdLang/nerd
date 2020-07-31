// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.1.3.3_A5.3;
 * @section: 15.1.3.3;
 * @assertion: The length property of encodeURI has the attribute ReadOnly;
 * @description: Checking if varying the length property fails;
*/

//CHECK#1
x = encodeURI.length;
encodeURI.length = Infinity;
if (encodeURI.length !== x) {
  $ERROR('#1: x = encodeURI.length; encodeURI.length = Infinity; encodeURI.length === x. Actual: ' + (encodeURI.length));
}

