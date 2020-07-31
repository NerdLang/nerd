// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.4.4.7_A6.2;
* @section: 15.4.4.7, 15.2.4.5, 11.4.1;
* @assertion: The length property of push has the attribute DontDelete;
* @description: Checking use hasOwnProperty, delete;
*/

//CHECK#1
if (Array.prototype.push.hasOwnProperty('length') !== true) {
  $FAIL('#1: Array.prototype.push.hasOwnProperty(\'length\') === true. Actual: ' + (Array.prototype.push.hasOwnProperty('length')));
}

delete Array.prototype.push.length;

//CHECK#2
if (Array.prototype.push.hasOwnProperty('length') !== true) {
  $ERROR('#2: delete Array.prototype.push.length; Array.prototype.push.hasOwnProperty(\'length\') === true. Actual: ' + (Array.prototype.push.hasOwnProperty('length')));
}

//CHECK#3
if (Array.prototype.push.length === undefined) {
  $ERROR('#3: delete Array.prototype.push.length; Array.prototype.push.length !== undefined');
}


