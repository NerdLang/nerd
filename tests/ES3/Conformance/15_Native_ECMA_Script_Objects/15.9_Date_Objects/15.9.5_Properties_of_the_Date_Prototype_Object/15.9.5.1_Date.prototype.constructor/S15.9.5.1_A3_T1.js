// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.9.5.1_A3_T1;
 * @section: 15.9.5.1;
 * @assertion: The Date.prototype.constructor property "length" has { ReadOnly, DontDelete, DontEnum } attributes;
 * @description: Checking ReadOnly attribute;
 */

x = Date.prototype.constructor.length;
Date.prototype.constructor.length = 1;
if (Date.prototype.constructor.length !== x) {
  $ERROR('#1: The Date.prototype.constructor.length has the attribute ReadOnly');
}

