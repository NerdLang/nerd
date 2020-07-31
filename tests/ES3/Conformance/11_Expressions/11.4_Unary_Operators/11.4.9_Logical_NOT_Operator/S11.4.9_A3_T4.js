// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S11.4.9_A3_T4;
* @section: 11.4.9;
* @assertion: Operator !x returns !ToBoolean(x);
* @description: Type(x) is undefined or null;
*/

//CHECK#1
if (!void 0 !== true) {
  $ERROR('#1: !void 0 === true');
}

//CHECK#2
if (!null !== true) {
  $ERROR('#2: !null === true');
}
