// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.4.3_A2.2;
 * @section: 15.4.3, 15.2.4.5, 11.4.1;
 * @assertion: The length property of Array has the attribute DontDelete;
 * @description: Checking use hasOwnProperty, delete;
*/

//CHECK#1
if (Array.hasOwnProperty('length') !== true) {
  $FAIL('#1: Array.hasOwnProperty(\'length\') === true. Actual: ' + (Array.hasOwnProperty('length')));
}

delete Array.length;

//CHECK#2
if (Array.hasOwnProperty('length') !== true) {
  $ERROR('#2: delete Array.length; Array.hasOwnProperty(\'length\') === true. Actual: ' + (Array.hasOwnProperty('length')));
}

//CHECK#3
if (Array.length === undefined) {
  $ERROR('#3: delete Array.length; Array.length !== undefined');
}


