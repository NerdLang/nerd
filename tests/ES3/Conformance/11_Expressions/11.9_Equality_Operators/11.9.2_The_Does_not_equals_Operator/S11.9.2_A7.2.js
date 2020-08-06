// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S11.9.2_A7.2;
 * @section: 11.9.2, 11.9.3;
 * @assertion: If Type(x) is Object and Type(y) is Boolean, 
 * return ToPrimitive(x) != y;
 * @description: x is object, y is primitive boolean;
*/

//CHECK#1
if ((new Boolean(true) != true) !== false) {
  $ERROR('#1: (new Boolean(true) != true) === false');
}

//CHECK#2
if ((new Number(1) != true) !== false) {
  $ERROR('#2: (new Number(1) != true) === false');
}

//CHECK#3
if ((new String("1") != true) !== false) {
  $ERROR('#3: (new String("1") != true) === false');
}
