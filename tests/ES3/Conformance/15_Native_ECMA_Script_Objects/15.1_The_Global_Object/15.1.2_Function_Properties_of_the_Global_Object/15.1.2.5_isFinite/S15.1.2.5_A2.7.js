// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.1.2.5_A2.7;
* @section: 15.1.2.5, 11.2.2;
* @assertion: The isFinite property can't be used as constructor;
* @description: If property does not implement the internal [[Construct]] method, throw a TypeError exception;
*/

//CHECK#1

try {
  new isFinite();
  $ERROR('#1.1: new isFinite() throw TypeError. Actual: ' + (new isFinite()));
} catch (e) {
  if ((e instanceof TypeError) !== true) {
    $ERROR('#1.2: new isFinite() throw TypeError. Actual: ' + (e));
  }
}
