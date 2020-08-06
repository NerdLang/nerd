// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.13_A2_T1;
* @section: 15.5.4.13;
* @assertion: String.prototype.slice (start, end) returns a string value(not object);
* @description: Checking type of slice();
*/

__string = new String("this is a string object");

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (typeof __string.slice() !== "string") {
  $ERROR('#1: __string = new String("this is a string object"); typeof __string.slice() === "string". Actual: '+typeof __string.slice() );
}
//
//////////////////////////////////////////////////////////////////////////////
