// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S11.4.3_A3.4;
* @section: 11.4.3;
* @assertion: Result of appying "typeof" operator to number is "number";
* @description: typeof (number value) === "number";
*/

//CHECK#1
if (typeof 1 !== "number") {
  $ERROR('#1: typeof 1 === "number". Actual: ' + (typeof 1));
}

//CHECK#2
if (typeof Number.NaN !== "number") {
  $ERROR('#2: typeof NaN === "number". Actual: ' + (typeof NaN));
}

//CHECK#3
if (typeof Number.POSITIVE_INFINITY !== "number") {
  $ERROR('#3: typeof Infinity === "number". Actual: ' + (typeof Infinity));
}

//CHECK#4
if (typeof Number.NEGATIVE_INFINITY !== "number") {
  $ERROR('#4: typeof -Infinity === "number". Actual: ' + (typeof -Infinity));
}

//CHECK#5
if (typeof Math.PI !== "number") {
  $ERROR('#5: typeof Math.PI === "number". Actual: ' + (typeof Math.PI));
}
