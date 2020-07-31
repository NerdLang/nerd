// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.9.5.7_A1_T1;
 * @section: 15.9.5.7;
 * @assertion: The Date.prototype property "toLocaleTimeString" has { DontEnum } attributes;
 * @description: Checking absence of ReadOnly attribute;
 */

x = Date.prototype.toLocaleTimeString;
if(x === 1)
  Date.prototype.toLocaleTimeString = 2;
else
  Date.prototype.toLocaleTimeString = 1;
if (Date.prototype.toLocaleTimeString === x) {
  $ERROR('#1: The Date.prototype.toLocaleTimeString has not the attribute ReadOnly');
}

