// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.4.4.12_A5.3;
* @section: 15.4.4.12; 
* @assertion: The length property of splice has the attribute ReadOnly;
* @description: Checking if varying the length property fails;
*/

//CHECK#1
x = Array.prototype.splice.length;
Array.prototype.splice.length = Infinity;
if (Array.prototype.splice.length !== x) {
  $ERROR('#1: x = Array.prototype.splice.length; Array.prototype.splice.length = Infinity; Array.prototype.splice.length === x. Actual: ' + (Array.prototype.splice.length));
}

