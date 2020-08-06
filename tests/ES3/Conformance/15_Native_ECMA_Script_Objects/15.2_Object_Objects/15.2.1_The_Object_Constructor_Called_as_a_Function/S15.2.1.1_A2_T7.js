// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.2.1.1_A2_T7;
* @section: 15.2.1.1;
* @assertion: When the Object function is called with one argument value,
* and the value neither is null nor undefined, and is supplied, return ToObject(value);
* @description: Calling Object function with empty string argument value;
*/

str = '';

// CHECK#1
if (typeof(str) !== 'string') {
  $FAIL('#1: "" is NOT a String');
}

obj = Object(str);

//CHECK#2
if (obj.constructor !== String) {
  $ERROR('#2: Object("") returns ToObject("")');
}

//CHECK#3
if (typeof obj !== "object") {
  $ERROR('#3: Object("") returns ToObject("")');
}

//CHECK#4
if ((obj != "")||(obj === "")) {
  $ERROR('#4: Object("") returns ToObject("")');
}
