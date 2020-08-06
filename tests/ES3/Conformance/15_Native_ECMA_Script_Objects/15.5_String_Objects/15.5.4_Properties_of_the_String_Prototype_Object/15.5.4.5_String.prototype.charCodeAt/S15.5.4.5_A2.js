// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.5_A2;
* @section: 15.5.4.5;
* @assertion: When String.prototype.charCodeAt(pos) calls if ToInteger(pos) less than 0 the NaN returns;
* @description: Call charCodeAt(pos) with negative pos;
*/

function __FACTORY(){};

__FACTORY.prototype.charCodeAt = String.prototype.charCodeAt;

__instance = new __FACTORY;

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (!isNaN(__instance.charCodeAt(-1))) {
  $ERROR('#1: function __FACTORY(){}; __FACTORY.prototype.charCodeAt = String.prototype.charCodeAt; __instance = new __FACTORY; isNaN(__instance.charCodeAt(-1)) return true. Actual: '+isNaN(__instance.charCodeAt(-1)));
}
//
//////////////////////////////////////////////////////////////////////////////
