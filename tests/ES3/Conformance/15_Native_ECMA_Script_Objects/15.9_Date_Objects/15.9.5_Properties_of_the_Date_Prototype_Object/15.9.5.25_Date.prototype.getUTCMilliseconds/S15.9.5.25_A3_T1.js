// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.9.5.25_A3_T1;
 * @section: 15.9.5.25;
 * @assertion: The Date.prototype.getUTCMilliseconds property "length" has { ReadOnly, DontDelete, DontEnum } attributes;
 * @description: Checking ReadOnly attribute;
 */

x = Date.prototype.getUTCMilliseconds.length;
Date.prototype.getUTCMilliseconds.length = 1;
if (Date.prototype.getUTCMilliseconds.length !== x) {
  $ERROR('#1: The Date.prototype.getUTCMilliseconds.length has the attribute ReadOnly');
}

