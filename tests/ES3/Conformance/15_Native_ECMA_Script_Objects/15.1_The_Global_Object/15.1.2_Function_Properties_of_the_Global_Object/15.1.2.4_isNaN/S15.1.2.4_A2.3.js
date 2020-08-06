// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.1.2.4_A2.3;
 * @section: 15.1.2.4;
 * @assertion: The length property of isNaN has the attribute ReadOnly;
 * @description: Checking if varying the length property fails;
*/

//CHECK#1
x = isNaN.length;
isNaN.length = Infinity;
if (isNaN.length !== x) {
  $ERROR('#1: x = isNaN.length; isNaN.length = Infinity; isNaN.length === x. Actual: ' + (isNaN.length));
}

