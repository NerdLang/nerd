// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.15_A3_T7;
* @section: 15.5.4.15;
* @assertion: String.prototype.substring (start, end) can be applied to non String object instance and 
* returns a string value(not object);
* @description: Apply String.prototype.substring to Object instance. Call instance.substring(...).substring(...);
*/

__instance = function(){};
 
__instance.substring = String.prototype.substring;

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (__instance.substring(8,Infinity).substring(-Infinity,1) !== " ") {
  $ERROR('#1: __instance = function(){}; __instance.substring = String.prototype.substring;  __instance.substring(8,Infinity).substring(-Infinity,1) === " ". Actual: '+__instance.substring(8,Infinity).substring(-Infinity,1) );
}
//
//////////////////////////////////////////////////////////////////////////////
