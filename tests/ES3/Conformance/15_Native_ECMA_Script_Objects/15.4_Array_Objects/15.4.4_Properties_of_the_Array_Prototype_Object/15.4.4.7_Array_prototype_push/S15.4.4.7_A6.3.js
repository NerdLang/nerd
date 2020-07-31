// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.4.4.7_A6.3;
* @section: 15.4.4.7;
* @assertion: The length property of push has the attribute ReadOnly;
* @description: Checking if varying the length property fails;
*/

//CHECK#1
x = Array.prototype.push.length;
Array.prototype.push.length = Infinity;
if (Array.prototype.push.length !== x) {
  $ERROR('#1: x = Array.prototype.push.length; Array.prototype.push.length = Infinity; Array.prototype.push.length === x. Actual: ' + (Array.prototype.push.length));
}

