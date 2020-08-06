// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.1.2.1_A4.3;
 * @section: 15.1.2.1;
 * @assertion: The length property of eval has the attribute ReadOnly;
 * @description: Checking if varying the length property fails;
*/

//CHECK#1
x = eval.length;
eval.length = Infinity;
if (eval.length !== x) {
  $ERROR('#1: x = eval.length; eval.length = Infinity; eval.length === x. Actual: ' + (eval.length));
}

