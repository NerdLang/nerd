// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.16_A1_T1;
* @section: 15.5.4.16;
* @assertion: String.prototype.toLowerCase();
* @description: Arguments is true, and instance is object;
*/

__instance = new Object(true);

__instance.toLowerCase = String.prototype.toLowerCase;

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (__instance.toLowerCase() !== "true") {
  $ERROR('#1: __instance = new Object(true); __instance.toLowerCase = String.prototype.toLowerCase;  __instance.toLowerCase() === "true". Actual: '+__instance.toLowerCase() );
}
//
//////////////////////////////////////////////////////////////////////////////
