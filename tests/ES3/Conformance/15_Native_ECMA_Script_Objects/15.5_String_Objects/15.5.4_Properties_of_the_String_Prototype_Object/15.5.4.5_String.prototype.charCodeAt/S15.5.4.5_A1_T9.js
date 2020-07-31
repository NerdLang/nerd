// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.5_A1_T9;
* @section: 15.5.4.5;
* @assertion: String.prototype.charCodeAt(pos);
* @description: Call charCodeAt() function with function(){}() argument of string object;
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
//since ToInteger(undefined) evaluates to 0 charCodeAt() evaluates to charCodeAt(0)
if (new String(42).charCodeAt(function(){}()) !== 0x34) {
  $ERROR('#1: new String(42).charCodeAt(function(){}()) === 0x34. Actual: new String(42).charCodeAt(function(){}()) ==='+new String(42).charCodeAt(function(){}()) ); 
}
//
//////////////////////////////////////////////////////////////////////////////
