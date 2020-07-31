// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S7.2_A1.2_T2;
 * @section: 7.2, 7.5;
 * @assertion: VERTICAL TAB (U+000B) between any two tokens is allowed;
 * @description: Insert real VERTICAL TAB between tokens of var x=1;  
*/

//CHECK#1
varx=1;
if (x !== 1) {
  $ERROR('#1: varx=1; x === 1. Actual: ' + (x));
}

//CHECK#2
eval("var\vx=\v1");
if (x !== 1) {
  $ERROR('#2: var\\vx=\\v1; x === 1. Actual: ' + (x));
}

