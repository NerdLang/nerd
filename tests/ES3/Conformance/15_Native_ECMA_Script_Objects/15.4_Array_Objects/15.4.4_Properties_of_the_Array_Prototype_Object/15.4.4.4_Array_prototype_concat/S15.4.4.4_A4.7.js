// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.4.4.4_A4.7;
* @section: 15.4.4.4, 11.2.2;
* @assertion: The concat property of Array can't be used as constructor;
* @description: If property does not implement the internal [[Construct]] method, throw a TypeError exception;
*/

//CHECK#1

try {
  new Array.prototype.concat();
  $ERROR('#1.1: new Array.prototype.concat() throw TypeError. Actual: ' + (new Array.prototype.concat()));
} catch (e) {
  if ((e instanceof TypeError) !== true) {
    $ERROR('#1.2: new Array.prototype.concat() throw TypeError. Actual: ' + (e));
  }
}
