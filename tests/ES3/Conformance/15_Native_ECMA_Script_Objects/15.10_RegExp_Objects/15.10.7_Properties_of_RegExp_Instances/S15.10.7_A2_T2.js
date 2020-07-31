// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.10.7_A2_T2;
* @section: 15.10.7;
* @assertion: RegExp instance has not [[construct]] property;
* @description: Checking if creating "new RegExp" instance fails;
*/

//CHECK#1
try {
  $ERROR('#1.1: new new RegExp throw TypeError. Actual: ' + (new new RegExp));
} catch (e) {
  if ((e instanceof TypeError) !== true) {
    $ERROR('#1.2: new new RegExp throw TypeError. Actual: ' + (e));
  }
}

