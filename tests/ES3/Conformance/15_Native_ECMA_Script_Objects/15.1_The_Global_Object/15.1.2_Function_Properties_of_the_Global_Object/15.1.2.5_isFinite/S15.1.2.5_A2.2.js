// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.1.2.5_A2.2;
 * @section: 15.1.2.5, 15.2.4.5, 11.4.1;
 * @assertion: The length property of isFinite has the attribute DontDelete;
 * @description: Checking use hasOwnProperty, delete;
*/

//CHECK#1
if (isFinite.hasOwnProperty('length') !== true) {
  $FAIL('#1: isFinite.hasOwnProperty(\'length\') === true. Actual: ' + (isFinite.hasOwnProperty('length')));
}

delete isFinite.length;

//CHECK#2
if (isFinite.hasOwnProperty('length') !== true) {
  $ERROR('#2: delete isFinite.length; isFinite.hasOwnProperty(\'length\') === true. Actual: ' + (isFinite.hasOwnProperty('length')));
}

//CHECK#3
if (isFinite.length === undefined) {
  $ERROR('#3: delete isFinite.length; isFinite.length !== undefined');
}
