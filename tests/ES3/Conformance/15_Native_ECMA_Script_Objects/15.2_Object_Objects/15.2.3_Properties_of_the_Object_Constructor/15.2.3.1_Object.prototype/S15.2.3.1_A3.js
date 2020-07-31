// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.2.3.1_A3;
* @section: 15.2.3.1, 15.2.4;
* @assertion: The Object.prototype property has the attribute DontDelete;
* @description: Checking if deleting "Object.prototype" property fails;
*/

delete Object.prototype;

//CHECK#2
if (!(Object.hasOwnProperty('prototype'))) {
  $ERROR('#2: the Object.prototype property has the attributes DontDelete.');
}
