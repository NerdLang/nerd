// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.2.4.6_A7;
* @section: 15.2.4.6, 13.2;
* @assertion: Object.prototype.isPrototypeOf can't be used as a constructor;
* @description: Checking if creating new "Object.prototype.isPrototypeOf" fails;
*/

FACTORY = Object.prototype.isPrototypeOf;

try {
  instance = new FACTORY;
  $FAIL('#1: Object.prototype.isPrototypeOf can\'t be used as a constructor');
} catch (e) {
  $PRINT(e);

}
