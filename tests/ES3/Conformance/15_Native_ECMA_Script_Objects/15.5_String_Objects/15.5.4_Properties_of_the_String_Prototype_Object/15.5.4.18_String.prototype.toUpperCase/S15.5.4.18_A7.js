// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.18_A7;
* @section: 15.5.4.18, 13.2;
* @assertion: String.prototype.toUpperCase can't be used as constructor;
* @description: Checking if creating the String.prototype.toUpperCase object fails;
*/

__FACTORY = String.prototype.toUpperCase;

try {
  __instance = new __FACTORY;
  $FAIL('#1: __FACTORY = String.prototype.toUpperCase; "__instance = new __FACTORY" lead to throwing exception');
} catch (e) {}
