// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S11.1.6_A3_T6;
* @section: 11.1.6;
* @assertion: "This" operator only evaluates Expression;
* @description: Applying grouping operator to delete and typeof operators;
*/

//CHECK#1
if (delete (x) !== true) {
  $ERROR('#1: delete (x) === true');
}

//CHECK#2
if (typeof (x) !== "undefined") {
  $ERROR('#2: typeof (x) === "undefined". Actual: ' + (typeof (x)));
}
