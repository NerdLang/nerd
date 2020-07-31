// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.4.2.1_A1.3_T1;
 * @section: 15.4.2.1;
 * @assertion: This description of Array constructor applies if and only if 
 * the Array constructor is given no arguments or at least two arguments;
 * @description: Checking case when Array constructor is given one argument;
*/

var x = new Array(2);

//CHECK#1
if (x.length === 1) {
  $ERROR('#1: var x = new Array(2); x.length !== 1');
}

//CHECK#2
if (x[0] === 2) {
  $ERROR('#2: var x = new Array(2); x[0] !== 2');
}
