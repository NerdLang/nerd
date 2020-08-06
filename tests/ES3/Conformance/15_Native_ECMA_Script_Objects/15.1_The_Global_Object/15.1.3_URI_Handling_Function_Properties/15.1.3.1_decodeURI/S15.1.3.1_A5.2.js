// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.1.3.1_A5.2;
 * @section: 15.1.3.1, 15.2.4.5, 11.4.1;
 * @assertion: The length property of decodeURI has the attribute DontDelete;
 * @description: Checking use hasOwnProperty, delete;
*/

//CHECK#1
if (decodeURI.hasOwnProperty('length') !== true) {
  $FAIL('#1: decodeURI.hasOwnProperty(\'length\') === true. Actual: ' + (decodeURI.hasOwnProperty('length')));
}

delete decodeURI.length;

//CHECK#2
if (decodeURI.hasOwnProperty('length') !== true) {
  $ERROR('#2: delete decodeURI.length; decodeURI.hasOwnProperty(\'length\') === true. Actual: ' + (decodeURI.hasOwnProperty('length')));
}

//CHECK#3
if (decodeURI.length === undefined) {
  $ERROR('#3: delete decodeURI.length; decodeURI.length !== undefined');
}



