// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S11.11.1_A2.1_T4;
* @section: 11.11.1, 8.7.1, 16;
* @assertion: Operator x && y uses GetValue;
* @description: If ToBoolean(x) is false and GetBase(y) is null, return false;
*/

//CHECK#1
if ((false && x) !== false) {
  $ERROR('#1: (false && x) === false');
}
