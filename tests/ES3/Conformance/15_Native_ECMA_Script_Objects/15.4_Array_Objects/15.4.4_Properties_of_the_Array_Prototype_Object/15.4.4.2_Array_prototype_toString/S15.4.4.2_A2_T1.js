// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.4.4.2_A2_T1;
 * @section: 15.4.4.2;
 * @assertion: The toString function is not generic. 
 * it throws a TypeError exception if its this value is not an Array object;
 * @description: {}.toString = Array.prototype.toString; 
*/

var obj = {};
obj.toString = Array.prototype.toString;

//CHECK#1
try {
  obj.toString();
  $ERROR('#1.1: var obj = {}; obj.toString = Array.prototype.toString; obj.toString() throw TypeError. Actual: ' + (obj.toString()));
} catch(e) {
  if ((e instanceof TypeError) !== true) {
    $ERROR('#1.2: var obj = {}; obj.toString = Array.prototype.toString; obj.toString() throw TypeError. Actual: ' + (e));
  }
}

obj[0] = 1;
obj.length = 1;

//CHECK#2
try {
  obj.toString();
  $ERROR('#2.1: var obj = {}; obj.toString = Array.prototype.toString; obj[0] = 1; obj.length = 1; obj.toString() throw TypeError. Actual: ' + (obj.toString()));
} catch(e) {
  if ((e instanceof TypeError) !== true) {
    $ERROR('#2.2: var obj = {}; obj.toString = Array.prototype.toString; obj[0] = 1; obj.length = 1; obj.toString() throw TypeError. Actual: ' + (e));
  }
}
