// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S8.4_A12;
* @section: 8.4, 7.8.4;
* @assertion: Assignment to string literal calls String constructor;
* @description: Check constructor of simple assigned variable;
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
var str = "rock'n'roll";
if (str.constructor !== String){
  $ERROR('#1: var str = "rock\'n\'roll"; str.constructor === String. Actual: ' + (str.constructor));
}
//
//////////////////////////////////////////////////////////////////////////////
