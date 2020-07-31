// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S8.7_A6;
* @section: 8.7;
* @assertion: Passing arguments by value differs from by reference and do not change values to be passed;
* @description: Adding original variable with referenced one inside function;
*/

var n = 1;
var m = n;

function addFirst2Second(first, second){first += second;}

addFirst2Second(n, m);

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (m !== 1) {
  $ERROR('#1: var n = 1; var m = n; function addFirst2Second(first, second){first += second;} addFirst2Second(n, m); m === 1. Actual: ' + (m));
}

//
//////////////////////////////////////////////////////////////////////////////

