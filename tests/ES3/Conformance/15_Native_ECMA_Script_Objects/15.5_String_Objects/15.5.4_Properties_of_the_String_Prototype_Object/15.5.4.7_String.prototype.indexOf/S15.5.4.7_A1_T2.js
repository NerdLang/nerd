// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.7_A1_T2;
* @section: 15.5.4.7;
* @assertion: String.prototype.indexOf(searchString, position);
* @description: Arguments are boolean equation, function and null, and instance is Boolean object;
*/

__instance = new Boolean;

__instance.indexOf = String.prototype.indexOf;

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (__instance.indexOf("A"!=="\u0041", function(){return 0;}(),null) !== 0) {
  $ERROR('#1: __instance = new Boolean; __instance.indexOf = String.prototype.indexOf;  __instance.indexOf("A"!=="\\u0041", function(){return 0;}(),null) === 0. Actual: '+__instance.indexOf("A"!=="\u0041", function(){return 0;}(),null) ); 
}
//
//////////////////////////////////////////////////////////////////////////////
