// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4_A2;
* @section: 15.5.4;
* @assertion: The String prototype object is itself a String object whose value is an empty string;
* @description: Checking String.prototype;
*/


//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (String.prototype !="") {
  $ERROR('#1: String.prototype =="". Actual: String.prototype =='+String.prototype ); 
}
//
//////////////////////////////////////////////////////////////////////////////
