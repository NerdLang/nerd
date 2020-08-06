// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.9.5.5_A1_T1;
 * @section: 15.9.5.5;
 * @assertion: The Date.prototype property "toLocaleString" has { DontEnum } attributes;
 * @description: Checking absence of ReadOnly attribute;
 */

x = Date.prototype.toLocaleString;
if(x === 1)
  Date.prototype.toLocaleString = 2;
else
  Date.prototype.toLocaleString = 1;
if (Date.prototype.toLocaleString === x) {
  $ERROR('#1: The Date.prototype.toLocaleString has not the attribute ReadOnly');
}

