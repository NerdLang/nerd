// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.2.1.1_A2_T3;
* @section: 15.2.1.1;
* @assertion: When the Object function is called with one argument value,
* and the value neither is null nor undefined, and is supplied, return ToObject(value);
* @description: Calling Object function with string argument value;
*/

str = 'Luke Skywalker';

// CHECK#1
if (typeof str  !== 'string') {
  $ERROR('#1: "Luke Skywalker" should be a String primitive');
}

obj = Object(str);

//CHECK#2
if (obj.constructor !== String) {
  $ERROR('#2: Object("Luke Skywalker") returns ToObject("Luke Skywalker")');
}

//CHECK#3
if (typeof obj !== "object") {
  $ERROR('#3: Object("Luke Skywalker") returns ToObject("Luke Skywalker")');
}

//CHECK#4
if ((obj != "Luke Skywalker")||(obj === "Luke Skywalker")) {
  $ERROR('#4: Object("Luke Skywalker") returns ToObject("Luke Skywalker")');
}
