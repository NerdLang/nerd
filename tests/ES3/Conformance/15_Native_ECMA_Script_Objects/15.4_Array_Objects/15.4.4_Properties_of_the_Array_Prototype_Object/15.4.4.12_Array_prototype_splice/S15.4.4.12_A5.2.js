// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.4.4.12_A5.2;
* @section: 15.4.4.12, 15.2.4.5, 11.4.1;
* @assertion: The length property of splice has the attribute DontDelete;
* @description: Checking use hasOwnProperty, delete;
*/

//CHECK#1
if (Array.prototype.splice.hasOwnProperty('length') !== true) {
  $FAIL('#1: Array.prototype.splice.hasOwnProperty(\'length\') === true. Actual: ' + (Array.prototype.splice.hasOwnProperty('length')));
}

delete Array.prototype.splice.length;

//CHECK#2
if (Array.prototype.splice.hasOwnProperty('length') !== true) {
  $ERROR('#2: delete Array.prototype.splice.length; Array.prototype.splice.hasOwnProperty(\'length\') === true. Actual: ' + (Array.prototype.splice.hasOwnProperty('length')));
}

//CHECK#3
if (Array.prototype.splice.length === undefined) {
  $ERROR('#3: delete Array.prototype.splice.length; Array.prototype.splice.length !== undefined');
}


