// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.2.4_A1_T2;
 * @section: 15.2.4, 8.6.2;
 * @assertion: Object prototype object has not prototype;
 * @description: Since the Object prototype object has not prototype, deleted toString method can not be found in prototype chain;
*/

//CHECK#1
if (Object.prototype.toString() == false) {
  $ERROR('#1: Object prototype object has not prototype');
}

delete Object.prototype.toString;

// CHECK#2
try {
  Object.prototype.toString();
  $ERROR('#2: Object prototype object has not prototype');
} catch (e) {
  ;
}
//
