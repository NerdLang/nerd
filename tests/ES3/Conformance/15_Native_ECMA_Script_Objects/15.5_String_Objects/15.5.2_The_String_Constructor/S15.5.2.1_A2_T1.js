// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.2.1_A2_T1;
* @section: 15.5.2.1, 15.5.3.1;
* @assertion: The [[Prototype]] property of the newly constructed object is set to the original String prototype object;
* @description: Creating string object with "new String(string)" to check prototype;
*/

var __str__obj = new String("abba");

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (!(String.prototype.isPrototypeOf(__str__obj))) {
  $ERROR('#1: var __str__obj = new String("abba"); String.prototype.isPrototypeOf(__str__obj)===true');
}
//
//////////////////////////////////////////////////////////////////////////////


