// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S11.4.6_A3_T1;
* @section: 11.4.6;
* @assertion: Operator +x returns ToNumber(x);
* @description: Type(x) is boolean primitive or Boolean object;
*/

//CHECK#1
if (+false !== 0) {
  $ERROR('#1: +false === 0. Actual: ' + (+false));
}

//CHECK#2
if (+new Boolean(true) !== 1) {
  $ERROR('#2: +new Boolean(true) === 1. Actual: ' + (+new Boolean(true)));
}
