// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.9.5.19_A3_T1;
 * @section: 15.9.5.19;
 * @assertion: The Date.prototype.getUTCHours property "length" has { ReadOnly, DontDelete, DontEnum } attributes;
 * @description: Checking ReadOnly attribute;
 */

x = Date.prototype.getUTCHours.length;
Date.prototype.getUTCHours.length = 1;
if (Date.prototype.getUTCHours.length !== x) {
  $ERROR('#1: The Date.prototype.getUTCHours.length has the attribute ReadOnly');
}

