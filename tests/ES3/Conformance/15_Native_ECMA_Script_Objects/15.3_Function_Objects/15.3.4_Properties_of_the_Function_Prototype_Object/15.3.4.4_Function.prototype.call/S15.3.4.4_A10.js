// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.3.4.4_A10;
* @section: 15.3.4.4;
* @assertion: The Function.prototype.call.length property has the attribute ReadOnly;
* @description: Checking if varying the Function.prototype.call.length property fails;
*/

//CHECK#1
if (!(Function.prototype.call.hasOwnProperty('length'))) {
  $FAIL('#1: the Function.prototype.call has length property.');
}

obj = Function.prototype.call.length;

Function.prototype.call.length = function(){return "shifted";};

//CHECK#2
if (Function.prototype.call.length !== obj) {
  $ERROR('#2: the Function.prototype.call length property has the attributes ReadOnly.');
}
