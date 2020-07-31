// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.8_A1_T11;
* @section: 15.5.4.8;
* @assertion: String.prototype.lastIndexOf(searchString, position);
* @description: Instance is Date(0) object;
*/

__instance = new Date(0);

__instance.lastIndexOf = String.prototype.lastIndexOf;

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if ((__instance.lastIndexOf('1970')) !== 11) {
  $ERROR('#1: __instance = new Date(0); __instance.lastIndexOf = String.prototype.lastIndexOf;  __instance.lastIndexOf(\'1970\') === 11. Actual: '+(__instance.lastIndexOf('1970')) );
}
//
//////////////////////////////////////////////////////////////////////////////
