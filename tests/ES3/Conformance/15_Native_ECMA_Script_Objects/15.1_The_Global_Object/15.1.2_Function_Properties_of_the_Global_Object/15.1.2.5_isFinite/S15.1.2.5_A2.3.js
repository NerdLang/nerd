// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.1.2.5_A2.3;
 * @section: 15.1.2.5;
 * @assertion: The length property of isFinite has the attribute ReadOnly;
 * @description: Checking if varying the length property fails;
*/

//CHECK#1
x = isFinite.length;
isFinite.length = Infinity;
if (isFinite.length !== x) {
  $ERROR('#1: x = isFinite.length; isFinite.length = Infinity; isFinite.length === x. Actual: ' + (isFinite.length));
}

