// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.10_A7;
* @section: 15.5.4.10, 13.2;
* @assertion: String.prototype.match can't be used as constructor;
* @description: Checking if creating "String.prototype.match object" fails;
*/

__FACTORY = String.prototype.match;

try {
  __instance = new __FACTORY;
  $FAIL('#1: __FACTORY = String.prototype.match; __FACTORY = String.prototype.match; __instance = new __FACTORY lead to throwing exception');
} catch (e) {}
