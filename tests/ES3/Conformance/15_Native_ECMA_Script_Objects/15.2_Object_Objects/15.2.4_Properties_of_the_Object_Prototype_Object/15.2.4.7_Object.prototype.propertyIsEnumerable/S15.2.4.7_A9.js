// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.2.4.7_A9;
* @section: 15.2.4.7;
* @assertion: The Object.prototype.propertyIsEnumerable.length property has the attribute DontDelete;
* @description: Checking if deleting the Object.prototype.propertyIsEnumerable.length property fails;
*/

//CHECK#0
if (!(Object.prototype.propertyIsEnumerable.hasOwnProperty('length'))) {
  $FAIL('#0: the Object.prototype.propertyIsEnumerable has length property');
}

//CHECK#1
if (delete Object.prototype.propertyIsEnumerable.length) {
  $ERROR('#1: The Object.prototype.propertyIsEnumerable.length property has the attributes DontDelete');
}
//
