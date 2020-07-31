// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.9.5.31_A1_T1;
 * @section: 15.9.5.31;
 * @assertion: The Date.prototype property "setUTCSeconds" has { DontEnum } attributes;
 * @description: Checking absence of ReadOnly attribute;
 */

x = Date.prototype.setUTCSeconds;
if(x === 1)
  Date.prototype.setUTCSeconds = 2;
else
  Date.prototype.setUTCSeconds = 1;
if (Date.prototype.setUTCSeconds === x) {
  $ERROR('#1: The Date.prototype.setUTCSeconds has not the attribute ReadOnly');
}

