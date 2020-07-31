// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.15_A2_T5;
* @section: 15.5.4.15;
* @assertion: String.prototype.substring (start, end) returns a string value(not object);
* @description: start is Infinity, end is Infinity;
*/

__string = new String("this is a string object");

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (__string.substring(Infinity, Infinity) !== "") {
  $ERROR('#1: __string = new String("this is a string object"); __string.substring(Infinity, Infinity) === "". Actual: '+__string.substring(Infinity, Infinity) );
}
//
//////////////////////////////////////////////////////////////////////////////
