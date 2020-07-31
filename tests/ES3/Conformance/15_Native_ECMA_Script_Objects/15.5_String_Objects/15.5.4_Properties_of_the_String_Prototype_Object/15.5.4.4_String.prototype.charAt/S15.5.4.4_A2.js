// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.4_A2;
* @section: 15.5.4.4;
* @assertion: When String.prototype.charAt(pos) calls if ToInteger(pos) less than 0 the empty string returns;
* @description: Call charAt(pos) with negative pos;
*/

function __FACTORY(){};

__FACTORY.prototype.charAt = String.prototype.charAt;

__instance = new __FACTORY;

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (__instance.charAt(-1) !== "") {
  $ERROR('#1: __instance.charAt(-1) === "". Actual: __instance.charAt(-1) ==='+__instance.charAt(-1) ); 
}
//
//////////////////////////////////////////////////////////////////////////////
