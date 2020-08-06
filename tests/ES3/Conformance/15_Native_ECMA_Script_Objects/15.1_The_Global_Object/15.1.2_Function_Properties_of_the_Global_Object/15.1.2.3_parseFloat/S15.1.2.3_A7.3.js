// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.1.2.3_A7.3;
 * @section: 15.1.2.3;
 * @assertion: The length property of parseFloat has the attribute ReadOnly;
 * @description: Checking if varying the length property fails;
*/

//CHECK#1
x = parseFloat.length;
parseFloat.length = Infinity;
if (parseFloat.length !== x) {
  $ERROR('#1: x = parseFloat.length; parseFloat.length = Infinity; parseFloat.length === x. Actual: ' + (parseFloat.length));
}

