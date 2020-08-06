// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S11.1.6_A3_T1;
* @section: 11.1.6;
* @assertion: "This" operator only evaluates Expression;
* @description: Applying grouping operator to Boolean;
*/

// Check for Boolean

//CHECK#1
if ((true) !== true) {
  $ERROR('#1: (true) === true');
}

//CHECK#2
var x = new Boolean(true);
if ((x) !== x) {
  $ERROR('#2: var x = new Boolean(true); (x) === x. Actual: ' + ((x)));
}
