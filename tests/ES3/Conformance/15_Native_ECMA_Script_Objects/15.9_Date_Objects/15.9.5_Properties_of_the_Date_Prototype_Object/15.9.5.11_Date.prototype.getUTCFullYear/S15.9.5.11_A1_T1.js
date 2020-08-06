// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.9.5.11_A1_T1;
 * @section: 15.9.5.11;
 * @assertion: The Date.prototype property "getUTCFullYear" has { DontEnum } attributes;
 * @description: Checking absence of ReadOnly attribute;
 */

x = Date.prototype.getUTCFullYear;
if(x === 1)
  Date.prototype.getUTCFullYear = 2;
else
  Date.prototype.getUTCFullYear = 1;
if (Date.prototype.getUTCFullYear === x) {
  $ERROR('#1: The Date.prototype.getUTCFullYear has not the attribute ReadOnly');
}

