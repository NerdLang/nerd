// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.13_A1_T15;
* @section: 15.5.4.13;
* @assertion: String.prototype.slice (start, end);
* @description: Call slice without arguments. Instance is Number with prototype.slice = String.prototype.slice;
*/

var __num = 11.001002;

Number.prototype.slice = String.prototype.slice;


//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (__num.slice()!=="11.001002") {
  $ERROR('#1: var __num = 11.001002; Number.prototype.slice = String.prototype.slice; __num.slice()==="11.001002". Actual: '+__num.slice());
}
//
//////////////////////////////////////////////////////////////////////////////
