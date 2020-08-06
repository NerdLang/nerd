// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S11.9.4_A3;
 * @section: 11.9.4, 11.9.6;
 * @assertion: Type(x) and Type(y) are Boolean-s. 
 * Return true, if x and y are both true and both false; otherwise, return false;
 * @description: x and y are primitive booleans;
 */

//CHECK#1
if (!(true === true)) {
  $ERROR('#1: true === true');
}

//CHECK#2
if (!(false === false)) {
  $ERROR('#2: false === false');
}

//CHECK#3
if (true === false) {
  $ERROR('#3: true !== false');
}

//CHECK#4
if (false === true) {
  $ERROR('#4: false !== true');
}
