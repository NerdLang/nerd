// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.9.5.24_A3_T1;
 * @section: 15.9.5.24;
 * @assertion: The Date.prototype.getMilliseconds property "length" has { ReadOnly, DontDelete, DontEnum } attributes;
 * @description: Checking ReadOnly attribute;
 */

x = Date.prototype.getMilliseconds.length;
Date.prototype.getMilliseconds.length = 1;
if (Date.prototype.getMilliseconds.length !== x) {
  $ERROR('#1: The Date.prototype.getMilliseconds.length has the attribute ReadOnly');
}

