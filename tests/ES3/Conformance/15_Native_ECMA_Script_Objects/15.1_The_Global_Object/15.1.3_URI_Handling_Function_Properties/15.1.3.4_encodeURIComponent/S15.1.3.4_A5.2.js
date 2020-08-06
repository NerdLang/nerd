// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.1.3.4_A5.2;
 * @section: 15.1.3.4, 15.2.4.5, 11.4.1;
 * @assertion: The length property of encodeURIComponent has the attribute DontDelete;
 * @description: Checking use hasOwnProperty, delete;
*/

//CHECK#1
if (encodeURIComponent.hasOwnProperty('length') !== true) {
  $FAIL('#1: encodeURIComponent.hasOwnProperty(\'length\') === true. Actual: ' + (encodeURIComponent.hasOwnProperty('length')));
}

delete encodeURIComponent.length;

//CHECK#2
if (encodeURIComponent.hasOwnProperty('length') !== true) {
  $ERROR('#2: delete encodeURIComponent.length; encodeURIComponent.hasOwnProperty(\'length\') === true. Actual: ' + (encodeURIComponent.hasOwnProperty('length')));
}

//CHECK#3
if (encodeURIComponent.length === undefined) {
  $ERROR('#3: delete encodeURIComponent.length; encodeURIComponent.length !== undefined');
}



