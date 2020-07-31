// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.2.4.4_A7;
* @section: 15.2.4.4, 13.2;
* @assertion: Object.prototype.valueOf can't be used as a constructor;
* @description: Checking if creating "new Object.prototype.valueOf" fails;
*/

FACTORY = Object.prototype.valueOf;

try {
  instance = new FACTORY;
  $FAIL('#1: Object.prototype.valueOf can\'t be used as a constructor');
} catch (e) {
  $PRINT(e);

}
