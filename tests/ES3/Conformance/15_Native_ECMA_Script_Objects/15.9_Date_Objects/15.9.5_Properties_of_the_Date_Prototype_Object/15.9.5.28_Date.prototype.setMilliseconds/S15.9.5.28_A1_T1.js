// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.9.5.28_A1_T1;
 * @section: 15.9.5.28;
 * @assertion: The Date.prototype property "setMilliseconds" has { DontEnum } attributes;
 * @description: Checking absence of ReadOnly attribute;
 */

x = Date.prototype.setMilliseconds;
if(x === 1)
  Date.prototype.setMilliseconds = 2;
else
  Date.prototype.setMilliseconds = 1;
if (Date.prototype.setMilliseconds === x) {
  $ERROR('#1: The Date.prototype.setMilliseconds has not the attribute ReadOnly');
}

