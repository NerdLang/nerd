// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.1.2.1_A4.4;
 * @section: 15.1.2.1;
 * @assertion: The length property of eval is 1;
 * @description: eval.length === 1;
*/

//CHECK#1
if (eval.length !== 1) {
  $ERROR('#1: eval.length === 1. Actual: ' + (eval.length));
} 

