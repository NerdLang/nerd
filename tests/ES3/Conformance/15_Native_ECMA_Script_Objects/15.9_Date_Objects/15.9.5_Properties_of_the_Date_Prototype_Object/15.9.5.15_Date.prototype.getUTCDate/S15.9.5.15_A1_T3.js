// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.9.5.15_A1_T3;
 * @section: 15.9.5.15;
 * @assertion: The Date.prototype property "getUTCDate" has { DontEnum } attributes;
 * @description: Checking DontEnum attribute;
 */

if (Date.prototype.propertyIsEnumerable('getUTCDate')) {
  $ERROR('#1: The Date.prototype.getUTCDate property has the attribute DontEnum');
}

for(x in Date.prototype) {
  if(x === "getUTCDate") {
    $ERROR('#2: The Date.prototype.getUTCDate has the attribute DontEnum');
  }
}

