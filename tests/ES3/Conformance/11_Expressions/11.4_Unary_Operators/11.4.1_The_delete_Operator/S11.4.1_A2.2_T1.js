// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S11.4.1_A2.2_T1;
* @section: 11.4.1;
* @assertion: If GetBase(x) doesn't have a property GetPropertyName(x), return true;
* @description: Checking undeclared variable case;
*/

//CHECK#1
if (delete x !== true) {
  $ERROR('#1: delete x === true');
}

//CHECK#2
if (delete this.x !== true) {
  $ERROR('#2: delete this.x === true');
}
