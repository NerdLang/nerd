// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.14_A7;
* @section: 15.5.4.14, 13.2;
* @assertion: String.prototype.split can't be used as constructor;
* @description: Checking if creating the String.prototype.split object fails;
*/

__FACTORY = String.prototype.split;

try {
  __instance = new __FACTORY;
  $FAIL('#1: __FACTORY = String.prototype.split; "__instance = new __FACTORY" lead to throwing exception');
} catch (e) {}
