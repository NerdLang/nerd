// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.9.5.13_A1_T3;
 * @section: 15.9.5.13;
 * @assertion: The Date.prototype property "getUTCMonth" has { DontEnum } attributes;
 * @description: Checking DontEnum attribute;
 */

if (Date.prototype.propertyIsEnumerable('getUTCMonth')) {
  $ERROR('#1: The Date.prototype.getUTCMonth property has the attribute DontEnum');
}

for(x in Date.prototype) {
  if(x === "getUTCMonth") {
    $ERROR('#2: The Date.prototype.getUTCMonth has the attribute DontEnum');
  }
}

