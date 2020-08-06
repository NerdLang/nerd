// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.4.4.10_A5.2;
* @section: 15.4.4.10, 15.2.4.5, 11.4.1;
* @assertion: The length property of slice has the attribute DontDelete;
* @description: Checking use hasOwnProperty, delete;
*/

//CHECK#1
if (Array.prototype.slice.hasOwnProperty('length') !== true) {
  $FAIL('#1: Array.prototype.slice.hasOwnProperty(\'length\') === true. Actual: ' + (Array.prototype.slice.hasOwnProperty('length')));
}

delete Array.prototype.slice.length;

//CHECK#2
if (Array.prototype.slice.hasOwnProperty('length') !== true) {
  $ERROR('#2: delete Array.prototype.slice.length; Array.prototype.slice.hasOwnProperty(\'length\') === true. Actual: ' + (Array.prototype.slice.hasOwnProperty('length')));
}

//CHECK#3
if (Array.prototype.slice.length === undefined) {
  $ERROR('#3: delete Array.prototype.slice.length; Array.prototype.slice.length !== undefined');
}


