// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.1.3.2_A5.2;
 * @section: 15.1.3.2, 15.2.4.5, 11.4.1;
 * @assertion: The length property of decodeURIComponent has the attribute DontDelete;
 * @description: Checking use hasOwnProperty, delete;
*/

//CHECK#1
if (decodeURIComponent.hasOwnProperty('length') !== true) {
  $FAIL('#1: decodeURIComponent.hasOwnProperty(\'length\') === true. Actual: ' + (decodeURIComponent.hasOwnProperty('length')));
}

delete decodeURIComponent.length;

//CHECK#2
if (decodeURIComponent.hasOwnProperty('length') !== true) {
  $ERROR('#2: delete decodeURIComponent.length; decodeURIComponent.hasOwnProperty(\'length\') === true. Actual: ' + (decodeURIComponent.hasOwnProperty('length')));
}

//CHECK#3
if (decodeURIComponent.length === undefined) {
  $ERROR('#3: delete decodeURIComponent.length; decodeURIComponent.length !== undefined');
}



