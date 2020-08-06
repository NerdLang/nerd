// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.4.2.2_A1.1_T2;
 * @section: 15.4.2.2, 15.2.4.2;
 * @assertion: The [[Prototype]] property of the newly constructed object 
 * is set to the original Array prototype object, the one that 
 * is the initial value of Array.prototype;
 * @description: Array.prototype.toString = Object.prototype.toString;
*/

//CHECK#1
Array.prototype.toString = Object.prototype.toString;
var x = new Array(0); 
if (x.toString() !== "[object " + "Array" + "]") {
  $ERROR('#1: Array.prototype.toString = Object.prototype.toString; var x = new Array(0); x.toString() === "[object " + "Array" + "]". Actual: ' + (x.toString()));
}
