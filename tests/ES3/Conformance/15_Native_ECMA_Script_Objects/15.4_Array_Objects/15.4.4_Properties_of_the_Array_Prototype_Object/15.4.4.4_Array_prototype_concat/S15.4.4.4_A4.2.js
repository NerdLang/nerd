// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.4.4.4_A4.2;
* @section: 15.4.4.4, 15.2.4.5, 11.4.1;
* @assertion: The length property of concat has the attribute DontDelete;
* @description: Checking use hasOwnProperty, delete;
*/

//CHECK#1
if (Array.prototype.concat.hasOwnProperty('length') !== true) {
  $FAIL('#1: Array.prototype.concat.hasOwnProperty(\'length\') === true. Actual: ' + (Array.prototype.concat.hasOwnProperty('length')));
}

delete Array.prototype.concat.length;

//CHECK#2
if (Array.prototype.concat.hasOwnProperty('length') !== true) {
  $ERROR('#2: delete Array.prototype.concat.length; Array.prototype.concat.hasOwnProperty(\'length\') === true. Actual: ' + (Array.prototype.concat.hasOwnProperty('length')));
}

//CHECK#3
if (Array.prototype.concat.length === undefined) {
  $ERROR('#3: delete Array.prototype.concat.length; Array.prototype.concat.length !== undefined');
}


