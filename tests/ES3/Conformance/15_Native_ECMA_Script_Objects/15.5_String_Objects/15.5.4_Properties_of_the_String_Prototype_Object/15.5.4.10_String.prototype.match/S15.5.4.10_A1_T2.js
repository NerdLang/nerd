// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.10_A1_T2;
* @section: 15.5.4.10;
* @assertion: String.prototype.match (regexp);
* @description: Argument is function that return boolean, and instance is Boolean object;
*/

__instance = new Boolean;

__instance.match = String.prototype.match;

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (__instance.match(function(){return false;}())[0] !== "false") {
  $ERROR('#1: __instance = new Boolean; __instance.match = String.prototype.match;  __instance.match(function(){return false;}())[0] === "false". Actual: '+__instance.match(function(){return false;}())[0] );
}
//
//////////////////////////////////////////////////////////////////////////////
