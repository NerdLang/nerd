// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.7.3.1_A1_T2;
 * @section: 15.7.3.1;
 * @assertion: The Number property "prototype" has { DontEnum, DontDelete, ReadOnly } attributes;
 * @description: Checking if deleting the Number.prototype property fails;
*/

// CHECK#1
if (delete Number.prototype !== false) {
  $ERROR('#1: The Number.prototype property has the attributes DontDelete');
}

if (!Number.hasOwnProperty('prototype')) {
  $FAIL('#2: The Number.prototype property has the attributes DontDelete');
}
