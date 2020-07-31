// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S9.2_A1_T2;
 * @section: 9.2, 11.4.9;
 * @assertion: Result of boolean conversion from undefined value is false;
 * @description: Undefined, void and others are converted to Boolean by implicit transformation;
*/

// CHECK#1
if (!(undefined) !== true) {
  $ERROR('#1: !(undefined) === true. Actual: ' + (!(undefined)));
}

// CHECK#2
if (!(void 0) !== true) {
  $ERROR('#2: !(undefined) === true. Actual: ' + (!(undefined)));
}

// CHECK#3
if (!(eval("var x")) !== true) {
  $ERROR('#3: !(eval("var x")) === true. Actual: ' + (!(eval("var x"))));
}
