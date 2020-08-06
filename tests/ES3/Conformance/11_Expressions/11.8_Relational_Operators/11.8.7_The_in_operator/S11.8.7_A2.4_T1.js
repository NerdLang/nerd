// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S11.8.7_A2.4_T1;
 * @section: 11.8.7;
 * @assertion: First expression is evaluated first, and then second expression;
 * @description: Checking with "=";
*/

//CHECK#1 
var NUMBER = 0;
if ((NUMBER = Number, "MAX_VALUE") in NUMBER !== true) {
  $ERROR('#1: var NUMBER = 0; (NUMBER = Number, "MAX_VALUE") in NUMBER === true');
}

//CHECK#2
var max_value = "MAX_VALUE"; 
if (max_value in (max_value = "none", Number) !== true) {
  $ERROR('#2: var max_value = "MAX_VALUE"; max_value in (max_value = "none", Number) === true');
}

