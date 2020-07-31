// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.4.4.3_A2_T1;
 * @section: 15.4.4.3;
 * @assertion: The toLocalString function is not generic. 
 * it throws a TypeError exception if its this value is not an Array object; 
 * @description: {}.toLocaleString = Array.prototype.toLocaleString; 
*/

var obj = {};
obj.toLocaleString = Array.prototype.toLocaleString;

//CHECK#1
try {
  obj.toLocaleString();
  $ERROR('#1.1: var obj = {}; obj.toLocaleString = Array.prototype.toLocaleString; obj.toLocaleString() throw TypeError. Actual: ' + (obj.toLocaleString()));
} catch(e) {
  if ((e instanceof TypeError) !== true) {
    $ERROR('#1.2: var obj = {}; obj.toLocaleString = Array.prototype.toLocaleString; obj.toLocaleString() throw TypeError. Actual: ' + (e));
  }
}

obj[0] = 1;
obj.length = 1;

//CHECK#2
try {
  obj.toLocaleString();
  $ERROR('#2.1: var obj = {}; obj.toLocaleString = Array.prototype.toLocaleString; obj[0] = 1; obj.length = 1; obj.toLocaleString() throw TypeError. Actual: ' + (obj.toLocaleString()));
} catch(e) {
  if ((e instanceof TypeError) !== true) {
    $ERROR('#2.2: var obj = {}; obj.toLocaleString = Array.prototype.toLocaleString; obj[0] = 1; obj.length = 1; obj.toLocaleString() throw TypeError. Actual: ' + (e));
  }
}
