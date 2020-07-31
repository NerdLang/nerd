// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.4_A3;
* @section: 15.5.4.4;
* @assertion: When String.prototype.charAt(pos) calls if ToInteger(pos) not less than ToString(this value) the empty string returns;
* @description: pos is bigger of string length;
*/

__instance = new String("ABC");

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (__instance.charAt(3) !== "") {
  $ERROR('#1: __instance = new String("ABC"); __instance.charAt(3) === "". Actual: __instance.charAt(3) ==='+__instance.charAt(3) ); 
}
//
//////////////////////////////////////////////////////////////////////////////
