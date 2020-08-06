// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.3.4.2_A7;
* @section: 15.3.4.2, 13.2;
* @assertion: Function.prototype.toString can't be used as constructor;
* @description: Checking if creating "new Function.prototype.toString" fails;
*/

FACTORY = Function.prototype.toString;

try {
  instance = new FACTORY;
  $FAIL('#1: Function.prototype.toString can\'t be used as constructor');
} catch (e) {
  $PRINT(e);
}
