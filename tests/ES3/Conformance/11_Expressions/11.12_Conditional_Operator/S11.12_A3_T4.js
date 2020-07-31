// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S11.12_A3_T4;
* @section: 11.12;
* @assertion: If ToBoolean(x) is false, return z;
* @description: Type(x) or Type(y) is changed between null and undefined;
*/

//CHECK#1
if ((false ? true : undefined) !== undefined) {
  $ERROR('#1: (false ? true : undefined) === undefined');
}

//CHECK#2
if ((false ? true : null) !== null) {
  $ERROR('#2: (false ? true : null) === null');
}
