// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.7.3.1_A2_T1;
 * @section: 15.7.3.1;
 * @assertion: Number.prototype is itself Number object;
 * @description: Checking type of Number.prototype property - test based on 
 * deleting Number.prototype.toString;
*/

//CHECK#1
if (typeof Number.prototype !== "object") {
  $ERROR('#1: typeof Number.prototype === "object"');
}

delete Number.prototype.toString;

if (Number.prototype.toString() !== "[object Number]") {
  $ERROR('#3: The [[Class]] property of the Number prototype object is set to "Number"');
}
