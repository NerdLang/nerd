// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.9.5.33_A3_T1;
 * @section: 15.9.5.33;
 * @assertion: The Date.prototype.setUTCMinutes property "length" has { ReadOnly, DontDelete, DontEnum } attributes;
 * @description: Checking ReadOnly attribute;
 */

x = Date.prototype.setUTCMinutes.length;
Date.prototype.setUTCMinutes.length = 1;
if (Date.prototype.setUTCMinutes.length !== x) {
  $ERROR('#1: The Date.prototype.setUTCMinutes.length has the attribute ReadOnly');
}

