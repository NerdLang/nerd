// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.7_A2_T3;
* @section: 15.5.4.7;
* @assertion: When length of searchString less than length of ToString(this) -1 returns;
* @description: Call "abcd".indexOf("abcdab",99) and check result;
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if ("abcd".indexOf("abcdab",99)!==-1) {
  $ERROR('#1: "abcd".indexOf("abcdab",99)===-1. Actual: '+("abcd".indexOf("abcdab",99))); 
}
//
//////////////////////////////////////////////////////////////////////////////
