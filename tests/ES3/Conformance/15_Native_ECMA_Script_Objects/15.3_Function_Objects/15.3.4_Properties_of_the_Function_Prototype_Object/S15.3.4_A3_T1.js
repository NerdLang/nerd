// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.3.4_A3_T1;
* @section: 15.3.4, 15.3.2.1;
* @assertion: The value of the internal [[Prototype]] property of the Function prototype object is the Object prototype object (15.3.2.1);
* @description: Checking prototype of Function.prototype;
*/

//CHECK#1
if (!(Object.prototype.isPrototypeOf(Function.prototype))) {
  $ERROR('#1: The value of the internal [[Prototype]] property of the Function prototype object is the Object prototype object (15.3.2.1)');
}

delete Function.prototype.toString;

//CHECK#2
if (Function.prototype.toString() !== "[object "+"Function"+"]") {
  $ERROR('#2: The value of the internal [[Prototype]] property of the Function prototype object is the Object prototype object (15.3.2.1)');
}
