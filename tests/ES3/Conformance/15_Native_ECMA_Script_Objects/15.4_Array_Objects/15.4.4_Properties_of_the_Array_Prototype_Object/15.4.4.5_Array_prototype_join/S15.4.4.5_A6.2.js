// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.4.4.5_A6.2;
* @section: 15.4.4.5, 15.2.4.5, 11.4.1;
* @assertion: The length property of join has the attribute DontDelete;
* @description: Checking use hasOwnProperty, delete;
*/

//CHECK#1
if (Array.prototype.join.hasOwnProperty('length') !== true) {
  $FAIL('#1: Array.prototype.join.hasOwnProperty(\'length\') === true. Actual: ' + (Array.prototype.join.hasOwnProperty('length')));
}

delete Array.prototype.join.length;

//CHECK#2
if (Array.prototype.join.hasOwnProperty('length') !== true) {
  $ERROR('#2: delete Array.prototype.join.length; Array.prototype.join.hasOwnProperty(\'length\') === true. Actual: ' + (Array.prototype.join.hasOwnProperty('length')));
}

//CHECK#3
if (Array.prototype.join.length === undefined) {
  $ERROR('#3: delete Array.prototype.join.length; Array.prototype.join.length !== undefined');
}


