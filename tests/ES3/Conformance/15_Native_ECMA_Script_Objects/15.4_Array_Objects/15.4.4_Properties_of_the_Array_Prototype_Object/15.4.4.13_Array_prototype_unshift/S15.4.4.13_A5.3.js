// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.4.4.13_A5.3;
* @section: 15.4.4.13; 
* @assertion: The length property of unshift has the attribute ReadOnly;
* @description: Checking if varying the length property fails;
*/

//CHECK#1
x = Array.prototype.unshift.length;
Array.prototype.unshift.length = Infinity;
if (Array.prototype.unshift.length !== x) {
  $ERROR('#1: x = Array.prototype.unshift.length; Array.prototype.unshift.length = Infinity; Array.prototype.unshift.length === x. Actual: ' + (Array.prototype.unshift.length));
}

