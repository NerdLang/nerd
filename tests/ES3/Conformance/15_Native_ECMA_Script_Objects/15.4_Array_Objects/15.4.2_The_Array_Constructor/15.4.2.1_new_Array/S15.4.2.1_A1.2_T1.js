// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.4.2.1_A1.2_T1;
 * @section: 15.4.2.1, 15.2.4.2;
 * @assertion: The [[Class]] property of the newly constructed object is set to "Array";
 * @description: Checking use Object.prototype.toString;
*/

//CHECK#1
var x = new Array(); 
x.getClass = Object.prototype.toString;
if (x.getClass() !== "[object " + "Array" + "]") {
  $ERROR('#1: var x = new Array(); x.getClass = Object.prototype.toString; x is Array object. Actual: ' + (x.getClass()));
}

//CHECK#2
var x = new Array(0,1,2); 
x.getClass = Object.prototype.toString;
if (x.getClass() !== "[object " + "Array" + "]") {
  $ERROR('#2: var x = new Array(0,1,2); x.getClass = Object.prototype.toString; x is Array object. Actual: ' + (x.getClass()));
}
