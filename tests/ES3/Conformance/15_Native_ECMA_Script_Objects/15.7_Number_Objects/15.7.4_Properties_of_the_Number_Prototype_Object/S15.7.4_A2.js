// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.7.4_A2;
 * @section: 15.7.4;
 * @assertion: The value of the internal [[Prototype]] property of the Number 
 * prototype object is the Object prototype object;
 * @description: Checking Object.prototype.isPrototypeOf(Number.prototype);
*/

//CHECK#1
if (!Object.prototype.isPrototypeOf(Number.prototype)) {
  $ERROR('#1: Object prototype object is the prototype of Number prototype object');
}
