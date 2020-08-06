// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.4.3_A2.3;
 * @section: 15.4.3; 
 * @assertion: The length property of Array has the attribute ReadOnly;
 * @description: Checking if varying the length property fails;
*/

//CHECK#1
x = Array.length;
Array.length = Infinity;
if (Array.length !== x) {
  $ERROR('#1: x = Array.length; Array.length = Infinity; Array.length === x. Actual: ' + (Array.length));
}

