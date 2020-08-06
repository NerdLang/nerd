// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S11.9.2_A7.6;
 * @section: 11.9.2, 11.9.3;
 * @assertion: If Type(x) is Object and Type(y) is String, 
 * return ToPrimitive(x) != y;
 * @description: x is object, y is primitive string;
 */

//CHECK#1
if ((new Boolean(true) != "1") !== false) {
  $ERROR('#1: (new Boolean(true) != "1") === false');
}

//CHECK#2
if ((new Number(-1) != "-1") !== false) {
  $ERROR('#2: (new Number(-1) != "-1") === false');
}

//CHECK#3
if ((new String("x") != "x") !== false) {
  $ERROR('#3: (new String("x") != "x") === false');
}
