// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.2.1.1_A2_T5;
* @section: 15.2.1.1;
* @assertion: When the Object function is called with one argument value,
* and the value neither is null nor undefined, and is supplied, return ToObject(value);
* @description: Calling Object function with NaN argument value;
*/

num = NaN;

// CHECK#1
if(typeof num  !== 'number'){
  $ERROR('#1: num = NaN should have number type');
}

obj = Object(num);

//CHECK#2
if (obj.constructor !== Number) {
  $ERROR('#2: Object(Infinity) returns ToObject(Infinity)');
}

//CHECK#3
if (typeof obj!=="object") {
  $ERROR('#2: Object(Infinity) returns ToObject(Infinity)');
}
//
