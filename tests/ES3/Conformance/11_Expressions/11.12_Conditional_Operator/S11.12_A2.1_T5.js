// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S11.12_A2.1_T5;
* @section: 11.12, 8.7.1, 16;
* @assertion: Operator x ? y : z uses GetValue;
* @description: If ToBoolean(x) is true and GetBase(z) is null, return y;
*/

//CHECK#1
var y = new Object();
if ((true ? y : z) !== y) {
  $ERROR('#1: var y = new Object(); (true ? y : z) === y');
}
