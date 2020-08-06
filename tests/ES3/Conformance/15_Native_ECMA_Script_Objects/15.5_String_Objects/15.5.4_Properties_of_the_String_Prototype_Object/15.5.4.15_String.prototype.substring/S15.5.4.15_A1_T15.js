// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.15_A1_T15;
* @section: 15.5.4.15;
* @assertion: String.prototype.substring (start, end);
* @description: Call substring without arguments. Instance is Number with prototype.substring = String.prototype.substring;
*/

var __num = 11.001002;

Number.prototype.substring = String.prototype.substring;


//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (__num.substring()!=="11.001002") {
  $ERROR('#1: var __num = 11.001002; Number.prototype.substring = String.prototype.substring; __num.substring()==="11.001002". Actual: '+__num.substring());
}
//
//////////////////////////////////////////////////////////////////////////////
