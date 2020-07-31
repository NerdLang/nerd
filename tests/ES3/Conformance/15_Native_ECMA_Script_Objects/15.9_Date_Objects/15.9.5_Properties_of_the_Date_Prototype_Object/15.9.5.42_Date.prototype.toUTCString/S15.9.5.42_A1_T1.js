// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.9.5.42_A1_T1;
 * @section: 15.9.5.42;
 * @assertion: The Date.prototype property "toUTCString" has { DontEnum } attributes;
 * @description: Checking absence of ReadOnly attribute;
 */

x = Date.prototype.toUTCString;
if(x === 1)
  Date.prototype.toUTCString = 2;
else
  Date.prototype.toUTCString = 1;
if (Date.prototype.toUTCString === x) {
  $ERROR('#1: The Date.prototype.toUTCString has not the attribute ReadOnly');
}

