// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.10.3.1_A1_T3;
* @section: 15.10.3.1;
* @assertion: If pattern is an object R whose [[Class]] property is "RegExp" and flags is undefined, then return R unchanged;
* @description: R is new RegExp() and instance is RegExp(R, x), where x is undefined variable;
*/

__re = new RegExp();
__instance = RegExp(__re, x);
__re.indicator = 1;

//CHECK#1
if (__instance.indicator !== 1) {
	$ERROR('#1: __re = new RegExp(); __instance = RegExp(__re, x); __re.indicator = 1; __instance.indicator === 1. Actual: ' + (__instance.indicator));
}

var x;
