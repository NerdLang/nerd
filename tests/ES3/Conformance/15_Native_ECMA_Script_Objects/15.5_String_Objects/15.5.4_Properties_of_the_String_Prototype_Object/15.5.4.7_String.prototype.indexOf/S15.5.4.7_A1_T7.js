// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.7_A1_T7;
* @section: 15.5.4.7;
* @assertion: String.prototype.indexOf(searchString, position);
* @description: Call indexOf(searchString, position) function with undefined argument of string object;
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
//since ToString(undefined) evaluates to "undefined" indexOf(undefined) evaluates to indexOf("undefined",0)
if (String("undefined").indexOf(undefined) !== 0) {
  $ERROR('#1: String("undefined").indexOf(undefined) === 0. Actual: '+String("undefined").indexOf(undefined) ); 
}
//
//////////////////////////////////////////////////////////////////////////////
