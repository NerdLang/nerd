// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S7.2_A3.2_T2;
 * @section: 7.2, 7.4;
 * @assertion: Single line comment can contain VERTICAL TAB (U+000B);
 * @description: Use real VERTICAL TAB;
 */

//CHECK#1
var x = 0;
//singlelinecommentx = 1;
if (x !== 0) {
  $ERROR('#1: var x = 0; //singlelinecommentx = 1; x === 0. Actual: ' + (x));
}
