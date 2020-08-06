// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.11_A7;
* @section: 15.5.4.11, 13.2;
* @assertion: String.prototype.replace can't be used as constructor;
* @description: Checking if creating the String.prototype.replace object fails;
*/

__FACTORY = String.prototype.replace;

try {
  __instance = new __FACTORY;
  $FAIL('#1: __FACTORY = String.prototype.replace; "__instance = new __FACTORY" lead to throwing exception');
} catch (e) {}
