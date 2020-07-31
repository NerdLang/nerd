// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.12_A1_T1;
* @section: 15.5.4.12;
* @assertion: String.prototype.search (regexp);
* @description: Argument is true, and instance is object;
*/

__instance = new Object(true);

__instance.search = String.prototype.search;

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (__instance.search(true) !== 0) {
  $ERROR('#1: __instance = new Object(true); __instance.search = String.prototype.search;  __instance.search(true) === 0. Actual: '+__instance.search(true) );
}
//
//////////////////////////////////////////////////////////////////////////////
