// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.9.5.12_A1_T1;
 * @section: 15.9.5.12;
 * @assertion: The Date.prototype property "getMonth" has { DontEnum } attributes;
 * @description: Checking absence of ReadOnly attribute;
 */

x = Date.prototype.getMonth;
if(x === 1)
  Date.prototype.getMonth = 2;
else
  Date.prototype.getMonth = 1;
if (Date.prototype.getMonth === x) {
  $ERROR('#1: The Date.prototype.getMonth has not the attribute ReadOnly');
}

