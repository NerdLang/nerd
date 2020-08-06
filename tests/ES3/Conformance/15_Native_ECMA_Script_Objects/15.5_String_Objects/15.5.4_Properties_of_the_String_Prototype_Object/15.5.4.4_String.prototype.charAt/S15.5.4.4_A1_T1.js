// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.4_A1_T1;
* @section: 15.5.4.4;
* @assertion: String.prototype.charAt(pos);
* @description: pos is false and true, and instance is object;
*/

__instance = new Object(42);

__instance.charAt = String.prototype.charAt;

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (__instance.charAt(false)+__instance.charAt(true) !== "42") {
  $ERROR('#1: __instance = new Object(42); __instance.charAt = String.prototype.charAt;  __instance = new Object(42); __instance.charAt = String.prototype.charAt; __instance.charAt(false)+__instance.charAt(true) === "42". Actual: '+__instance.charAt(false)+__instance.charAt(true) ); 
}
//
//////////////////////////////////////////////////////////////////////////////
