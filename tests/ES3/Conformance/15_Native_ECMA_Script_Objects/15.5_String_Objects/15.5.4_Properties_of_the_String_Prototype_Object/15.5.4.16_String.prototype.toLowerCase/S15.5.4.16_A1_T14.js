// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.16_A1_T14;
* @section: 15.5.4.16;
* @assertion: String.prototype.toLowerCase();
* @description: Call toLowerCase() function for RegExp object;
*/

var __reg = new RegExp("ABC");
__reg.toLowerCase = String.prototype.toLowerCase;

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (__reg.toLowerCase() !== "/abc/") {
  $ERROR('#1: var __reg = new RegExp("ABC"); __reg.toLowerCase = String.prototype.toLowerCase; __reg.toLowerCase() === "/abc/". Actual: '+__reg.toLowerCase() );
}
//
//////////////////////////////////////////////////////////////////////////////
