// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S11.6.1_A4_T3;
* @section: 11.6.1, 11.6.3;
* @assertion: The result of an addition is determined using the rules of IEEE 754 double-precision arithmetics; 
* @description: The sum of two infinities of the same sign is the infinity of that sign;
*/

//CHECK#1
if (Number.POSITIVE_INFINITY + Number.POSITIVE_INFINITY !== Number.POSITIVE_INFINITY ) {
  $ERROR('#1: Infinity + Infinity === Infinity. Actual: ' + (Infinity + Infinity));
}

//CHECK#2
if (Number.NEGATIVE_INFINITY + Number.NEGATIVE_INFINITY !== Number.NEGATIVE_INFINITY ) {
  $ERROR('#2: -Infinity + -Infinity === -Infinity. Actual: ' + (-Infinity + -Infinity));
}



