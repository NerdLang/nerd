// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S11.12_A4_T4;
* @section: 11.12;
* @assertion: If ToBoolean(x) is true, return y;
* @description: Type(x) or Type(y) is changed between null and undefined;
*/

//CHECK#1
if ((true ? undefined : true) !== undefined) {
  $ERROR('#1: (true ? undefined : true) === undefined');
}

//CHECK#2
if ((true ? null : true) !== null) {
  $ERROR('#2: (true ? null : true) === null');
}
