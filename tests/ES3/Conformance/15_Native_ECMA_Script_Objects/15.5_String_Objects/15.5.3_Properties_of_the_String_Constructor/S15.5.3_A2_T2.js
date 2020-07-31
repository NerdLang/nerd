// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.3_A2_T2;
* @section: 15.5.3, 15.5.4;
* @assertion: The value of the internal [[Prototype]] property of the String constructor is the Function prototype object;
* @description: Add custom property to Function.prototype and check it at String; 
*/

Function.prototype.indicator = 1;

//////////////////////////////////////////////////////////////////////////////
// CHECK#
if (String.indicator !== 1) {
  $ERROR('#1: Function.prototype.indicator = 1; String.indicator === 1. Actual: String.indicator ==='+String.indicator ); 
}
//
//////////////////////////////////////////////////////////////////////////////
