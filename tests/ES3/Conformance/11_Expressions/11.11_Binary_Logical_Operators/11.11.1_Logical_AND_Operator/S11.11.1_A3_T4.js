// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S11.11.1_A3_T4;
* @section: 11.11.1;
* @assertion: If ToBoolean(x) is false, return x;
* @description: Type(x) or Type(y) is changed between null and undefined;
*/

//CHECK#1
if ((undefined && true) !== undefined) {
  $ERROR('#1: (undefined && true) === undefined');
}

//CHECK#2
if ((null && false) !== null) {
  $ERROR('#2: (null && false) === null');
}
