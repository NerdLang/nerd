// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.2.1.1_A3_T2;
* @section: 15.2.1.1;
* @assertion: Since calling Object as a function is identical to calling a function, list of arguments bracketing is allowed;
* @description: Creating an object with "Object(null,2,3)";
*/

obj = Object(null,2,3);

//CHECK#1
if (obj.constructor !== Object) {
  $ERROR('#1: Since Object as a function calling is the same as function calling list of arguments can appears in braces;');
}

//CHECK#2
if (typeof obj !== "object") {
  $ERROR('#2: Since Object as a function calling is the same as function calling list of arguments can appears in braces;');
}
