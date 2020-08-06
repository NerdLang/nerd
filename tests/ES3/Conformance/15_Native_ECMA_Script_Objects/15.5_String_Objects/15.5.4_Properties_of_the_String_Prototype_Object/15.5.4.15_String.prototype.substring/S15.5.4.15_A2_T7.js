// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.15_A2_T7;
* @section: 15.5.4.15;
* @assertion: String.prototype.substring (start, end) returns a string value(not object);
* @description: start is tested_string.length, end is tested_string.length;
*/

__string = new String("this is a string object");

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (__string.substring(__string.length, __string.length) !== "") {
  $ERROR('#1: __string = new String("this is a string object"); __string.substring(__string.length, __string.length) === "". Actual: '+__string.substring(__string.length, __string.length) );
}
//
//////////////////////////////////////////////////////////////////////////////
