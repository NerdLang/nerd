// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.2.4.2_A9;
* @section: 15.2.4.2;
* @assertion: The Object.prototype.toString.length property has the attribute DontDelete;
* @description: Checknig if deleting of the Object.prototype.toString.length property fails;
*/

//CHECK#0
if (!(Object.prototype.toString.hasOwnProperty('length'))) {
  $FAIL('#0: the Object.prototype.toString has length property');
}

//CHECK#1
if (delete Object.prototype.toString.length) {
  $ERROR('#1: The Object.prototype.toString.length property has the attributes DontDelete');
}

//CHECK#2
if (!(Object.prototype.toString.hasOwnProperty('length'))) {
  $FAIL('#2: The Object.prototype.toString.length property has the attributes DontDelete');
}
