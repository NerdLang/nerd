// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.1.2.4_A2.2;
 * @section: 15.1.2.4, 15.2.4.5, 11.4.1;
 * @assertion: The length property of isNaN has the attribute DontDelete;
 * @description: Checking use hasOwnProperty, delete;
*/

//CHECK#1
if (isNaN.hasOwnProperty('length') !== true) {
  $FAIL('#1: isNaN.hasOwnProperty(\'length\') === true. Actual: ' + (isNaN.hasOwnProperty('length')));
}

delete isNaN.length;

//CHECK#2
if (isNaN.hasOwnProperty('length') !== true) {
  $ERROR('#2: delete isNaN.length; isNaN.hasOwnProperty(\'length\') === true. Actual: ' + (isNaN.hasOwnProperty('length')));
}

//CHECK#3
if (isNaN.length === undefined) {
  $ERROR('#3: delete isNaN.length; isNaN.length !== undefined');
}
